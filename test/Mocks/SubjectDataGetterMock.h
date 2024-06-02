#pragma once

#include "ISubjectDataGetter.h"

#include <gmock/gmock.h>

template <typename T>
class SubjectDataGetterMock : public ISubjectDataGetter<T> {
public:
  MOCK_METHOD(T, GetData, (), (const, override));
};
