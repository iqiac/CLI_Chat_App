#include "CommandCreator.h"

#include "EditorControlCommands.h"
#include "MoveCursorCommands.h"

CommandCreator::CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer) :
_commandMap({}) {
  // Cursor movement commands
  _commandMap["\x1b[A"] = [&cursorManager] { return std::make_unique<MoveCursorUp>(cursorManager); };
  _commandMap["\x1b[B"] = [&cursorManager] { return std::make_unique<MoveCursorDown>(cursorManager); };
  _commandMap["\x1b[D"] = [&cursorManager] { return std::make_unique<MoveCursorLeft>(cursorManager); };
  _commandMap["\x1b[C"] = [&cursorManager] { return std::make_unique<MoveCursorRight>(cursorManager); };

  // Editor control commands
  _commandMap["\033"] = [&screenRenderer] { return std::make_unique<ExitEditor>(screenRenderer); };

  // Text modification commands
}

CommandMap CommandCreator::GetCommandMap() {
  return _commandMap;
}
