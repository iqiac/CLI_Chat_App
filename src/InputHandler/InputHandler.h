#pragma once

#include "IInputHandler.h"
#include "InputHandler/CommandPattern/ICommand.h"

#include <functional>
#include <map>
#include <memory>
#include <thread>

using CommandMap = std::map<std::string, std::function<std::unique_ptr<ICommand>()>>;

class InputHandler : public IInputHandler {
public:
  InputHandler(CommandMap commandMap) : _commandMap{std::move(commandMap)}, _running{false} {}

  void Start() override;
  void Stop() override;

private:
  void HandleInput() override;

  std::atomic<bool> _running;
  std::thread       _pollInputThread;

  CommandMap _commandMap;
};
