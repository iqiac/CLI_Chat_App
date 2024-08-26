#include "CommandCreator.hpp"

#include "EditorControlCommands.hpp"
#include "ICursorManager.hpp"
#include "ITextBuffer.hpp"
#include "ModifyTextCommands.hpp"
#include "MoveCursorCommands.hpp"
#include "ScreenRenderer.hpp"

CommandCreator::CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer) :
_commandMap({}) {
  MoveCursorCommands::RegisterCommands(_commandMap, cursorManager);
  EditorControlCommands::RegisterCommands(_commandMap, screenRenderer);
  ModifyTextCommands::RegisterCommands(_commandMap, cursorManager, textBuffer);
}

CommandPattern::CommandMap CommandCreator::GetCommandMap() const {
  return _commandMap;
}
