cmake_minimum_required(VERSION 3.22)

project(
  TextEditor
  LANGUAGES CXX
  VERSION 0.1
)

# Set language standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type
set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATIS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE)
endif()

# Use ccache for speedup
find_program(ccache "ccache")
if(ccache)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${ccache})
  message(STATUS "Using ${ccache}")
else()
  message(NOTICE "${ccache} not found")
endif(ccache)

# Include GoogleTest. Instructions from https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Add compile options
add_compile_options(
  -std=c++20
  -Werror
)

# Process subdirectories
add_subdirectory(src)
add_subdirectory(test)
