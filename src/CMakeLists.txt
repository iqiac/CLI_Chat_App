# Setup libraries from subdirectories

# Setup main executable
add_executable(${CMAKE_PROJECT_NAME})
target_sources(
  ${CMAKE_PROJECT_NAME} PRIVATE
  main.cpp
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE
)

# Setup testing
enable_testing()
message(STATUS "Enable testing with GoogleTest")
set(TEST_NAME ${CMAKE_PROJECT_NAME}_test)

add_executable(${TEST_NAME})
target_sources(
  ${TEST_NAME} PRIVATE
  test_main.cpp
)

target_link_libraries(
  ${TEST_NAME} PRIVATE
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

add_custom_target(
  ${TEST_NAME}_execution ALL
  DEPENDS ${TEST_NAME}
)

add_custom_command(
  TARGET ${TEST_NAME}_execution
  POST_BUILD
  COMMAND ctest --output-on-failure
  VERBATIM
)
