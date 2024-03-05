#include "TextBuffer.h"

#include <gtest/gtest.h>

class TextBufferStub : public testing::Test {
protected:
  const std::string defaultText{"Hello world!"};
  const std::string dummyText{"FOO"};
  TextBuffer        emptyTextBuffer{};
  TextBuffer        textBuffer{};

  void SetUp() override {
    textBuffer.InsertText(0, defaultText);
  }

  void TearDown() override {
  }
};

TEST_F(TextBufferStub, GetText_EmptyTextBuffer_ContainsEmptyString) {
  const auto actualText{emptyTextBuffer.GetText()};

  EXPECT_EQ("", actualText);
}

TEST_F(TextBufferStub, GetText_NonEmptyTextBuffer_GetCorrectText) {
  const auto actualText{textBuffer.GetText()};

  EXPECT_EQ(defaultText, actualText);
}

TEST_F(TextBufferStub, InsertText_EmptyTextBuffer_ContainsInsertedText) {
  emptyTextBuffer.InsertText(0, defaultText);

  EXPECT_EQ(defaultText, emptyTextBuffer.GetText());
}

TEST_F(TextBufferStub, InsertText_InsertAtInBoundIndex_TextCorrectlyInserted) {
  textBuffer.InsertText(4, dummyText);

  EXPECT_EQ("HellFOOo world!", textBuffer.GetText());
}

TEST_F(TextBufferStub, InsertText_InsertAtTextSize_TextAppended) {
  textBuffer.InsertText(defaultText.size(), dummyText);

  EXPECT_EQ("Hello world!FOO", textBuffer.GetText());
}

TEST_F(TextBufferStub, InsertText_InsertAtOutOfBoundIndex_TextNotInserted) {
  textBuffer.InsertText(200, dummyText);

  EXPECT_EQ(defaultText, textBuffer.GetText());
}

TEST_F(TextBufferStub, DeleteText_EmptyTextBuffer_NoChange) {
  emptyTextBuffer.DeleteText(0, 4);

  EXPECT_EQ("", emptyTextBuffer.GetText());
}

TEST_F(TextBufferStub, DeleteText_ValidPositionAndLength_TextDeleted) {
  textBuffer.DeleteText(1, 4);

  EXPECT_EQ("H world!", textBuffer.GetText());
}

TEST_F(TextBufferStub, DeleteText_LengthGoesOutOfBounds_SuffixTextDeleted) {
  textBuffer.DeleteText(2, 200);

  EXPECT_EQ("He", textBuffer.GetText());
}

TEST_F(TextBufferStub, DeleteText_OutOfBoundsPosition_NothingDeleted) {
  textBuffer.DeleteText(100, 2);

  EXPECT_EQ(defaultText, textBuffer.GetText());
}

TEST_F(TextBufferStub, ReplaceText_EmptyTextBufferAndValidPosition_TextInserted) {
  emptyTextBuffer.ReplaceText(0, 4, defaultText);

  EXPECT_EQ(defaultText, emptyTextBuffer.GetText());
}

TEST_F(TextBufferStub, ReplaceText_EmptyTextBufferOutOfBoundsPosition_NoChange) {
  emptyTextBuffer.ReplaceText(2, 4, defaultText);

  EXPECT_EQ("", emptyTextBuffer.GetText());
}

TEST_F(TextBufferStub, ReplaceText_InboundPositionAndLength_TextReplaced) {
  textBuffer.ReplaceText(1, 2, dummyText);

  EXPECT_EQ("HFOOlo world!", textBuffer.GetText());
}

TEST_F(TextBufferStub, ReplaceText_OutOfBoundsPosition_NoChange) {
  textBuffer.ReplaceText(200, 3, dummyText);

  EXPECT_EQ(defaultText, textBuffer.GetText());
}

TEST_F(TextBufferStub, ReplaceText_OutOfBoundsLength_SuffixTextReplaced) {
  constexpr auto start{3}, end{200};

  textBuffer.ReplaceText(3, 200, dummyText);

  EXPECT_EQ("HelFOO", textBuffer.GetText());
}
