cmake_minimum_required(VERSION 3.16)
project(Base_GA)
set(CMAKE_CXX_STANDARD 17)
include_directories(
        ./include
)
add_executable(base_GA main.cpp include/Genome.hpp)
