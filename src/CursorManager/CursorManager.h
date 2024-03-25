#pragma once

#include "ICursorManager.h"
#include "ITextBuffer.h"
#include "ObserverPattern.h"

#include <memory>
#include <utility>

class CursorManager : public ICursorManager, ISubject {
public:
  explicit CursorManager(const ITextBuffer& textBuffer) : _textBuffer(textBuffer) {}

  void MoveCursorUp() override;
  void MoveCursorDown() override;
  void MoveCursorLeft() override;
  void MoveCursorRight() override;

  void SetCursorPosition(const Position position) override;

  Position GetCursorPosition() const override;

  void Attach(IObserver& observer) override;
  void Detach(IObserver& observer) override;
  void Notify() override;

private:
  std::size_t        _rowIndex;
  std::size_t        _colIndex;
  const ITextBuffer& _textBuffer;
};
