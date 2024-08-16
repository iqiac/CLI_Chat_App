#include "CommandPattern/EditorControlCommands.h"

#include "CommandPattern/ICommand.h"
#include "Mocks/ScreenRendererMock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class EditorControlCommandsTest : public Test {
protected:
  ScreenRendererMock _screenRendererMock{};

  CommandPattern::CommandMap _commandMap;

  void SetUp() override {
    EditorControlCommands::RegisterCommands(_commandMap, _screenRendererMock);
  }
  void TearDown() override {}
};

TEST_F(EditorControlCommandsTest, ExecuteExitEditor_Call_CorrectFunctionsCalled) {
  const auto command{_commandMap["\x1b"]()};
  EXPECT_CALL(_screenRendererMock, Stop()).Times(1);

  command->Execute();
}
