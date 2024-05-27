# Setup TextBuffer
add_library(TextBuffer STATIC
  TextBuffer/TextBuffer.cpp
)
target_include_directories(TextBuffer PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ObserverPattern
)

# Setup CursorManager
add_library(CursorManager STATIC
  CursorManager/CursorManager.cpp
)
target_include_directories(CursorManager PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ObserverPattern
  TextBuffer
)

# Setup ScreenRenderer
add_library(ScreenRenderer STATIC
  ScreenRenderer/ScreenRenderer.cpp
  ScreenRenderer/ScreenAdapter.cpp
)
target_include_directories(ScreenRenderer PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ObserverPattern
)
target_link_libraries(ScreenRenderer PUBLIC
  ftxui::component
  ftxui::dom
  ftxui::screen
)

# Setup InputHandler
add_library(InputHandler STATIC
  InputHandler/InputHandler.cpp
  InputHandler/CommandPattern/MoveCursorCommands.cpp
)
target_include_directories(InputHandler PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  TextBuffer
  CursorManager
)
target_link_libraries(InputHandler PUBLIC
  ftxui::component
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
  InputHandler
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/TextBuffer
  ${CMAKE_CURRENT_SOURCE_DIR}/CursorManager
  ${CMAKE_CURRENT_SOURCE_DIR}/ScreenRenderer
  ${CMAKE_CURRENT_SOURCE_DIR}/InputHandler
)
