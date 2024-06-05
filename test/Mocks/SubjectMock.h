#pragma once

#include "ISubject.h"

#include <gmock/gmock.h>

template <typename T>
class SubjectMock : public ISubject<T> {
public:
  MOCK_METHOD(void, Attach, (std::shared_ptr<IObserver<T>> observer), (override));
  MOCK_METHOD(void, Detach, (std::shared_ptr<IObserver<T>> observer), (override));
  MOCK_METHOD(void, Notify, (), (const, override));
  MOCK_METHOD(T, GetData, (), (const, override));
};
