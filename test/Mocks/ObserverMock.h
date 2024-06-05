#pragma once

#include "IObserver.h"

#include <gmock/gmock.h>
template <typename T>
class ObserverMock : public IObserver<T> {
public:
  MOCK_METHOD(void, Update, (const ISubject<T>&), (override));
};
