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

# Setup CommandPattern
add_library(CommandPattern STATIC
  InputHandler/CommandPattern/CommandCreator.cpp
  InputHandler/CommandPattern/MoveCursorCommands.cpp
  InputHandler/CommandPattern/EditorControlCommands.cpp
)
target_include_directories(CommandPattern PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  TextBuffer
  CursorManager
  ScreenRenderer
)
target_link_libraries(CommandPattern PRIVATE
  TextBuffer
  CursorManager
  ScreenRenderer
)

# Setup InputHandler
add_library(InputHandler STATIC
  InputHandler/InputHandler.cpp
)
target_include_directories(InputHandler PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
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
  CommandPattern
  InputHandler
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/TextBuffer
  ${CMAKE_CURRENT_SOURCE_DIR}/CursorManager
  ${CMAKE_CURRENT_SOURCE_DIR}/ScreenRenderer
  ${CMAKE_CURRENT_SOURCE_DIR}/InputHandler
)
