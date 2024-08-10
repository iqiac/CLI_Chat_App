#pragma once

#include "IScreen.h"

#include <gmock/gmock.h>

class ScreenMock : public IScreen {
public:
  MOCK_METHOD(void, Start, (), (override));
  MOCK_METHOD(void, Stop, (), (override));
  MOCK_METHOD(void, SetCursor, (const Position&), (override));
  MOCK_METHOD(void, SetText, (const std::vector<Line>&), (override));
};
