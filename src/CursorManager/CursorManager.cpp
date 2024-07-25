#include "CursorManager.h"

void CursorManager::MoveCursorUp(const std::size_t amount) {
  if (amount > _rowIndex) {
    SetCursorPosition({0, _colIndex});
    return;
  }
  SetCursorPosition({_rowIndex - amount, _colIndex});
}

void CursorManager::MoveCursorDown(const std::size_t amount) {
  // TODO: Don't write outside borders
  SetCursorPosition({_rowIndex + amount, _colIndex});
}

void CursorManager::MoveCursorLeft(const std::size_t amount) {
  if (amount > _colIndex) {
    SetCursorPosition({_rowIndex, 0});
    return;
  }
  SetCursorPosition({_rowIndex, _colIndex - amount});
}

void CursorManager::MoveCursorRight(const std::size_t amount) {
  // TODO: Don't write outside borders
  SetCursorPosition({_rowIndex, _colIndex + amount});
}

void CursorManager::SetCursorPosition(const Position position) {
  const auto& [rowIndex, colIndex]{position.GetRowAndColIndices()};

  const auto numberOfLines{_textBuffer.GetNumberOfLines()};
  const auto validRowIndex{std::min(rowIndex, numberOfLines - 1)};

  const auto numberOfCols{_textBuffer.GetLineLength(validRowIndex)};
  const auto validColIndex{std::min(colIndex, numberOfCols)};

  _rowIndex = validRowIndex;
  _colIndex = validColIndex;

  Notify();
}

auto CursorManager::GetCursorPosition() const -> Position {
  return {_rowIndex, _colIndex};
}

auto CursorManager::GetData() const -> Position {
  return GetCursorPosition();
}

void CursorManager::Notify() const {
  ISubject::Notify();
}
