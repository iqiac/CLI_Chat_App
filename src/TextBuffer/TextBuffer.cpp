#include "TextBuffer.h"

#include <stdexcept>

TextBuffer::TextBuffer() {
  _allLines.push_back("");
};

TextBuffer::TextBuffer(const Line& line) {
  _allLines.push_back(line);
}

TextBuffer::TextBuffer(const std::vector<Line>& lines) {
  if (lines.empty()) {
    throw std::invalid_argument("The vector cannot be empty.");
  }
  _allLines = lines;
}

void TextBuffer::InsertText(const Position position, const std::string& text) {
  const auto& [rowIndex, colIndex]{position};
  InsertText(rowIndex, colIndex, text);
}

void TextBuffer::InsertText(const Index rowIndex, const Index colIndex, const std::string& text) {
  _allLines.at(rowIndex).insert(colIndex, text);
}

void TextBuffer::DeleteText(const Position position, const std::size_t length) {
  const auto& [rowIndex, colIndex]{position};
  DeleteText(rowIndex, colIndex, length);
}

void TextBuffer::DeleteText(const Index rowIndex, const Index colIndex, const std::size_t length) {
  _allLines.at(rowIndex).erase(colIndex, length);
}

void TextBuffer::ReplaceText(const Position position, const std::size_t length, const std::string& text) {
  const auto& [rowIndex, colIndex]{position};
  ReplaceText(rowIndex, colIndex, length, text);
}

void TextBuffer::ReplaceText(const Index rowIndex, const Index colIndex, const std::size_t length, const std::string& text) {
  _allLines.at(rowIndex).replace(colIndex, length, text);
}

void TextBuffer::InsertLine(const Index rowIndex, const Line& line) {
  if (rowIndex > _allLines.size()) {
    throw std::out_of_range("The row index must be in range.");
  }
  const auto iterator{std::next(_allLines.begin(), rowIndex)};
  _allLines.insert(iterator, line);
}

void TextBuffer::DeleteLine(const Index rowIndex) {
  const auto iterator{std::next(_allLines.begin(), rowIndex)};
  _allLines.erase(iterator);
}

void TextBuffer::ReplaceLine(const Index rowIndex, const Line& line) {
  _allLines.at(rowIndex) = line;
}

std::size_t TextBuffer::GetNumberOfLines() const {
  return _allLines.size();
}

std::size_t TextBuffer::GetLineLength(const Index rowIndex) const {
  return _allLines.at(rowIndex).size();
}

std::string TextBuffer::GetLine(const Index rowIndex) const {
  return _allLines.at(rowIndex);
}

std::vector<Line> TextBuffer::GetAllLines() const {
  return _allLines;
}

void TextBuffer::ClearAllLines() {
  _allLines.clear();
  _allLines.push_back("");
}

std::vector<Line> TextBuffer::GetData() const {
  return GetAllLines();
}

void TextBuffer::Notify() const {
  ISubject<std::vector<Line>>::Notify();
}
