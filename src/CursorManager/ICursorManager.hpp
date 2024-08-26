#pragma once

#include "CommonTypes.hpp"

class ICursorManager {
public:
  virtual ~ICursorManager() = default;

  virtual void MoveCursorUp(std::size_t amount = 1)    = 0;
  virtual void MoveCursorDown(std::size_t amount = 1)  = 0;
  virtual void MoveCursorLeft(std::size_t amount = 1)  = 0;
  virtual void MoveCursorRight(std::size_t amount = 1) = 0;

  virtual void SetCursorPosition(Position position) = 0;

  [[nodiscard]] virtual Position GetCursorPosition() const = 0;
};
