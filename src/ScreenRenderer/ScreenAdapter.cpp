#include "ScreenAdapter.hpp"

#include "CommonTypes.hpp"

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <limits>
#include <stdexcept>
#include <vector>

void ScreenAdapter::Start() {
  _screen.Loop(_textBox);
}

void ScreenAdapter::Stop() {
  _screen.Exit();
}

void ScreenAdapter::SetCursor(const Position& position) {
  using namespace ftxui;

  const auto& [rowIndex, colIndex]{position.GetRowAndColIndices()};
  if (rowIndex > std::numeric_limits<int>::max() || colIndex > std::numeric_limits<int>::max()) {
    throw std::overflow_error("Conversion would cause overflow");
  }
  const int posX = static_cast<int>(colIndex + 1); // +1 because of border, cast because ftxui::Cursor expects int
  const int posY = static_cast<int>(rowIndex + 1); // +1 because of border, cast because ftxui::Cursor expects int

  const Screen::Cursor cursor{.x = posX, .y = posY, .shape = Screen::Cursor::BlockBlinking};
  _screen.SetCursor(cursor);

  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}

void ScreenAdapter::SetText(const std::vector<Line>& lines) {
  using namespace ftxui;

  _allLines = lines;
  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}

[[nodiscard]] ftxui::Element ScreenAdapter::RenderText() const {
  ftxui::Elements elements;
  for (const auto& line : _allLines) {
    elements.push_back(ftxui::text(line));
  }
  return ftxui::vbox(elements) | ftxui::border;
}
