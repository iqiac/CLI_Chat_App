#pragma once

#include "CursorManagerInterfaces.h"
#include "TextBufferInterfaces.h"

#include <utility>

class CursorManager : public ICursorManagerInfo, ICursorManagerMovement {
public:
  explicit CursorManager(ITextBufferInfo& textBuffer) : _textBufferInfo(textBuffer) {}

  void MoveCursorUp() override;
  void MoveCursorDown() override;
  void MoveCursorLeft() override;
  void MoveCursorRight() override;

  void SetCursorPosition(const std::size_t rowIndex, const std::size_t colIndex) override;

  std::pair<std::size_t, std::size_t> GetCursorPosition() const override;

private:
  std::size_t      _rowIndex;
  std::size_t      _colIndex;
  ITextBufferInfo& _textBufferInfo;
};
