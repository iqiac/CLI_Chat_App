#include "EditorControlCommands.h"

void ExitEditor::Execute() const {
  _screenRenderer.Exit();
}
