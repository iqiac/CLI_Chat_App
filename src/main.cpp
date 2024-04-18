// Core Components
// 1. Text Buffer: A data structure to hold the text being edited.
// 2. Cursor: A component to keep track of the current position in the text buffer.
// 3. Command Handling: A mechanism to interpret user inputs as commands.
// 4. Screen Rendering: A component to display the text buffer and cursor in the terminal.

#include "CursorManager.h"
#include "ScreenRenderer.h"
#include "TextBuffer.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

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

  // Initialize the components
  TextBuffer            textBuffer{lines};
  CursorManager         cursorManager{textBuffer};
  ScreenRenderer        screenRenderer{textBuffer, cursorManager};
  std::function<void()> screenRendererUpdate = [&screenRenderer]() { screenRenderer.Update(); };
  textBuffer.Attach(screenRenderer.GetObserverName(), screenRendererUpdate);
  cursorManager.Attach(screenRenderer.GetObserverName(), screenRendererUpdate);
  screenRenderer.Update();

  // Run TextEditor
  bool running{true};
  while (running) {
    char input;
    std::cin >> input;
    if (input == 'q') {
      running = false;
    }
    // Sleep for short duration to prevent high CPU usage
    usleep(100000);
  }

  return 0;
}
