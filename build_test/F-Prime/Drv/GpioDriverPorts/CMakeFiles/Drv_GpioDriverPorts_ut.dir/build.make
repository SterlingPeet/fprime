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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jishii/Documents/split_repo/fprime-sw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jishii/Documents/split_repo/fprime-sw/build_test

# Include any dependencies generated for this target.
include F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/depend.make

# Include the progress variables for this target.
include F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/progress.make

# Include the compile flags for this target's objects.
include F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/flags.make

F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp: F-Prime/Drv/GpioDriverPorts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jishii/Documents/split_repo/fprime-sw/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating GpioWritePortAc.cpp, GpioWritePortAc.hpp"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E env PYTHONPATH=/Users/jishii/Documents/split_repo/fprime-sw/Autocoders/Python/src:/Users/jishii/Documents/split_repo/fprime-sw/Autocoders/Python/utils BUILD_ROOT=/Users/jishii/Documents/split_repo/fprime-sw/cmake/.. PYTHON_AUTOCODER_DIR=/Users/jishii/Documents/split_repo/fprime-sw/Autocoders/Python DICTIONARY_DIR= FPRIME_CORE_DIR=/Users/jishii/Documents/split_repo/fprime-sw/cmake/.. /Users/jishii/Documents/split_repo/fprime-sw/cmake/../Autocoders/Python/bin/codegen.py --build_root /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts/GpioWritePortAi.xml
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E copy GpioWritePortAc.cpp /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E copy GpioWritePortAc.hpp /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.hpp
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E remove GpioWritePortAc.cpp
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E remove GpioWritePortAc.hpp

F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.hpp: F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.hpp

F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp: F-Prime/Drv/GpioDriverPorts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jishii/Documents/split_repo/fprime-sw/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating GpioReadPortAc.cpp, GpioReadPortAc.hpp"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E env PYTHONPATH=/Users/jishii/Documents/split_repo/fprime-sw/Autocoders/Python/src:/Users/jishii/Documents/split_repo/fprime-sw/Autocoders/Python/utils BUILD_ROOT=/Users/jishii/Documents/split_repo/fprime-sw/cmake/.. PYTHON_AUTOCODER_DIR=/Users/jishii/Documents/split_repo/fprime-sw/Autocoders/Python DICTIONARY_DIR= FPRIME_CORE_DIR=/Users/jishii/Documents/split_repo/fprime-sw/cmake/.. /Users/jishii/Documents/split_repo/fprime-sw/cmake/../Autocoders/Python/bin/codegen.py --build_root /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts/GpioReadPortAi.xml
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E copy GpioReadPortAc.cpp /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E copy GpioReadPortAc.hpp /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.hpp
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E remove GpioReadPortAc.cpp
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E chdir /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /opt/local/bin/cmake -E remove GpioReadPortAc.hpp

F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.hpp: F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.hpp

F-Prime/Drv/GpioDriverPorts:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/jishii/Documents/split_repo/fprime-sw/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating ."
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /opt/local/bin/cmake -E make_directory /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.o: F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/flags.make
F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.o: F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jishii/Documents/split_repo/fprime-sw/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.o"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.o -c /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.i"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp > CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.i

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.s"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp -o CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.s

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.o: F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/flags.make
F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.o: F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jishii/Documents/split_repo/fprime-sw/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.o"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.o -c /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.i"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp > CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.i

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.s"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp -o CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.s

# Object files for target Drv_GpioDriverPorts_ut
Drv_GpioDriverPorts_ut_OBJECTS = \
"CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.o" \
"CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.o"

# External object files for target Drv_GpioDriverPorts_ut
Drv_GpioDriverPorts_ut_EXTERNAL_OBJECTS =

lib/Darwin/libDrv_GpioDriverPorts_ut.a: F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioWritePortAc.cpp.o
lib/Darwin/libDrv_GpioDriverPorts_ut.a: F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/GpioReadPortAc.cpp.o
lib/Darwin/libDrv_GpioDriverPorts_ut.a: F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/build.make
lib/Darwin/libDrv_GpioDriverPorts_ut.a: F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jishii/Documents/split_repo/fprime-sw/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library ../../../lib/Darwin/libDrv_GpioDriverPorts_ut.a"
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && $(CMAKE_COMMAND) -P CMakeFiles/Drv_GpioDriverPorts_ut.dir/cmake_clean_target.cmake
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Drv_GpioDriverPorts_ut.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/build: lib/Darwin/libDrv_GpioDriverPorts_ut.a

.PHONY : F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/build

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/clean:
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts && $(CMAKE_COMMAND) -P CMakeFiles/Drv_GpioDriverPorts_ut.dir/cmake_clean.cmake
.PHONY : F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/clean

F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/depend: F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.cpp
F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/depend: F-Prime/Drv/GpioDriverPorts/GpioWritePortAc.hpp
F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/depend: F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.cpp
F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/depend: F-Prime/Drv/GpioDriverPorts/GpioReadPortAc.hpp
F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/depend: F-Prime/Drv/GpioDriverPorts
	cd /Users/jishii/Documents/split_repo/fprime-sw/build_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jishii/Documents/split_repo/fprime-sw /Users/jishii/Documents/split_repo/fprime-sw/Drv/GpioDriverPorts /Users/jishii/Documents/split_repo/fprime-sw/build_test /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts /Users/jishii/Documents/split_repo/fprime-sw/build_test/F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : F-Prime/Drv/GpioDriverPorts/CMakeFiles/Drv_GpioDriverPorts_ut.dir/depend

