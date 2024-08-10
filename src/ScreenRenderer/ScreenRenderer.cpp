#include "ScreenRenderer.h"

#include "CommonTypes.h"
#include "ISubject.h"

#include <ftxui/dom/elements.hpp>
#include <vector>

void ScreenRenderer::Loop() {
  _screenAdapter.Loop(_textBox);
}

void ScreenRenderer::Exit() {
  _screenAdapter.Exit();
}

void ScreenRenderer::Update(const ISubject<std::vector<Line>>& subject) {
  using namespace ftxui;

  _allLines = subject.GetData();
  _screenAdapter.PostEvent(Event::Custom); // Request new frame to be drawn
}

void ScreenRenderer::Update(const ISubject<Position>& subject) {
  const auto cursorPosition{subject.GetData()};
  _screenAdapter.SetCursor(cursorPosition);
}

[[nodiscard]] ftxui::Element ScreenRenderer::RenderText() const {
  ftxui::Elements elements;
  for (const auto& line : _allLines) {
    elements.push_back(ftxui::text(line));
  }
  return ftxui::vbox(elements) | ftxui::border;
}
