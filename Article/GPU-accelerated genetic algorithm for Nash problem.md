# GPU-accelerated genetic algorithm for Nash problem

The mating problem discussed above can be evaluated and validated by generations of individuals, fortunately, this process fit the essence of genetic algorithm: generating alleles and select them by specific pressure. We hence come up with the idea to solve nash problem with the aid of genetic algorithm. We also noticed that the algorithm we choose to solve the problem Island-Model genetic algorithm(IMGA) can be parallelized to shorten the computation cost. Consequently, we are targeting at the implementation of parallelized IMGA on GPU to solve the Nash Problem.

## Nash Genetic Algorithms

Let $S={X,Y}$ denotes the potential solution of a non-cooperate optimization problem $f_1(X,Y)$ and $f_2(X,Y)$. We can set two populations for the player $A\&B$ of the game. The optimization object of different $f_i(X,Y)$ is carried out by different population. $X$ denotes the variables handled by player $A$ and will be optimized with $f_1(X,Y)$ in population $A$ . Similarly,  $Y$ denotes the variables handled by player $B$ and will be optimized with $f_2(X,Y)$ in population $B$ . Under such circumstances, $X$ will be optimized in population $A$ when $Y$ is fixed. At each generation $k$, the possible value is concluded by another player in generation $k-1$ which means that player $i$ will optimize $X_k$ using $Y_{k-1}$ from another player $\hat{i}$ . After the optimization process, two groups exchange the optimized value and enter the next generation.

```algorithm
\KwData{Variables to be optimized $X,Y$}
\KwResult{Variables optimized $X',Y'$}
\While{Result not converge}{
	Optimize f_1(X,\hat{Y}) in population A
	Optimize f_2(\hat{X},Y) in population B
	\elf{X,Y Not reach Nash Equilibrium}{
		Convert X to \hat{X}
		Convert Y to \hat{Y}
	}{
		return X',Y'
	}
}
```

## Island-Model Genetic algorithm

We have seen that the iteration or the population of generations limit the computation cost of genetic algorithm, however, if there is one single population, the algorithm also suffers from local-optimal, which means that the algorithm may get a non-stable solution of the system. Island-model genetic algorithm is hence arisen to solve these problems.  In IMGA, population is divided into smaller partitions and distributed to different "parts" to perform simultaneous random searches, and exchanging the individuals through a migration operator. The IMGA model is possible to explore different regions of the search space, so as to improve issues of premature convergence or convergence to local optimal solutions in the standard GA using a single large population.

```IMGA
\KwData{Initial population of n players and n islands}
\While{}{
	\foreach{island i}{
		\While{repeat}{
			Select the best indviduals for reproduction
			Use the cross-over operator
			Update the fitness of modified individuals
			Generate the new population for next generation
			\IF{Reach the limit of migration}{
			Migrate the m best individuals to another island j
			}
		}
	}
}
```

## Essential CUDA architecture 

Nowadays, modern GPUs have evolved into very powerful and flexible processors. Especially after CUDA (compute unified device architecture) platform were distributed, developing highly parallel GPU applications becomes much easier. To provide data parallelism, a multithreaded CUDA application is partitioned into blocks of threads that execute independently (and often concurrently) from each other. Each parallel invocation of kernel is referred to as a block. Each block have multiple threads. These block of threads can be scheduled on any of the available streaming multiprocessors (SM) and a global memory accessible by all SMs within a GPU. Each SM contains multiple cores which share a shared memory as well as one local to itself.

When a CUDA application on the host invokes a kernel grid, the blocks of the grid are enumerated and a global work distribution engine assign them to SM with available execution capacity. Threads of the same block always run on the same SM. Multiple thread blocks and multiple threads in a thread block can execute concurrently on one SM. As thread blocks terminate, new blocks are launched on the vacated multiprocessors.

Once a block of threads is assigned to a SM, the threads are divided into units called warps. A block is partitioned into warps with each warp contains threads of consecutive, increasing thread IDs with the first warp containing thread 0. The size of a warp is determined by the hardware implementation. A warp scheduler selects a warp that is ready to execute its next instruction. In Fermi architect, the warp scheduler schedule a warp of 32 threads. Each warp of threads runs the same instruction. In each warp, it runs the same instruction. When the threads in a warp is wait for the previous instruction to complete, the warp scheduler will select another warp to execute. Two warps from different blocks or different kernels can be executed concurrently. This architecture is also called single instruction multiple data (SIMD).  

Multiple cores and strong computing capacity make task cost on each core no longer a limit to the overall cost. Accessibility to data or in GPU "memory" just restrict the communication between threads , grids or even SMs due to the special local-share-global model. The speed of reaching local and global memory is much slower that reaching the shared memory for a thread. Memory allocation thus become much important in the designing of a CUDA program for better performance. In a nutshell, GPUs are now becoming the most suitable processor for implementing algorithms with simple and large amount of computations.

# Parallelize IMGA on GPU

The genetic algorithm framework is implemented using CUDA device lambdas so any arbitrary genetic algorithm can be encoded in the framework without having to write a separate kernel. The framework supports specification of `spawn`, `evaluate`, `mutate`, and `cross` functions to specify the algorithm. Each function takes in a `curandState_t` that has been seeded specifically for that thread so that randomized behavior is easily implemented. Note that we seed each thread with its thread id. It is sufficient to do this since we only care that each thread has independent random numbers, but we do not care if the program acts randomly between invocations. In the following subsections, we choose the main parts in the program to illustrate our soulutions.

## Overall structure

In our island model algorithm, there are 2 countries which just like 2 players in Nash genetic algorithm. Each country aimed at optimizing one specific criteria of the object equation system and has several islands to maintain the diversity of chromosome. There are three main hyperparameters that will change the structure: Numbers of the country(Fixed 2 in this project); Islands per country;  Population per island.  The total population of individuals is stored in global memory which is the largest in terms of size. For each block, a group of threads execute standard GA in parallel. Threads on each block are responsible for executing the procedures of IMGA including initialization, evaluation, crossover, mutation, replacement, and migration operators. Regarding the migration, communications are carried out through the global memory which stores global population, resulting in each island being able to communicate with each other according to our ring topology.

## Evaluation and Selection 

The evaluation and selection are the first step to treat the chromosome. In this part, we would give a fitness to each individual and choose the better solution on current evaluation. In general, there are two main selection methods which are tournament selection or roulette wheel selection. They both take the whole island into consideration. This might increase the converge rate but will cost much of time comparing data from different grid due to the limit of bandwidth.  Thus we take following algorithm:

```algorithm2e
\KwData{
	agm_count: The count of variables in the object functions\
	args: Arrays containing the variables to be solved\
	functions: Object functions
	parameter:Parameters that can be changed from commandline
	rand_state:Random number to choose chromsomes
	test_genome:Genome to be evaluatd
	fitness:Fitness of the test_genome 
	index: Index of island to specify the country
}
\KwInput{
	index,genome,randstate
}
\For{i in agm_count}{
	\eif{index=i}{
		args[i]=genome
	}{
		args[i]=opponent_genome
	}
}
result<- -1
result=functions(args)
\For{Select genome}{
	other_result=other_tread.data
	Syncthreads()
	\eif{result>other_result}{
		replace current with other
	}{
		replace other with current
	}
}
```

As shown above, the selection just compare the current fitness with binary reduction function which can be described as

```
\KwData{
	Dimension:The overall dimension of the block\
	ThreadIdx:The index of thread\
}
\For{bound=Dimension>>2;ThreadIdx<bound;bound>>=2}{
	*other=current+bound
}
```

Here we conduct a pointer to visit others. The selection array goes as the different half of the overall dimension until it replace with other genomes that have a smaller ThreadIdex. In the algorithm, shared memory is used to store the genome and fitness for individuals. Threads in one block carry out selections of individuals for next generation, respectively. With the fast-shared memory to communicate with each other, the system performance is improved.