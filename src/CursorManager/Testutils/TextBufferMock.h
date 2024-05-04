#pragma once

#include "ITextBuffer.h"

#include <gmock/gmock.h>

class TextBufferMock : public ITextBuffer {
public:
  MOCK_METHOD(void, InsertText, (const Position position, const std::string& text), (override));
  MOCK_METHOD(void, InsertText, (const Index rowIndex, const Index colIndex, const std::string& text), (override));

  MOCK_METHOD(void, DeleteText, (const Position position, const std::size_t length), (override));
  MOCK_METHOD(void, DeleteText, (const Index rowIndex, const Index colIndex, const std::size_t length), (override));

  MOCK_METHOD(void, ReplaceText, (const Position position, const std::size_t length, const std::string& text), (override));
  MOCK_METHOD(void,
              ReplaceText,
              (const Index rowIndex, const Index colIndex, const std::size_t length, const std::string& text),
              (override));

  MOCK_METHOD(void, InsertLine, (const Index rowIndex, const Line& line), (override));
  MOCK_METHOD(void, DeleteLine, (const Index rowIndex), (override));
  MOCK_METHOD(void, ReplaceLine, (const Index rowIndex, const Line& line), (override));

  MOCK_METHOD(std ::size_t, GetNumberOfLines, (), (const, override));
  MOCK_METHOD(std::size_t, GetLineLength, (const Index rowIndex), (const, override));
  MOCK_METHOD(std::string, GetLine, (const Index rowIndex), (const, override));
  MOCK_METHOD(std::vector<std::string>, GetAllLines, (), (const, override));
  MOCK_METHOD(void, ClearAllLines, (), (override));
};
