#pragma once

#include <string>

using Line  = std::string;
using Index = std::size_t;

class Position {
public:
  Position() = default;
  Position(Index rowIndex, Index colIndex) : _rowIndex(rowIndex), _colIndex(colIndex) {}

  [[nodiscard]] Index GetRowIndex() const {
    return _rowIndex;
  }
  [[nodiscard]] Index GetColIndex() const {
    return _colIndex;
  }

  [[nodiscard]] std::pair<Index, Index> GetRowAndColIndices() const {
    return {_rowIndex, _colIndex};
  }
  bool operator==(const Position& other) const {
    return (_rowIndex == other._rowIndex && _colIndex == other._colIndex);
  }

private:
  Index _rowIndex{0};
  Index _colIndex{0};
};
