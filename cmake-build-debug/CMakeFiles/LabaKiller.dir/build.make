# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2016.3.5\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2016.3.5\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\plyus\ClionProjects\LabaKiller

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\plyus\ClionProjects\LabaKiller\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LabaKiller.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LabaKiller.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LabaKiller.dir/flags.make

CMakeFiles/LabaKiller.dir/main.cpp.obj: CMakeFiles/LabaKiller.dir/flags.make
CMakeFiles/LabaKiller.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\plyus\ClionProjects\LabaKiller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LabaKiller.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\LabaKiller.dir\main.cpp.obj -c C:\Users\plyus\ClionProjects\LabaKiller\main.cpp

CMakeFiles/LabaKiller.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LabaKiller.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\plyus\ClionProjects\LabaKiller\main.cpp > CMakeFiles\LabaKiller.dir\main.cpp.i

CMakeFiles/LabaKiller.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LabaKiller.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\plyus\ClionProjects\LabaKiller\main.cpp -o CMakeFiles\LabaKiller.dir\main.cpp.s

CMakeFiles/LabaKiller.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/LabaKiller.dir/main.cpp.obj.requires

CMakeFiles/LabaKiller.dir/main.cpp.obj.provides: CMakeFiles/LabaKiller.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\LabaKiller.dir\build.make CMakeFiles/LabaKiller.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/LabaKiller.dir/main.cpp.obj.provides

CMakeFiles/LabaKiller.dir/main.cpp.obj.provides.build: CMakeFiles/LabaKiller.dir/main.cpp.obj


# Object files for target LabaKiller
LabaKiller_OBJECTS = \
"CMakeFiles/LabaKiller.dir/main.cpp.obj"

# External object files for target LabaKiller
LabaKiller_EXTERNAL_OBJECTS =

LabaKiller.exe: CMakeFiles/LabaKiller.dir/main.cpp.obj
LabaKiller.exe: CMakeFiles/LabaKiller.dir/build.make
LabaKiller.exe: CMakeFiles/LabaKiller.dir/linklibs.rsp
LabaKiller.exe: CMakeFiles/LabaKiller.dir/objects1.rsp
LabaKiller.exe: CMakeFiles/LabaKiller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\plyus\ClionProjects\LabaKiller\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LabaKiller.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LabaKiller.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LabaKiller.dir/build: LabaKiller.exe

.PHONY : CMakeFiles/LabaKiller.dir/build

CMakeFiles/LabaKiller.dir/requires: CMakeFiles/LabaKiller.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/LabaKiller.dir/requires

CMakeFiles/LabaKiller.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LabaKiller.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LabaKiller.dir/clean

CMakeFiles/LabaKiller.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\plyus\ClionProjects\LabaKiller C:\Users\plyus\ClionProjects\LabaKiller C:\Users\plyus\ClionProjects\LabaKiller\cmake-build-debug C:\Users\plyus\ClionProjects\LabaKiller\cmake-build-debug C:\Users\plyus\ClionProjects\LabaKiller\cmake-build-debug\CMakeFiles\LabaKiller.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LabaKiller.dir/depend

