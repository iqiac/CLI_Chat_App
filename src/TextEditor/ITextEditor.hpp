#pragma once

class ITextEditor {
public:
  virtual ~ITextEditor() = default;

  virtual void Run() = 0;
};
