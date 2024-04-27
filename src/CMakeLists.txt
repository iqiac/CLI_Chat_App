# Setup libraries from subdirectories
add_library(TextBuffer SHARED TextBuffer/TextBuffer.cpp)
target_include_directories(TextBuffer PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(CursorManager SHARED CursorManager/CursorManager.cpp)
target_include_directories(CursorManager PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  TextBuffer
)

# Setup main executable
add_executable(${CMAKE_PROJECT_NAME})
target_sources(
  ${CMAKE_PROJECT_NAME} PRIVATE
  main.cpp
)

target_link_libraries(
  ${CMAKE_PROJECT_NAME} PRIVATE
  TextBuffer
  CursorManager
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/TextBuffer
  ${CMAKE_CURRENT_SOURCE_DIR}/CursorManager
)

# Setup testing
enable_testing()
message(STATUS "Enable testing with GoogleTest")
set(TEST_NAME ${CMAKE_PROJECT_NAME}_test)

add_executable(${TEST_NAME})
target_sources(
  ${TEST_NAME} PRIVATE
  test_main.cpp
  TextBuffer/TextBufferTest.cpp
  CursorManager/CursorManagerTest.cpp
)

target_include_directories(
  ${TEST_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/TextBuffer
  ${CMAKE_CURRENT_SOURCE_DIR}/CursorManager
)

target_link_libraries(
  ${TEST_NAME} PRIVATE
  GTest::gtest_main
  GTest::gmock_main
  TextBuffer
  CursorManager
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
