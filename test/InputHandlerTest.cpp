#include "InputHandler.h"

#include "Mocks/CommandMock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

namespace {
auto commandMock{std::make_unique<CommandMock>()};
} // namespace

class InputHandlerTest : public Test {
protected:
  const std::string key;
  CommandMap        commandMap = {{key, [] { return std::unique_ptr<ICommand>(commandMock.release()); }}};
  InputHandler      _inputHandler{commandMap};
};
