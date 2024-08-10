#include "ScreenAdapter.h"

#include "CommonTypes.h"

#include <ftxui/component/component_base.hpp>
#include <ftxui/screen/screen.hpp>
#include <limits>
#include <stdexcept>

void ScreenAdapter::Loop(ftxui::Component component) {
  _screen.Loop(component);
}

void ScreenAdapter::Exit() {
  _screen.Exit();
}

void ScreenAdapter::SetCursor(const Position position) {
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

void ScreenAdapter::PostEvent(const ftxui::Event event) {
  _screen.PostEvent(event);
}
