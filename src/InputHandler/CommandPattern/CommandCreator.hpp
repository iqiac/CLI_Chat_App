#pragma once

#include "ICommand.hpp"
#include "ICursorManager.hpp"
#include "ITextBuffer.hpp"
#include "ScreenRenderer.hpp"

class CommandCreator {
public:
  CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer);

  [[nodiscard]] CommandPattern::CommandMap GetCommandMap() const;

private:
  CommandPattern::CommandMap _commandMap;
};
