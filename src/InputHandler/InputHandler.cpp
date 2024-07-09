#include "InputHandler.h"

#include "CommandPattern/MoveCursorCommands.h"

#include <chrono>
#include <termios.h>
#include <unistd.h>

namespace {
void        EnableRawMode();
void        DisableRawMode();
std::string ReadInput();

std::map<std::string, Key> inputKeyMap{
    {"\x1b[A", Key::Up},
    {"\x1b[B", Key::Down},
    {"\x1b[C", Key::Right},
    {"\x1b[D", Key::Left},
};

void EnableRawMode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void DisableRawMode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= ICANON | ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

std::string ReadInput() {
  std::string inputSequence{};
  char        c;
  if (read(STDIN_FILENO, &c, 1) < 1) {
    return inputSequence;
  }
  inputSequence += c;
  if (c == '\x1b') { // Escape character
    // Read the next two characters of the escape sequence
    for (auto i = 0; i < 2; ++i) {
      if (read(STDIN_FILENO, &c, 1) > 0) {
        inputSequence += c;
      }
    }
  }
  return inputSequence;
}
} // namespace

InputHandler::InputHandler(ITextBuffer& textBuffer, ICursorManager& cursorManager) :
_textBuffer(textBuffer),
_cursorManager(cursorManager),
_running(false) {
  _cursorCommandMap[Key::Up]    = std::make_unique<MoveCursorUp>(_cursorManager);
  _cursorCommandMap[Key::Down]  = std::make_unique<MoveCursorDown>(_cursorManager);
  _cursorCommandMap[Key::Left]  = std::make_unique<MoveCursorLeft>(_cursorManager);
  _cursorCommandMap[Key::Right] = std::make_unique<MoveCursorRight>(_cursorManager);
}

void InputHandler::Start() {
  EnableRawMode();
  _running         = true;
  _pollInputThread = std::thread(&InputHandler::HandleInput, this);
}

void InputHandler::Stop() {
  _running = false;
  _pollInputThread.join();
  DisableRawMode();
}

void InputHandler::HandleInput() {
  const auto pollingInterval_ms{100};
  while (_running) {
    const auto input{ReadInput()};
    if (input.empty()) {
      continue;
    }
    if (!inputKeyMap.contains(input)) {
      continue;
    }
    if (const auto key{inputKeyMap[input]}; _cursorCommandMap.contains(key)) {
      _cursorCommandMap[key]->Execute();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(pollingInterval_ms));
  }
}
