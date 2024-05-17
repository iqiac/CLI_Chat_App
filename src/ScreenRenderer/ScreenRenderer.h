#pragma once

#include "IScreenRenderer.h"
#include "Observer.h"

#include <ftxui/component/screen_interactive.hpp>

class ScreenRenderer : public IScreenRenderer, public Observer {
public:
  ScreenRenderer(ftxui::ScreenInteractive& screen) : _screen(screen) {
    _observerName = "ScreenRenderer";
  }

  void Update(const EventMessage eventMessage) override;
  void Loop() override;

private:
  void UpdateText(const std::vector<Line>& allLines) override;
  void UpdateCursor(const Position& cursorPosition) override;

  ftxui::ScreenInteractive& _screen;
  ftxui::Component          _textBox;
};
