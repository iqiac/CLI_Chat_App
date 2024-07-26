#include "CommandPattern/EditorControlCommands.h"
#include "CommandPattern/ModifyTextCommands.h"
#include "CommandPattern/MoveCursorCommands.h"
#include "CommonTypes.h"
#include "Mocks/CursorManagerMock.h"
#include "Mocks/ScreenRendererMock.h"
#include "Mocks/TextBufferMock.h"

#include <cstddef>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

using namespace testing;

class CommandTest : public Test {
protected:
  CursorManagerMock  _cursorManagerMock{};
  ScreenRendererMock _screenRendererMock{};
  TextBufferMock     _textBufferMock{};

  const std::size_t _arbitraryAmount{5};
  const Position    _arbitraryPosition{4, 2};
  const std::string _arbitraryText{"Some text."};

  void SetUp() override {
    ON_CALL(_cursorManagerMock, GetCursorPosition()).WillByDefault(Return(_arbitraryPosition));
  }

  void TearDown() override {}
};

TEST_F(CommandTest, ExecuteMoveCursorUp_Call_CorrectFunctionsCalled) {
  const MoveCursorUp command{_cursorManagerMock, _arbitraryAmount};
  EXPECT_CALL(_cursorManagerMock, MoveCursorUp(_arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteMoveCursorDown_Call_CorrectFunctionsCalled) {
  const MoveCursorDown command{_cursorManagerMock, _arbitraryAmount};
  EXPECT_CALL(_cursorManagerMock, MoveCursorDown(_arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteMoveCursorLeft_Call_CorrectFunctionsCalled) {
  const MoveCursorLeft command{_cursorManagerMock, _arbitraryAmount};
  EXPECT_CALL(_cursorManagerMock, MoveCursorLeft(_arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteMoveCursorRight_Call_CorrectFunctionsCalled) {
  const MoveCursorRight command{_cursorManagerMock, _arbitraryAmount};
  EXPECT_CALL(_cursorManagerMock, MoveCursorRight(_arbitraryAmount)).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteExitEditor_Call_CorrectFunctionsCalled) {
  const ExitEditor command{_screenRendererMock};
  EXPECT_CALL(_screenRendererMock, Exit()).Times(1);

  command.Execute();
}

TEST_F(CommandTest, ExecuteInsertText_Call_CorrectFunctionsCalled) {
  const InsertText command{_textBufferMock, _cursorManagerMock, _arbitraryText};
  EXPECT_CALL(_textBufferMock, InsertText(_arbitraryPosition, _arbitraryText)).Times(1);
  EXPECT_CALL(_cursorManagerMock, MoveCursorRight(_arbitraryText.size())).Times(1);

  command.Execute();
}
