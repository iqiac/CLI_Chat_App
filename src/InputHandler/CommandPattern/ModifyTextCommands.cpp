#include "ModifyTextCommands.hpp"

#include "ICommand.hpp"
#include "ICursorManager.hpp"
#include "ITextBuffer.hpp"

#include <cstddef>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace {
class InsertText : public ICommand {
public:
  InsertText(ITextBuffer& textBuffer, ICursorManager& cursorManager, const std::string text) :
  _textBuffer(textBuffer),
  _cursorManager(cursorManager),
  _text(text) {}

  void Execute() const override {
    _textBuffer.InsertText(_cursorManager.GetCursorPosition(), _text);
    _cursorManager.MoveCursorRight(_text.size());
  }

private:
  ITextBuffer&      _textBuffer;
  ICursorManager&   _cursorManager;
  const std::string _text;
};

class RemoveTextBackward : public ICommand {
public:
  RemoveTextBackward(ITextBuffer& textBuffer, ICursorManager& cursorManager, const std::size_t textSize = 1) :
  _textBuffer(textBuffer),
  _cursorManager(cursorManager),
  _textSize(textSize) {}

  void Execute() const override {
    const auto currentPosition{_cursorManager.GetCursorPosition()};
    if (currentPosition.GetColIndex() < _textSize) {
      return;
    }
    _cursorManager.MoveCursorLeft(_textSize);
    const auto newPosition{_cursorManager.GetCursorPosition()};
    _textBuffer.DeleteText(newPosition, _textSize);
  }

private:
  ITextBuffer&      _textBuffer;
  ICursorManager&   _cursorManager;
  const std::size_t _textSize;
};

class RemoveTextForward : public ICommand {
public:
  RemoveTextForward(ITextBuffer& textBuffer, ICursorManager& cursorManager, const std::size_t textSize = 1) :
  _textBuffer(textBuffer),
  _cursorManager(cursorManager),
  _textSize(textSize) {}

  void Execute() const override {
    const auto currentPosition{_cursorManager.GetCursorPosition()};
    _textBuffer.DeleteText(currentPosition, _textSize);
  }

private:
  ITextBuffer&          _textBuffer;
  const ICursorManager& _cursorManager;
  const std::size_t     _textSize;
};

} // namespace

void ModifyTextCommands::RegisterCommands(CommandPattern::CommandMap& commandMap, ICursorManager& cursorManager,
                                          ITextBuffer& textBuffer) {
  constexpr auto alphabetSize{26};

  std::vector<char> alphabetUpperCase(alphabetSize);
  std::iota(alphabetUpperCase.begin(), alphabetUpperCase.end(), 'A');

  std::vector<char> alphabetLowerCase(alphabetSize);
  std::iota(alphabetLowerCase.begin(), alphabetLowerCase.end(), 'a');

  for (auto i{0}; i < alphabetSize; ++i) {
    const std::string upperCase{alphabetUpperCase[i]};
    const std::string lowerCase{alphabetLowerCase[i]};
    commandMap[upperCase] = [&textBuffer, &cursorManager, upperCase] {
      return std::make_unique<InsertText>(textBuffer, cursorManager, upperCase);
    };
    commandMap[lowerCase] = [&textBuffer, &cursorManager, lowerCase] {
      return std::make_unique<InsertText>(textBuffer, cursorManager, lowerCase);
    };
  }

  commandMap["\x7f"] = [&textBuffer, &cursorManager] {
    return std::make_unique<RemoveTextBackward>(textBuffer, cursorManager);
  };
  commandMap["\x1b[3~"] = [&textBuffer, &cursorManager] {
    return std::make_unique<RemoveTextForward>(textBuffer, cursorManager);
  };
}
