#pragma once

#include "IObserver.h"

#include <gmock/gmock.h>

class ObserverMock : public IObserver {
public:
  MOCK_METHOD(void, Update, (const EventMessage eventMessage), (override));
  MOCK_METHOD(std::string, GetObserverName, (), (const, override));
};
