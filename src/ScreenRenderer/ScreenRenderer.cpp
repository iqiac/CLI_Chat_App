#include "ScreenRenderer.h"

#include <ncurses.h>
#include <stdexcept>
#include <vector>

void ScreenRenderer::Update() {
  RenderText();
  RenderCursor();
}

void ScreenRenderer::RenderText() {
  // clear();
  // auto i{0};
  // for (const auto& line : _textBufferContent->GetTextBuffer()) {
  //   mvprintw(i, 0, "%s", line.c_str());
  //   i++;
  // }
  // refresh();
}

void ScreenRenderer::RenderCursor() {
  // const auto [rowIndex, colIndex]{_cursorManagerInfo->GetCursorPosition()};
  // move(rowIndex, colIndex);
  // chgat(1, A_REVERSE, 0, NULL);
  // refresh();
}
