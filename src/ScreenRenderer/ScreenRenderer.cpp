#include "ScreenRenderer.h"

#include <ncurses.h>
#include <stdexcept>
#include <vector>

void ScreenRenderer::Update() {}

void ScreenRenderer::RenderText() {
  clear();
  auto i{0};
  for (const auto& line : _textBufferContent.GetTextBuffer()) {
    mvprintw(i, 0, "%s", line.c_str());
  }
  refresh();
}

void ScreenRenderer::RenderCursor() {}
