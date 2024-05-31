# Setup libraries from subdirectories
add_library(ObserverPattern STATIC
  ObserverPattern/ISubject.cpp
  ObserverPattern/IObserver.cpp
)
target_include_directories(ObserverPattern PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ObserverPattern
)

add_library(TextBuffer STATIC
  TextBuffer/TextBuffer.cpp
)
target_include_directories(TextBuffer PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ObserverPattern
)

add_library(CursorManager STATIC
  CursorManager/CursorManager.cpp
)
target_include_directories(CursorManager PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ObserverPattern
  TextBuffer
)

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

# Setup main executable
add_executable(${CMAKE_PROJECT_NAME})
target_sources(
  ${CMAKE_PROJECT_NAME} PRIVATE
  main.cpp
)

target_link_libraries(
  ${CMAKE_PROJECT_NAME} PRIVATE
  ObserverPattern
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
