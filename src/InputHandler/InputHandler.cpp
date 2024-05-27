#include "InputHandler.h"

#include "CommandPattern/MoveCursorCommands.h"

#include <map>
#include <memory>

namespace {

class InputHandlerImpl : public ftxui::ComponentBase {
public:
  InputHandlerImpl(ITextBuffer& textBuffer, ICursorManager& cursorManager) :
  _textBuffer(textBuffer),
  _cursorManager(cursorManager) {
    using namespace ftxui;
    _cursorCommandMap[Event::ArrowUp]    = std::make_unique<MoveCursorUp>(_cursorManager);
    _cursorCommandMap[Event::ArrowDown]  = std::make_unique<MoveCursorDown>(_cursorManager);
    _cursorCommandMap[Event::ArrowLeft]  = std::make_unique<MoveCursorLeft>(_cursorManager);
    _cursorCommandMap[Event::ArrowRight] = std::make_unique<MoveCursorRight>(_cursorManager);
  }

  bool OnEvent(ftxui::Event event) override {
    if (_cursorCommandMap.contains(event)) {
      _cursorCommandMap[event]->Execute();
      return true;
    }
    return false;
  }

private:
  struct EventComparator {
    bool operator()(const ftxui::Event& lhs, const ftxui::Event& rhs) const {
      return lhs.input() < rhs.input();
    }
  };
  ITextBuffer&                                                       _textBuffer;
  ICursorManager&                                                    _cursorManager;
  std::map<ftxui::Event, std::unique_ptr<ICommand>, EventComparator> _cursorCommandMap;
};

} // namespace

ftxui::Component InputHandler(ITextBuffer& textBuffer, ICursorManager& cursorManager) {
  return ftxui::Make<InputHandlerImpl>(textBuffer, cursorManager);
}
