#pragma once

#include "ICommand.h"
#include "ICursorManager.h"
#include "ITextBuffer.h"
#include "ScreenRenderer.h"

#include <functional>
#include <map>
#include <memory>

using CommandMap = std::map<std::string, std::function<std::unique_ptr<ICommand>()>>;

class CommandCreator {
public:
  CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer);

  CommandMap GetCommandMap();

private:
  CommandMap _commandMap;
};
