#pragma once

#include "ICommand.h"
#include "IScreenRenderer.h"

class ExitEditor : public ICommand {
public:
  explicit ExitEditor(IScreenRenderer& screenRenderer) : _screenRenderer(screenRenderer) {}
  void Execute() const override;

private:
  IScreenRenderer& _screenRenderer;
};
