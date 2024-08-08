#pragma once

#include "IObserver.h"
#include "IScreen.h"
#include "IScreenRenderer.h"
#include "ISubject.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

class ScreenRenderer : public IScreenRenderer, public IObserver<std::vector<Line>>, public IObserver<Position> {
public:
  explicit ScreenRenderer(IScreen& screen) : _screen(screen) {
    _textBox = ftxui::Renderer([this] { return this->RenderText(); });
  }

  void Update(const ISubject<std::vector<Line>>& subject) override;
  void Update(const ISubject<Position>& subject) override;
  void Loop() override;
  void Exit() override;

private:
  [[nodiscard]] ftxui::Element RenderText() const;

  IScreen&          _screen;
  ftxui::Component  _textBox;
  std::vector<Line> _allLines;
};
