#pragma once

#include "CommonTypes.h"

#include <string>

class IObserver {
public:
  virtual ~IObserver() = default;

  virtual void        Update(const EventMessage eventMessage) = 0;
  virtual std::string GetObserverName() const                 = 0;

protected:
  std::string _observerName;
};
