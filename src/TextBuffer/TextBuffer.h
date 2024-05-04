#pragma once

#include "ITextBuffer.h"

class TextBuffer : public ITextBuffer {
public:
  TextBuffer();
  TextBuffer(const Line& line);
  TextBuffer(const std::vector<Line>& lines);

  void InsertText(const Position position, const std::string& text) override;
  void InsertText(const Index rowIndex, const Index colIndex, const std::string& text) override;

  void DeleteText(const Position position, const std::size_t length) override;
  void DeleteText(const Index rowIndex, const Index colIndex, const std::size_t length) override;

  void ReplaceText(const Position position, const std::size_t length, const std::string& text) override;
  void ReplaceText(const Index rowIndex, const Index colIndex, const std::size_t length, const std::string& text) override;

  void InsertLine(const Index rowIndex, const Line& line) override;
  void DeleteLine(const Index rowIndex) override;
  void ReplaceLine(const Index rowIndex, const Line& line) override;

  std::size_t       GetNumberOfLines() const override;
  std::size_t       GetLineLength(const Index rowIndex) const override;
  Line              GetLine(const Index rowIndex) const override;
  std::vector<Line> GetAllLines() const override;
  void              ClearAllLines() override;

private:
  std::vector<Line> _allLines;
};
