#ifndef CUDA_UTILS
#define CUDA_UTILS

#define BLOCK_WIDTH 64
#define BYTE_SIZE 8

#include "cuda.h"

bool isPowerOfTwo(unsigned int x);
const char *cuda_error_string(CUresult result);

#define CU_CALL(X)											\
	if((X) != CUDA_SUCCESS) {								\
		printf("cuda error (line %d): %s\n", __LINE__, #X);	\
		printf("%s\n", cuda_error_string(X));				\
		exit(1); 											\
	}

#endif //CUDA_UTILS