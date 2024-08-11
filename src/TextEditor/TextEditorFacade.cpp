#include "TextEditorFacade.hpp"

#include <fstream>

namespace {
[[nodiscard]] std::optional<std::vector<Line>> GetLinesFromFile(std::string filePath);

std::optional<std::vector<Line>> GetLinesFromFile(const std::string filePath) {
  // Open file
  std::ifstream file(filePath);
  if (!file.is_open()) {
    return std::nullopt;
  }

  // Store file content into appropriate format
  std::vector<Line> lines;
  Line              line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  file.close();

  return lines;
}
} // namespace

TextEditorFacade::TextEditorFacade(const std::string filePath) {
  _lines = GetLinesFromFile(filePath);
}

void TextEditorFacade::Run() {}
