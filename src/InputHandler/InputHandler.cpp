#include "InputHandler.h"

#include <chrono>
#include <termios.h>
#include <unistd.h>

void InputHandler::Start() {
  EnableRawMode();
  _isRunning.store(true);
  _pollInputThread = std::thread(&InputHandler::HandleInput, this);
}

void InputHandler::Stop() {
  _isRunning.store(false);
  _pollInputThread.join();
  DisableRawMode();
}

void InputHandler::HandleInput() {
  constexpr auto pollingInterval_ms{100};
  while (_isRunning.load()) {
    const auto input{ReadInput()};
    if (input.empty()) {
      continue;
    }
    if (_commandMap.contains(input)) {
      const auto& command = _commandMap[input]();
      command->Execute();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(pollingInterval_ms));
  }
}
void InputHandler::EnableRawMode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void InputHandler::DisableRawMode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= ICANON | ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

std::string InputHandler::ReadInput() {
  std::string inputSequence;
  char        buffer[4];

  ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
  if (bytesRead == -1) {
    return "";
  }
  inputSequence.append(buffer, bytesRead);

  return inputSequence;
}
