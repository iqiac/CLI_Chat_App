#pragma once

#include "IScreen.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

class ScreenAdapter : public IScreen {
public:
  explicit ScreenAdapter();

  void Start() override;
  void Stop() override;
  void SetCursor(const Position& position) override;
  void SetText(const std::vector<Line>& lines) override;

private:
  [[nodiscard]] ftxui::Element RenderText() const;

  ftxui::ScreenInteractive _screen;
  ftxui::Component         _textBox;
  std::vector<Line>        _allLines;
};
