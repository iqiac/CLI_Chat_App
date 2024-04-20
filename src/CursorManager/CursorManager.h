#pragma once

#include "ICursorManager.h"
#include "ITextBuffer.h"

#include <utility>

class CursorManager : public ICursorManager {
public:
  explicit CursorManager(const ITextBuffer& textBuffer) : _textBuffer(textBuffer) {}

  void MoveCursorUp() override;
  void MoveCursorDown() override;
  void MoveCursorLeft() override;
  void MoveCursorRight() override;

  void SetCursorPosition(const std::size_t rowIndex, const std::size_t colIndex) override;

  std::pair<std::size_t, std::size_t> GetCursorPosition() const override;

private:
  std::size_t        _rowIndex;
  std::size_t        _colIndex;
  const ITextBuffer& _textBuffer;
};
