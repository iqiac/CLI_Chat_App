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
  ScreenRenderer
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/TextBuffer
  ${CMAKE_CURRENT_SOURCE_DIR}/CursorManager
  ${CMAKE_CURRENT_SOURCE_DIR}/ScreenRenderer
)
