#include "ModifyTextCommands.h"

void InsertText::Execute() const {
  _textBuffer.InsertText(_cursorManager.GetCursorPosition(), _text);
  _cursorManager.MoveCursorRight(_text.size());
}

void RemoveTextBackward::Execute() const {
  const auto currentPosition{_cursorManager.GetCursorPosition()};
  if (currentPosition.GetColIndex() < _textSize) {
    return;
  }
  _cursorManager.MoveCursorLeft(_textSize);
  const auto newPosition{_cursorManager.GetCursorPosition()};
  _textBuffer.DeleteText(newPosition, _textSize);
}

void RemoveTextForward::Execute() const {
  const auto currentPosition{_cursorManager.GetCursorPosition()};
  _textBuffer.DeleteText(currentPosition, _textSize);
}
