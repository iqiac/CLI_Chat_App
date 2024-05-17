#pragma once

#include "CommonTypes.h"

class IScreenRenderer {

public:
  virtual ~IScreenRenderer() = default;

  virtual void Loop() = 0;

private:
  virtual void UpdateText(const std::vector<Line>& allLines) = 0;
  virtual void UpdateCursor(const Position& cursorPosition)  = 0;
};
