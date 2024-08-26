#include "CommandPattern/MoveCursorCommands.hpp"

#include "CommandPattern/ICommand.hpp"
#include "Mocks/CursorManagerMock.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class MoveCursorCommandsTest : public Test {
protected:
  CursorManagerMock _cursorManagerMock{};

  CommandPattern::CommandMap _commandMap;

  void SetUp() override {
    MoveCursorCommands::RegisterCommands(_commandMap, _cursorManagerMock);
  }

  void TearDown() override {}
};

TEST_F(MoveCursorCommandsTest, ExecuteMoveCursorUp_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["\x1b[A"]()};
  EXPECT_CALL(_cursorManagerMock, MoveCursorUp(_)).Times(1);

  command->Execute();
}
TEST_F(MoveCursorCommandsTest, ExecuteMoveCursorDown_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["\x1b[B"]()};
  EXPECT_CALL(_cursorManagerMock, MoveCursorDown(_)).Times(1);

  command->Execute();
}

TEST_F(MoveCursorCommandsTest, ExecuteMoveCursorLeft_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["\x1b[D"]()};
  EXPECT_CALL(_cursorManagerMock, MoveCursorLeft(_)).Times(1);

  command->Execute();
}

TEST_F(MoveCursorCommandsTest, ExecuteMoveCursorRight_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["\x1b[C"]()};
  EXPECT_CALL(_cursorManagerMock, MoveCursorRight(_)).Times(1);

  command->Execute();
}
