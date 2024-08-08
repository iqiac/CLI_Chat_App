#pragma once

#include "ICommand.h"
#include "ICursorManager.h"
#include "ITextBuffer.h"

class InsertText : public ICommand {
public:
  InsertText(ITextBuffer& textBuffer, ICursorManager& cursorManager, const std::string text) :
  _textBuffer(textBuffer),
  _cursorManager(cursorManager),
  _text(text) {}
  void Execute() const override;

private:
  ITextBuffer&      _textBuffer;
  ICursorManager&   _cursorManager;
  const std::string _text;
};
