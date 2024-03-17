#include "TextBuffer.h"

#include <gtest/gtest.h>
#include <stdexcept>


namespace {
const std::string              line1{"Hello world!"};
const std::string              line2{"FOO"};
const std::string              line3{"Goodbye world."};
const std::vector<std::string> lines{line1, line2, line3};
}; // namespace

TEST(TextBufferConstructor, TextBuffer_NoArguments_HasVectorOfSizeOneWithEmptyString) {
  const TextBuffer textBuffer{};

  const std::vector<std::string> expectedBuffer{{""}};
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST(TextBufferConstructor, TextBuffer_StringArgument_HasVectorOfSizeOneWithGivenString) {
  const TextBuffer textBuffer{line1};

  const std::vector<std::string> expectedBuffer{line1};
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST(TextBufferConstructor, TextBuffer_VectorWithStringsArgument_HasSameVectorOfStrings) {
  const TextBuffer textBuffer{lines};

  EXPECT_EQ(lines, textBuffer.GetTextBuffer());
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

  EXPECT_EQ(line2 + line1, textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, InsertText_InsertAtEnd_TextInserted) {
  const auto colIndex{textBuffer.GetLineLength(validRowIndex)};

  textBuffer.InsertText({validRowIndex, colIndex}, line2);

  EXPECT_EQ(line1 + line2, textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, InsertText_RowIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertText({invalidRowIndex, 0}, line2), std::out_of_range);
}

TEST_F(TextBufferSingleLine, InsertText_ColIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertText({validRowIndex, 200}, line2), std::out_of_range);
}

TEST_F(TextBufferSingleLine, DeleteText_DeleteAtBeginning_TextDeleted) {
  constexpr auto length {2};

  textBuffer.DeleteText({validRowIndex, 0}, length);

  EXPECT_EQ(line1.substr(length), textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, DeleteText_DeleteAtEnd_TextDeleted) {
  constexpr auto length {2};
  const auto colIndex{textBuffer.GetLineLength(validRowIndex)};

  textBuffer.DeleteText({validRowIndex, colIndex}, length);

  EXPECT_EQ(line1, textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, DeleteText_LengthGoesOutOfBounds_TextDeletedFromGivenPosition) {
 constexpr auto colIndex{5}, length {200};

  textBuffer.DeleteText({validRowIndex, colIndex}, length);

  EXPECT_EQ(line1.substr(0, colIndex), textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, ReplaceText_ReplaceSubstring_SubstringReplaced) {
  constexpr auto colIndex{1}, length{2};

  textBuffer.ReplaceText({validRowIndex, colIndex}, length, line2);

  EXPECT_EQ(line1.substr(0, colIndex) + line2 + line1.substr(colIndex + length), textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, ReplaceText_ReplaceWholeString_StringReplaced) {
  constexpr auto colIndex{0};
  const auto length(textBuffer.GetLineLength(validRowIndex));

  textBuffer.ReplaceText({validRowIndex, colIndex}, length, line2);

  EXPECT_EQ(line2, textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, ReplaceText_LengthGoesOutOfBounds_TextReplacedFromGivenPosition) {
  const auto colIndex{3}, length{200};

  textBuffer.ReplaceText({validRowIndex, colIndex}, length, line2);

  EXPECT_EQ(line1.substr(0, colIndex) + line2, textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferSingleLine, ReplaceText_RowIndexGoesOutOfBounds_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertText({invalidRowIndex, 0}, line2), std::out_of_range);
}

class TextBufferMultiLine : public testing::Test {
protected:
  const std::size_t        validRowIndex{1}, invalidRowIndex{200};
  const std::string        line{"Random line here?"};
  std::vector<std::string> expectedBuffer{lines};
  TextBuffer               textBuffer{lines};
};

TEST_F(TextBufferMultiLine, GetNumberOfLines_MultiLine_ReturnsCorrectNumberOfLines) {
  EXPECT_EQ(lines.size(), textBuffer.GetNumberOfLines());
}

TEST_F(TextBufferMultiLine, GetLineLength_MultiLineAndValidIndices_ReturnsCorrectValues) {
  for (auto i{0}; i < textBuffer.GetNumberOfLines(); i++) {
    EXPECT_EQ(lines.at(i).size(), textBuffer.GetLineLength(i));
  }
}

TEST_F(TextBufferMultiLine, GetLineLength_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.GetLineLength(invalidRowIndex), std::out_of_range);
}

TEST_F(TextBufferMultiLine, GetLine_MultiLineAndValidIndex_ReturnsCorrectLine) {
  EXPECT_EQ(lines.at(validRowIndex), textBuffer.GetLine(validRowIndex));
}

TEST_F(TextBufferMultiLine, GetLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.GetLine(invalidRowIndex), std::out_of_range);
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtBeginning_LineInserted) {
  textBuffer.InsertLine(0, line);

  expectedBuffer.insert(expectedBuffer.begin(), line);
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtEnd_LineInserted) {
  const auto rowIndex{textBuffer.GetNumberOfLines()};

  textBuffer.InsertLine(rowIndex, line);

  expectedBuffer.insert(expectedBuffer.end(), line);
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, InsertLine_InsertAtValidIndex_LineInserted) {
  textBuffer.InsertLine(validRowIndex, line);

  const auto iterator{std::next(expectedBuffer.begin(), validRowIndex)};
  expectedBuffer.insert(iterator, line);
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, InsertLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.InsertLine(invalidRowIndex, line), std::out_of_range);
}

TEST_F(TextBufferMultiLine, DeleteLine_DeleteAtBeginning_LineDeleted) {
  textBuffer.DeleteLine(0);

  expectedBuffer.erase(expectedBuffer.begin());
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, DeleteLine_DeletetAtEnd_LineDeleted) {
  const auto rowIndex{textBuffer.GetNumberOfLines()};

  textBuffer.DeleteLine(rowIndex);

  expectedBuffer.erase(expectedBuffer.end());
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, DeleteLine_DeleteAtValidIndex_LineDeleted) {
  textBuffer.DeleteLine(validRowIndex);

  const auto iterator{std::next(expectedBuffer.begin(), validRowIndex)};
  expectedBuffer.erase(iterator);
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, DeleteLine_InvalidRowIndex_LineDeletedAtEnd) {
  textBuffer.DeleteLine(invalidRowIndex);

  expectedBuffer.erase(expectedBuffer.end());
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, ReplaceLine_ValidRowIndex_LineReplaced) {
  textBuffer.ReplaceLine(validRowIndex, line);

  expectedBuffer.at(validRowIndex) = line;
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}

TEST_F(TextBufferMultiLine, ReplaceLine_InvalidRowIndex_ThrowsException) {
  EXPECT_THROW(textBuffer.ReplaceLine(invalidRowIndex, line), std::out_of_range);
}

TEST_F(TextBufferMultiLine, ClearTextBuffer_Call_HasVectorOfSizeOneWithEmptyString) {
  textBuffer.ClearTextBuffer();

  expectedBuffer = {""};
  EXPECT_EQ(expectedBuffer, textBuffer.GetTextBuffer());
}
