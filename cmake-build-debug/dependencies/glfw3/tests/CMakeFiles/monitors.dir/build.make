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
include dependencies\glfw3\tests\CMakeFiles\monitors.dir\depend.make

# Include the progress variables for this target.
include dependencies\glfw3\tests\CMakeFiles\monitors.dir\progress.make

# Include the compile flags for this target's objects.
include dependencies\glfw3\tests\CMakeFiles\monitors.dir\flags.make

dependencies\glfw3\tests\CMakeFiles\monitors.dir\monitors.c.obj: dependencies\glfw3\tests\CMakeFiles\monitors.dir\flags.make
dependencies\glfw3\tests\CMakeFiles\monitors.dir\monitors.c.obj: ..\dependencies\glfw3\tests\monitors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object dependencies/glfw3/tests/CMakeFiles/monitors.dir/monitors.c.obj"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\monitors.dir\monitors.c.obj /FdCMakeFiles\monitors.dir\ /FS -c C:\dev\c_cpp\mrld_engine\dependencies\glfw3\tests\monitors.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\monitors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/monitors.c.i"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\monitors.dir\monitors.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\c_cpp\mrld_engine\dependencies\glfw3\tests\monitors.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\monitors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/monitors.c.s"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\monitors.dir\monitors.c.s /c C:\dev\c_cpp\mrld_engine\dependencies\glfw3\tests\monitors.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\getopt.c.obj: dependencies\glfw3\tests\CMakeFiles\monitors.dir\flags.make
dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\getopt.c.obj: ..\dependencies\glfw3\deps\getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object dependencies/glfw3/tests/CMakeFiles/monitors.dir/__/deps/getopt.c.obj"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\monitors.dir\__\deps\getopt.c.obj /FdCMakeFiles\monitors.dir\ /FS -c C:\dev\c_cpp\mrld_engine\dependencies\glfw3\deps\getopt.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/__/deps/getopt.c.i"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\monitors.dir\__\deps\getopt.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\c_cpp\mrld_engine\dependencies\glfw3\deps\getopt.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/__/deps/getopt.c.s"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\monitors.dir\__\deps\getopt.c.s /c C:\dev\c_cpp\mrld_engine\dependencies\glfw3\deps\getopt.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\glad_gl.c.obj: dependencies\glfw3\tests\CMakeFiles\monitors.dir\flags.make
dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\glad_gl.c.obj: ..\dependencies\glfw3\deps\glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object dependencies/glfw3/tests/CMakeFiles/monitors.dir/__/deps/glad_gl.c.obj"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\monitors.dir\__\deps\glad_gl.c.obj /FdCMakeFiles\monitors.dir\ /FS -c C:\dev\c_cpp\mrld_engine\dependencies\glfw3\deps\glad_gl.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/__/deps/glad_gl.c.i"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\monitors.dir\__\deps\glad_gl.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\c_cpp\mrld_engine\dependencies\glfw3\deps\glad_gl.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/__/deps/glad_gl.c.s"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\monitors.dir\__\deps\glad_gl.c.s /c C:\dev\c_cpp\mrld_engine\dependencies\glfw3\deps\glad_gl.c
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

# Object files for target monitors
monitors_OBJECTS = \
"CMakeFiles\monitors.dir\monitors.c.obj" \
"CMakeFiles\monitors.dir\__\deps\getopt.c.obj" \
"CMakeFiles\monitors.dir\__\deps\glad_gl.c.obj"

# External object files for target monitors
monitors_EXTERNAL_OBJECTS =

dependencies\glfw3\tests\monitors.exe: dependencies\glfw3\tests\CMakeFiles\monitors.dir\monitors.c.obj
dependencies\glfw3\tests\monitors.exe: dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\getopt.c.obj
dependencies\glfw3\tests\monitors.exe: dependencies\glfw3\tests\CMakeFiles\monitors.dir\__\deps\glad_gl.c.obj
dependencies\glfw3\tests\monitors.exe: dependencies\glfw3\tests\CMakeFiles\monitors.dir\build.make
dependencies\glfw3\tests\monitors.exe: dependencies\glfw3\src\glfw3.lib
dependencies\glfw3\tests\monitors.exe: dependencies\glfw3\tests\CMakeFiles\monitors.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\dev\c_cpp\mrld_engine\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable monitors.exe"
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	C:\Users\Piotr\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\202.7660.37\bin\cmake\win\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\monitors.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~3\2019\BUILDT~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\monitors.dir\objects1.rsp @<<
 /out:monitors.exe /implib:monitors.lib /pdb:C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests\monitors.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  ..\src\glfw3.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug

# Rule to build all files generated by this target.
dependencies\glfw3\tests\CMakeFiles\monitors.dir\build: dependencies\glfw3\tests\monitors.exe

.PHONY : dependencies\glfw3\tests\CMakeFiles\monitors.dir\build

dependencies\glfw3\tests\CMakeFiles\monitors.dir\clean:
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests
	$(CMAKE_COMMAND) -P CMakeFiles\monitors.dir\cmake_clean.cmake
	cd C:\dev\c_cpp\mrld_engine\cmake-build-debug
.PHONY : dependencies\glfw3\tests\CMakeFiles\monitors.dir\clean

dependencies\glfw3\tests\CMakeFiles\monitors.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\dev\c_cpp\mrld_engine C:\dev\c_cpp\mrld_engine\dependencies\glfw3\tests C:\dev\c_cpp\mrld_engine\cmake-build-debug C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests C:\dev\c_cpp\mrld_engine\cmake-build-debug\dependencies\glfw3\tests\CMakeFiles\monitors.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : dependencies\glfw3\tests\CMakeFiles\monitors.dir\depend

