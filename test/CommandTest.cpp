#include "CommandPattern/EditorControlCommands.h"
#include "CommandPattern/ModifyTextCommands.h"
#include "CommandPattern/MoveCursorCommands.h"
#include "Mocks/CursorManagerMock.h"
#include "Mocks/ScreenRendererMock.h"
#include "Mocks/TextBufferMock.h"

#include <gtest/gtest.h>

using namespace testing;

class CommandTest : public Test {
protected:
  CursorManagerMock  cursorManagerMock{};
  ScreenRendererMock screenRendererMock{};
  TextBufferMock     textBufferMock{};

  const std::size_t arbitraryAmount{5};
  const Position    arbitraryPosition{4, 2};
  const std::string arbitraryText{"Some text."};

  void SetUp() override {
    ON_CALL(cursorManagerMock, GetCursorPosition()).WillByDefault(Return(arbitraryPosition));
  }

  void TearDown() override {}
};

TEST_F(CommandTest, ExecuteMoveCursorUp_Call_CorrectFunctionsCalled) {
  const MoveCursorUp command{cursorManagerMock, arbitraryAmount};
  EXPECT_CALL(cursorManagerMock, MoveCursorUp(arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteMoveCursorDown_Call_CorrectFunctionsCalled) {
  const MoveCursorDown command{cursorManagerMock, arbitraryAmount};
  EXPECT_CALL(cursorManagerMock, MoveCursorDown(arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteMoveCursorLeft_Call_CorrectFunctionsCalled) {
  const MoveCursorLeft command{cursorManagerMock, arbitraryAmount};
  EXPECT_CALL(cursorManagerMock, MoveCursorLeft(arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteMoveCursorRight_Call_CorrectFunctionsCalled) {
  const MoveCursorRight command{cursorManagerMock, arbitraryAmount};
  EXPECT_CALL(cursorManagerMock, MoveCursorRight(arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteExitEditor_Call_CorrectFunctionsCalled) {
  const ExitEditor command{screenRendererMock};
  EXPECT_CALL(screenRendererMock, Exit()).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteInsertText_Call_CorrectFunctionsCalled) {
  const InsertText command{textBufferMock, cursorManagerMock, arbitraryText};
  EXPECT_CALL(textBufferMock, InsertText(arbitraryPosition, arbitraryText)).Times(1);
  EXPECT_CALL(cursorManagerMock, MoveCursorRight(arbitraryText.size())).Times(1);

  command.Execute();
}
