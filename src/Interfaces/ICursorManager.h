#pragma once

#include <utility>

class ICursorManager {
public:
  virtual ~ICursorManager() = default;

  virtual void MoveCursorUp()    = 0;
  virtual void MoveCursorDown()  = 0;
  virtual void MoveCursorLeft()  = 0;
  virtual void MoveCursorRight() = 0;

  virtual void SetCursorPosition(const std::size_t row, const std::size_t col) = 0;

  virtual std::pair<std::size_t, std::size_t> GetCursorPosition() const = 0;
};
