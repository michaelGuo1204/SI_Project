#include "cuda.h"
#include "curand_kernel.h"
#include "utils.h"
#include "knapsack.h"

extern "C"
{
    __global__
    void initChromosomes(char* chromosomes, int length, curandState* states)
    {
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        curandState localState;
        char localPart;
        curand_init(SEED, id, 0, &localState);
        for(int i = 0; i < length; ++i)
        {
            if(curand_uniform(&localState) < INIT_RATE)
                localPart ^= (1<<(i % BYTE_SIZE));
            if(i % BYTE_SIZE == BYTE_SIZE-1)
                chromosomes[(id * length / BYTE_SIZE) + (i / BYTE_SIZE)] = localPart;
        }
        states[id] = localState;
    }

    __global__
    void computeFitness(char* chromosomes, int length, int* values, int* weights, int knapsackSize, int* fitness)
    {
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        char localPart;
        int w = 0, v = 0;
        for(int i = 0; i < length; ++i)
        {
            if(i % BYTE_SIZE == 0)
                localPart = chromosomes[(id * length / BYTE_SIZE) + (i / BYTE_SIZE)];
            if(localPart & (1<< (i%BYTE_SIZE)))
            {
                w += weights[i];
                v += values[i];
            }
        }
        if(w > knapsackSize)
            v = 0;
        fitness[id] = v;
    }

    __global__
    void prefixSumInBlocks(int* array, int* sumsInBlocks)
    {
        __shared__ int part[BLOCK_WIDTH];
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        part[threadIdx.x] = array[id];
        
        __syncthreads();
        for(int len = 1; len < blockDim.x; len *= 2)
        {
            int tmp = 0;
            if (threadIdx.x >= len)
                tmp = part[threadIdx.x - len];
            __syncthreads();
            part[threadIdx.x] += tmp;
            __syncthreads();
        }

        array[id] = part[threadIdx.x];
        if(threadIdx.x == blockDim.x-1)
            sumsInBlocks[blockIdx.x] = part[threadIdx.x];
    }

    __global__
    void propagatePrefixSums(int* array, int* sumsInBlocks)
    {
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        if(blockIdx.x > 0)
        {
            int localSum = sumsInBlocks[blockIdx.x-1];
            array[id] += localSum;
        }
    }

    __global__
    void selectChromosomes(char* currentPop, char* nextPop, int length, int* fitness, curandState* states)
    {
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        int rnd = int(curand_uniform(&states[id]) * (fitness[POPULATION_SIZE-1] + 0.999999));
        int beg = 0, end = POPULATION_SIZE-1, mid;
        while(beg < end)
        {
            mid = (beg + end) / 2;
            if(fitness[mid] < rnd)
                beg = mid+1;
            else
                end = mid;
        }
        __syncthreads();

        for(int i = 0; i < length / BYTE_SIZE; ++i)
            nextPop[(id * length / BYTE_SIZE) + i] = currentPop[(beg * length / BYTE_SIZE) + i];
    }

    __global__
    void crossOverChromosomes(char* chromosomes, int length, curandState* states)
    {
        int id = 2 * (blockIdx.x * blockDim.x + threadIdx.x);
        int place = int(curand_uniform(&states[id]) * (length + 0.999999));
        if(place == length || curand_uniform(&states[id]) > CROSSING_OVER_RATE)
            return;

        char tmp, tmp2, mask;
        mask = (1 << (place % BYTE_SIZE)) - 1;
        tmp = chromosomes[(id * length / BYTE_SIZE) + place / BYTE_SIZE];
        tmp2 = chromosomes[((id+1) * length / BYTE_SIZE) + place / BYTE_SIZE];
        chromosomes[(id * length / BYTE_SIZE) + place / BYTE_SIZE] = (tmp & mask) | (tmp2 & ~mask);
        chromosomes[((id+1) * length / BYTE_SIZE) + place / BYTE_SIZE] = (tmp2 & mask) | (tmp & ~mask);;

        for(int i = place / BYTE_SIZE + 1; i < length / BYTE_SIZE; ++i)
        {
            tmp = chromosomes[(id * length / BYTE_SIZE) + i];
            chromosomes[(id * length / BYTE_SIZE) + i] = chromosomes[((id+1) * length / BYTE_SIZE) + i];
            chromosomes[((id+1) * length / BYTE_SIZE) + i] = tmp;
        }
    }

    __global__
    void mutateChromosomes(char* chromosomes, int length, curandState* states)
    {
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        curandState localState = states[id];
        char localPart;
        for(int i = 0; i < length; ++i)
        {
            if(i % BYTE_SIZE == 0)
                localPart = chromosomes[(id * length / BYTE_SIZE) + (i / BYTE_SIZE)];
            if(curand_uniform(&localState) < MUTATION_RATE)
                localPart ^= (1<<(i % BYTE_SIZE));
            if(i % BYTE_SIZE == BYTE_SIZE-1)
                chromosomes[(id * length / BYTE_SIZE) + (i / BYTE_SIZE)] = localPart;
        }
        states[id] = localState;
    }

    __global__
    void findBestChromosome(char* chromosomes, int* fitness, int* results, int* where)
    {
        __shared__ int maxes[BLOCK_WIDTH];
        __shared__ int indices[BLOCK_WIDTH];
        int id = blockIdx.x * blockDim.x + threadIdx.x;
        maxes[threadIdx.x] = fitness[id];
        indices[threadIdx.x] = id;
        
        __syncthreads();
        for(int len = 1; len < blockDim.x; len *= 2)
        {
            int otherValue = 0, otherIndex;
            if (threadIdx.x % (2*len) == 0 && threadIdx.x + len < blockDim.x)
            {
                otherValue = maxes[threadIdx.x + len];
                otherIndex = indices[threadIdx.x + len];
            }
            __syncthreads();
            if(otherValue > maxes[threadIdx.x])
            {
                maxes[threadIdx.x] = otherValue;
                indices[threadIdx.x] = otherIndex;
            }
            __syncthreads();
        }

        if(threadIdx.x == 0)
        {
            results[blockIdx.x] = maxes[0];
            where[blockIdx.x] = indices[0];
        }

    }
}
