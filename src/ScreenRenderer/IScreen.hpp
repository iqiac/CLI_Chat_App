#pragma once

#include "CommonTypes.hpp"

#include <vector>

class IScreen {
public:
  virtual ~IScreen() = default;

  virtual void Start()                                 = 0;
  virtual void Stop()                                  = 0;
  virtual void SetCursor(const Position& position)     = 0;
  virtual void SetText(const std::vector<Line>& lines) = 0;
};
