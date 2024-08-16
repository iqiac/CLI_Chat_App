#include "CommandCreator.h"

#include "EditorControlCommands.h"
#include "ICursorManager.h"
#include "ITextBuffer.h"
#include "ModifyTextCommands.h"
#include "MoveCursorCommands.h"
#include "ScreenRenderer.h"

#include <memory>
#include <numeric>
#include <string>
#include <vector>

CommandCreator::CommandCreator(ITextBuffer& textBuffer, ICursorManager& cursorManager, ScreenRenderer& screenRenderer) :
_commandMap({}) {
  // Cursor movement commands
  _commandMap["\x1b[A"] = [&cursorManager] { return std::make_unique<MoveCursorUp>(cursorManager); };
  _commandMap["\x1b[B"] = [&cursorManager] { return std::make_unique<MoveCursorDown>(cursorManager); };
  _commandMap["\x1b[D"] = [&cursorManager] { return std::make_unique<MoveCursorLeft>(cursorManager); };
  _commandMap["\x1b[C"] = [&cursorManager] { return std::make_unique<MoveCursorRight>(cursorManager); };

  // Editor control commands
  _commandMap["\x1b"] = [&screenRenderer] { return std::make_unique<ExitEditor>(screenRenderer); };

  // Text modification commands
  constexpr auto alphabetSize{26};

  std::vector<char> alphabetUpperCase(alphabetSize);
  std::iota(alphabetUpperCase.begin(), alphabetUpperCase.end(), 'A');

  std::vector<char> alphabetLowerCase(alphabetSize);
  std::iota(alphabetLowerCase.begin(), alphabetLowerCase.end(), 'a');

  for (auto i{0}; i < alphabetSize; ++i) {
    const std::string upperCase{alphabetUpperCase[i]};
    const std::string lowerCase{alphabetLowerCase[i]};
    _commandMap[upperCase] = [&textBuffer, &cursorManager, upperCase] {
      return std::make_unique<InsertText>(textBuffer, cursorManager, upperCase);
    };
    _commandMap[lowerCase] = [&textBuffer, &cursorManager, lowerCase] {
      return std::make_unique<InsertText>(textBuffer, cursorManager, lowerCase);
    };
  }

  _commandMap["\x7f"] = [&textBuffer, &cursorManager] {
    return std::make_unique<RemoveTextBackward>(textBuffer, cursorManager, 1);
  };
  _commandMap["\x1b[3~"] = [&textBuffer, &cursorManager] {
    return std::make_unique<RemoveTextForward>(textBuffer, cursorManager, 1);
  };
}

CommandPattern::CommandMap CommandCreator::GetCommandMap() const {
  return _commandMap;
}
