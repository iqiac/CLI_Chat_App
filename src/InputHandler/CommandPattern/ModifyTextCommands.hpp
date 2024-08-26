#pragma once

#include "ICommand.hpp"
#include "ICursorManager.hpp"
#include "ITextBuffer.hpp"

class ModifyTextCommands {
public:
  ModifyTextCommands()                                     = delete;
  ModifyTextCommands(const ModifyTextCommands&)            = delete;
  ModifyTextCommands(ModifyTextCommands&&)                 = delete;
  ModifyTextCommands& operator=(const ModifyTextCommands&) = delete;
  ModifyTextCommands& operator=(ModifyTextCommands&&)      = delete;
  ~ModifyTextCommands()                                    = delete;

  static void RegisterCommands(CommandPattern::CommandMap& commandMap, ICursorManager& cursorManager,
                               ITextBuffer& textBuffer);
};
