#include "CursorManager.hpp"

#include "Mocks/ObserverMock.hpp"
#include "Mocks/TextBufferMock.hpp"

#include <cstddef>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

class CursorManagerTests : public Test {
protected:
  const std::size_t _numRows{20}, _numCols{30};
  const std::size_t _validRowIndex{_numRows / 2}, _validColIndex{_numCols / 2};
  const std::size_t _invalidRowIndex{_numRows * 10}, _invalidColIndex{_numCols * 10};

  const TextBufferMock _textBufferMock{};

  CursorManager _cursorManager{_textBufferMock};

  void SetUp() override {
    ON_CALL(_textBufferMock, GetNumberOfLines()).WillByDefault(Return(_numRows));
    ON_CALL(_textBufferMock, GetLineLength(_)).WillByDefault(Return(_numCols));
  }

  void TearDown() override {}
};

TEST_F(CursorManagerTests, GetPosition_InitialPosition_ReturnsZeroZero) {
  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(0, 0));
}

TEST_F(CursorManagerTests, SetPosition_ValidIndices_SetsPosition) {
  EXPECT_CALL(_textBufferMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(_textBufferMock, GetLineLength(_)).Times(1);

  _cursorManager.SetCursorPosition({_validRowIndex, _validColIndex});

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex, _validColIndex));
}

TEST_F(CursorManagerTests, SetPosition_OutOfBoundsRowIndex_PositionedAtLastRowIndex) {
  _cursorManager.SetCursorPosition({_invalidRowIndex, _validColIndex});

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_numRows - 1, _validColIndex));
}

TEST_F(CursorManagerTests, SetPosition_OutOfBoundsColIndex_PositionedAtLineLengthIndex) {
  _cursorManager.SetCursorPosition({_validRowIndex, _invalidColIndex});

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex, _numCols));
}

TEST_F(CursorManagerTests, SetPosition_OutOfBoundsRowAndColIndex_PositionedAtLastPossibleRowAndCol) {
  _cursorManager.SetCursorPosition({_invalidRowIndex, _invalidColIndex});

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_numRows - 1, _numCols));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorIsAtFirstRow_RowIndexStays) {
  _cursorManager.SetCursorPosition({0, 0});

  _cursorManager.MoveCursorUp();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(0, 0));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorIsBelowFirstRow_RowIndexDecrements) {
  _cursorManager.SetCursorPosition({_validRowIndex, 0});

  _cursorManager.MoveCursorUp();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex - 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorAtEndAndAboveRowIsShorter_CursorIsAtEndOfAboveLine) {
  _cursorManager.SetCursorPosition({_validRowIndex, _numCols});
  const auto aboveRowLength{_numCols - 5};
  EXPECT_CALL(_textBufferMock, GetLineLength(_)).WillOnce(Return(aboveRowLength));

  _cursorManager.MoveCursorUp();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex - 1, aboveRowLength));
}

TEST_F(CursorManagerTests, MoveCursorUp_CursorAtEndAndAboveRowIsLonger_CursorIsAtSameColIndexOnLineAbove) {
  _cursorManager.SetCursorPosition({_validRowIndex, _numCols});
  const auto aboveRowLength{_numCols + 5};
  EXPECT_CALL(_textBufferMock, GetLineLength(_)).WillOnce(Return(aboveRowLength));

  _cursorManager.MoveCursorUp();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex - 1, _numCols));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorIsAtLastRow_RowIndexStays) {
  _cursorManager.SetCursorPosition({_numRows - 1, 0});
  EXPECT_CALL(_textBufferMock, GetNumberOfLines()).Times(1);

  _cursorManager.MoveCursorDown();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_numRows - 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorIsAboveLastRow_RowIndexIncrements) {
  _cursorManager.SetCursorPosition({_validRowIndex, 0});
  EXPECT_CALL(_textBufferMock, GetNumberOfLines()).Times(1);

  _cursorManager.MoveCursorDown();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex + 1, 0));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorAtEndAndBelowRowIsShorter_CursorIsAtEndOfBelowLine) {
  _cursorManager.SetCursorPosition({_validRowIndex, _numCols});
  const auto belowRowLength{_numCols - 5};
  EXPECT_CALL(_textBufferMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(_textBufferMock, GetLineLength(_)).WillOnce(Return(belowRowLength));

  _cursorManager.MoveCursorDown();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex + 1, belowRowLength));
}

TEST_F(CursorManagerTests, MoveCursorDown_CursorAtEndAndBelowRowIsLonger_CursorIsAtSameColIndexOnLineBelow) {
  _cursorManager.SetCursorPosition({_validRowIndex, _numCols});
  const auto belowRowLength{_numCols + 5};
  EXPECT_CALL(_textBufferMock, GetNumberOfLines()).Times(1);
  EXPECT_CALL(_textBufferMock, GetLineLength(_)).WillOnce(Return(belowRowLength));

  _cursorManager.MoveCursorDown();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(_validRowIndex + 1, _numCols));
}

TEST_F(CursorManagerTests, MoveCursorLeft_CursorIsAtFirstColumn_ColIndexStays) {
  _cursorManager.SetCursorPosition({0, 0});

  _cursorManager.MoveCursorLeft();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(0, 0));
}

TEST_F(CursorManagerTests, MoveCursorLeft_CursorIsAtRightOfFirstColumn_ColIndexDecrements) {
  _cursorManager.SetCursorPosition({0, _validColIndex});

  _cursorManager.MoveCursorLeft();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(0, _validColIndex - 1));
}

TEST_F(CursorManagerTests, MoveCursorRight_CursorIsAtLastColumn_ColIndexStays) {
  _cursorManager.SetCursorPosition({0, _numCols});
  EXPECT_CALL(_textBufferMock, GetLineLength(_)).Times(1);

  _cursorManager.MoveCursorRight();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(0, _numCols));
}

TEST_F(CursorManagerTests, MoveCursorRight_CursorIsAtLeftOfLastColumn_ColIndexIncrements) {
  _cursorManager.SetCursorPosition({0, _validColIndex});
  EXPECT_CALL(_textBufferMock, GetLineLength(_)).Times(1);

  _cursorManager.MoveCursorRight();

  EXPECT_THAT(_cursorManager.GetCursorPosition(), Position(0, _validColIndex + 1));
}

TEST_F(CursorManagerTests, Attach_Call_ObserverUpdateCalled) {
  auto observerMock{std::make_shared<ObserverMock<Position>>()};
  EXPECT_CALL(*observerMock, Update(_)).Times(1);

  _cursorManager.Attach(observerMock);
}

TEST_F(CursorManagerTests, Notify_Call_AllObserverUpdateCalled) {
  auto observerMock1{std::make_shared<ObserverMock<Position>>()};
  auto observerMock2{std::make_shared<ObserverMock<Position>>()};
  _cursorManager.Attach(observerMock1);
  _cursorManager.Attach(observerMock2);
  EXPECT_CALL(*observerMock1, Update(_)).Times(1);
  EXPECT_CALL(*observerMock2, Update(_)).Times(1);

  _cursorManager.Notify();
}
