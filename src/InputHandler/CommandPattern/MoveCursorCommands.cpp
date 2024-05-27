#include "MoveCursorCommands.h"

void MoveCursorUp::Execute() const {
  _cursorManager.MoveCursorUp();
}

void MoveCursorDown::Execute() const {
  _cursorManager.MoveCursorDown();
}

void MoveCursorLeft::Execute() const {
  _cursorManager.MoveCursorLeft();
}

void MoveCursorRight::Execute() const {
  _cursorManager.MoveCursorRight();
}
