#pragma once

#include "ICommand.h"
#include "ScreenRenderer.h"

class ExitEditor : public ICommand {
public:
  explicit ExitEditor(ScreenRenderer& screenRenderer) : _screenRenderer(screenRenderer) {}
  void Execute() const override;

private:
  ScreenRenderer& _screenRenderer;
};
