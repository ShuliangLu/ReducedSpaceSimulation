# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /home/shuliang/app/clion-2019.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/shuliang/app/clion-2019.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shuliang/Documents/ReducedSpaceSimulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug

# Include any dependencies generated for this target.
include src/config/CMakeFiles/configuration.dir/depend.make

# Include the progress variables for this target.
include src/config/CMakeFiles/configuration.dir/progress.make

# Include the compile flags for this target's objects.
include src/config/CMakeFiles/configuration.dir/flags.make

src/config/CMakeFiles/configuration.dir/Configuration.cpp.o: src/config/CMakeFiles/configuration.dir/flags.make
src/config/CMakeFiles/configuration.dir/Configuration.cpp.o: ../src/config/Configuration.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/config/CMakeFiles/configuration.dir/Configuration.cpp.o"
	cd /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/src/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/configuration.dir/Configuration.cpp.o -c /home/shuliang/Documents/ReducedSpaceSimulation/src/config/Configuration.cpp

src/config/CMakeFiles/configuration.dir/Configuration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/configuration.dir/Configuration.cpp.i"
	cd /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/src/config && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shuliang/Documents/ReducedSpaceSimulation/src/config/Configuration.cpp > CMakeFiles/configuration.dir/Configuration.cpp.i

src/config/CMakeFiles/configuration.dir/Configuration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/configuration.dir/Configuration.cpp.s"
	cd /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/src/config && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shuliang/Documents/ReducedSpaceSimulation/src/config/Configuration.cpp -o CMakeFiles/configuration.dir/Configuration.cpp.s

# Object files for target configuration
configuration_OBJECTS = \
"CMakeFiles/configuration.dir/Configuration.cpp.o"

# External object files for target configuration
configuration_EXTERNAL_OBJECTS =

../lib/libconfiguration.so: src/config/CMakeFiles/configuration.dir/Configuration.cpp.o
../lib/libconfiguration.so: src/config/CMakeFiles/configuration.dir/build.make
../lib/libconfiguration.so: src/config/CMakeFiles/configuration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../../lib/libconfiguration.so"
	cd /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/src/config && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/configuration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/config/CMakeFiles/configuration.dir/build: ../lib/libconfiguration.so

.PHONY : src/config/CMakeFiles/configuration.dir/build

src/config/CMakeFiles/configuration.dir/clean:
	cd /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/src/config && $(CMAKE_COMMAND) -P CMakeFiles/configuration.dir/cmake_clean.cmake
.PHONY : src/config/CMakeFiles/configuration.dir/clean

src/config/CMakeFiles/configuration.dir/depend:
	cd /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shuliang/Documents/ReducedSpaceSimulation /home/shuliang/Documents/ReducedSpaceSimulation/src/config /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/src/config /home/shuliang/Documents/ReducedSpaceSimulation/cmake-build-debug/src/config/CMakeFiles/configuration.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/config/CMakeFiles/configuration.dir/depend

