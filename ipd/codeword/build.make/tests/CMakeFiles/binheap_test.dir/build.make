# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.3.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.3.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Henry/Documents/workspace/ipd/codeword

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Henry/Documents/workspace/ipd/codeword/build.make

# Include any dependencies generated for this target.
include tests/CMakeFiles/binheap_test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/binheap_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/binheap_test.dir/flags.make

tests/CMakeFiles/binheap_test.dir/binheap.cpp.o: tests/CMakeFiles/binheap_test.dir/flags.make
tests/CMakeFiles/binheap_test.dir/binheap.cpp.o: ../tests/binheap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Henry/Documents/workspace/ipd/codeword/build.make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/binheap_test.dir/binheap.cpp.o"
	cd /Users/Henry/Documents/workspace/ipd/codeword/build.make/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/binheap_test.dir/binheap.cpp.o -c /Users/Henry/Documents/workspace/ipd/codeword/tests/binheap.cpp

tests/CMakeFiles/binheap_test.dir/binheap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/binheap_test.dir/binheap.cpp.i"
	cd /Users/Henry/Documents/workspace/ipd/codeword/build.make/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Henry/Documents/workspace/ipd/codeword/tests/binheap.cpp > CMakeFiles/binheap_test.dir/binheap.cpp.i

tests/CMakeFiles/binheap_test.dir/binheap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/binheap_test.dir/binheap.cpp.s"
	cd /Users/Henry/Documents/workspace/ipd/codeword/build.make/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Henry/Documents/workspace/ipd/codeword/tests/binheap.cpp -o CMakeFiles/binheap_test.dir/binheap.cpp.s

tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.requires:

.PHONY : tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.requires

tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.provides: tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/binheap_test.dir/build.make tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.provides.build
.PHONY : tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.provides

tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.provides.build: tests/CMakeFiles/binheap_test.dir/binheap.cpp.o


# Object files for target binheap_test
binheap_test_OBJECTS = \
"CMakeFiles/binheap_test.dir/binheap.cpp.o"

# External object files for target binheap_test
binheap_test_EXTERNAL_OBJECTS =

tests/binheap_test: tests/CMakeFiles/binheap_test.dir/binheap.cpp.o
tests/binheap_test: tests/CMakeFiles/binheap_test.dir/build.make
tests/binheap_test: src/binheap/libbinheap.a
tests/binheap_test: 3rdparty/unittest-cpp/libUnitTest++.a
tests/binheap_test: tests/CMakeFiles/binheap_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Henry/Documents/workspace/ipd/codeword/build.make/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable binheap_test"
	cd /Users/Henry/Documents/workspace/ipd/codeword/build.make/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binheap_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/binheap_test.dir/build: tests/binheap_test

.PHONY : tests/CMakeFiles/binheap_test.dir/build

tests/CMakeFiles/binheap_test.dir/requires: tests/CMakeFiles/binheap_test.dir/binheap.cpp.o.requires

.PHONY : tests/CMakeFiles/binheap_test.dir/requires

tests/CMakeFiles/binheap_test.dir/clean:
	cd /Users/Henry/Documents/workspace/ipd/codeword/build.make/tests && $(CMAKE_COMMAND) -P CMakeFiles/binheap_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/binheap_test.dir/clean

tests/CMakeFiles/binheap_test.dir/depend:
	cd /Users/Henry/Documents/workspace/ipd/codeword/build.make && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Henry/Documents/workspace/ipd/codeword /Users/Henry/Documents/workspace/ipd/codeword/tests /Users/Henry/Documents/workspace/ipd/codeword/build.make /Users/Henry/Documents/workspace/ipd/codeword/build.make/tests /Users/Henry/Documents/workspace/ipd/codeword/build.make/tests/CMakeFiles/binheap_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/binheap_test.dir/depend

