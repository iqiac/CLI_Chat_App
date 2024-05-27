#pragma once
#include "CommonTypes.h"

class ICommand {
public:
  virtual ~ICommand() = default;

  virtual void Execute() const = 0;
};
