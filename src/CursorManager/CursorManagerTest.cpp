#include "CursorManager.h"

#include "Testutils/TextBufferInfoMock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using namespace testing;

class CursorManagerTests : public testing::Test {
protected:
  const std::size_t   numRows{20}, numCols{30};
  const std::size_t   validRowIndex{numRows / 2}, validColIndex{numCols / 2};
  const std::size_t   invalidRowIndex{numRows * 10}, invalidColIndex{numCols * 10};
  ITextBufferInfoMock textBufferInfoMock{};
  CursorManager       cursorManager{textBufferInfoMock};

  void SetUp() override {
    ON_CALL(textBufferInfoMock, GetNumberOfLines()).WillByDefault(Return(numRows));
    ON_CALL(textBufferInfoMock, GetLineLength(_)).WillByDefault(Return(numCols));
  }

  void TearDown() override {}
};

TEST_F(CursorManagerTests, GetPosition_InitialPosition_ReturnsZeroZero) {
  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(0, 0));
}

TEST_F(CursorManagerTests, SetPosition_ValidIndices_SetsPosition) {
  EXPECT_CALL(textBufferInfoMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).Times(1);

  cursorManager.SetCursorPosition(validRowIndex, validColIndex);

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(validRowIndex, validColIndex));
}

TEST_F(CursorManagerTests, SetPosition_InvalidRowIndex_ThrowsException) {
  EXPECT_CALL(textBufferInfoMock, GetNumberOfLines()).Times(1);
  EXPECT_THROW(cursorManager.SetCursorPosition(invalidRowIndex, validColIndex), std::invalid_argument);
}

TEST_F(CursorManagerTests, SetPosition_InvalidColIndex_ThrowsException) {
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).Times(1);
  EXPECT_THROW(cursorManager.SetCursorPosition(validRowIndex, invalidColIndex), std::invalid_argument);
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorIsAtFirstRow_RowIndexStays) {
  cursorManager.SetCursorPosition(0, 0);

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(0, 0));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorIsBelowFirstRow_RowIndexDecrements) {
  cursorManager.SetCursorPosition(validRowIndex, 0);

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(validRowIndex - 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorAtEndAndAboveRowIsShorter_CursorIsAtEndOfAboveLine) {
  cursorManager.SetCursorPosition(validRowIndex, numCols);
  const auto aboveRowLength{numCols - 5};
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).WillOnce(Return(aboveRowLength));

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(validRowIndex - 1, aboveRowLength));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorAtEndAndAboveRowIsLonger_CursorIsAtSameColIndexOnLineAbove) {
  cursorManager.SetCursorPosition(validRowIndex, numCols);
  const auto aboveRowLength{numCols + 5};
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).WillOnce(Return(aboveRowLength));

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(validRowIndex - 1, numCols));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorIsAtLastRow_RowIndexStays) {
  cursorManager.SetCursorPosition(numRows - 1, 0);
  EXPECT_CALL(textBufferInfoMock, GetNumberOfLines()).Times(1);

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(numRows - 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorIsAboveLastRow_RowIndexIncrements) {
  cursorManager.SetCursorPosition(validRowIndex, 0);
  EXPECT_CALL(textBufferInfoMock, GetNumberOfLines()).Times(1);

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(validRowIndex + 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorAtEndAndBelowRowIsShorter_CursorIsAtEndOfBelowLine) {
  cursorManager.SetCursorPosition(validRowIndex, numCols);
  const auto belowRowLength{numCols - 5};
  EXPECT_CALL(textBufferInfoMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).WillOnce(Return(belowRowLength));

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(validRowIndex + 1, belowRowLength));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorAtEndAndBelowRowIsLonger_CursorIsAtSameColIndexOnLineBelow) {
  cursorManager.SetCursorPosition(validRowIndex, numCols);
  const auto belowRowLength{numCols + 5};
  EXPECT_CALL(textBufferInfoMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).WillOnce(Return(belowRowLength));

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(validRowIndex + 1, numCols));
}

TEST_F(CursorManagerTests, MoveCursorLeft_CursorIsAtFirstColumn_ColIndexStays) {
  cursorManager.SetCursorPosition(0, 0);

  cursorManager.MoveCursorLeft();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(0, 0));
}

TEST_F(CursorManagerTests, MoveCursorLeft_CursorIsatRightOfFirstColumn_ColIndexDecrements) {
  cursorManager.SetCursorPosition(0, validColIndex);

  cursorManager.MoveCursorLeft();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(0, validColIndex - 1));
}

TEST_F(CursorManagerTests, MoveCursorRight_CursorIsAtLastColumn_ColIndexStays) {
  cursorManager.SetCursorPosition(0, numCols - 1);
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).Times(1);

  cursorManager.MoveCursorRight();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(0, numCols - 1));
}

TEST_F(CursorManagerTests, MoveCursorRight_CursorIsAtLeftOfLastColumn_ColIndexIncrements) {
  cursorManager.SetCursorPosition(0, validColIndex);
  EXPECT_CALL(textBufferInfoMock, GetLineLength(_)).Times(1);

  cursorManager.MoveCursorRight();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Pair(0, validColIndex + 1));
}
