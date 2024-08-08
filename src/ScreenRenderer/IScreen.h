#pragma once
#include "CommonTypes.h"

#include <ftxui/component/component.hpp>

class IScreen {
public:
  virtual ~IScreen() = default;

  virtual void Loop(ftxui::Component component)        = 0;
  virtual void Exit()                                  = 0;
  virtual void SetCursor(ftxui::Screen::Cursor cursor) = 0;
  virtual void PostEvent(ftxui::Event event)           = 0;
};
