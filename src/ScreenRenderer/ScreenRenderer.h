#pragma once

#include "CursorManagerInterfaces.h"
#include "ObserverPattern.h"
#include "TextBufferInterfaces.h"

class ScreenRenderer : public IObserver {
public:
  ScreenRenderer(ITextBufferContent& textBufferContent, ICursorManagerInfo& cursorManagerInfo) :
  _textBufferContent(textBufferContent),
  _cursorManagerInfo(cursorManagerInfo) {}

  void Update() override;

private:
  void RenderText();
  void RenderCursor();

  ITextBufferContent& _textBufferContent;
  ICursorManagerInfo& _cursorManagerInfo;
};
