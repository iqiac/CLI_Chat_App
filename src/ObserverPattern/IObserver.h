#pragma once

#include "CommonTypes.h"

#include <string>

class IObserver {
public:
  virtual ~IObserver() = default;

  virtual void        Update(const EventMessage& eventMessage) = 0;
  virtual std::string GetObserverName() const;

protected:
  std::string _observerName;
};
