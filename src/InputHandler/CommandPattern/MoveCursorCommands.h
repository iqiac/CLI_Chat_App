#pragma once

#include "ICommand.h"
#include "ICursorManager.h"

class MoveCursorUp : public ICommand {
public:
  MoveCursorUp(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}

  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};

class MoveCursorDown : public ICommand {
public:
  MoveCursorDown(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}

  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};

class MoveCursorLeft : public ICommand {
public:
  MoveCursorLeft(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}

  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};

class MoveCursorRight : public ICommand {
public:
  MoveCursorRight(ICursorManager& cursorManager) : _cursorManager(cursorManager) {}

  void Execute() const override;

private:
  ICursorManager& _cursorManager;
};
