#include "CursorManager.h"

void CursorManager::MoveCursorUp() {
  if (_rowIndex == 0) {
    return;
  }
  SetCursorPosition({_rowIndex - 1, _colIndex});
}

void CursorManager::MoveCursorDown() {
  SetCursorPosition({_rowIndex + 1, _colIndex});
}

void CursorManager::MoveCursorLeft() {
  if (_colIndex == 0) {
    return;
  }
  SetCursorPosition({_rowIndex, _colIndex - 1});
}

void CursorManager::MoveCursorRight() {
  SetCursorPosition({_rowIndex, _colIndex + 1});
}

void CursorManager::SetCursorPosition(const Position position) {
  const auto& [rowIndex, colIndex]{position};

  const auto numberOfLines{_textBuffer.GetNumberOfLines()};
  const auto validRowIndex{std::min(rowIndex, numberOfLines - 1)};

  const auto numberOfCols{_textBuffer.GetLineLength(validRowIndex)};
  const auto validColIndex{std::min(colIndex, numberOfCols)};

  _rowIndex = validRowIndex;
  _colIndex = validColIndex;
}

Position CursorManager::GetCursorPosition() const {
  return {_rowIndex, _colIndex};
}

void CursorManager::Notify() const {
  for (const auto& [_, updateFunction] : _observerUpdateFunctions) {
    const Position     newPosition{_rowIndex, _colIndex};
    const EventMessage message{.eventSender   = EventSender::CURSOR_MANAGER,
                               .dataReference = DataReference{std::ref(newPosition)}};
    updateFunction(message);
  }
}
