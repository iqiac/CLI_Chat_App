#include "CursorManager.h"
#include "ScreenAdapter.h"
#include "ScreenRenderer.h"
#include "TextBuffer.h"

#include <fstream>

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

  // Run TextEditor
  screenRenderer->Loop();

  return 0;
}
