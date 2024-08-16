#include "EditorControlCommands.h"

#include "ICommand.h"
#include "IScreenRenderer.h"

#include <memory>

namespace {
class ExitEditor : public ICommand {
public:
  explicit ExitEditor(IScreenRenderer& screenRenderer) : _screenRenderer(screenRenderer) {}
  void Execute() const override {
    _screenRenderer.Stop();
  }

private:
  IScreenRenderer& _screenRenderer;
};
} // namespace

void EditorControlCommands::RegisterCommands(CommandPattern::CommandMap& commandMap, IScreenRenderer& screenRenderer) {
  commandMap["\x1b"] = [&screenRenderer] { return std::make_unique<ExitEditor>(screenRenderer); };
}
