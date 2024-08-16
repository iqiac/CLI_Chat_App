#include "CommandPattern/ModifyTextCommands.h"

#include "CommandPattern/ICommand.h"
#include "CommonTypes.h"
#include "Mocks/CursorManagerMock.h"
#include "Mocks/TextBufferMock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class ModifyTextCommandsTest : public Test {
protected:
  CursorManagerMock _cursorManagerMock{};
  TextBufferMock    _textBufferMock{};

  const Position             _arbitraryPosition{4, 2};
  CommandPattern::CommandMap _commandMap;

  void SetUp() override {
    ModifyTextCommands::RegisterCommands(_commandMap, _cursorManagerMock, _textBufferMock);
    ON_CALL(_cursorManagerMock, GetCursorPosition()).WillByDefault(Return(_arbitraryPosition));
  }

  void TearDown() override {}
};

TEST_F(ModifyTextCommandsTest, ExecuteInsertText_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["i"]()};
  EXPECT_CALL(_textBufferMock, InsertText(_arbitraryPosition, "i")).Times(1);
  EXPECT_CALL(_cursorManagerMock, MoveCursorRight(1)).Times(1);

  command->Execute();
}

TEST_F(ModifyTextCommandsTest, ExecuteRemoveTextBackward_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["\x7f"]()};
  EXPECT_CALL(_textBufferMock, DeleteText(_arbitraryPosition, 1)).Times(1);
  EXPECT_CALL(_cursorManagerMock, MoveCursorLeft(1)).Times(1);

  command->Execute();
}

TEST_F(ModifyTextCommandsTest, ExecuteRemoveTextForward_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["\x1b[3~"]()};
  EXPECT_CALL(_textBufferMock, DeleteText(_arbitraryPosition, 1)).Times(1);
  EXPECT_CALL(_cursorManagerMock, MoveCursorLeft(_)).Times(0);
  EXPECT_CALL(_cursorManagerMock, MoveCursorRight(_)).Times(0);
  EXPECT_CALL(_cursorManagerMock, MoveCursorUp(_)).Times(0);
  EXPECT_CALL(_cursorManagerMock, MoveCursorDown(_)).Times(0);

  command->Execute();
}
