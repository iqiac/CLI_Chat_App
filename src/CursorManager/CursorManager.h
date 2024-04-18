#pragma once

#include "ICursorManager.h"
#include "ISubject.h"
#include "ITextBuffer.h"

#include <map>
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

  void Attach(const std::string observerName, std::function<void()> updateFunction) override;
  void Detach(const std::string observerName) override;
  void Notify() const override;

private:
  std::size_t                                  _rowIndex;
  std::size_t                                  _colIndex;
  const ITextBuffer&                           _textBuffer;
  std::map<std::string, std::function<void()>> _observerUpdateFunctions;
};
