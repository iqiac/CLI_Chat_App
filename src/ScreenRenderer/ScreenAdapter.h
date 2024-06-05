#pragma once
#include "IScreen.h"

#include <ftxui/component/screen_interactive.hpp>

class ScreenAdapter : public IScreen {
public:
  explicit ScreenAdapter(ftxui::ScreenInteractive& screen) : _screen(screen){};

  void Loop(const ftxui::Component component) override;
  void SetCursor(const ftxui::Screen::Cursor cursor) override;
  void PostEvent(const ftxui::Event event) override;

private:
  ftxui::ScreenInteractive& _screen;
};
