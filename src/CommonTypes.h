#pragma once

#include <string>

using Line  = std::string;
using Index = std::size_t;

struct Position {
  Index rowIndex;
  Index colIndex;

  bool operator==(const Position& other) const {
    return (rowIndex == other.rowIndex && colIndex == other.colIndex);
  }
};
