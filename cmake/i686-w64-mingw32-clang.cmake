# Define the environment for cross-compiling with 32-bit MinGW-w64 Clang
set(CMAKE_SYSTEM_NAME Windows) # Target system name
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_C_COMPILER "i686-w64-mingw32-clang")
set(CMAKE_CXX_COMPILER "i686-w64-mingw32-clang++")
set(CMAKE_RC_COMPILER "i686-w64-mingw32-windres")
set(CMAKE_RANLIB "i686-w64-mingw32-ranlib")

# Configure the behaviour of the find commands
set(CMAKE_FIND_ROOT_PATH "/usr/i686-w64-mingw32")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
