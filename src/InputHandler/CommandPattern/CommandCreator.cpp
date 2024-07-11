#include "CommandCreator.h"

CommandCreator::CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer) :
_commandMap({}) {
  // Cursor movement commands
  _commandMap["\x1b[A"] = [&cursorManager] { return std::make_unique<MoveCursorUp>(cursorManager); };
  _commandMap["\x1b[B"] = [&cursorManager] { return std::make_unique<MoveCursorDown>(cursorManager); };
  _commandMap["\x1b[D"] = [&cursorManager] { return std::make_unique<MoveCursorLeft>(cursorManager); };
  _commandMap["\x1b[C"] = [&cursorManager] { return std::make_unique<MoveCursorRight>(cursorManager); };
}

CommandMap CommandCreator::GetCommandMap() {
  return _commandMap;
}
