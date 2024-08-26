#pragma once

#include "CommandPattern/ICommand.hpp"

#include <gmock/gmock.h>

class CommandMock : public ICommand {
public:
  MOCK_METHOD(void, Execute, (), (const, override));
};
