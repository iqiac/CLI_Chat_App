#include "CommonTypes.h"

class IScreenRenderer {

public:
  virtual ~IScreenRenderer() = default;

private:
  virtual void RenderText(const std::vector<Line>& allLines) = 0;
  virtual void RenderCursor(const Position& cursorPosition)  = 0;
};
