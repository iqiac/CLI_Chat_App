#pragma once

#include <utility>

class ICursorManagerInfo {
public:
  virtual ~ICursorManagerInfo() = default;

  virtual std::pair<std::size_t, std::size_t> GetCursorPosition() const = 0;
};

class ICursorManagerMovement {
public:
  virtual ~ICursorManagerMovement() = default;

  virtual void MoveCursorUp()    = 0;
  virtual void MoveCursorDown()  = 0;
  virtual void MoveCursorLeft()  = 0;
  virtual void MoveCursorRight() = 0;

  virtual void SetCursorPosition(const std::size_t row, const std::size_t col) = 0;
};
