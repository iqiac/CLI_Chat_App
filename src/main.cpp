#include "CursorManager.h"
#include "InputHandler.h"
#include "InputHandler/CommandPattern/CommandCreator.h"
#include "ScreenAdapter.h"
#include "ScreenRenderer.h"
#include "TextBuffer.h"

#include <fstream>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/terminal.hpp>
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

  // Setup screen
  const auto [dimX, dimY]{ftxui::Terminal::Size()};
  auto screen = ftxui::ScreenInteractive::FixedSize(dimX, dimY); // Fixed size for now. Need to adjust components to fixed size
  screen.TrackMouse(false);
  ScreenAdapter screenAdapter{screen};

  // Initialize the components
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
