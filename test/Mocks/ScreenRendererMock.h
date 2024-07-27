#pragma once

#include "IScreenRenderer.h"

#include <gmock/gmock.h>

class ScreenRendererMock : public IScreenRenderer {
public:
  MOCK_METHOD(void, Loop, (), (override));
  MOCK_METHOD(void, Exit, (), (override));
};
