#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "knapsack.h"

int main()
{
    int objectsNumber;
    int knapsackSize;
    scanf("%d%d", &objectsNumber, &knapsackSize);
    std::vector<int> values, weights;
    values.reserve(objectsNumber);
    weights.reserve(objectsNumber);
    
    while(objectsNumber--)
    {
        int w, v;
        scanf("%d%d", &w, &v);
        values.push_back(v);
        weights.push_back(w);
    }
    KnapsackGA knapsack(values, weights, knapsackSize);
    printf("%d\n", knapsack.BestValue().first);

    return 0;
}