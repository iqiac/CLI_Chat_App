#pragma once

#include "CommandPattern/ICommand.h"
#include "CommonTypes.h"
#include "ICursorManager.h"
#include "ITextBuffer.h"

#include <ftxui/component/component.hpp>

ftxui::Component InputHandler(ITextBuffer& textBuffer, ICursorManager& cursorManager);
