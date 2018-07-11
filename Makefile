# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/regular/Documents/BU_2018/falafels/cpisync

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/regular/Documents/BU_2018/falafels/cpisync

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/regular/Documents/BU_2018/falafels/cpisync/CMakeFiles /home/regular/Documents/BU_2018/falafels/cpisync/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/regular/Documents/BU_2018/falafels/cpisync/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named IBLTTester.exe

# Build rule for target.
IBLTTester.exe: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 IBLTTester.exe
.PHONY : IBLTTester.exe

# fast build rule for target.
IBLTTester.exe/fast:
	$(MAKE) -f CMakeFiles/IBLTTester.exe.dir/build.make CMakeFiles/IBLTTester.exe.dir/build
.PHONY : IBLTTester.exe/fast

#=============================================================================
# Target rules for targets named cpisynclib

# Build rule for target.
cpisynclib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cpisynclib
.PHONY : cpisynclib

# fast build rule for target.
cpisynclib/fast:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/build
.PHONY : cpisynclib/fast

#=============================================================================
# Target rules for targets named systemTest

# Build rule for target.
systemTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 systemTest
.PHONY : systemTest

# fast build rule for target.
systemTest/fast:
	$(MAKE) -f CMakeFiles/systemTest.dir/build.make CMakeFiles/systemTest.dir/build
.PHONY : systemTest/fast

src/CPISync.o: src/CPISync.cpp.o

.PHONY : src/CPISync.o

# target to build an object file
src/CPISync.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CPISync.cpp.o
.PHONY : src/CPISync.cpp.o

src/CPISync.i: src/CPISync.cpp.i

.PHONY : src/CPISync.i

# target to preprocess a source file
src/CPISync.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CPISync.cpp.i
.PHONY : src/CPISync.cpp.i

src/CPISync.s: src/CPISync.cpp.s

.PHONY : src/CPISync.s

# target to generate assembly for a file
src/CPISync.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CPISync.cpp.s
.PHONY : src/CPISync.cpp.s

src/CommSocket.o: src/CommSocket.cpp.o

.PHONY : src/CommSocket.o

# target to build an object file
src/CommSocket.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CommSocket.cpp.o
.PHONY : src/CommSocket.cpp.o

src/CommSocket.i: src/CommSocket.cpp.i

.PHONY : src/CommSocket.i

# target to preprocess a source file
src/CommSocket.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CommSocket.cpp.i
.PHONY : src/CommSocket.cpp.i

src/CommSocket.s: src/CommSocket.cpp.s

.PHONY : src/CommSocket.s

# target to generate assembly for a file
src/CommSocket.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CommSocket.cpp.s
.PHONY : src/CommSocket.cpp.s

src/CommString.o: src/CommString.cpp.o

.PHONY : src/CommString.o

# target to build an object file
src/CommString.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CommString.cpp.o
.PHONY : src/CommString.cpp.o

src/CommString.i: src/CommString.cpp.i

.PHONY : src/CommString.i

# target to preprocess a source file
src/CommString.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CommString.cpp.i
.PHONY : src/CommString.cpp.i

src/CommString.s: src/CommString.cpp.s

.PHONY : src/CommString.s

# target to generate assembly for a file
src/CommString.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/CommString.cpp.s
.PHONY : src/CommString.cpp.s

src/Communicant.o: src/Communicant.cpp.o

.PHONY : src/Communicant.o

# target to build an object file
src/Communicant.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/Communicant.cpp.o
.PHONY : src/Communicant.cpp.o

src/Communicant.i: src/Communicant.cpp.i

.PHONY : src/Communicant.i

# target to preprocess a source file
src/Communicant.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/Communicant.cpp.i
.PHONY : src/Communicant.cpp.i

src/Communicant.s: src/Communicant.cpp.s

.PHONY : src/Communicant.s

# target to generate assembly for a file
src/Communicant.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/Communicant.cpp.s
.PHONY : src/Communicant.cpp.s

src/DataObject.o: src/DataObject.cpp.o

.PHONY : src/DataObject.o

# target to build an object file
src/DataObject.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/DataObject.cpp.o
.PHONY : src/DataObject.cpp.o

src/DataObject.i: src/DataObject.cpp.i

.PHONY : src/DataObject.i

# target to preprocess a source file
src/DataObject.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/DataObject.cpp.i
.PHONY : src/DataObject.cpp.i

src/DataObject.s: src/DataObject.cpp.s

.PHONY : src/DataObject.s

# target to generate assembly for a file
src/DataObject.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/DataObject.cpp.s
.PHONY : src/DataObject.cpp.s

src/GenSync.o: src/GenSync.cpp.o

.PHONY : src/GenSync.o

# target to build an object file
src/GenSync.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/GenSync.cpp.o
.PHONY : src/GenSync.cpp.o

src/GenSync.i: src/GenSync.cpp.i

.PHONY : src/GenSync.i

# target to preprocess a source file
src/GenSync.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/GenSync.cpp.i
.PHONY : src/GenSync.cpp.i

src/GenSync.s: src/GenSync.cpp.s

.PHONY : src/GenSync.s

# target to generate assembly for a file
src/GenSync.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/GenSync.cpp.s
.PHONY : src/GenSync.cpp.s

src/IBLTSync.o: src/IBLTSync.cpp.o

.PHONY : src/IBLTSync.o

# target to build an object file
src/IBLTSync.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/IBLTSync.cpp.o
.PHONY : src/IBLTSync.cpp.o

src/IBLTSync.i: src/IBLTSync.cpp.i

.PHONY : src/IBLTSync.i

# target to preprocess a source file
src/IBLTSync.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/IBLTSync.cpp.i
.PHONY : src/IBLTSync.cpp.i

src/IBLTSync.s: src/IBLTSync.cpp.s

.PHONY : src/IBLTSync.s

# target to generate assembly for a file
src/IBLTSync.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/IBLTSync.cpp.s
.PHONY : src/IBLTSync.cpp.s

src/InterCPISync.o: src/InterCPISync.cpp.o

.PHONY : src/InterCPISync.o

# target to build an object file
src/InterCPISync.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/InterCPISync.cpp.o
.PHONY : src/InterCPISync.cpp.o

src/InterCPISync.i: src/InterCPISync.cpp.i

.PHONY : src/InterCPISync.i

# target to preprocess a source file
src/InterCPISync.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/InterCPISync.cpp.i
.PHONY : src/InterCPISync.cpp.i

src/InterCPISync.s: src/InterCPISync.cpp.s

.PHONY : src/InterCPISync.s

# target to generate assembly for a file
src/InterCPISync.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/InterCPISync.cpp.s
.PHONY : src/InterCPISync.cpp.s

src/Logger.o: src/Logger.cpp.o

.PHONY : src/Logger.o

# target to build an object file
src/Logger.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/Logger.cpp.o
.PHONY : src/Logger.cpp.o

src/Logger.i: src/Logger.cpp.i

.PHONY : src/Logger.i

# target to preprocess a source file
src/Logger.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/Logger.cpp.i
.PHONY : src/Logger.cpp.i

src/Logger.s: src/Logger.cpp.s

.PHONY : src/Logger.s

# target to generate assembly for a file
src/Logger.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/Logger.cpp.s
.PHONY : src/Logger.cpp.s

src/SyncMethod.o: src/SyncMethod.cpp.o

.PHONY : src/SyncMethod.o

# target to build an object file
src/SyncMethod.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/SyncMethod.cpp.o
.PHONY : src/SyncMethod.cpp.o

src/SyncMethod.i: src/SyncMethod.cpp.i

.PHONY : src/SyncMethod.i

# target to preprocess a source file
src/SyncMethod.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/SyncMethod.cpp.i
.PHONY : src/SyncMethod.cpp.i

src/SyncMethod.s: src/SyncMethod.cpp.s

.PHONY : src/SyncMethod.s

# target to generate assembly for a file
src/SyncMethod.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/SyncMethod.cpp.s
.PHONY : src/SyncMethod.cpp.s

src/UID.o: src/UID.cpp.o

.PHONY : src/UID.o

# target to build an object file
src/UID.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/UID.cpp.o
.PHONY : src/UID.cpp.o

src/UID.i: src/UID.cpp.i

.PHONY : src/UID.i

# target to preprocess a source file
src/UID.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/UID.cpp.i
.PHONY : src/UID.cpp.i

src/UID.s: src/UID.cpp.s

.PHONY : src/UID.s

# target to generate assembly for a file
src/UID.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/UID.cpp.s
.PHONY : src/UID.cpp.s

src/iblt.o: src/iblt.cpp.o

.PHONY : src/iblt.o

# target to build an object file
src/iblt.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/iblt.cpp.o
.PHONY : src/iblt.cpp.o

src/iblt.i: src/iblt.cpp.i

.PHONY : src/iblt.i

# target to preprocess a source file
src/iblt.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/iblt.cpp.i
.PHONY : src/iblt.cpp.i

src/iblt.s: src/iblt.cpp.s

.PHONY : src/iblt.s

# target to generate assembly for a file
src/iblt.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/iblt.cpp.s
.PHONY : src/iblt.cpp.s

src/murmurhash3.o: src/murmurhash3.cpp.o

.PHONY : src/murmurhash3.o

# target to build an object file
src/murmurhash3.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/murmurhash3.cpp.o
.PHONY : src/murmurhash3.cpp.o

src/murmurhash3.i: src/murmurhash3.cpp.i

.PHONY : src/murmurhash3.i

# target to preprocess a source file
src/murmurhash3.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/murmurhash3.cpp.i
.PHONY : src/murmurhash3.cpp.i

src/murmurhash3.s: src/murmurhash3.cpp.s

.PHONY : src/murmurhash3.s

# target to generate assembly for a file
src/murmurhash3.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/murmurhash3.cpp.s
.PHONY : src/murmurhash3.cpp.s

src/probCPISync.o: src/probCPISync.cpp.o

.PHONY : src/probCPISync.o

# target to build an object file
src/probCPISync.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/probCPISync.cpp.o
.PHONY : src/probCPISync.cpp.o

src/probCPISync.i: src/probCPISync.cpp.i

.PHONY : src/probCPISync.i

# target to preprocess a source file
src/probCPISync.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/probCPISync.cpp.i
.PHONY : src/probCPISync.cpp.i

src/probCPISync.s: src/probCPISync.cpp.s

.PHONY : src/probCPISync.s

# target to generate assembly for a file
src/probCPISync.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/probCPISync.cpp.s
.PHONY : src/probCPISync.cpp.s

src/utilstrencodings.o: src/utilstrencodings.cpp.o

.PHONY : src/utilstrencodings.o

# target to build an object file
src/utilstrencodings.cpp.o:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/utilstrencodings.cpp.o
.PHONY : src/utilstrencodings.cpp.o

src/utilstrencodings.i: src/utilstrencodings.cpp.i

.PHONY : src/utilstrencodings.i

# target to preprocess a source file
src/utilstrencodings.cpp.i:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/utilstrencodings.cpp.i
.PHONY : src/utilstrencodings.cpp.i

src/utilstrencodings.s: src/utilstrencodings.cpp.s

.PHONY : src/utilstrencodings.s

# target to generate assembly for a file
src/utilstrencodings.cpp.s:
	$(MAKE) -f CMakeFiles/cpisynclib.dir/build.make CMakeFiles/cpisynclib.dir/src/utilstrencodings.cpp.s
.PHONY : src/utilstrencodings.cpp.s

tests/IBLTTester.o: tests/IBLTTester.cpp.o

.PHONY : tests/IBLTTester.o

# target to build an object file
tests/IBLTTester.cpp.o:
	$(MAKE) -f CMakeFiles/IBLTTester.exe.dir/build.make CMakeFiles/IBLTTester.exe.dir/tests/IBLTTester.cpp.o
.PHONY : tests/IBLTTester.cpp.o

tests/IBLTTester.i: tests/IBLTTester.cpp.i

.PHONY : tests/IBLTTester.i

# target to preprocess a source file
tests/IBLTTester.cpp.i:
	$(MAKE) -f CMakeFiles/IBLTTester.exe.dir/build.make CMakeFiles/IBLTTester.exe.dir/tests/IBLTTester.cpp.i
.PHONY : tests/IBLTTester.cpp.i

tests/IBLTTester.s: tests/IBLTTester.cpp.s

.PHONY : tests/IBLTTester.s

# target to generate assembly for a file
tests/IBLTTester.cpp.s:
	$(MAKE) -f CMakeFiles/IBLTTester.exe.dir/build.make CMakeFiles/IBLTTester.exe.dir/tests/IBLTTester.cpp.s
.PHONY : tests/IBLTTester.cpp.s

tests/cpi_system_test.o: tests/cpi_system_test.cpp.o

.PHONY : tests/cpi_system_test.o

# target to build an object file
tests/cpi_system_test.cpp.o:
	$(MAKE) -f CMakeFiles/systemTest.dir/build.make CMakeFiles/systemTest.dir/tests/cpi_system_test.cpp.o
.PHONY : tests/cpi_system_test.cpp.o

tests/cpi_system_test.i: tests/cpi_system_test.cpp.i

.PHONY : tests/cpi_system_test.i

# target to preprocess a source file
tests/cpi_system_test.cpp.i:
	$(MAKE) -f CMakeFiles/systemTest.dir/build.make CMakeFiles/systemTest.dir/tests/cpi_system_test.cpp.i
.PHONY : tests/cpi_system_test.cpp.i

tests/cpi_system_test.s: tests/cpi_system_test.cpp.s

.PHONY : tests/cpi_system_test.s

# target to generate assembly for a file
tests/cpi_system_test.cpp.s:
	$(MAKE) -f CMakeFiles/systemTest.dir/build.make CMakeFiles/systemTest.dir/tests/cpi_system_test.cpp.s
.PHONY : tests/cpi_system_test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... IBLTTester.exe"
	@echo "... rebuild_cache"
	@echo "... cpisynclib"
	@echo "... systemTest"
	@echo "... src/CPISync.o"
	@echo "... src/CPISync.i"
	@echo "... src/CPISync.s"
	@echo "... src/CommSocket.o"
	@echo "... src/CommSocket.i"
	@echo "... src/CommSocket.s"
	@echo "... src/CommString.o"
	@echo "... src/CommString.i"
	@echo "... src/CommString.s"
	@echo "... src/Communicant.o"
	@echo "... src/Communicant.i"
	@echo "... src/Communicant.s"
	@echo "... src/DataObject.o"
	@echo "... src/DataObject.i"
	@echo "... src/DataObject.s"
	@echo "... src/GenSync.o"
	@echo "... src/GenSync.i"
	@echo "... src/GenSync.s"
	@echo "... src/IBLTSync.o"
	@echo "... src/IBLTSync.i"
	@echo "... src/IBLTSync.s"
	@echo "... src/InterCPISync.o"
	@echo "... src/InterCPISync.i"
	@echo "... src/InterCPISync.s"
	@echo "... src/Logger.o"
	@echo "... src/Logger.i"
	@echo "... src/Logger.s"
	@echo "... src/SyncMethod.o"
	@echo "... src/SyncMethod.i"
	@echo "... src/SyncMethod.s"
	@echo "... src/UID.o"
	@echo "... src/UID.i"
	@echo "... src/UID.s"
	@echo "... src/iblt.o"
	@echo "... src/iblt.i"
	@echo "... src/iblt.s"
	@echo "... src/murmurhash3.o"
	@echo "... src/murmurhash3.i"
	@echo "... src/murmurhash3.s"
	@echo "... src/probCPISync.o"
	@echo "... src/probCPISync.i"
	@echo "... src/probCPISync.s"
	@echo "... src/utilstrencodings.o"
	@echo "... src/utilstrencodings.i"
	@echo "... src/utilstrencodings.s"
	@echo "... tests/IBLTTester.o"
	@echo "... tests/IBLTTester.i"
	@echo "... tests/IBLTTester.s"
	@echo "... tests/cpi_system_test.o"
	@echo "... tests/cpi_system_test.i"
	@echo "... tests/cpi_system_test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
