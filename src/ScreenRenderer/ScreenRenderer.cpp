#include "ScreenRenderer.h"

#include "CommonTypes.h"
#include "ISubject.h"

#include <vector>

void ScreenRenderer::Loop() {
  _screenAdapter.Loop();
}

void ScreenRenderer::Exit() {
  _screenAdapter.Exit();
}

void ScreenRenderer::Update(const ISubject<std::vector<Line>>& subject) {
  const auto allLines = subject.GetData();
  _screenAdapter.SetText(allLines);
}

void ScreenRenderer::Update(const ISubject<Position>& subject) {
  const auto cursorPosition{subject.GetData()};
  _screenAdapter.SetCursor(cursorPosition);
}
