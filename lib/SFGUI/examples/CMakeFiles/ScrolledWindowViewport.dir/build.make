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
CMAKE_COMMAND = /snap/cmake/340/bin/cmake

# The command to remove a file.
RM = /snap/cmake/340/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/or/studio/c++/agarios/lib/SFGUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/or/studio/c++/agarios/lib/SFGUI

# Include any dependencies generated for this target.
include examples/CMakeFiles/ScrolledWindowViewport.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/ScrolledWindowViewport.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/ScrolledWindowViewport.dir/flags.make

examples/CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.o: examples/CMakeFiles/ScrolledWindowViewport.dir/flags.make
examples/CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.o: examples/ScrolledWindowViewport.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/or/studio/c++/agarios/lib/SFGUI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.o"
	cd /home/or/studio/c++/agarios/lib/SFGUI/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.o -c /home/or/studio/c++/agarios/lib/SFGUI/examples/ScrolledWindowViewport.cpp

examples/CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.i"
	cd /home/or/studio/c++/agarios/lib/SFGUI/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/or/studio/c++/agarios/lib/SFGUI/examples/ScrolledWindowViewport.cpp > CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.i

examples/CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.s"
	cd /home/or/studio/c++/agarios/lib/SFGUI/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/or/studio/c++/agarios/lib/SFGUI/examples/ScrolledWindowViewport.cpp -o CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.s

# Object files for target ScrolledWindowViewport
ScrolledWindowViewport_OBJECTS = \
"CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.o"

# External object files for target ScrolledWindowViewport
ScrolledWindowViewport_EXTERNAL_OBJECTS =

examples/ScrolledWindowViewport: examples/CMakeFiles/ScrolledWindowViewport.dir/ScrolledWindowViewport.cpp.o
examples/ScrolledWindowViewport: examples/CMakeFiles/ScrolledWindowViewport.dir/build.make
examples/ScrolledWindowViewport: lib/libsfgui.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libsfml-window.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libsfml-system.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libGL.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libSM.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libICE.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libX11.so
examples/ScrolledWindowViewport: /usr/lib/x86_64-linux-gnu/libXext.so
examples/ScrolledWindowViewport: examples/CMakeFiles/ScrolledWindowViewport.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/or/studio/c++/agarios/lib/SFGUI/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ScrolledWindowViewport"
	cd /home/or/studio/c++/agarios/lib/SFGUI/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ScrolledWindowViewport.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/ScrolledWindowViewport.dir/build: examples/ScrolledWindowViewport

.PHONY : examples/CMakeFiles/ScrolledWindowViewport.dir/build

examples/CMakeFiles/ScrolledWindowViewport.dir/clean:
	cd /home/or/studio/c++/agarios/lib/SFGUI/examples && $(CMAKE_COMMAND) -P CMakeFiles/ScrolledWindowViewport.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/ScrolledWindowViewport.dir/clean

examples/CMakeFiles/ScrolledWindowViewport.dir/depend:
	cd /home/or/studio/c++/agarios/lib/SFGUI && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/or/studio/c++/agarios/lib/SFGUI /home/or/studio/c++/agarios/lib/SFGUI/examples /home/or/studio/c++/agarios/lib/SFGUI /home/or/studio/c++/agarios/lib/SFGUI/examples /home/or/studio/c++/agarios/lib/SFGUI/examples/CMakeFiles/ScrolledWindowViewport.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/ScrolledWindowViewport.dir/depend
