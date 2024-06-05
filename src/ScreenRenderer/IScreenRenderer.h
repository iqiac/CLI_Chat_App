#pragma once

#include "CommonTypes.h"

class IScreenRenderer {

public:
  virtual ~IScreenRenderer() = default;

  virtual void Loop() = 0;
};
