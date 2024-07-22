#pragma once

#include "ICommand.h"
#include "ICursorManager.h"

class MoveCursorUp : public ICommand {
public:
  explicit MoveCursorUp(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};

class MoveCursorDown : public ICommand {
public:
  explicit MoveCursorDown(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};

class MoveCursorLeft : public ICommand {
public:
  explicit MoveCursorLeft(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};

class MoveCursorRight : public ICommand {
public:
  explicit MoveCursorRight(ICursorManager& cursorManager, std::size_t amount = 1) :
  _cursorManager(cursorManager),
  _amount(amount) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
  std::size_t     _amount;
};
