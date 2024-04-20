#pragma once

#include "ITextBuffer.h"

#include <gmock/gmock.h>

class TextBufferMock : public ITextBuffer {
public:
  MOCK_METHOD(void, InsertText, ((const std::pair<std::size_t, std::size_t>)position, const std::string& text), (override));
  MOCK_METHOD(void, InsertText, (const std::size_t rowIndex, const std::size_t colIndex, const std::string& text), (override));

  MOCK_METHOD(void, DeleteText, ((const std::pair<std::size_t, std::size_t>)position, const std::size_t length), (override));
  MOCK_METHOD(void, DeleteText, (const std::size_t rowIndex, const std::size_t colIndex, const std::size_t length), (override));

  MOCK_METHOD(void,
              ReplaceText,
              ((const std::pair<std::size_t, std::size_t>)position, const std::size_t length, const std::string& text),
              (override));
  MOCK_METHOD(void,
              ReplaceText,
              (const std::size_t rowIndex, const std::size_t colIndex, const std::size_t length, const std::string& text),
              (override));

  MOCK_METHOD(void, InsertLine, (const std::size_t rowIndex, const std::string& line), (override));
  MOCK_METHOD(void, DeleteLine, (const std::size_t rowIndex), (override));
  MOCK_METHOD(void, ReplaceLine, (const std::size_t rowIndex, const std::string& line), (override));

  MOCK_METHOD(std ::size_t, GetNumberOfLines, (), (const, override));
  MOCK_METHOD(std::size_t, GetLineLength, (const std::size_t rowIndex), (const, override));
  MOCK_METHOD(std::string, GetLine, (const std::size_t rowIndex), (const, override));
  MOCK_METHOD(std::vector<std::string>, GetAllLines, (), (const, override));
  MOCK_METHOD(void, ClearAllLines, (), (override));
};
