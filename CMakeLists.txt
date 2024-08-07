cmake_minimum_required(VERSION 3.5...3.25 FATAL_ERROR)
project(PONG C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

foreach(POL CMP0069 CMP0072 CMP0077)
  if(POLICY POL)
    cmake_policy(SET POL NEW)
  endif()
endforeach()

include(CMakeDependentOption)

cmake_dependent_option(GLFW_BUILD_WIN32 "Build support for Win32" ON WIN32 OFF)
cmake_dependent_option(GLFW_BUILD_COCOA "Build support for Cocoa" ON APPLE OFF)
cmake_dependent_option(GLFW_BUILD_X11 "Build support for X11" ON
                       "UNIX;NOT APPLE" OFF)
cmake_dependent_option(GLFW_BUILD_WAYLAND "Build support for Wayland" ON
                       "UNIX;NOT APPLE" OFF)
cmake_dependent_option(
  GLFW_USE_HYBRID_HPG "Force use of high-performance GPU on hybrid systems" OFF
  WIN32 OFF)
cmake_dependent_option(USE_MSVC_RUNTIME_LIBRARY_DLL
                       "Use MSVC runtime library DLL" ON MSVC OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/modules")

if(GLFW_BUILD_WIN32)
  message(STATUS "Including Win32 support")
elseif(GLFW_BUILD_COCOA)
  message(STATUS "Including Cocoa support")
else()
  message(STATUS "Including X11 & Wayland support")
endif()

if(MSVC AND NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
  if(CMAKE_VERSION VERSION_LESS 3.15)
    foreach(flag CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
                 CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

      if(flag MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
      endif()
      if(flag MATCHES "/MDd")
        string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
      endif()

    endforeach()
  else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()
endif()

add_compile_options(-g;-O0;-Wall;-Wextra;-Wpedantic)

add_subdirectory(src/glad)
add_subdirectory(src/glfw)
add_subdirectory(src/pong)
