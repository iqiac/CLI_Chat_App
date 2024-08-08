#pragma once
#include "CommonTypes.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

class ICommand {
public:
  virtual ~ICommand() = default;

  virtual void Execute() const = 0;
};

namespace CommandPattern {
using CommandMap = std::map<std::string, std::function<std::unique_ptr<ICommand>()>>;
} // namespace CommandPattern
