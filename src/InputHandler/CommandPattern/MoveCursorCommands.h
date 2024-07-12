#pragma once

#include "ICommand.h"
#include "ICursorManager.h"

class MoveCursorUp : public ICommand {
public:
  explicit MoveCursorUp(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};

class MoveCursorDown : public ICommand {
public:
  explicit MoveCursorDown(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};

class MoveCursorLeft : public ICommand {
public:
  explicit MoveCursorLeft(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};

class MoveCursorRight : public ICommand {
public:
  explicit MoveCursorRight(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}
  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};
