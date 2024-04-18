#include "ScreenRenderer.h"

#include <ncurses.h>
#include <stdexcept>
#include <vector>

void ScreenRenderer::Update() {
  RenderText();
  RenderCursor();
}

std::string ScreenRenderer::GetObserverName() const {
  return _observerName;
}

void ScreenRenderer::RenderText() {
  clear();
  auto i{0};
  for (const auto& line : _textBuffer.GetAllLines()) {
    mvprintw(i, 0, "%s", line.c_str());
    i++;
  }
  refresh();
}

void ScreenRenderer::RenderCursor() {
  const auto [rowIndex, colIndex]{_cursorManager.GetCursorPosition()};
  move(rowIndex, colIndex);
  chgat(1, A_REVERSE, 0, NULL);
  refresh();
}
