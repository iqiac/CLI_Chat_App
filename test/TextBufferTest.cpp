#include "TextBuffer.hpp"

#include "CommonTypes.hpp"
#include "Mocks/ObserverMock.hpp"

#include <cstddef>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace testing;

namespace {
const std::string              line1{"Hello world!"};
const std::string              line2{"FOO"};
const std::string              line3{"Goodbye world."};
const std::vector<std::string> lines{line1, line2, line3};
}; // namespace

TEST(TextBufferConstructor, TextBuffer_NoArguments_HasVectorOfSizeOneWithEmptyString) {
  const TextBuffer textBuffer{};

  EXPECT_THAT(textBuffer.GetAllLines(), AllOf(SizeIs(1), Contains("")));
}

TEST(TextBufferConstructor, TextBuffer_StringArgument_HasVectorOfSizeOneWithGivenString) {
  const TextBuffer textBuffer{line1};

  EXPECT_THAT(textBuffer.GetAllLines(), AllOf(SizeIs(1), Contains(line1)));
}

TEST(TextBufferConstructor, TextBuffer_VectorWithStringsArgument_HasSameVectorOfStrings) {
  const TextBuffer textBuffer{lines};

  EXPECT_THAT(textBuffer.GetAllLines(), ContainerEq(lines));
}

TEST(TextBufferConstructor, TextBuffer_EmptyVectorArgument_ThrowsException) {
  const auto emptyVector{std::vector<std::string>()};
  EXPECT_THROW(const TextBuffer textBuffer{emptyVector}, std::invalid_argument);
}

TEST(TextBufferSubject, Attach_Call_ObserverUpdateCalled) {
  auto       observerMock{std::make_shared<ObserverMock<std::vector<Line>>>()};
  TextBuffer textBuffer{};
  EXPECT_CALL(*observerMock, Update(_)).Times(1);

  textBuffer.Attach(observerMock);
}

TEST(TextBufferSubject, Notify_Call_AllObserverUpdateCalled) {
  auto       observerMock1{std::make_shared<ObserverMock<std::vector<Line>>>()};
  auto       observerMock2{std::make_shared<ObserverMock<std::vector<Line>>>()};
  TextBuffer textBuffer{};
  textBuffer.Attach(observerMock1);
  textBuffer.Attach(observerMock2);
  EXPECT_CALL(*observerMock1, Update(_)).Times(1);
  EXPECT_CALL(*observerMock2, Update(_)).Times(1);

  textBuffer.Notify();
}

class TextBufferSingleLine : public Test {
protected:
  const std::size_t _validRowIndex{0}, _invalidRowIndex{200};
  TextBuffer        _textBuffer{line1};
};

TEST_F(TextBufferSingleLine, InsertText_InsertAtBeginning_TextInserted) {
  _textBuffer.InsertText({_validRowIndex, 0}, line2);

  EXPECT_THAT(_textBuffer.GetLine(_validRowIndex), StrEq(line2 + line1));
}

TEST_F(TextBufferSingleLine, InsertText_InsertAtEnd_TextInserted) {
  const auto colIndex{_textBuffer.GetLineLength(_validRowIndex)};

  _textBuffer.InsertText({_validRowIndex, colIndex}, line2);

  EXPECT_THAT(_textBuffer.GetLine(_validRowIndex), StrEq(line1 + line2));
}

TEST_F(TextBufferSingleLine, InsertText_RowIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(_textBuffer.InsertText({_invalidRowIndex, 0}, line2), std::out_of_range);
}

TEST_F(TextBufferSingleLine, InsertText_ColIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(_textBuffer.InsertText({_validRowIndex, 200}, line2), std::out_of_range);
}

TEST_F(TextBufferSingleLine, DeleteText_DeleteAtBeginning_TextDeleted) {
  constexpr auto length{2};

  _textBuffer.DeleteText({_validRowIndex, 0}, length);

  EXPECT_THAT(_textBuffer.GetLine(_validRowIndex), StrEq(line1.substr(length)));
}

TEST_F(TextBufferSingleLine, DeleteText_DeleteAtEnd_TextDeleted) {
  constexpr auto length{2};
  const auto     colIndex{_textBuffer.GetLineLength(_validRowIndex)};

  _textBuffer.DeleteText({_validRowIndex, colIndex}, length);

  EXPECT_THAT(_textBuffer.GetLine(_validRowIndex), StrEq(line1));
}

TEST_F(TextBufferSingleLine, DeleteText_LengthGoesOutOfBounds_TextDeletedFromGivenPosition) {
  constexpr auto colIndex{5};
  constexpr auto length{200};

  _textBuffer.DeleteText({_validRowIndex, colIndex}, length);

  EXPECT_THAT(_textBuffer.GetLine(_validRowIndex), StrEq(line1.substr(0, colIndex)));
}

TEST_F(TextBufferSingleLine, ReplaceText_ReplaceSubstring_SubstringReplaced) {
  constexpr auto colIndex{1};
  constexpr auto length{2};

  _textBuffer.ReplaceText({_validRowIndex, colIndex}, length, line2);

  const auto actualLine{_textBuffer.GetLine(_validRowIndex)};
  EXPECT_THAT(actualLine, StartsWith(line1.substr(0, colIndex)));
  EXPECT_THAT(actualLine, HasSubstr(line2));
  EXPECT_THAT(actualLine, EndsWith(line1.substr(colIndex + length)));
}

TEST_F(TextBufferSingleLine, ReplaceText_ReplaceWholeString_StringReplaced) {
  constexpr auto colIndex{0};
  const auto     length(_textBuffer.GetLineLength(_validRowIndex));

  _textBuffer.ReplaceText({_validRowIndex, colIndex}, length, line2);

  EXPECT_THAT(_textBuffer.GetLine(_validRowIndex), StrEq(line2));
}

TEST_F(TextBufferSingleLine, ReplaceText_LengthGoesOutOfBounds_TextReplacedFromGivenPosition) {
  constexpr auto colIndex{3};
  constexpr auto length{200};

  _textBuffer.ReplaceText({_validRowIndex, colIndex}, length, line2);

  const auto actualLine{_textBuffer.GetLine(_validRowIndex)};
  EXPECT_THAT(actualLine, StartsWith(line1.substr(0, colIndex)));
  EXPECT_THAT(actualLine, EndsWith(line2));
}

TEST_F(TextBufferSingleLine, ReplaceText_RowIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(_textBuffer.InsertText({_invalidRowIndex, 0}, line2), std::out_of_range);
}

class TextBufferMultiLine : public testing::Test {
protected:
  const std::size_t _validRowIndex{1}, _invalidRowIndex{200};
  const std::string _line{"Random line here?"};
  TextBuffer        _textBuffer{lines};
};

TEST_F(TextBufferMultiLine, GetNumberOfLines_MultiLine_ReturnsCorrectNumberOfLines) {
  EXPECT_THAT(_textBuffer.GetNumberOfLines(), Eq(lines.size()));
}

TEST_F(TextBufferMultiLine, GetLineLength_MultiLineAndValidIndices_ReturnsCorrectValues) {
  for (auto i{0}; i < _textBuffer.GetNumberOfLines(); ++i) {
    EXPECT_THAT(_textBuffer.GetLineLength(i), Eq(lines.at(i).size()));
  }
}

TEST_F(TextBufferMultiLine, GetLineLength_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(static_cast<void>(_textBuffer.GetLineLength(_invalidRowIndex)), std::out_of_range);
}

TEST_F(TextBufferMultiLine, GetLine_MultiLineAndValidIndex_ReturnsCorrectLine) {
  EXPECT_THAT(_textBuffer.GetLine(_validRowIndex), StrEq(lines.at(_validRowIndex)));
}

TEST_F(TextBufferMultiLine, GetLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(static_cast<void>(_textBuffer.GetLine(_invalidRowIndex)), std::out_of_range);
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtBeginning_LineInserted) {
  _textBuffer.InsertLine(0, _line);

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(_line).Times(1));
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtEnd_LineInserted) {
  _textBuffer.InsertLine(_textBuffer.GetNumberOfLines(), _line);

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(_line).Times(1));
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtValidIndex_LineInserted) {
  _textBuffer.InsertLine(_validRowIndex, _line);

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(_line).Times(1));
}

TEST_F(TextBufferMultiLine, InsertLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(_textBuffer.InsertLine(_invalidRowIndex, _line), std::out_of_range);
}

TEST_F(TextBufferMultiLine, DeleteLine_DeleteAtBeginning_LineDeleted) {
  _textBuffer.DeleteLine(0);

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(line1).Times(0));
}

TEST_F(TextBufferMultiLine, DeleteLine_DeletetAtEnd_LineDeleted) {
  _textBuffer.DeleteLine(_textBuffer.GetNumberOfLines());

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(line3).Times(0));
}

TEST_F(TextBufferMultiLine, DeleteLine_DeleteAtValidIndex_LineDeleted) {
  _textBuffer.DeleteLine(_validRowIndex);

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(lines.at(_validRowIndex)).Times(0));
}

TEST_F(TextBufferMultiLine, DeleteLine_InvalidRowIndex_LineDeletedAtEnd) {
  _textBuffer.DeleteLine(_invalidRowIndex);

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(line3).Times(0));
}

TEST_F(TextBufferMultiLine, ReplaceLine_ValidRowIndex_LineReplaced) {
  _textBuffer.ReplaceLine(_validRowIndex, _line);

  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(lines.at(_validRowIndex)).Times(0));
  EXPECT_THAT(_textBuffer.GetAllLines(), Contains(_line).Times(1));
}

TEST_F(TextBufferMultiLine, ReplaceLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(_textBuffer.ReplaceLine(_invalidRowIndex, _line), std::out_of_range);
}

TEST_F(TextBufferMultiLine, ClearTextBuffer_Call_HasVectorOfSizeOneWithEmptyString) {
  _textBuffer.ClearAllLines();

  EXPECT_THAT(_textBuffer.GetAllLines(), AllOf(SizeIs(1), Contains("")));
}
