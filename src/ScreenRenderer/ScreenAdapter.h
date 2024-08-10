#pragma once
#include "IScreen.h"

#include <ftxui/component/screen_interactive.hpp>

class ScreenAdapter : public IScreen {
public:
  explicit ScreenAdapter(ftxui::ScreenInteractive& screen) : _screen(screen) {}

  void Loop(ftxui::Component component) override;
  void Exit() override;
  void SetCursor(Position position) override;
  void PostEvent(ftxui::Event event) override;

private:
  ftxui::ScreenInteractive& _screen;
};
