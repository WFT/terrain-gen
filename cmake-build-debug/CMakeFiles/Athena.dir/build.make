# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/vjiaoblack/Compsci/clion-2018.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/vjiaoblack/Compsci/clion-2018.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vjiaoblack/Compsci/Athena

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vjiaoblack/Compsci/Athena/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Athena.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Athena.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Athena.dir/flags.make

CMakeFiles/Athena.dir/src/TrGame.cpp.o: CMakeFiles/Athena.dir/flags.make
CMakeFiles/Athena.dir/src/TrGame.cpp.o: ../src/TrGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vjiaoblack/Compsci/Athena/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Athena.dir/src/TrGame.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Athena.dir/src/TrGame.cpp.o -c /home/vjiaoblack/Compsci/Athena/src/TrGame.cpp

CMakeFiles/Athena.dir/src/TrGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Athena.dir/src/TrGame.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vjiaoblack/Compsci/Athena/src/TrGame.cpp > CMakeFiles/Athena.dir/src/TrGame.cpp.i

CMakeFiles/Athena.dir/src/TrGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Athena.dir/src/TrGame.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vjiaoblack/Compsci/Athena/src/TrGame.cpp -o CMakeFiles/Athena.dir/src/TrGame.cpp.s

CMakeFiles/Athena.dir/src/TrGame.cpp.o.requires:

.PHONY : CMakeFiles/Athena.dir/src/TrGame.cpp.o.requires

CMakeFiles/Athena.dir/src/TrGame.cpp.o.provides: CMakeFiles/Athena.dir/src/TrGame.cpp.o.requires
	$(MAKE) -f CMakeFiles/Athena.dir/build.make CMakeFiles/Athena.dir/src/TrGame.cpp.o.provides.build
.PHONY : CMakeFiles/Athena.dir/src/TrGame.cpp.o.provides

CMakeFiles/Athena.dir/src/TrGame.cpp.o.provides.build: CMakeFiles/Athena.dir/src/TrGame.cpp.o


# Object files for target Athena
Athena_OBJECTS = \
"CMakeFiles/Athena.dir/src/TrGame.cpp.o"

# External object files for target Athena
Athena_EXTERNAL_OBJECTS =

Athena: CMakeFiles/Athena.dir/src/TrGame.cpp.o
Athena: CMakeFiles/Athena.dir/build.make
Athena: /usr/lib/x86_64-linux-gnu/libSDL2main.a
Athena: /usr/lib/x86_64-linux-gnu/libSDL2.so
Athena: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
Athena: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
Athena: CMakeFiles/Athena.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vjiaoblack/Compsci/Athena/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Athena"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Athena.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Athena.dir/build: Athena

.PHONY : CMakeFiles/Athena.dir/build

CMakeFiles/Athena.dir/requires: CMakeFiles/Athena.dir/src/TrGame.cpp.o.requires

.PHONY : CMakeFiles/Athena.dir/requires

CMakeFiles/Athena.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Athena.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Athena.dir/clean

CMakeFiles/Athena.dir/depend:
	cd /home/vjiaoblack/Compsci/Athena/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vjiaoblack/Compsci/Athena /home/vjiaoblack/Compsci/Athena /home/vjiaoblack/Compsci/Athena/cmake-build-debug /home/vjiaoblack/Compsci/Athena/cmake-build-debug /home/vjiaoblack/Compsci/Athena/cmake-build-debug/CMakeFiles/Athena.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Athena.dir/depend
