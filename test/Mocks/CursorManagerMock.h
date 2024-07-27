#pragma once

#include "ICursorManager.h"

#include <gmock/gmock.h>

class CursorManagerMock : public ICursorManager {
public:
  MOCK_METHOD(void, MoveCursorUp, (const std::size_t amount), (override));
  MOCK_METHOD(void, MoveCursorDown, (const std::size_t amount), (override));
  MOCK_METHOD(void, MoveCursorLeft, (const std::size_t amount), (override));
  MOCK_METHOD(void, MoveCursorRight, (const std::size_t amount), (override));
  MOCK_METHOD(void, SetCursorPosition, (const Position position), (override));
  MOCK_METHOD(Position, GetCursorPosition, (), (const, override));
};
