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
CMAKE_SOURCE_DIR = /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda

# Include any dependencies generated for this target.
include CMakeFiles/hello_world.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hello_world.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hello_world.dir/flags.make

CMakeFiles/hello_world.dir/hello_world.cu.o: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/hello_world.cu.o: ../hello_world.cu
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CUDA object CMakeFiles/hello_world.dir/hello_world.cu.o"
	/usr/local/cuda-10.2/bin/nvcc -forward-unknown-to-host-compiler $(CUDA_DEFINES) $(CUDA_INCLUDES) $(CUDA_FLAGS) -x cu -dc /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/hello_world.cu -o CMakeFiles/hello_world.dir/hello_world.cu.o

CMakeFiles/hello_world.dir/hello_world.cu.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CUDA source to CMakeFiles/hello_world.dir/hello_world.cu.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CUDA_CREATE_PREPROCESSED_SOURCE

CMakeFiles/hello_world.dir/hello_world.cu.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CUDA source to assembly CMakeFiles/hello_world.dir/hello_world.cu.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CUDA_CREATE_ASSEMBLY_SOURCE

# Object files for target hello_world
hello_world_OBJECTS = \
"CMakeFiles/hello_world.dir/hello_world.cu.o"

# External object files for target hello_world
hello_world_EXTERNAL_OBJECTS =

CMakeFiles/hello_world.dir/cmake_device_link.o: CMakeFiles/hello_world.dir/hello_world.cu.o
CMakeFiles/hello_world.dir/cmake_device_link.o: CMakeFiles/hello_world.dir/build.make
CMakeFiles/hello_world.dir/cmake_device_link.o: CMakeFiles/hello_world.dir/dlink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CUDA device code CMakeFiles/hello_world.dir/cmake_device_link.o"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello_world.dir/dlink.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hello_world.dir/build: CMakeFiles/hello_world.dir/cmake_device_link.o

.PHONY : CMakeFiles/hello_world.dir/build

# Object files for target hello_world
hello_world_OBJECTS = \
"CMakeFiles/hello_world.dir/hello_world.cu.o"

# External object files for target hello_world
hello_world_EXTERNAL_OBJECTS =

hello_world: CMakeFiles/hello_world.dir/hello_world.cu.o
hello_world: CMakeFiles/hello_world.dir/build.make
hello_world: CMakeFiles/hello_world.dir/cmake_device_link.o
hello_world: CMakeFiles/hello_world.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CUDA executable hello_world"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello_world.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hello_world.dir/build: hello_world

.PHONY : CMakeFiles/hello_world.dir/build

CMakeFiles/hello_world.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hello_world.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hello_world.dir/clean

CMakeFiles/hello_world.dir/depend:
	cd /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda /home/bili/Lernen/Essay_SI/CUDA_Practice/Chapter01/01_cuda_introduction/01_hello_world/cmake-build-debug-cuda/CMakeFiles/hello_world.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hello_world.dir/depend

