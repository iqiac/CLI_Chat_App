#pragma once

#include "TextBufferInterfaces.h"

#include <string>
#include <vector>

class TextBuffer : public ITextBufferModification, ITextBufferInfo {
public:
  TextBuffer();
  TextBuffer(const std::string& line);
  TextBuffer(const std::vector<std::string>& lines);

  void InsertText(const std::pair<std::size_t, std::size_t> position, const std::string& text) override;
  void InsertText(const std::size_t rowIndex, const std::size_t colIndex, const std::string& text) override;

  void DeleteText(const std::pair<std::size_t, std::size_t> position, const std::size_t length) override;
  void DeleteText(const std::size_t rowIndex, const std::size_t colIndex, const std::size_t length) override;

  void ReplaceText(const std::pair<std::size_t, std::size_t> position, const std::size_t length, const std::string& text) override;
  void ReplaceText(const std::size_t  rowIndex,
                   const std::size_t  colIndex,
                   const std::size_t  length,
                   const std::string& text) override;

  void InsertLine(const std::size_t rowIndex, const std::string& line) override;
  void DeleteLine(const std::size_t rowIndex) override;
  void ReplaceLine(const std::size_t rowIndex, const std::string& line) override;

  std::size_t              GetNumberOfLines() const override;
  std::size_t              GetLineLength(const std::size_t rowIndex) const override;
  std::string              GetLine(const std::size_t rowIndex) const override;
  std::vector<std::string> GetAllLines() const override;
  void                     ClearAllLines() override;

private:
  std::vector<std::string> _allLines;
};
