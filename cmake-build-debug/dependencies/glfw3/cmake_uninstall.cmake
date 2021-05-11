
if (NOT EXISTS "C:/dev/c_cpp/mrld_engine/cmake-build-debug/dependencies/glfw3/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"C:/dev/c_cpp/mrld_engine/cmake-build-debug/dependencies/glfw3/install_manifest.txt\"")
endif()

file(READ "C:/dev/c_cpp/mrld_engine/cmake-build-debug/dependencies/glfw3/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("C:/Users/Piotr/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/win/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("C:/Users/Piotr/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/win/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

