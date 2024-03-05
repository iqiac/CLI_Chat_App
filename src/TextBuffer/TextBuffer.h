#pragma once

#include <string>


class TextBuffer {
public:
  void        InsertText(const std::size_t position, const std::string& text);
  void        DeleteText(const std::size_t position, const std::size_t length);
  void        ReplaceText(const std::size_t position, const std::size_t length, const std::string& text);
  std::string GetText() const;

private:
  std::string _text;
};
