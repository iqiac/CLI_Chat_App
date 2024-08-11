#pragma once

#include "CommonTypes.hpp"
#include "ITextEditor.hpp"

#include <optional>
#include <string>
#include <vector>

class TextEditorFacade : public ITextEditor {
public:
  TextEditorFacade() = default;
  explicit TextEditorFacade(std::string filePath);

  void Run() override;

private:
  std::optional<std::vector<Line>> _lines{std::nullopt};
};
