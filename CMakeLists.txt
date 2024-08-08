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

include(FetchContent)
# Include GoogleTest. Instructions from https://google.github.io/googletest/quickstart-cmake.html
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Include FTXUI. Instructions from https://arthursonzogni.github.io/FTXUI/
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# Enable clang-tidy
find_program(clangtidy NAMES "clang-tidy")
if(clangtidy)
  set(CMAKE_CXX_CLANG_TIDY ${clangtidy} "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
  message(STATUS "Using ${clangtidy}")
else()
  message(NOTICE "${clangtidy} not found")
endif(clangtidy)

# Add compile options
add_compile_options(
  -std=c++20
  -Werror
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Process subdirectories
add_subdirectory(src)
add_subdirectory(test)
