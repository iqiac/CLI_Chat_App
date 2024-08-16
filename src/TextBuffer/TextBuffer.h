#pragma once

#include "ISubject.h"
#include "ITextBuffer.h"

class TextBuffer : public ITextBuffer, public ISubject<std::vector<Line>> {
public:
  TextBuffer() : _allLines({""}) {}
  explicit TextBuffer(const Line& line) : _allLines({line}) {}
  explicit TextBuffer(const std::vector<Line>& lines);

  void InsertText(Position position, const std::string& text) override;
  void InsertText(Index rowIndex, Index colIndex, const std::string& text) override;

  void DeleteText(Position position, std::size_t length = 1) override;
  void DeleteText(Index rowIndex, Index colIndex, std::size_t length = 1) override;

  void ReplaceText(Position position, std::size_t length, const std::string& text) override;
  void ReplaceText(Index rowIndex, Index colIndex, std::size_t length, const std::string& text) override;

  void InsertLine(Index rowIndex, const Line& line) override;
  void DeleteLine(Index rowIndex) override;
  void ReplaceLine(Index rowIndex, const Line& line) override;

  [[nodiscard]] std::size_t       GetNumberOfLines() const override;
  [[nodiscard]] std::size_t       GetLineLength(Index rowIndex) const override;
  [[nodiscard]] Line              GetLine(Index rowIndex) const override;
  [[nodiscard]] std::vector<Line> GetAllLines() const override;
  void                            ClearAllLines() override;

  [[nodiscard]] std::vector<Line> GetData() const override;
  void                            Notify() const override;

private:
  std::vector<Line> _allLines;
};
