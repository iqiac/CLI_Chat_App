#pragma once

#include "ICursorManager.hpp"
#include "ISubject.hpp"
#include "ITextBuffer.hpp"

class CursorManager : public ICursorManager, public ISubject<Position> {
public:
  explicit CursorManager(const ITextBuffer& textBuffer) : _textBuffer(textBuffer) {}

  void MoveCursorUp(std::size_t amount = 1) override;
  void MoveCursorDown(std::size_t amount = 1) override;
  void MoveCursorLeft(std::size_t amount = 1) override;
  void MoveCursorRight(std::size_t amount = 1) override;

  void SetCursorPosition(Position position) override;

  [[nodiscard]] Position GetCursorPosition() const override;

  [[nodiscard]] Position GetData() const override;
  void                   Notify() const override;

private:
  std::size_t        _rowIndex{0};
  std::size_t        _colIndex{0};
  const ITextBuffer& _textBuffer;
};
