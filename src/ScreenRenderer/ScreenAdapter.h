#pragma once
#include "IScreen.h"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

class ScreenAdapter : public IScreen {
public:
  explicit ScreenAdapter(ftxui::ScreenInteractive& screen) : _screen(screen) {
    _textBox = ftxui::Renderer([this] { return this->RenderText(); });
  }

  void Loop() override;
  void Exit() override;
  void SetCursor(const Position& position) override;
  void SetText(const std::vector<Line>& lines) override;

private:
  [[nodiscard]] ftxui::Element RenderText() const;

  ftxui::ScreenInteractive& _screen;
  ftxui::Component          _textBox;
  std::vector<Line>         _allLines;
};
