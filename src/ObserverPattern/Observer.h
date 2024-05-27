#pragma once

#include "IObserver.h"

class Observer : public IObserver {
public:
  virtual ~Observer() = default;
  std::string GetObserverName() const override;
};
