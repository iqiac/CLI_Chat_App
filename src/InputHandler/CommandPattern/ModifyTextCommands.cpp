#include "ModifyTextCommands.h"

void InsertText::Execute() const {
  _textBuffer.InsertText(_cursorManager.GetCursorPosition(), _text);
  _cursorManager.MoveCursorRight(_text.size());
}
