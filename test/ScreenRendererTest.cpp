#include "ScreenRenderer.h"

#include "Mocks/ScreenMock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class ScreenRendererTests : public Test {
protected:
  const std::vector<Line> defaultLines{"Line1", "Line2", "Line3"};
  const Position          defaultPosition{.rowIndex = 0, .colIndex = 0};
  ScreenMock              screenMock{};
  ScreenRenderer          screenRenderer{screenMock};
};

TEST_F(ScreenRendererTests, GetObserverName_Call_GetCorrectName) {
  const auto expectedName{"ScreenRenderer"};

  const auto actualName{screenRenderer.GetObserverName()};

  EXPECT_THAT(actualName, StrEq(expectedName));
}

TEST_F(ScreenRendererTests, Update_CallWithTextBufferMessage_ScreenPostEventCalled) {
  EventMessage message{.eventSender = EventSender::TEXT_BUFFER, .dataReference = defaultLines};
  EXPECT_CALL(screenMock, SetCursor(_)).Times(0);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(1);

  screenRenderer.Update(message);
}

TEST_F(ScreenRendererTests, Update_CallWithCursorManagerMessage_ScreenPostEventAndSetCursorCalled) {
  EventMessage message{.eventSender = EventSender::CURSOR_MANAGER, .dataReference = defaultPosition};
  EXPECT_CALL(screenMock, SetCursor(_)).Times(1);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(1);

  screenRenderer.Update(message);
}

TEST_F(ScreenRendererTests, Update_CallWithCursorManagerMessageAndValidPosition_ScreenPostEventAndSetCursorCalled) {
  Position     validPosition{.rowIndex = 1, .colIndex = 1};
  EventMessage message{.eventSender = EventSender::CURSOR_MANAGER, .dataReference = validPosition};
  EXPECT_CALL(screenMock, SetCursor(_)).Times(1);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(1);

  screenRenderer.Update(message);
}

TEST_F(ScreenRendererTests, Update_CallWithCursorManagerMessageAndInvalidPosition_ThrowsException) {
  Index        overflowValue{static_cast<std::size_t>(std::numeric_limits<int>::max()) + 1};
  Position     invalidPosition{.rowIndex = overflowValue, .colIndex = overflowValue};
  EventMessage message{.eventSender = EventSender::CURSOR_MANAGER, .dataReference = invalidPosition};
  EXPECT_CALL(screenMock, SetCursor(_)).Times(0);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(0);

  EXPECT_THROW(screenRenderer.Update(message), std::overflow_error);
}

TEST_F(ScreenRendererTests, Loop_Call_ScreenLoopCalled) {
  EXPECT_CALL(screenMock, Loop(_)).Times(1);

  screenRenderer.Loop();
}
