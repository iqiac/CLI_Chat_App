#include "ScreenRenderer.h"

#include <exception>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>

void ScreenRenderer::Update(const EventMessage eventMessage) {
  switch (EventSender sender{eventMessage.eventSender}) {
    case EventSender::TEXT_BUFFER:
      UpdateText(std::get<std::reference_wrapper<const std::vector<Line>>>(eventMessage.dataRef).get());
      break;

    case EventSender::CURSOR_MANAGER:
      UpdateCursor(std::get<std::reference_wrapper<const Position>>(eventMessage.dataRef).get());
      break;
  }
}

void ScreenRenderer::Loop() {
  _screen.Loop(_textBox);
}

void ScreenRenderer::UpdateText(const std::vector<Line>& allLines) {
  using namespace ftxui;

  auto convert  = [](const Line& line) { return text(line); };
  auto elements = Elements();
  std::transform(allLines.begin(), allLines.end(), std::back_inserter(elements), convert);
  _textBox = Renderer([elements] { return vbox(elements) | border; });

  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}

void ScreenRenderer::UpdateCursor(const Position& cursorPosition) {
  using namespace ftxui;

  const auto& [rowIndex, colIndex]{cursorPosition};
  if (rowIndex > std::numeric_limits<int>::max() || colIndex > std::numeric_limits<int>::max()) {
    throw std::overflow_error("Conversion would cause overflow");
  }
  const int posX = static_cast<int>(colIndex);
  const int posY = static_cast<int>(rowIndex);

  const Screen::Cursor cursor{.x = posX, .y = posY, .shape = Screen::Cursor::BlockBlinking};
  _screen.SetCursor(cursor);

  _screen.PostEvent(Event::Custom); // Request new frame to be drawn
}
