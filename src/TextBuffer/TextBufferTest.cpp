#include "TextBuffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using namespace testing;

namespace {
const std::string              line1{"Hello world!"};
const std::string              line2{"FOO"};
const std::string              line3{"Goodbye world."};
const std::vector<std::string> lines{line1, line2, line3};
}; // namespace

TEST(TextBufferConstructor, TextBuffer_NoArguments_HasVectorOfSizeOneWithEmptyString) {
  const TextBuffer textBuffer{};

  EXPECT_THAT(textBuffer.GetTextBuffer(), AllOf(SizeIs(1), Contains("")));
}

TEST(TextBufferConstructor, TextBuffer_StringArgument_HasVectorOfSizeOneWithGivenString) {
  const TextBuffer textBuffer{line1};

  EXPECT_THAT(textBuffer.GetTextBuffer(), AllOf(SizeIs(1), Contains(line1)));
}

TEST(TextBufferConstructor, TextBuffer_VectorWithStringsArgument_HasSameVectorOfStrings) {
  const TextBuffer textBuffer{lines};

  EXPECT_THAT(textBuffer.GetTextBuffer(), ContainerEq(lines));
}

TEST(TextBufferConstructor, TextBuffer_EmptyVectorArgument_ThrowsException) {
  const auto emptyVector{std::vector<std::string>()};
  EXPECT_THROW(const TextBuffer textBuffer{emptyVector}, std::invalid_argument);
}

class TextBufferSingleLine : public testing::Test {
protected:
  const std::size_t validRowIndex{0}, invalidRowIndex{200};
  TextBuffer        textBuffer{line1};
};

TEST_F(TextBufferSingleLine, InsertText_InsertAtBeginning_TextInserted) {
  textBuffer.InsertText({validRowIndex, 0}, line2);

  EXPECT_THAT(textBuffer.GetLine(validRowIndex), StrEq(line2 + line1));
}

TEST_F(TextBufferSingleLine, InsertText_InsertAtEnd_TextInserted) {
  const auto colIndex{textBuffer.GetLineLength(validRowIndex)};

  textBuffer.InsertText({validRowIndex, colIndex}, line2);

  EXPECT_THAT(textBuffer.GetLine(validRowIndex), StrEq(line1 + line2));
}

TEST_F(TextBufferSingleLine, InsertText_RowIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertText({invalidRowIndex, 0}, line2), std::out_of_range);
}

TEST_F(TextBufferSingleLine, InsertText_ColIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertText({validRowIndex, 200}, line2), std::out_of_range);
}

TEST_F(TextBufferSingleLine, DeleteText_DeleteAtBeginning_TextDeleted) {
  constexpr auto length{2};

  textBuffer.DeleteText({validRowIndex, 0}, length);

  EXPECT_THAT(textBuffer.GetLine(validRowIndex), StrEq(line1.substr(length)));
}

TEST_F(TextBufferSingleLine, DeleteText_DeleteAtEnd_TextDeleted) {
  constexpr auto length{2};
  const auto     colIndex{textBuffer.GetLineLength(validRowIndex)};

  textBuffer.DeleteText({validRowIndex, colIndex}, length);

  EXPECT_THAT(textBuffer.GetLine(validRowIndex), StrEq(line1));
}

TEST_F(TextBufferSingleLine, DeleteText_LengthGoesOutOfBounds_TextDeletedFromGivenPosition) {
  constexpr auto colIndex{5}, length{200};

  textBuffer.DeleteText({validRowIndex, colIndex}, length);

  EXPECT_THAT(textBuffer.GetLine(validRowIndex), StrEq(line1.substr(0, colIndex)));
}

TEST_F(TextBufferSingleLine, ReplaceText_ReplaceSubstring_SubstringReplaced) {
  constexpr auto colIndex{1}, length{2};

  textBuffer.ReplaceText({validRowIndex, colIndex}, length, line2);

  const auto actualLine{textBuffer.GetLine(validRowIndex)};
  EXPECT_THAT(actualLine, StartsWith(line1.substr(0, colIndex)));
  EXPECT_THAT(actualLine, HasSubstr(line2));
  EXPECT_THAT(actualLine, EndsWith(line1.substr(colIndex + length)));
}

TEST_F(TextBufferSingleLine, ReplaceText_ReplaceWholeString_StringReplaced) {
  constexpr auto colIndex{0};
  const auto     length(textBuffer.GetLineLength(validRowIndex));

  textBuffer.ReplaceText({validRowIndex, colIndex}, length, line2);

  EXPECT_THAT(textBuffer.GetLine(validRowIndex), StrEq(line2));
}

TEST_F(TextBufferSingleLine, ReplaceText_LengthGoesOutOfBounds_TextReplacedFromGivenPosition) {
  const auto colIndex{3}, length{200};

  textBuffer.ReplaceText({validRowIndex, colIndex}, length, line2);

  const auto actualLine{textBuffer.GetLine(validRowIndex)};
  EXPECT_THAT(actualLine, StartsWith(line1.substr(0, colIndex)));
  EXPECT_THAT(actualLine, EndsWith(line2));
}

TEST_F(TextBufferSingleLine, ReplaceText_RowIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertText({invalidRowIndex, 0}, line2), std::out_of_range);
}

class TextBufferMultiLine : public testing::Test {
protected:
  const std::size_t validRowIndex{1}, invalidRowIndex{200};
  const std::string line{"Random line here?"};
  TextBuffer        textBuffer{lines};
};

TEST_F(TextBufferMultiLine, GetNumberOfLines_MultiLine_ReturnsCorrectNumberOfLines) {
  EXPECT_THAT(textBuffer.GetNumberOfLines(), Eq(lines.size()));
}

TEST_F(TextBufferMultiLine, GetLineLength_MultiLineAndValidIndices_ReturnsCorrectValues) {
  for (auto i{0}; i < textBuffer.GetNumberOfLines(); i++) {
    EXPECT_THAT(textBuffer.GetLineLength(i), Eq(lines.at(i).size()));
  }
}

TEST_F(TextBufferMultiLine, GetLineLength_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.GetLineLength(invalidRowIndex), std::out_of_range);
}

TEST_F(TextBufferMultiLine, GetLine_MultiLineAndValidIndex_ReturnsCorrectLine) {
  EXPECT_THAT(textBuffer.GetLine(validRowIndex), StrEq(lines.at(validRowIndex)));
}

TEST_F(TextBufferMultiLine, GetLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.GetLine(invalidRowIndex), std::out_of_range);
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtBeginning_LineInserted) {
  textBuffer.InsertLine(0, line);

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(line).Times(1));
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtEnd_LineInserted) {
  textBuffer.InsertLine(textBuffer.GetNumberOfLines(), line);

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(line).Times(1));
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtValidIndex_LineInserted) {
  textBuffer.InsertLine(validRowIndex, line);

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(line).Times(1));
}

TEST_F(TextBufferMultiLine, InsertLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertLine(invalidRowIndex, line), std::out_of_range);
}

TEST_F(TextBufferMultiLine, DeleteLine_DeleteAtBeginning_LineDeleted) {
  textBuffer.DeleteLine(0);

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(line1).Times(0));
}

TEST_F(TextBufferMultiLine, DeleteLine_DeletetAtEnd_LineDeleted) {
  textBuffer.DeleteLine(textBuffer.GetNumberOfLines());

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(line3).Times(0));
}

TEST_F(TextBufferMultiLine, DeleteLine_DeleteAtValidIndex_LineDeleted) {
  textBuffer.DeleteLine(validRowIndex);

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(lines.at(validRowIndex)).Times(0));
}

TEST_F(TextBufferMultiLine, DeleteLine_InvalidRowIndex_LineDeletedAtEnd) {
  textBuffer.DeleteLine(invalidRowIndex);

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(line3).Times(0));
}

TEST_F(TextBufferMultiLine, ReplaceLine_ValidRowIndex_LineReplaced) {
  textBuffer.ReplaceLine(validRowIndex, line);

  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(lines.at(validRowIndex)).Times(0));
  EXPECT_THAT(textBuffer.GetTextBuffer(), Contains(line).Times(1));
}

TEST_F(TextBufferMultiLine, ReplaceLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.ReplaceLine(invalidRowIndex, line), std::out_of_range);
}

TEST_F(TextBufferMultiLine, ClearTextBuffer_Call_HasVectorOfSizeOneWithEmptyString) {
  textBuffer.ClearTextBuffer();

  EXPECT_THAT(textBuffer.GetTextBuffer(), AllOf(SizeIs(1), Contains("")));
}
