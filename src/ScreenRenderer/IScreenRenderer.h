#pragma once

#include "CommonTypes.h"

class IScreenRenderer {

public:
  virtual ~IScreenRenderer() = default;

  virtual void Start() = 0;
  virtual void Stop()  = 0;
};
