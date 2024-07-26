#include "CursorManager.h"

#include "Mocks/ObserverMock.h"
#include "Mocks/TextBufferMock.h"

#include <cstddef>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class CursorManagerTests : public Test {
protected:
  const std::size_t numRows{20}, numCols{30};
  const std::size_t validRowIndex{numRows / 2}, validColIndex{numCols / 2};
  const std::size_t invalidRowIndex{numRows * 10}, invalidColIndex{numCols * 10};

  const TextBufferMock textBufferMock{};

  CursorManager cursorManager{textBufferMock};

  void SetUp() override {
    ON_CALL(textBufferMock, GetNumberOfLines()).WillByDefault(Return(numRows));
    ON_CALL(textBufferMock, GetLineLength(_)).WillByDefault(Return(numCols));
  }

  void TearDown() override {}
};

TEST_F(CursorManagerTests, GetPosition_InitialPosition_ReturnsZeroZero) {
  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(0, 0));
}

TEST_F(CursorManagerTests, SetPosition_ValidIndices_SetsPosition) {
  EXPECT_CALL(textBufferMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(textBufferMock, GetLineLength(_)).Times(1);

  cursorManager.SetCursorPosition({validRowIndex, validColIndex});

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex, validColIndex));
}

TEST_F(CursorManagerTests, SetPosition_OutOfBoundsRowIndex_PositionedAtLastRowIndex) {
  cursorManager.SetCursorPosition({invalidRowIndex, validColIndex});

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(numRows - 1, validColIndex));
}

TEST_F(CursorManagerTests, SetPosition_OutOfBoundsColIndex_PositionedAtLineLengthIndex) {
  cursorManager.SetCursorPosition({validRowIndex, invalidColIndex});

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex, numCols));
}

TEST_F(CursorManagerTests, SetPosition_OutOfBoundsRowAndColIndex_PositionedAtLastPossibleRowAndCol) {
  cursorManager.SetCursorPosition({invalidRowIndex, invalidColIndex});

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(numRows - 1, numCols));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorIsAtFirstRow_RowIndexStays) {
  cursorManager.SetCursorPosition({0, 0});

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(0, 0));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorIsBelowFirstRow_RowIndexDecrements) {
  cursorManager.SetCursorPosition({validRowIndex, 0});

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex - 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorAtEndAndAboveRowIsShorter_CursorIsAtEndOfAboveLine) {
  cursorManager.SetCursorPosition({validRowIndex, numCols});
  const auto aboveRowLength{numCols - 5};
  EXPECT_CALL(textBufferMock, GetLineLength(_)).WillOnce(Return(aboveRowLength));

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex - 1, aboveRowLength));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorAtEndAndAboveRowIsLonger_CursorIsAtSameColIndexOnLineAbove) {
  cursorManager.SetCursorPosition({validRowIndex, numCols});
  const auto aboveRowLength{numCols + 5};
  EXPECT_CALL(textBufferMock, GetLineLength(_)).WillOnce(Return(aboveRowLength));

  cursorManager.MoveCursorUp();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex - 1, numCols));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorIsAtLastRow_RowIndexStays) {
  cursorManager.SetCursorPosition({numRows - 1, 0});
  EXPECT_CALL(textBufferMock, GetNumberOfLines()).Times(1);

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(numRows - 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorIsAboveLastRow_RowIndexIncrements) {
  cursorManager.SetCursorPosition({validRowIndex, 0});
  EXPECT_CALL(textBufferMock, GetNumberOfLines()).Times(1);

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex + 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorAtEndAndBelowRowIsShorter_CursorIsAtEndOfBelowLine) {
  cursorManager.SetCursorPosition({validRowIndex, numCols});
  const auto belowRowLength{numCols - 5};
  EXPECT_CALL(textBufferMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(textBufferMock, GetLineLength(_)).WillOnce(Return(belowRowLength));

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex + 1, belowRowLength));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorAtEndAndBelowRowIsLonger_CursorIsAtSameColIndexOnLineBelow) {
  cursorManager.SetCursorPosition({validRowIndex, numCols});
  const auto belowRowLength{numCols + 5};
  EXPECT_CALL(textBufferMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(textBufferMock, GetLineLength(_)).WillOnce(Return(belowRowLength));

  cursorManager.MoveCursorDown();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(validRowIndex + 1, numCols));
}

TEST_F(CursorManagerTests, MoveCursorLeft_CursorIsAtFirstColumn_ColIndexStays) {
  cursorManager.SetCursorPosition({0, 0});

  cursorManager.MoveCursorLeft();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(0, 0));
}

TEST_F(CursorManagerTests, MoveCursorLeft_CursorIsAtRightOfFirstColumn_ColIndexDecrements) {
  cursorManager.SetCursorPosition({0, validColIndex});

  cursorManager.MoveCursorLeft();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(0, validColIndex - 1));
}

TEST_F(CursorManagerTests, MoveCursorRight_CursorIsAtLastColumn_ColIndexStays) {
  cursorManager.SetCursorPosition({0, numCols});
  EXPECT_CALL(textBufferMock, GetLineLength(_)).Times(1);

  cursorManager.MoveCursorRight();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(0, numCols));
}

TEST_F(CursorManagerTests, MoveCursorRight_CursorIsAtLeftOfLastColumn_ColIndexIncrements) {
  cursorManager.SetCursorPosition({0, validColIndex});
  EXPECT_CALL(textBufferMock, GetLineLength(_)).Times(1);

  cursorManager.MoveCursorRight();

  EXPECT_THAT(cursorManager.GetCursorPosition(), Position(0, validColIndex + 1));
}

TEST_F(CursorManagerTests, Attach_Call_ObserverUpdateCalled) {
  auto observerMock{std::make_shared<ObserverMock<Position>>()};
  EXPECT_CALL(*observerMock, Update(_)).Times(1);

  cursorManager.Attach(observerMock);
}

TEST_F(CursorManagerTests, Notify_Call_AllObserverUpdateCalled) {
  auto observerMock1{std::make_shared<ObserverMock<Position>>()};
  auto observerMock2{std::make_shared<ObserverMock<Position>>()};
  cursorManager.Attach(observerMock1);
  cursorManager.Attach(observerMock2);
  EXPECT_CALL(*observerMock1, Update(_)).Times(1);
  EXPECT_CALL(*observerMock2, Update(_)).Times(1);

  cursorManager.Notify();
}
