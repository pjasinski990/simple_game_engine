# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Piotr\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7660.37\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Piotr\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7660.37\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\dev\c_cpp\mrld_engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\dev\c_cpp\mrld_engine\cmake-build-debug

# Utility rule file for glad-generate-files.

# Include the progress variables for this target.
include dependencies\glad\CMakeFiles\glad-generate-files.dir\progress.make

dependencies\glad\CMakeFiles\glad-generate-files: dependencies\glad\include\glad\glad.h
dependencies\glad\CMakeFiles\glad-generate-files: dependencies\glad\src\glad.c
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glad
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glad\include\glad\glad.h:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating GLAD"
	cd C:\dev\c_cpp\mrld_engine\dependencies\glad
	echo >nul && "C:\Program Files\WindowsApps\PythonSoftwareFoundation.Python.3.9_3.9.1520.0_x64__qbz5n2kfra8p0\python3.9.exe" -m glad --profile=compatibility --out-path=C:/dev/c_cpp/mrld_engine/cmake-build-debug/dependencies/glad --api= --generator=c --extensions= --spec=gl
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glad\src\glad.c: dependencies\glad\include\glad\glad.h
	@$(CMAKE_COMMAND) -E touch_nocreate dependencies\glad\src\glad.c

glad-generate-files: dependencies\glad\CMakeFiles\glad-generate-files
glad-generate-files: dependencies\glad\include\glad\glad.h
glad-generate-files: dependencies\glad\src\glad.c
glad-generate-files: dependencies\glad\CMakeFiles\glad-generate-files.dir\build.make

.PHONY : glad-generate-files

# Rule to build all files generated by this target.
dependencies\glad\CMakeFiles\glad-generate-files.dir\build: glad-generate-files

.PHONY : dependencies\glad\CMakeFiles\glad-generate-files.dir\build

dependencies\glad\CMakeFiles\glad-generate-files.dir\clean:
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glad
	$(CMAKE_COMMAND) -P CMakeFiles\glad-generate-files.dir\cmake_clean.cmake
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug
.PHONY : dependencies\glad\CMakeFiles\glad-generate-files.dir\clean

dependencies\glad\CMakeFiles\glad-generate-files.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\dev\c_cpp\mrld_engine C:\dev\c_cpp\mrld_engine\dependencies\glad C:\dev\c_cpp\mrld_engine\cmake-build-debug C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glad C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glad\CMakeFiles\glad-generate-files.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : dependencies\glad\CMakeFiles\glad-generate-files.dir\depend
