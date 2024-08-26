#pragma once

#include "IInputHandler.hpp"
#include "InputHandler/CommandPattern/ICommand.hpp"

#include <atomic>
#include <thread>

class InputHandler : public IInputHandler {
public:
  InputHandler(CommandPattern::CommandMap commandMap) : _commandMap{std::move(commandMap)}, _isRunning{false} {}

  void Start() override;
  void Stop() override;

private:
  void HandleInput() override;

  std::atomic<bool>          _isRunning;
  std::thread                _handleInputThread;
  CommandPattern::CommandMap _commandMap;
};
