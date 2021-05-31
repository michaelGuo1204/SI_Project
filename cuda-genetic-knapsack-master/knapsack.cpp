#include <cstdio>
#include <algorithm>
#include <vector>

#include "knapsack.h"
#include "cuda.h"
#include "curand_kernel.h"
#include "utils.h"

KnapsackGA::KnapsackGA(const std::vector<int>& values, const std::vector<int>& weights, int knapsackSize)
    : values(values), weights(weights), knapsackSize(knapsackSize)
{
    while(this->values.size() < BYTE_SIZE || !isPowerOfTwo(this->values.size()))
    {
        this->values.push_back(0);
        this->weights.push_back(knapsackSize+1);
    }
    objectsNumber = this->values.size();

    initCuda();
    allocateMemory();
}

void KnapsackGA::initCuda()
{
    CU_CALL(cuInit(0));
    CU_CALL(cuDeviceGet(&cuDevice, 0));
    CU_CALL(cuCtxCreate(&cuContext, 0, cuDevice));
    CU_CALL(cuModuleLoad(&cuModule, "knapsack.ptx"));
    CU_CALL(cuModuleGetFunction(&cuInitChromosomesFunc, cuModule, "initChromosomes"));
    CU_CALL(cuModuleGetFunction(&cuComputeFitnessFunc, cuModule, "computeFitness"));
    CU_CALL(cuModuleGetFunction(&cuPrefixSumInBlocksFunc, cuModule, "prefixSumInBlocks"));
    CU_CALL(cuModuleGetFunction(&cuPropagatePrefixSumsFunc, cuModule, "propagatePrefixSums"));
    CU_CALL(cuModuleGetFunction(&cuSelectChromosomesFunc, cuModule, "selectChromosomes"));
    CU_CALL(cuModuleGetFunction(&cuCrossOverChromosomesFunc, cuModule, "crossOverChromosomes"));
    CU_CALL(cuModuleGetFunction(&cuMutateChromosomesFunc, cuModule, "mutateChromosomes"));
    CU_CALL(cuModuleGetFunction(&cuFindBestChromosomeFunc, cuModule, "findBestChromosome"));
}

void KnapsackGA::allocateMemory()
{
    CU_CALL(cuMemAlloc(&d_values, objectsNumber * sizeof(int)));
    CU_CALL(cuMemcpyHtoD(d_values, &values[0], objectsNumber * sizeof(int)));
    CU_CALL(cuMemAlloc(&d_weights, objectsNumber * sizeof(int)));
    CU_CALL(cuMemcpyHtoD(d_weights, &weights[0], objectsNumber * sizeof(int)));
    CU_CALL(cuMemAlloc(&d_sumsInBlocks, POPULATION_SIZE/BLOCK_WIDTH * sizeof(int)));
    CU_CALL(cuMemAllocHost((void**)&sumsInBlocks, POPULATION_SIZE/BLOCK_WIDTH * sizeof(int)));
    CU_CALL(cuMemAlloc(&d_pop1, objectsNumber * POPULATION_SIZE / BYTE_SIZE));
    CU_CALL(cuMemAlloc(&d_pop2, objectsNumber * POPULATION_SIZE / BYTE_SIZE));
    CU_CALL(cuMemAlloc(&d_randStates, POPULATION_SIZE / BYTE_SIZE * sizeof(curandState)));
    CU_CALL(cuMemAlloc(&d_fitness, POPULATION_SIZE * sizeof(int)));
    CU_CALL(cuMemAlloc(&d_maxes, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));
    CU_CALL(cuMemAlloc(&d_indices, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));
    CU_CALL(cuMemAllocHost((void**)&maxes, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));
    CU_CALL(cuMemAllocHost((void**)&indices, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));
    CU_CALL(cuMemAllocHost((void**)&chromosome, objectsNumber / BYTE_SIZE));
    
    d_currentPopulation = &d_pop1;
    d_nextPopulation = &d_pop2;
}

std::pair<int, std::vector<bool> > KnapsackGA::BestValue()
{
    initChromosomes();
    for(int i = 0; i < GENERATIONS_NUMBER; ++i)
    {
        computeFitness();
        int idx = bestChromosomeIndex();
        printf("Generation %d: %d\n", i, computeFitness(idx).first);
        selectChromosomes();
        crossOverChromosomes();
        mutateChromosomes();
        cloneElite(idx);
        std::swap(d_currentPopulation, d_nextPopulation);
    }

    computeFitness();
    int idx = bestChromosomeIndex();
    return computeFitness(idx);
}

void KnapsackGA::initChromosomes()
{
    void* args[] = {d_currentPopulation, &objectsNumber, &d_randStates};
    CU_CALL(cuLaunchKernel(cuInitChromosomesFunc, POPULATION_SIZE / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args, 0));
    CU_CALL(cuCtxSynchronize());
}

void KnapsackGA::computeFitness()
{
    void* args[] = {d_currentPopulation, &objectsNumber, &d_values, &d_weights, &knapsackSize, &d_fitness};
    CU_CALL(cuLaunchKernel(cuComputeFitnessFunc, POPULATION_SIZE / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args, 0));
    CU_CALL(cuCtxSynchronize());
}

std::pair<int, std::vector<bool> > KnapsackGA::computeFitness(int idx)
{
    CU_CALL(cuMemcpyDtoH(chromosome, (*d_currentPopulation) + idx * objectsNumber / BYTE_SIZE, objectsNumber / BYTE_SIZE));

    int value = 0, weight = 0;
    std::vector<bool> mask(objectsNumber, false);
    for(int i = 0; i < objectsNumber; ++i)
    {
        if(chromosome[(i / BYTE_SIZE)] & (1<< (i%BYTE_SIZE)))
        {
            value += values[i];
            mask[i] = true;
            weight += weights[i];
        }
        
    }
    if(weight > knapsackSize)
        return std::make_pair(0, std::vector<bool>(objectsNumber, false));
    return std::make_pair(value, mask);
}

void KnapsackGA::selectChromosomes()
{
    void* args[] = {&d_fitness, &d_sumsInBlocks};
    CU_CALL(cuLaunchKernel(cuPrefixSumInBlocksFunc, POPULATION_SIZE / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args, 0));
    CU_CALL(cuCtxSynchronize());

    CU_CALL(cuMemcpyDtoH(sumsInBlocks, d_sumsInBlocks, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));
    for(int i = 1; i < POPULATION_SIZE / BLOCK_WIDTH; ++i)
        sumsInBlocks[i] += sumsInBlocks[i-1];
    CU_CALL(cuMemcpyHtoD(d_sumsInBlocks, sumsInBlocks, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));
    
    void* args2[] = {&d_fitness, &d_sumsInBlocks};
    CU_CALL(cuLaunchKernel(cuPropagatePrefixSumsFunc, POPULATION_SIZE / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args2, 0));
    CU_CALL(cuCtxSynchronize());
    
    void* args3[] = {d_currentPopulation, d_nextPopulation, &objectsNumber, &d_fitness, &d_randStates};
    CU_CALL(cuLaunchKernel(cuSelectChromosomesFunc, POPULATION_SIZE / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args3, 0));
    CU_CALL(cuCtxSynchronize());
}

void KnapsackGA::crossOverChromosomes()
{
    void* args[] = {d_nextPopulation, &objectsNumber, &d_randStates};
    CU_CALL(cuLaunchKernel(cuCrossOverChromosomesFunc, POPULATION_SIZE / 2 / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args, 0));
    CU_CALL(cuCtxSynchronize());
}

void KnapsackGA::mutateChromosomes()
{
    void* args[] = {d_nextPopulation, &objectsNumber, &d_randStates};
    CU_CALL(cuLaunchKernel(cuMutateChromosomesFunc, POPULATION_SIZE / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args, 0));
    CU_CALL(cuCtxSynchronize());
}

void KnapsackGA::cloneElite(int idx)
{
    CU_CALL(cuMemcpyDtoD(*d_nextPopulation, (*d_currentPopulation) + idx * objectsNumber / BYTE_SIZE, objectsNumber / BYTE_SIZE));
}

int KnapsackGA::bestChromosomeIndex()
{
    void* args[] = {d_currentPopulation, &d_fitness, &d_maxes, &d_indices};
    CU_CALL(cuLaunchKernel(cuFindBestChromosomeFunc, POPULATION_SIZE / BLOCK_WIDTH, 1, 1, BLOCK_WIDTH, 1, 1,
        0, 0, args, 0));
    CU_CALL(cuCtxSynchronize());
    
    CU_CALL(cuMemcpyDtoH(maxes, d_maxes, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));
    CU_CALL(cuMemcpyDtoH(indices, d_indices, POPULATION_SIZE / BLOCK_WIDTH * sizeof(int)));

    int maxValue = maxes[0], maxIndex = indices[0];
    for(int i = 1; i < POPULATION_SIZE / BLOCK_WIDTH; ++i)
    {
        if(maxValue < maxes[i])
        {
            maxValue = maxes[i];
            maxIndex = indices[i];
        }
    }
    return maxIndex;
}

KnapsackGA::~KnapsackGA()
{
    CU_CALL(cuMemFreeHost(maxes));
    CU_CALL(cuMemFreeHost(indices));
    CU_CALL(cuMemFreeHost(sumsInBlocks));
    CU_CALL(cuMemFreeHost(chromosome));
    CU_CALL(cuCtxDestroy(cuContext));
}
