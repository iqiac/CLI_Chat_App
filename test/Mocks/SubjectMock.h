#pragma once

#include "ISubject.h"

#include <gmock/gmock.h>

class SubjectMock : public ISubject {
public:
  MOCK_METHOD(void, Attach, (const std::string observerName, const UpdateFunction updateFunction), (override));
  MOCK_METHOD(void, Detach, (const std::string observerName), (override));
  MOCK_METHOD(void, Notify, (), (const, override));
};
