
#include "multiobjective_optimization.hpp"
#include <cmath>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //float male_Sf = (float)*argv[1]-'0';
    float optimized_arguments[2];
    float optimized_fitness[2];
    Parameter parameter={
        .male_Sf=atof(argv[1]),
        .male_k=atof(argv[2]),
        .female_Sf=atof(argv[3]),
        .female_k=atof(argv[4])
    };
    optimize(1000000, optimized_arguments,parameter, optimized_fitness, {
        func(0, (args[0])*(args[0]-args[1]+male_Sf+male_k*args[0]))//args[0] * (args[0] - args[1] - 2));+male_Sf-male_k*args[0]
        func(1, (args[1])*(args[1]-args[0]+female_Sf+female_k*args[0]))//args[1] * (args[1] - args[0] - 8));+female_Sf-female_k*args[1]
    });
    
    //printf("(");
    for (float *x = optimized_arguments; x < optimized_arguments + countof(optimized_arguments); x++) {
        //if (x != optimized_arguments) printf(",");
        printf("%f,", *x);
    }
    //printf(") => {");
    for (float *y = optimized_fitness; y < optimized_fitness + countof(optimized_fitness); y++) {
        if (y != optimized_fitness) printf(",");
        printf("%f", *y);
    }
    //printf("\n");
    
    return 0;
}
