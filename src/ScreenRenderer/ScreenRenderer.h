#pragma once

#include "IScreen.h"
#include "IScreenRenderer.h"
#include "Observer.h"

class ScreenRenderer : public IScreenRenderer, public Observer {
public:
  explicit ScreenRenderer(IScreen& screen) : _screen(screen) {
    _observerName = "ScreenRenderer";
  }

  void Update(const EventMessage& eventMessage) override;
  void Loop() override;

private:
  void UpdateText(const std::vector<Line>& allLines) override;
  void UpdateCursor(const Position& cursorPosition) override;

  IScreen&         _screen;
  ftxui::Component _textBox;
};
