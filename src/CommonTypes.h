#pragma once

#include <functional>
#include <string>
#include <variant>
#include <vector>

using Line  = std::string;
using Index = std::size_t;

struct Position {
  Index rowIndex;
  Index colIndex;

  bool operator==(const Position& other) const {
    return (rowIndex == other.rowIndex && colIndex == other.colIndex);
  }
};

enum class EventSender {
  TEXT_BUFFER,
  CURSOR_MANAGER,
};

using DataReference = std::variant<std::reference_wrapper<const std::vector<Line>>, std::reference_wrapper<const Position>>;

struct EventMessage {
  EventSender   eventSender;
  DataReference dataRef;
};

using UpdateFunction = std::function<void(EventMessage)>;
