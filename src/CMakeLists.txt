add_library(SrcLib STATIC Calculator.cpp)

target_include_directories(SrcLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
