# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kali/Desktop/aby3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kali/Desktop/aby3/build

# Include any dependencies generated for this target.
include aby3/CMakeFiles/aby3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include aby3/CMakeFiles/aby3.dir/compiler_depend.make

# Include the progress variables for this target.
include aby3/CMakeFiles/aby3.dir/progress.make

# Include the compile flags for this target's objects.
include aby3/CMakeFiles/aby3.dir/flags.make

aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o: ../aby3/Circuit/CircuitLibrary.cpp
aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o -MF CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o.d -o CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o -c /home/kali/Desktop/aby3/aby3/Circuit/CircuitLibrary.cpp

aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/Circuit/CircuitLibrary.cpp > CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.i

aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/Circuit/CircuitLibrary.cpp -o CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.s

aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.o: ../aby3/Circuit/Garble.cpp
aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.o -MF CMakeFiles/aby3.dir/Circuit/Garble.cpp.o.d -o CMakeFiles/aby3.dir/Circuit/Garble.cpp.o -c /home/kali/Desktop/aby3/aby3/Circuit/Garble.cpp

aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/Circuit/Garble.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/Circuit/Garble.cpp > CMakeFiles/aby3.dir/Circuit/Garble.cpp.i

aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/Circuit/Garble.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/Circuit/Garble.cpp -o CMakeFiles/aby3.dir/Circuit/Garble.cpp.s

aby3/CMakeFiles/aby3.dir/Common/Task.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/Common/Task.cpp.o: ../aby3/Common/Task.cpp
aby3/CMakeFiles/aby3.dir/Common/Task.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object aby3/CMakeFiles/aby3.dir/Common/Task.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/Common/Task.cpp.o -MF CMakeFiles/aby3.dir/Common/Task.cpp.o.d -o CMakeFiles/aby3.dir/Common/Task.cpp.o -c /home/kali/Desktop/aby3/aby3/Common/Task.cpp

aby3/CMakeFiles/aby3.dir/Common/Task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/Common/Task.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/Common/Task.cpp > CMakeFiles/aby3.dir/Common/Task.cpp.i

aby3/CMakeFiles/aby3.dir/Common/Task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/Common/Task.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/Common/Task.cpp -o CMakeFiles/aby3.dir/Common/Task.cpp.s

aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.o: ../aby3/OT/SharedOT.cpp
aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.o -MF CMakeFiles/aby3.dir/OT/SharedOT.cpp.o.d -o CMakeFiles/aby3.dir/OT/SharedOT.cpp.o -c /home/kali/Desktop/aby3/aby3/OT/SharedOT.cpp

aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/OT/SharedOT.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/OT/SharedOT.cpp > CMakeFiles/aby3.dir/OT/SharedOT.cpp.i

aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/OT/SharedOT.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/OT/SharedOT.cpp -o CMakeFiles/aby3.dir/OT/SharedOT.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o: ../aby3/sh3/Sh3BinaryEvaluator.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3BinaryEvaluator.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3BinaryEvaluator.cpp > CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3BinaryEvaluator.cpp -o CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o: ../aby3/sh3/Sh3Converter.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3Converter.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3Converter.cpp > CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3Converter.cpp -o CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o: ../aby3/sh3/Sh3Encryptor.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3Encryptor.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3Encryptor.cpp > CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3Encryptor.cpp -o CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o: ../aby3/sh3/Sh3Evaluator.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3Evaluator.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3Evaluator.cpp > CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3Evaluator.cpp -o CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o: ../aby3/sh3/Sh3FixedPoint.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3FixedPoint.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3FixedPoint.cpp > CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3FixedPoint.cpp -o CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o: ../aby3/sh3/Sh3Piecewise.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3Piecewise.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3Piecewise.cpp > CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3Piecewise.cpp -o CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o: ../aby3/sh3/Sh3Runtime.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3Runtime.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3Runtime.cpp > CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3Runtime.cpp -o CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.s

aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o: aby3/CMakeFiles/aby3.dir/flags.make
aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o: ../aby3/sh3/Sh3Types.cpp
aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o: aby3/CMakeFiles/aby3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o -MF CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o.d -o CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o -c /home/kali/Desktop/aby3/aby3/sh3/Sh3Types.cpp

aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.i"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kali/Desktop/aby3/aby3/sh3/Sh3Types.cpp > CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.i

aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.s"
	cd /home/kali/Desktop/aby3/build/aby3 && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kali/Desktop/aby3/aby3/sh3/Sh3Types.cpp -o CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.s

# Object files for target aby3
aby3_OBJECTS = \
"CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o" \
"CMakeFiles/aby3.dir/Circuit/Garble.cpp.o" \
"CMakeFiles/aby3.dir/Common/Task.cpp.o" \
"CMakeFiles/aby3.dir/OT/SharedOT.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o" \
"CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o"

# External object files for target aby3
aby3_EXTERNAL_OBJECTS =

../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/Circuit/CircuitLibrary.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/Circuit/Garble.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/Common/Task.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/OT/SharedOT.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3BinaryEvaluator.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3Converter.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3Encryptor.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3Evaluator.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3FixedPoint.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3Piecewise.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3Runtime.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/sh3/Sh3Types.cpp.o
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/build.make
../lib/libaby3.a: aby3/CMakeFiles/aby3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kali/Desktop/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX static library ../../lib/libaby3.a"
	cd /home/kali/Desktop/aby3/build/aby3 && $(CMAKE_COMMAND) -P CMakeFiles/aby3.dir/cmake_clean_target.cmake
	cd /home/kali/Desktop/aby3/build/aby3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aby3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
aby3/CMakeFiles/aby3.dir/build: ../lib/libaby3.a
.PHONY : aby3/CMakeFiles/aby3.dir/build

aby3/CMakeFiles/aby3.dir/clean:
	cd /home/kali/Desktop/aby3/build/aby3 && $(CMAKE_COMMAND) -P CMakeFiles/aby3.dir/cmake_clean.cmake
.PHONY : aby3/CMakeFiles/aby3.dir/clean

aby3/CMakeFiles/aby3.dir/depend:
	cd /home/kali/Desktop/aby3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/Desktop/aby3 /home/kali/Desktop/aby3/aby3 /home/kali/Desktop/aby3/build /home/kali/Desktop/aby3/build/aby3 /home/kali/Desktop/aby3/build/aby3/CMakeFiles/aby3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : aby3/CMakeFiles/aby3.dir/depend

