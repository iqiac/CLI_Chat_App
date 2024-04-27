#pragma once

#include "CommonTypes.h"

#include <vector>

class ITextBuffer {
public:
  ~ITextBuffer() = default;

  virtual void InsertText(const Position position, const std::string& text)                    = 0;
  virtual void InsertText(const Index rowIndex, const Index colIndex, const std::string& text) = 0;

  virtual void DeleteText(const Position position, const std::size_t length)                    = 0;
  virtual void DeleteText(const Index rowIndex, const Index colIndex, const std::size_t length) = 0;

  virtual void ReplaceText(const Position position, const std::size_t length, const std::string& text) = 0;
  virtual void ReplaceText(const Index rowIndex, const Index colIndex, const std::size_t length, const std::string& text) = 0;

  virtual void InsertLine(const Index rowIndex, const Line& line)  = 0;
  virtual void DeleteLine(const Index rowIndex)                    = 0;
  virtual void ReplaceLine(const Index rowIndex, const Line& line) = 0;

  virtual std::size_t       GetNumberOfLines() const                  = 0;
  virtual std::size_t       GetLineLength(const Index rowIndex) const = 0;
  virtual Line              GetLine(const Index rowIndex) const       = 0;
  virtual std::vector<Line> GetAllLines() const                       = 0;
  virtual void              ClearAllLines()                           = 0;
};
