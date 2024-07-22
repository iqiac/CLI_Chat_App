#pragma once

#include "ICursorManager.h"
#include "ISubject.h"
#include "ITextBuffer.h"

class CursorManager : public ICursorManager, public ISubject<Position> {
public:
  explicit CursorManager(const ITextBuffer& textBuffer) : _textBuffer(textBuffer) {}

  void MoveCursorUp(const std::size_t amount = 1) override;
  void MoveCursorDown(const std::size_t amount = 1) override;
  void MoveCursorLeft(const std::size_t amount = 1) override;
  void MoveCursorRight(const std::size_t amount = 1) override;

  void SetCursorPosition(const Position position) override;

  Position GetCursorPosition() const override;

  Position GetData() const override;
  void     Notify() const override;

private:
  std::size_t        _rowIndex{0};
  std::size_t        _colIndex{0};
  const ITextBuffer& _textBuffer;
};
