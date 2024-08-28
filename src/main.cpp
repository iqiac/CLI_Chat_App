#include "CursorManager.hpp"
#include "InputHandler.hpp"
#include "InputHandler/CommandPattern/CommandCreator.hpp"
#include "ScreenAdapter.hpp"
#include "ScreenRenderer.hpp"
#include "TextBuffer.hpp"

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
  const std::string filepath{argv[1]};
  std::ifstream     file(filepath);
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
  ScreenAdapter screenAdapter{};
  TextBuffer    textBuffer{lines};
  CursorManager cursorManager{textBuffer};
  auto          screenRenderer{std::make_shared<ScreenRenderer>(screenAdapter)};
  textBuffer.Attach(screenRenderer);
  cursorManager.Attach(screenRenderer);
  const CommandCreator commandCreator{textBuffer, cursorManager, *screenRenderer};
  InputHandler         inputHandler{commandCreator.GetCommandMap()};

  // Run TextEditor
  inputHandler.Start();
  screenRenderer->Start();

  // Stop TextEditor
  inputHandler.Stop();

  return 0;
}
