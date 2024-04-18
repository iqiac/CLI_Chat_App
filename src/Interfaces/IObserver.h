#pragma once

#include <string>

class IObserver {
public:
  virtual ~IObserver() = default;

  virtual void Update() = 0;

  virtual std::string GetObserverName() const = 0;
};
