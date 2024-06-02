#pragma once

#include "CommonTypes.h"
#include "ISubjectDataGetter.h"

#include <string>

template <typename T>
class IObserver {
public:
  virtual ~IObserver() = default;

  virtual void Update(const ISubjectDataGetter<T>& subject) = 0;
};
