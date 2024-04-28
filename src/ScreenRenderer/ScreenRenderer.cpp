#include "ScreenRenderer.h"

#include <ncurses.h>

void ScreenRenderer::Update(const EventMessage eventMessage) {
  switch (EventSender sender{eventMessage.eventSender}) {
    case EventSender::TEXT_BUFFER:
      RenderText(std::get<std::reference_wrapper<const std::vector<Line>>>(eventMessage.dataRef).get());
      break;

    case EventSender::CURSOR_MANAGER:
      RenderCursor(std::get<std::reference_wrapper<const Position>>(eventMessage.dataRef).get());
      break;
  }
}

void ScreenRenderer::RenderText(const std::vector<Line>& allLines) {
  attron(COLOR_PAIR(1));
  for (const auto& line : allLines) {
    printw("%s\n", line.c_str());
  }
  attroff(COLOR_PAIR(1));
  refresh();
}

void ScreenRenderer::RenderCursor(const Position& cursorPosition) {
  move(cursorPosition.rowIndex, cursorPosition.colIndex);
  refresh();
}
