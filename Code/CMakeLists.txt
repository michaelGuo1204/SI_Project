cmake_minimum_required(VERSION 3.16)
project(Simulate LANGUAGES CXX CUDA)
set(CMAKE_CXX_STANDARD 11)
find_package(CUDA  REQUIRED)
#set(CUDA_SEPARABLE_COMPILATION ON)
list(APPEND CMAKE_CUDA_FLAGS "--extended-lambda -gencode  arch=compute_60,code=sm_60")
include_directories(${CUDA_INCLUDE_DIRS})
link_directories(${CUDA_LIBRARY_DIRS})
set_source_files_properties(main.cpp PROPERTIES LANGUAGE CUDA)
cuda_add_executable(Simulate main.cpp OPTIONS -std=c++11)

TARGET_LINK_LIBRARIES(Simulate ${CUDA_LIBRARIES})

