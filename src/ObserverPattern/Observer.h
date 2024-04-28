#pragma once

#include "IObserver.h"

class Observer : public IObserver {
public:
  std::string GetObserverName() const override;
};
