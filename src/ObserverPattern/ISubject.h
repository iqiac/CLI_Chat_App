#pragma once

#include "CommonTypes.h"

#include <functional>
#include <map>
#include <string>

class ISubject {
public:
  virtual ~ISubject() = default;

  virtual void Attach(const std::string observerName, const UpdateFunction updateFunction);
  virtual void Detach(const std::string observerName);
  virtual void Notify() const = 0;

protected:
  std::map<std::string, UpdateFunction> _observerUpdateFunctions;
};
