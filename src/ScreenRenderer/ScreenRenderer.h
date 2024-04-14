#pragma once

#include "CursorManagerInterfaces.h"
#include "ObserverPattern.h"
#include "TextBufferInterfaces.h"

#include <memory>

class ScreenRenderer : public IObserver {
public:
  ScreenRenderer(std::shared_ptr<ITextBufferContent> textBufferContent,
                 std::shared_ptr<ICursorManagerInfo> cursorManagerInfo) :
  _textBufferContent(textBufferContent),
  _cursorManagerInfo(cursorManagerInfo) {}

  void Update() override;

private:
  void RenderText();
  void RenderCursor();

  std::shared_ptr<ITextBufferContent> _textBufferContent;
  std::shared_ptr<ICursorManagerInfo> _cursorManagerInfo;
  std::string                         _observerName{"ScreenRenderer"};
};
