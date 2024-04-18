#pragma once

#include "TextBufferInterfaces.h"

#include <gmock/gmock.h>

class ITextBufferInfoMock : public ITextBufferInfo {
public:
  MOCK_METHOD(std::size_t, GetNumberOfLines, (), (const, override));
  MOCK_METHOD(std::size_t, GetLineLength, (const std::size_t rowIndex), (const, override));
};
