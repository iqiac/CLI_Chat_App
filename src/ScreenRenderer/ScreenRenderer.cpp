#include "ScreenRenderer.h"

#include <exception>

void ScreenRenderer::Loop() {
  _screen.Loop(_textBox);
}

void ScreenRenderer::Exit() {
  _screen.Exit();
}

void ScreenRenderer::Update(const ISubject<std::vector<Line>>& subject) {
  using namespace ftxui;

  _allLines = subject.GetData();
  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}

void ScreenRenderer::Update(const ISubject<Position>& subject) {
  using namespace ftxui;

  const auto& [rowIndex, colIndex]{subject.GetData().GetRowAndColIndices()};
  if (rowIndex > std::numeric_limits<int>::max() || colIndex > std::numeric_limits<int>::max()) {
    throw std::overflow_error("Conversion would cause overflow");
  }
  const int posX = static_cast<int>(colIndex + 1); // +1 because of border, cast because ftxui::Cursor expects int
  const int posY = static_cast<int>(rowIndex + 1); // +1 because of border, cast because ftxui::Cursor expects int

  const Screen::Cursor cursor{.x = posX, .y = posY, .shape = Screen::Cursor::BlockBlinking};
  _screen.SetCursor(cursor);

  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}

[[nodiscard]] ftxui::Element ScreenRenderer::RenderText() const {
  ftxui::Elements elements;
  for (const auto& line : _allLines) {
    elements.push_back(ftxui::text(line));
  }
  return ftxui::vbox(elements) | ftxui::border;
}
