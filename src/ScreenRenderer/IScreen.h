#pragma once

#include "CommonTypes.h"

#include <vector>

class IScreen {
public:
  virtual ~IScreen() = default;

  virtual void Loop()                                  = 0;
  virtual void Exit()                                  = 0;
  virtual void SetCursor(const Position& position)     = 0;
  virtual void SetText(const std::vector<Line>& lines) = 0;
};
