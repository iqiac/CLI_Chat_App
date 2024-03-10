#include "CursorManager.h"

#include <stdexcept>

void CursorManager::MoveCursorUp() {
  if (_rowIndex == 0) {
    return;
  }
  _rowIndex--;
  _colIndex = std::min(_colIndex, _textBufferInfo.GetLineLength(_rowIndex));
}

void CursorManager::MoveCursorDown() {
  if (_rowIndex == _textBufferInfo.GetNumberOfLines() - 1) {
    return;
  }
  _rowIndex++;
  _colIndex = std::min(_colIndex, _textBufferInfo.GetLineLength(_rowIndex));
}

void CursorManager::MoveCursorLeft() {
  if (_colIndex == 0) {
    return;
  }
  _colIndex--;
}

void CursorManager::MoveCursorRight() {
  if (_colIndex == _textBufferInfo.GetLineLength(_rowIndex) - 1) {
    return;
  }
  _colIndex++;
}

void CursorManager::SetCursorPosition(const std::size_t rowIndex, const std::size_t colIndex) {
  if (rowIndex > _textBufferInfo.GetNumberOfLines()) {
    throw std::invalid_argument("Row index must be in range.");
  }
  if (colIndex > _textBufferInfo.GetLineLength(rowIndex)) {
    throw std::invalid_argument("Column index must be in range.");
  }
  _rowIndex = rowIndex;
  _colIndex = colIndex;
}

std::pair<std::size_t, std::size_t> CursorManager::GetCursorPosition() const {
  return {_rowIndex, _colIndex};
}
