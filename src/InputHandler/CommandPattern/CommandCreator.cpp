#include "CommandCreator.h"

#include "EditorControlCommands.h"
#include "ICursorManager.h"
#include "ITextBuffer.h"
#include "ModifyTextCommands.h"
#include "MoveCursorCommands.h"
#include "ScreenRenderer.h"

CommandCreator::CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer) :
_commandMap({}) {
  MoveCursorCommands::RegisterCommands(_commandMap, cursorManager);
  EditorControlCommands::RegisterCommands(_commandMap, screenRenderer);
  ModifyTextCommands::RegisterCommands(_commandMap, cursorManager, textBuffer);
}

CommandPattern::CommandMap CommandCreator::GetCommandMap() const {
  return _commandMap;
}
