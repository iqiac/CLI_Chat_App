cmake_minimum_required(VERSION 3.22)

project(
  ChatApp
  LANGUAGES CXX
  VERSION 0.1
)

# Set language standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use ccache for speedup
find_program(ccache "ccache")
if(ccache)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${ccache})
  message(STATUS "Using ${ccache}")
else()
  message(NOTICE "${ccache} not found")
endif(ccache)

# Add target and directories to search include files
add_subdirectory(src)

# Link executable to library
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} SrcLib)

# Program options
option(BUILD_UNITTESTS "Build unit tests" ON)
message(STATUS "BUILD_UNITTESTS       ${BUILD_UNITTESTS}")

# Include GoogleTest. Instructions from https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()
add_subdirectory(test)
