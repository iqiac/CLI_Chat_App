#pragma once

#include <functional>
#include <string>

class ISubject {
public:
  virtual ~ISubject() = default;

  virtual void Attach(const std::string observerName, const std::function<void()> updateFunction) = 0;
  virtual void Detach(const std::string observerName)                                             = 0;
  virtual void Notify() const                                                                     = 0;
};
