#pragma once

#include "CommonTypes.h"

class ICursorManager {
public:
  virtual ~ICursorManager() = default;

  virtual void MoveCursorUp()    = 0;
  virtual void MoveCursorDown()  = 0;
  virtual void MoveCursorLeft()  = 0;
  virtual void MoveCursorRight() = 0;

  virtual void SetCursorPosition(const Position position) = 0;

  virtual Position GetCursorPosition() const = 0;
};
