#pragma once

#include "CommonTypes.h"

class ICursorManager {
public:
  virtual ~ICursorManager() = default;

  virtual void MoveCursorUp(const std::size_t amount = 1)    = 0;
  virtual void MoveCursorDown(const std::size_t amount = 1)  = 0;
  virtual void MoveCursorLeft(const std::size_t amount = 1)  = 0;
  virtual void MoveCursorRight(const std::size_t amount = 1) = 0;

  virtual void SetCursorPosition(const Position position) = 0;

  virtual Position GetCursorPosition() const = 0;
};
