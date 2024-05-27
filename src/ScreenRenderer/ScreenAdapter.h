#pragma once
#include "IScreen.h"

#include <ftxui/component/screen_interactive.hpp>

class ScreenAdapter : public IScreen {
public:
  explicit ScreenAdapter(ftxui::ScreenInteractive& screen) : _screen(screen){};

  void Loop() override;
  void SetCursor(const ftxui::Screen::Cursor cursor) override;
  void PostEvent(const ftxui::Event event) override;
  void AddComponent(const ftxui::Component component) override;

private:
  ftxui::ScreenInteractive& _screen;
  ftxui::Component          _vbox;
};
