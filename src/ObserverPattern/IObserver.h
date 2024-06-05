#pragma once

#include "CommonTypes.h"

#include <string>
template <typename T>
class ISubject;

template <typename T>
class IObserver {
public:
  virtual ~IObserver() = default;

  virtual void Update(const ISubject<T>& subject) = 0;
};
