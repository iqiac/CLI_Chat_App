#pragma once

#include "IObserver.h"
#include "IScreen.h"
#include "IScreenRenderer.h"

class ScreenRenderer : public IScreenRenderer, public IObserver<std::vector<Line>>, public IObserver<Position> {
public:
  explicit ScreenRenderer(IScreen& screen) : _screen(screen) {}

  void Update(const ISubjectDataGetter<std::vector<Line>>& subject) override;
  void Update(const ISubjectDataGetter<Position>& subject) override;
  void Loop() override;

private:
  IScreen&         _screen;
  ftxui::Component _textBox;
};
