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
  std::shared_ptr<TextBuffer> textBuffer_ptr{std::make_shared<TextBuffer>()};

  std::shared_ptr<ITextBufferInfo> textBufferInfo_ptr{std::static_pointer_cast<ITextBufferInfo>(textBuffer_ptr)};
  std::shared_ptr<CursorManager>   cursorManager_ptr{std::make_shared<CursorManager>(textBufferInfo_ptr)};

  std::shared_ptr<ITextBufferContent> textBufferContent_ptr{std::static_pointer_cast<ITextBufferContent>(textBuffer_ptr)};
  std::shared_ptr<ICursorManagerInfo> cursorManagerInfo_ptr{std::static_pointer_cast<ICursorManagerInfo>(cursorManager_ptr)};
  std::shared_ptr<ScreenRenderer> screenRenderer_ptr{
      std::make_shared<ScreenRenderer>(textBufferContent_ptr, cursorManagerInfo_ptr)};

  return 0;
}
