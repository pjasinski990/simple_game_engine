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

# Include any dependencies generated for this target.
include CMakeFiles\GLAD.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\GLAD.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\GLAD.dir\flags.make

CMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.obj: CMakeFiles\GLAD.dir\flags.make
CMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.obj: ..\dependencies\glad\src\glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/GLAD.dir/dependencies/glad/src/glad.c.obj"
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.obj /FdCMakeFiles\GLAD.dir\GLAD.pdb /FS -c C:\dev\c_cpp\mrld_engine\dependencies\glad\src\glad.c
<<

CMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GLAD.dir/dependencies/glad/src/glad.c.i"
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\c_cpp\mrld_engine\dependencies\glad\src\glad.c
<<

CMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GLAD.dir/dependencies/glad/src/glad.c.s"
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.s /c C:\dev\c_cpp\mrld_engine\dependencies\glad\src\glad.c
<<

# Object files for target GLAD
GLAD_OBJECTS = \
"CMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.obj"

# External object files for target GLAD
GLAD_EXTERNAL_OBJECTS =

GLAD.lib: CMakeFiles\GLAD.dir\dependencies\glad\src\glad.c.obj
GLAD.lib: CMakeFiles\GLAD.dir\build.make
GLAD.lib: CMakeFiles\GLAD.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library GLAD.lib"
	$(CMAKE_COMMAND) -P CMakeFiles\GLAD.dir\cmake_clean_target.cmake
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /lib /nologo /machine:X86 /out:GLAD.lib @CMakeFiles\GLAD.dir\objects1.rsp 

# Rule to build all files generated by this target.
CMakeFiles\GLAD.dir\build: GLAD.lib

.PHONY : CMakeFiles\GLAD.dir\build

CMakeFiles\GLAD.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GLAD.dir\cmake_clean.cmake
.PHONY : CMakeFiles\GLAD.dir\clean

CMakeFiles\GLAD.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\dev\c_cpp\mrld_engine C:\dev\c_cpp\mrld_engine C:\dev\c_cpp\mrld_engine\cmake-build-debug C:\dev\c_cpp\mrld_engine\cmake-build-debug C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles\GLAD.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\GLAD.dir\depend
