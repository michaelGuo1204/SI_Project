# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/bili/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/bili/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda

# Include any dependencies generated for this target.
include CMakeFiles/vector_addition.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vector_addition.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vector_addition.dir/flags.make

CMakeFiles/vector_addition.dir/vector_addition.cu.o: CMakeFiles/vector_addition.dir/flags.make
CMakeFiles/vector_addition.dir/vector_addition.cu.o: ../vector_addition.cu
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CUDA object CMakeFiles/vector_addition.dir/vector_addition.cu.o"
	/usr/local/cuda-10.2/bin/nvcc -forward-unknown-to-host-compiler $(CUDA_DEFINES) $(CUDA_INCLUDES) $(CUDA_FLAGS) -x cu -dc /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/vector_addition.cu -o CMakeFiles/vector_addition.dir/vector_addition.cu.o

CMakeFiles/vector_addition.dir/vector_addition.cu.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CUDA source to CMakeFiles/vector_addition.dir/vector_addition.cu.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CUDA_CREATE_PREPROCESSED_SOURCE

CMakeFiles/vector_addition.dir/vector_addition.cu.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CUDA source to assembly CMakeFiles/vector_addition.dir/vector_addition.cu.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CUDA_CREATE_ASSEMBLY_SOURCE

# Object files for target vector_addition
vector_addition_OBJECTS = \
"CMakeFiles/vector_addition.dir/vector_addition.cu.o"

# External object files for target vector_addition
vector_addition_EXTERNAL_OBJECTS =

CMakeFiles/vector_addition.dir/cmake_device_link.o: CMakeFiles/vector_addition.dir/vector_addition.cu.o
CMakeFiles/vector_addition.dir/cmake_device_link.o: CMakeFiles/vector_addition.dir/build.make
CMakeFiles/vector_addition.dir/cmake_device_link.o: CMakeFiles/vector_addition.dir/dlink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CUDA device code CMakeFiles/vector_addition.dir/cmake_device_link.o"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vector_addition.dir/dlink.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vector_addition.dir/build: CMakeFiles/vector_addition.dir/cmake_device_link.o

.PHONY : CMakeFiles/vector_addition.dir/build

# Object files for target vector_addition
vector_addition_OBJECTS = \
"CMakeFiles/vector_addition.dir/vector_addition.cu.o"

# External object files for target vector_addition
vector_addition_EXTERNAL_OBJECTS =

vector_addition: CMakeFiles/vector_addition.dir/vector_addition.cu.o
vector_addition: CMakeFiles/vector_addition.dir/build.make
vector_addition: CMakeFiles/vector_addition.dir/cmake_device_link.o
vector_addition: CMakeFiles/vector_addition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CUDA executable vector_addition"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vector_addition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vector_addition.dir/build: vector_addition

.PHONY : CMakeFiles/vector_addition.dir/build

CMakeFiles/vector_addition.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vector_addition.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vector_addition.dir/clean

CMakeFiles/vector_addition.dir/depend:
	cd /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/02_vector_addition/cmake-build-release-cuda/CMakeFiles/vector_addition.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vector_addition.dir/depend

