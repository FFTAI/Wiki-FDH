# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/afer/project_user/dh/wiki-dh/c++/v1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/afer/project_user/dh/wiki-dh/c++/v1/build

# Include any dependencies generated for this target.
include CMakeFiles/GET_IP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GET_IP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GET_IP.dir/flags.make

CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.o: CMakeFiles/GET_IP.dir/flags.make
CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.o: ../source/demo_get_ip.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afer/project_user/dh/wiki-dh/c++/v1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.o -c /home/afer/project_user/dh/wiki-dh/c++/v1/source/demo_get_ip.cpp

CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afer/project_user/dh/wiki-dh/c++/v1/source/demo_get_ip.cpp > CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.i

CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afer/project_user/dh/wiki-dh/c++/v1/source/demo_get_ip.cpp -o CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.s

CMakeFiles/GET_IP.dir/source/dh.cpp.o: CMakeFiles/GET_IP.dir/flags.make
CMakeFiles/GET_IP.dir/source/dh.cpp.o: ../source/dh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afer/project_user/dh/wiki-dh/c++/v1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GET_IP.dir/source/dh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GET_IP.dir/source/dh.cpp.o -c /home/afer/project_user/dh/wiki-dh/c++/v1/source/dh.cpp

CMakeFiles/GET_IP.dir/source/dh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GET_IP.dir/source/dh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afer/project_user/dh/wiki-dh/c++/v1/source/dh.cpp > CMakeFiles/GET_IP.dir/source/dh.cpp.i

CMakeFiles/GET_IP.dir/source/dh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GET_IP.dir/source/dh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afer/project_user/dh/wiki-dh/c++/v1/source/dh.cpp -o CMakeFiles/GET_IP.dir/source/dh.cpp.s

CMakeFiles/GET_IP.dir/source/logger.cpp.o: CMakeFiles/GET_IP.dir/flags.make
CMakeFiles/GET_IP.dir/source/logger.cpp.o: ../source/logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afer/project_user/dh/wiki-dh/c++/v1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GET_IP.dir/source/logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GET_IP.dir/source/logger.cpp.o -c /home/afer/project_user/dh/wiki-dh/c++/v1/source/logger.cpp

CMakeFiles/GET_IP.dir/source/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GET_IP.dir/source/logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afer/project_user/dh/wiki-dh/c++/v1/source/logger.cpp > CMakeFiles/GET_IP.dir/source/logger.cpp.i

CMakeFiles/GET_IP.dir/source/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GET_IP.dir/source/logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afer/project_user/dh/wiki-dh/c++/v1/source/logger.cpp -o CMakeFiles/GET_IP.dir/source/logger.cpp.s

CMakeFiles/GET_IP.dir/source/os.cpp.o: CMakeFiles/GET_IP.dir/flags.make
CMakeFiles/GET_IP.dir/source/os.cpp.o: ../source/os.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afer/project_user/dh/wiki-dh/c++/v1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GET_IP.dir/source/os.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GET_IP.dir/source/os.cpp.o -c /home/afer/project_user/dh/wiki-dh/c++/v1/source/os.cpp

CMakeFiles/GET_IP.dir/source/os.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GET_IP.dir/source/os.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afer/project_user/dh/wiki-dh/c++/v1/source/os.cpp > CMakeFiles/GET_IP.dir/source/os.cpp.i

CMakeFiles/GET_IP.dir/source/os.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GET_IP.dir/source/os.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afer/project_user/dh/wiki-dh/c++/v1/source/os.cpp -o CMakeFiles/GET_IP.dir/source/os.cpp.s

# Object files for target GET_IP
GET_IP_OBJECTS = \
"CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.o" \
"CMakeFiles/GET_IP.dir/source/dh.cpp.o" \
"CMakeFiles/GET_IP.dir/source/logger.cpp.o" \
"CMakeFiles/GET_IP.dir/source/os.cpp.o"

# External object files for target GET_IP
GET_IP_EXTERNAL_OBJECTS =

../bin/GET_IP: CMakeFiles/GET_IP.dir/source/demo_get_ip.cpp.o
../bin/GET_IP: CMakeFiles/GET_IP.dir/source/dh.cpp.o
../bin/GET_IP: CMakeFiles/GET_IP.dir/source/logger.cpp.o
../bin/GET_IP: CMakeFiles/GET_IP.dir/source/os.cpp.o
../bin/GET_IP: CMakeFiles/GET_IP.dir/build.make
../bin/GET_IP: CMakeFiles/GET_IP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/afer/project_user/dh/wiki-dh/c++/v1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../bin/GET_IP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GET_IP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GET_IP.dir/build: ../bin/GET_IP

.PHONY : CMakeFiles/GET_IP.dir/build

CMakeFiles/GET_IP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GET_IP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GET_IP.dir/clean

CMakeFiles/GET_IP.dir/depend:
	cd /home/afer/project_user/dh/wiki-dh/c++/v1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/afer/project_user/dh/wiki-dh/c++/v1 /home/afer/project_user/dh/wiki-dh/c++/v1 /home/afer/project_user/dh/wiki-dh/c++/v1/build /home/afer/project_user/dh/wiki-dh/c++/v1/build /home/afer/project_user/dh/wiki-dh/c++/v1/build/CMakeFiles/GET_IP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GET_IP.dir/depend

