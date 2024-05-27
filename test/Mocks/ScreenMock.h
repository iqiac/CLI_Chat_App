#pragma once

#include "IScreen.h"

#include <gmock/gmock.h>

class ScreenMock : public IScreen {
public:
  MOCK_METHOD(void, Loop, (), (override));
  MOCK_METHOD(void, SetCursor, (const ftxui::Screen::Cursor), (override));
  MOCK_METHOD(void, PostEvent, (const ftxui::Event), (override));
  MOCK_METHOD(void, AddComponent, (const ftxui::Component), (override));
};
