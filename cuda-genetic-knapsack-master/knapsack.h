#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <algorithm>

#include "cuda.h"
#include "curand_kernel.h"

const int GENERATIONS_NUMBER = 300;
const int POPULATION_SIZE = 512;
const double INIT_RATE = 0.001;
const double MUTATION_RATE = 0.001;
const double CROSSING_OVER_RATE = 0.95;
const int SEED = 8201;

class KnapsackGA {
	CUdevice cuDevice;
    CUcontext cuContext;
    CUmodule cuModule;
    CUfunction cuInitChromosomesFunc;
    CUfunction cuComputeFitnessFunc;
    CUfunction cuPrefixSumInBlocksFunc;
    CUfunction cuPropagatePrefixSumsFunc;
    CUfunction cuSelectChromosomesFunc;
    CUfunction cuCrossOverChromosomesFunc;
    CUfunction cuMutateChromosomesFunc;
    CUfunction cuFindBestChromosomeFunc;
    
    int objectsNumber;
    int knapsackSize;
    std::vector<int> values;
    std::vector<int> weights;

    int* sumsInBlocks;
    int* maxes;
    int* indices;
    char* chromosome;
    CUdeviceptr d_weights;
    CUdeviceptr d_values;
    CUdeviceptr d_sumsInBlocks;
    CUdeviceptr d_pop1;
    CUdeviceptr d_pop2;
    CUdeviceptr d_randStates;
    CUdeviceptr d_fitness;
    CUdeviceptr *d_currentPopulation;
    CUdeviceptr *d_nextPopulation;
    CUdeviceptr d_maxes;
    CUdeviceptr d_indices;

    void initCuda();
    void allocateMemory();
    void initChromosomes();
    void computeFitness();
    std::pair<int, std::vector<bool> > computeFitness(int idx);
    void selectChromosomes();
    void crossOverChromosomes();
    void mutateChromosomes();
    void cloneElite(int idx);
    int bestChromosomeIndex();


public:
	KnapsackGA(const std::vector<int>& values, const std::vector<int>& weights, int knapsackSize);
	std::pair<int, std::vector<bool> > BestValue();
	~KnapsackGA();
};

#endif //KNAPSACK_H
