#pragma once

#include "ICommand.h"
#include "IScreenRenderer.h"

class EditorControlCommands {
public:
  EditorControlCommands()                                        = delete;
  EditorControlCommands(const EditorControlCommands&)            = delete;
  EditorControlCommands(EditorControlCommands&&)                 = delete;
  EditorControlCommands& operator=(const EditorControlCommands&) = delete;
  EditorControlCommands& operator=(EditorControlCommands&&)      = delete;
  ~EditorControlCommands()                                       = delete;

  static void RegisterCommands(CommandPattern::CommandMap& commandMap, IScreenRenderer& screenRenderer);
};
