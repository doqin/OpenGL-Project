# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/doqin/Projects/OpenGL-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/doqin/Projects/OpenGL-Project/build

# Include any dependencies generated for this target.
include CMakeFiles/OpenGL-Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGL-Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGL-Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGL-Project.dir/flags.make

CMakeFiles/OpenGL-Project.dir/codegen:
.PHONY : CMakeFiles/OpenGL-Project.dir/codegen

CMakeFiles/OpenGL-Project.dir/src/main.cpp.o: CMakeFiles/OpenGL-Project.dir/flags.make
CMakeFiles/OpenGL-Project.dir/src/main.cpp.o: /Users/doqin/Projects/OpenGL-Project/src/main.cpp
CMakeFiles/OpenGL-Project.dir/src/main.cpp.o: CMakeFiles/OpenGL-Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doqin/Projects/OpenGL-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGL-Project.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL-Project.dir/src/main.cpp.o -MF CMakeFiles/OpenGL-Project.dir/src/main.cpp.o.d -o CMakeFiles/OpenGL-Project.dir/src/main.cpp.o -c /Users/doqin/Projects/OpenGL-Project/src/main.cpp

CMakeFiles/OpenGL-Project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGL-Project.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doqin/Projects/OpenGL-Project/src/main.cpp > CMakeFiles/OpenGL-Project.dir/src/main.cpp.i

CMakeFiles/OpenGL-Project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGL-Project.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doqin/Projects/OpenGL-Project/src/main.cpp -o CMakeFiles/OpenGL-Project.dir/src/main.cpp.s

CMakeFiles/OpenGL-Project.dir/src/glad.c.o: CMakeFiles/OpenGL-Project.dir/flags.make
CMakeFiles/OpenGL-Project.dir/src/glad.c.o: /Users/doqin/Projects/OpenGL-Project/src/glad.c
CMakeFiles/OpenGL-Project.dir/src/glad.c.o: CMakeFiles/OpenGL-Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doqin/Projects/OpenGL-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OpenGL-Project.dir/src/glad.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OpenGL-Project.dir/src/glad.c.o -MF CMakeFiles/OpenGL-Project.dir/src/glad.c.o.d -o CMakeFiles/OpenGL-Project.dir/src/glad.c.o -c /Users/doqin/Projects/OpenGL-Project/src/glad.c

CMakeFiles/OpenGL-Project.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/OpenGL-Project.dir/src/glad.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/doqin/Projects/OpenGL-Project/src/glad.c > CMakeFiles/OpenGL-Project.dir/src/glad.c.i

CMakeFiles/OpenGL-Project.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/OpenGL-Project.dir/src/glad.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/doqin/Projects/OpenGL-Project/src/glad.c -o CMakeFiles/OpenGL-Project.dir/src/glad.c.s

CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o: CMakeFiles/OpenGL-Project.dir/flags.make
CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o: /Users/doqin/Projects/OpenGL-Project/src/readFile.cpp
CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o: CMakeFiles/OpenGL-Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/doqin/Projects/OpenGL-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o -MF CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o.d -o CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o -c /Users/doqin/Projects/OpenGL-Project/src/readFile.cpp

CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/doqin/Projects/OpenGL-Project/src/readFile.cpp > CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.i

CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/doqin/Projects/OpenGL-Project/src/readFile.cpp -o CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.s

# Object files for target OpenGL-Project
OpenGL__Project_OBJECTS = \
"CMakeFiles/OpenGL-Project.dir/src/main.cpp.o" \
"CMakeFiles/OpenGL-Project.dir/src/glad.c.o" \
"CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o"

# External object files for target OpenGL-Project
OpenGL__Project_EXTERNAL_OBJECTS =

OpenGL-Project: CMakeFiles/OpenGL-Project.dir/src/main.cpp.o
OpenGL-Project: CMakeFiles/OpenGL-Project.dir/src/glad.c.o
OpenGL-Project: CMakeFiles/OpenGL-Project.dir/src/readFile.cpp.o
OpenGL-Project: CMakeFiles/OpenGL-Project.dir/build.make
OpenGL-Project: /Users/doqin/Projects/OpenGL-Project/lib/libglfw.3.dylib
OpenGL-Project: CMakeFiles/OpenGL-Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/doqin/Projects/OpenGL-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable OpenGL-Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGL-Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGL-Project.dir/build: OpenGL-Project
.PHONY : CMakeFiles/OpenGL-Project.dir/build

CMakeFiles/OpenGL-Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGL-Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGL-Project.dir/clean

CMakeFiles/OpenGL-Project.dir/depend:
	cd /Users/doqin/Projects/OpenGL-Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/doqin/Projects/OpenGL-Project /Users/doqin/Projects/OpenGL-Project /Users/doqin/Projects/OpenGL-Project/build /Users/doqin/Projects/OpenGL-Project/build /Users/doqin/Projects/OpenGL-Project/build/CMakeFiles/OpenGL-Project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/OpenGL-Project.dir/depend

