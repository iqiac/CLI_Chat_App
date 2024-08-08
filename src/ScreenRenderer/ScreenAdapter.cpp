#include "ScreenAdapter.h"

#include <ftxui/component/component_base.hpp>
#include <ftxui/screen/screen.hpp>

void ScreenAdapter::Loop(ftxui::Component component) {
  _screen.Loop(component);
}

void ScreenAdapter::Exit() {
  _screen.Exit();
}

void ScreenAdapter::SetCursor(const ftxui::Screen::Cursor cursor) {
  _screen.SetCursor(cursor);
}

void ScreenAdapter::PostEvent(const ftxui::Event event) {
  _screen.PostEvent(event);
}
