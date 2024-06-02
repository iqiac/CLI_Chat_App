// Core Components
// 1. Text Buffer: A data structure to hold the text being edited.
// 2. Cursor: A component to keep track of the current position in the text buffer.
// 3. Command Handling: A mechanism to interpret user inputs as commands.
// 4. Screen Rendering: A component to display the text buffer and cursor in the terminal.

#include "CursorManager.h"
#include "ScreenAdapter.h"
#include "ScreenRenderer.h"
#include "TextBuffer.h"

#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

using namespace ftxui;

int main(int argc, char* argv[]) {
  // Get filepath as argument
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filepath>\n";
    return 1;
  }

  // Open file
  std::string   filepath{argv[1]};
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filepath << "\n";
    return 1;
  }

  // Store file content into appropriate format
  std::vector<std::string> lines;
  std::string              line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  file.close();

  // Setup screen
  const auto [dimX, dimY]{Terminal::Size()};
  auto screen = ScreenInteractive::FixedSize(dimX, dimY); // Fixed size for now. Need to adjust components to fixed size
  screen.TrackMouse(false);
  ScreenAdapter screenAdapter{screen};

  // Initialize the components
  TextBuffer    textBuffer{lines};
  CursorManager cursorManager{textBuffer};
  auto          screenRenderer{std::make_shared<ScreenRenderer>(screenAdapter)};
  textBuffer.Attach(screenRenderer);
  cursorManager.Attach(screenRenderer);

  // Run TextEditor
  screenRenderer->Loop();

  return 0;
}
