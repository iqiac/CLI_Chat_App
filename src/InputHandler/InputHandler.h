#pragma once

#include "CommandPattern/ICommand.h"
#include "CommonTypes.h"
#include "ICursorManager.h"
#include "IInputHandler.h"
#include "ITextBuffer.h"

#include <map>
#include <memory>
#include <thread>

class InputHandler : public IInputHandler {
public:
  InputHandler(ITextBuffer& textBuffer, ICursorManager& cursorManager);
  void Start() override;
  void Stop() override;

private:
  void HandleInput() override;

  ITextBuffer&      _textBuffer;
  ICursorManager&   _cursorManager;
  std::atomic<bool> _running;
  std::thread       _pollInputThread;

  std::map<std::string, std::unique_ptr<ICommand>> _commandMap;
};
