#pragma once

#include "ICommand.h"
#include "ICursorManager.h"

class MoveCursorCommands {
public:
  MoveCursorCommands()                                     = delete;
  MoveCursorCommands(const MoveCursorCommands&)            = delete;
  MoveCursorCommands(MoveCursorCommands&&)                 = delete;
  MoveCursorCommands& operator=(const MoveCursorCommands&) = delete;
  MoveCursorCommands& operator=(MoveCursorCommands&&)      = delete;
  ~MoveCursorCommands()                                    = delete;

  static void RegisterCommands(CommandPattern::CommandMap& commandMap, ICursorManager& cursorManager);
};
