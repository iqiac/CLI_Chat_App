#pragma once

#include "CommonTypes.h"

#include <vector>

class ITextBuffer {
public:
  virtual ~ITextBuffer() = default;

  virtual void InsertText(Position position, const std::string& text)              = 0;
  virtual void InsertText(Index rowIndex, Index colIndex, const std::string& text) = 0;

  virtual void DeleteText(Position position, std::size_t length)              = 0;
  virtual void DeleteText(Index rowIndex, Index colIndex, std::size_t length) = 0;

  virtual void ReplaceText(Position position, std::size_t length, const std::string& text)              = 0;
  virtual void ReplaceText(Index rowIndex, Index colIndex, std::size_t length, const std::string& text) = 0;

  virtual void InsertLine(Index rowIndex, const Line& line)  = 0;
  virtual void DeleteLine(Index rowIndex)                    = 0;
  virtual void ReplaceLine(Index rowIndex, const Line& line) = 0;

  [[nodiscard]] virtual std::size_t       GetNumberOfLines() const            = 0;
  [[nodiscard]] virtual std::size_t       GetLineLength(Index rowIndex) const = 0;
  [[nodiscard]] virtual Line              GetLine(Index rowIndex) const       = 0;
  [[nodiscard]] virtual std::vector<Line> GetAllLines() const                 = 0;
  virtual void                            ClearAllLines()                     = 0;
};
