#pragma once

#include "IScreen.h"

#include <gmock/gmock.h>

class ScreenMock : public IScreen {
public:
  MOCK_METHOD(void, Loop, (), (override));
  MOCK_METHOD(void, Exit, (), (override));
  MOCK_METHOD(void, SetCursor, (const Position&), (override));
  MOCK_METHOD(void, SetText, (const std::vector<Line>&), (override));
};
