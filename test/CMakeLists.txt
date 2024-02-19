message(STATUS "Enable testing with GoogleTest")

set(TEST_NAME ${PROJECT_NAME}_test)

add_executable(
  ${TEST_NAME}
  test_main.cpp
  CalculatorTest.cpp
)

target_include_directories(
  ${TEST_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/test
)

target_link_libraries(${TEST_NAME} SrcLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

add_custom_target(
  ${TEST_NAME}_execution ALL
  DEPENDS ${TEST_NAME}
)

add_custom_command(
  TARGET ${TEST_NAME}_execution
  POST_BUILD
  COMMAND ctest --output-on-failure -V
  VERBATIM
)
