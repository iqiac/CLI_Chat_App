#include "ScreenAdapter.h"

void ScreenAdapter::Loop() {
  _screen.Loop(_vbox);
}

void ScreenAdapter::SetCursor(const ftxui::Screen::Cursor cursor) {
  _screen.SetCursor(cursor);
}

void ScreenAdapter::PostEvent(const ftxui::Event event) {
  _screen.PostEvent(event);
}

void ScreenAdapter::AddComponent(const ftxui::Component component) {
  _vbox->Add(component);
}
