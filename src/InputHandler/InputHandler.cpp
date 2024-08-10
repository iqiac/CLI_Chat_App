#include "InputHandler.h"

#include <array>
#include <string>
#include <sys/types.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

namespace {
void                      EnableTerminalRawMode();
void                      DisableTerminalRawMode();
[[nodiscard]] std::string ReadInput();

enum class TerminalMode {
  CANONICAL_MODE = ICANON, // Determines whether terminal input waits for newline
  ECHO_MODE      = ECHO,   // Determines whether terminal input is displayed on screen
};

void ActivateTerminalMode(TerminalMode mode) {
  struct termios term {};
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= static_cast<int>(mode);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void DeactivateTerminalMode(TerminalMode mode) {
  struct termios term {};
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~static_cast<int>(mode);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void EnableTerminalRawMode() {
  DeactivateTerminalMode(TerminalMode::CANONICAL_MODE);
  DeactivateTerminalMode(TerminalMode::ECHO_MODE);
}

void DisableTerminalRawMode() {
  ActivateTerminalMode(TerminalMode::CANONICAL_MODE);
  ActivateTerminalMode(TerminalMode::ECHO_MODE);
}

std::string ReadInput() {
  std::string         inputSequence;
  std::array<char, 4> buffer{};

  const ssize_t bytesRead{read(STDIN_FILENO, buffer.data(), buffer.size())}; // read() is blocking
  if (constexpr auto readError{-1}; bytesRead == readError) {
    return "";
  }
  inputSequence.append(buffer.data(), bytesRead);

  return inputSequence;
}
} // namespace

void InputHandler::Start() {
  EnableTerminalRawMode();
  _isRunning.store(true);
  _handleInputThread = std::thread(&InputHandler::HandleInput, this);
}

void InputHandler::Stop() {
  _isRunning.store(false);
  _handleInputThread.join();
  DisableTerminalRawMode();
}

void InputHandler::HandleInput() {
  while (_isRunning.load()) {
    if (const auto input{ReadInput()}; _commandMap.contains(input)) {
      const auto& command = _commandMap[input]();
      command->Execute();
    }
  }
}
