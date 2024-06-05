#pragma once
#include "CommonTypes.h"

#include <ftxui/component/component.hpp>

class IScreen {
public:
  virtual ~IScreen() = default;

  virtual void Loop(const ftxui::Component component)        = 0;
  virtual void SetCursor(const ftxui::Screen::Cursor cursor) = 0;
  virtual void PostEvent(const ftxui::Event event)           = 0;
};
