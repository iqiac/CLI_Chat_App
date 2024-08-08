#include "MoveCursorCommands.h"

void MoveCursorUp::Execute() const {
  _cursorManager.MoveCursorUp(_amount);
}

void MoveCursorDown::Execute() const {
  _cursorManager.MoveCursorDown(_amount);
}

void MoveCursorLeft::Execute() const {
  _cursorManager.MoveCursorLeft(_amount);
}

void MoveCursorRight::Execute() const {
  _cursorManager.MoveCursorRight(_amount);
}
