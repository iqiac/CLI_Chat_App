#pragma once

#include "ICursorManager.h"
#include "IObserver.h"
#include "ITextBuffer.h"

#include <memory>

class ScreenRenderer : public IObserver {
public:
  ScreenRenderer(const ITextBuffer& textBuffer, const ICursorManager& cursorManager) :
  _textBuffer(textBuffer),
  _cursorManager(cursorManager) {}

  void Update() override;

  std::string GetObserverName() const override;

private:
  void RenderText();
  void RenderCursor();

  const ITextBuffer&    _textBuffer;
  const ICursorManager& _cursorManager;
  std::string           _observerName{"ScreenRenderer"};
};
