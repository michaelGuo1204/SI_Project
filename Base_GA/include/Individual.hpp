//
// Created by bili on 2021/5/30.
//

#ifndef BASE_GA_INDIVIDUAL_HPP
#define BASE_GA_INDIVIDUAL_HPP
#include "Genome.hpp"
template <typename t_type>
class Individual{
private:
    Genome<t_type> _individual_genome;
    double callFitness();
public:
    double fitness;
    Individual(Genome<t_type> input){
        _individual_genome=input;
    }
    Individual Mate(Individual<t_type> partner){
        Genome<t_type> _child_genome;
        for(int i =0 ;i<GENOME_SIZE;i++){

        }

    }

};

#endif //BASE_GA_INDIVIDUAL_HPP
