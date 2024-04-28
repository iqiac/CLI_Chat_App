#pragma once

#include "IScreenRenderer.h"
#include "Observer.h"

class ScreenRenderer : public IScreenRenderer, public Observer {
public:
  ScreenRenderer() {
    _observerName = "ScreenRenderer";
  }

  void Update(const EventMessage eventMessage) override;

private:
  void RenderText(const std::vector<Line>& allLines) override;
  void RenderCursor(const Position& cursorPosition) override;
};
