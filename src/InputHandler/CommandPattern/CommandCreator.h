#pragma once

#include "ICommand.h"
#include "ICursorManager.h"
#include "ITextBuffer.h"
#include "ScreenRenderer.h"

#include <functional>
#include <memory>

class CommandCreator {
public:
  CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer);

  [[nodiscard]] CommandPattern::CommandMap GetCommandMap() const;

private:
  CommandPattern::CommandMap _commandMap;
};
