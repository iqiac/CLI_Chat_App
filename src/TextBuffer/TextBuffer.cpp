#include "TextBuffer.h"


void TextBuffer::InsertText(const std::size_t position, const std::string& text) {
  if (position > this->_text.size()) {
    return;
  }
  this->_text.insert(position, text);
}

void TextBuffer::DeleteText(const std::size_t position, const std::size_t length) {
  if (position > this->_text.size()) {
    return;
  }
  this->_text.erase(position, length);
}

void TextBuffer::ReplaceText(const std::size_t position, const std::size_t length, const std::string& text) {
  this->DeleteText(position, length);
  this->InsertText(position, text);
}

std::string TextBuffer::GetText() const {
  return this->_text;
}
