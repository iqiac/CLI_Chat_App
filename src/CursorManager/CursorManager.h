#pragma once

#include "ICursorManager.h"
#include "ITextBuffer.h"
#include "Subject.h"

#include <functional>
#include <map>

class CursorManager : public ICursorManager, public Subject {
public:
  explicit CursorManager(const ITextBuffer& textBuffer) : _textBuffer(textBuffer) {}

  void MoveCursorUp() override;
  void MoveCursorDown() override;
  void MoveCursorLeft() override;
  void MoveCursorRight() override;

  void SetCursorPosition(const Position position) override;

  Position GetCursorPosition() const override;

  void Notify() const override;

private:
  std::size_t        _rowIndex{0};
  std::size_t        _colIndex{0};
  const ITextBuffer& _textBuffer;
};
