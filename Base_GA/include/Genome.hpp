//
// Created by bili on 2021/5/30.
//

#ifndef BASE_GA_GENOME_HPP
#define BASE_GA_GENOME_HPP
#include <iostream>
#include <random>
#include "GA_Deps.h"
template <typename t_type>
struct Genome:Gene<t_type>{
    std::vector<Gene<t_type>> _genome;

    Genome(){
        _genome.reserve(GENOME_SIZE);
    }
    Genome(Gene<t_type> input){
        if(_genome.size()<GENOME_SIZE)_genome.push_back(input);
    }
    Genome(std::vector<Gene<t_type>> input){
        if(input.size()==GENOME_SIZE)std::copy(input,_genome);
        else{
            throw std::invalid_argument("The size of genome is not valid!");
        }
    }

    template<typename T>
    void Mutation();

    template<> void Mutation<int>(){
        auto item=select_randomly(this->_genome.begin(),this->_genome);
        std::vector<int> selector;
        for(int i = 0;i<10;i++){
            selector.push_back(i);
        }
        item=*select_randomly(selector.begin(),selector.end());
    }

    template<> void Mutation<char>(){
        auto item=select_randomly(this->_genome.begin(),this->_genome);
        std::vector<int> selector;
        for(int i = 0;i<26;i++){
            selector.push_back(i);
        }
        item=((char)64+*select_randomly(selector.begin(),selector.end()));
    }

    template<typename Iter, typename RandomGenerator>
    inline Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(g));
        return start;
    }

    template<typename Iter>
    inline Iter select_randomly(Iter start, Iter end) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return select_randomly(start, end, gen);
    }
};
#endif //BASE_GA_GENOME_HPP
