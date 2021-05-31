//
// Created by bili on 2021/5/30.
//

#ifndef BASE_GA_GA_DEPS_H
#define BASE_GA_GA_DEPS_H
#include <stdexcept>
#include <vector>
#define GENOME_SIZE 1000
#define POPULATION_SIZE 100
// Definition of a target to be optimized

template <typename t_type>
struct Gene{
    t_type _gene_item;
    Gene(){throw std::invalid_argument("There shall be target");}
    Gene(t_type input){_gene_item=input;}
};
template <typename t_type,typename g_type>
struct Target:Gene<t_type>{
    std::vector<t_type> _target;
    Target(){throw std::invalid_argument("There shall be a gene");}
    Target(std::vector<g_type> input){
        if(std::is_same<t_type,g_type>::value) {
            std::copy(input,_target);
        }
        else {
            throw std::invalid_argument("The type of initial gene and the target shall be the same");
        }
    }
};


#endif //BASE_GA_GA_DEPS_H
