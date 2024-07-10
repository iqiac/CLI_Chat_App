#include "ScreenRenderer.h"

#include <exception>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

void ScreenRenderer::Loop() {
  _screen.Loop(_textBox);
}

void ScreenRenderer::Exit() {
  _screen.Exit();
}

void ScreenRenderer::Update(const ISubject<std::vector<Line>>& subject) {
  using namespace ftxui;

  const auto& allLines = subject.GetData();
  auto        convert  = [](const Line& line) { return text(line); };
  auto        elements = Elements();
  std::transform(allLines.begin(), allLines.end(), std::back_inserter(elements), convert);
  _textBox = CatchEvent(Renderer([elements] { return vbox(elements) | border; }), [](Event event) { return true; });

  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}

void ScreenRenderer::Update(const ISubject<Position>& subject) {
  using namespace ftxui;

  const auto& [rowIndex, colIndex]{subject.GetData()};
  if (rowIndex > std::numeric_limits<int>::max() || colIndex > std::numeric_limits<int>::max()) {
    throw std::overflow_error("Conversion would cause overflow");
  }
  const int posX = static_cast<int>(colIndex + 1); // +1 because of border, cast because ftxui::Cursor expects int
  const int posY = static_cast<int>(rowIndex + 1); // +1 because of border, cast because ftxui::Cursor expects int

  const Screen::Cursor cursor{.x = posX, .y = posY, .shape = Screen::Cursor::BlockBlinking};
  _screen.SetCursor(cursor);

  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}
