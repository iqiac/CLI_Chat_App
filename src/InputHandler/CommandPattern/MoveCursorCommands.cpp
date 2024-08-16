#include "MoveCursorCommands.h"

#include "ICommand.h"
#include "ICursorManager.h"

#include <cstddef>
#include <memory>

namespace {
class MoveCursorUp : public ICommand {
public:
  explicit MoveCursorUp(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override {
    _cursorManager.MoveCursorUp(_amount);
  }

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};

class MoveCursorDown : public ICommand {
public:
  explicit MoveCursorDown(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override {
    _cursorManager.MoveCursorDown(_amount);
  }

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};

class MoveCursorLeft : public ICommand {
public:
  explicit MoveCursorLeft(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override {
    _cursorManager.MoveCursorLeft(_amount);
  }

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};

class MoveCursorRight : public ICommand {
public:
  explicit MoveCursorRight(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override {
    _cursorManager.MoveCursorRight(_amount);
  }

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};
} // namespace

void MoveCursorCommands::RegisterCommands(CommandPattern::CommandMap& commandMap, ICursorManager& cursorManager) {
  commandMap["\x1b[A"] = [&cursorManager] { return std::make_unique<MoveCursorUp>(cursorManager); };
  commandMap["\x1b[B"] = [&cursorManager] { return std::make_unique<MoveCursorDown>(cursorManager); };
  commandMap["\x1b[D"] = [&cursorManager] { return std::make_unique<MoveCursorLeft>(cursorManager); };
  commandMap["\x1b[C"] = [&cursorManager] { return std::make_unique<MoveCursorRight>(cursorManager); };
}
