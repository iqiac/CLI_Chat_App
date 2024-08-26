#include "ScreenRenderer.hpp"

#include "CommonTypes.hpp"
#include "ISubject.hpp"

#include <vector>

void ScreenRenderer::Start() {
  _screenAdapter.Start();
}

void ScreenRenderer::Stop() {
  _screenAdapter.Stop();
}

void ScreenRenderer::Update(const ISubject<std::vector<Line>>& subject) {
  const auto allLines = subject.GetData();
  _screenAdapter.SetText(allLines);
}

void ScreenRenderer::Update(const ISubject<Position>& subject) {
  const auto cursorPosition{subject.GetData()};
  _screenAdapter.SetCursor(cursorPosition);
}
