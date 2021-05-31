#include "utils.h"

const char *cuda_error_string(CUresult result) 
{ 
	switch(result) { 
	case CUDA_SUCCESS: return "No errors"; 
	case CUDA_ERROR_INVALID_VALUE: return "Invalid value"; 
	case CUDA_ERROR_OUT_OF_MEMORY: return "Out of memory"; 
	case CUDA_ERROR_NOT_INITIALIZED: return "Driver not initialized"; 
	case CUDA_ERROR_DEINITIALIZED: return "Driver deinitialized"; 

	case CUDA_ERROR_NO_DEVICE: return "No CUDA-capable device available"; 
	case CUDA_ERROR_INVALID_DEVICE: return "Invalid device"; 

	case CUDA_ERROR_INVALID_IMAGE: return "Invalid kernel image"; 
	case CUDA_ERROR_INVALID_CONTEXT: return "Invalid context"; 
	case CUDA_ERROR_CONTEXT_ALREADY_CURRENT: return "Context already current"; 
	case CUDA_ERROR_MAP_FAILED: return "Map failed"; 
	case CUDA_ERROR_UNMAP_FAILED: return "Unmap failed"; 
	case CUDA_ERROR_ARRAY_IS_MAPPED: return "Array is mapped"; 
	case CUDA_ERROR_ALREADY_MAPPED: return "Already mapped"; 
	case CUDA_ERROR_NO_BINARY_FOR_GPU: return "No binary for GPU"; 
	case CUDA_ERROR_ALREADY_ACQUIRED: return "Already acquired"; 
	case CUDA_ERROR_NOT_MAPPED: return "Not mapped"; 
	case CUDA_ERROR_NOT_MAPPED_AS_ARRAY: return "Mapped resource not available for access as an array"; 
	case CUDA_ERROR_NOT_MAPPED_AS_POINTER: return "Mapped resource not available for access as a pointer"; 
	case CUDA_ERROR_ECC_UNCORRECTABLE: return "Uncorrectable ECC error detected"; 
	case CUDA_ERROR_UNSUPPORTED_LIMIT: return "CUlimit not supported by device";    

	case CUDA_ERROR_INVALID_SOURCE: return "Invalid source"; 
	case CUDA_ERROR_FILE_NOT_FOUND: return "File not found"; 
	case CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND: return "Link to a shared object failed to resolve"; 
	case CUDA_ERROR_SHARED_OBJECT_INIT_FAILED: return "Shared object initialization failed"; 

	case CUDA_ERROR_INVALID_HANDLE: return "Invalid handle"; 

	case CUDA_ERROR_NOT_FOUND: return "Not found"; 

	case CUDA_ERROR_NOT_READY: return "CUDA not ready"; 

	case CUDA_ERROR_LAUNCH_FAILED: return "Launch failed"; 
	case CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES: return "Launch exceeded resources"; 
	case CUDA_ERROR_LAUNCH_TIMEOUT: return "Launch exceeded timeout"; 
	case CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING: return "Launch with incompatible texturing"; 

	case CUDA_ERROR_UNKNOWN: return "Unknown error"; 

	default: return "Unknown CUDA error value"; 
	} 
}

bool isPowerOfTwo(unsigned int x)
{
	return ((x != 0) && !(x & (x - 1)));
}