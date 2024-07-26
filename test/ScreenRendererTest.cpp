#include "ScreenRenderer.h"

#include "CommonTypes.h"
#include "Mocks/ScreenMock.h"
#include "Mocks/SubjectMock.h"

#include <cstddef>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace testing;

class ScreenRendererTests : public Test {
protected:
  const std::vector<Line> defaultLines{"Line1", "Line2", "Line3"};
  const Position          defaultPosition;

  const SubjectMock<std::vector<Line>> textBufferMock{};
  const SubjectMock<Position>          cursorManagerMock{};
  ScreenMock                           screenMock{};

  ScreenRenderer screenRenderer{screenMock};
};

TEST_F(ScreenRendererTests, Update_CallWithTextBufferSubject_ScreenPostEventCalled) {
  EXPECT_CALL(screenMock, SetCursor(_)).Times(0);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(1);

  screenRenderer.Update(textBufferMock);
}

TEST_F(ScreenRendererTests, Update_CallWithCursorManagerSubject_ScreenPostEventAndSetCursorCalled) {
  EXPECT_CALL(screenMock, SetCursor(_)).Times(1);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(1);

  screenRenderer.Update(cursorManagerMock);
}

TEST_F(ScreenRendererTests, Update_CallWithCursorManagerSubjectAndValidPosition_ScreenPostEventAndSetCursorCalled) {
  const Position validPosition{1, 1};
  EXPECT_CALL(cursorManagerMock, GetData()).WillOnce(Return(validPosition));
  EXPECT_CALL(screenMock, SetCursor(_)).Times(1);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(1);

  screenRenderer.Update(cursorManagerMock);
}

TEST_F(ScreenRendererTests, Update_CallWithCursorManagerMessageAndInvalidPosition_ThrowsException) {
  const Index    overflowValue{static_cast<std::size_t>(std::numeric_limits<int>::max()) + 1};
  const Position invalidPosition{overflowValue, overflowValue};
  EXPECT_CALL(cursorManagerMock, GetData()).WillOnce(Return(invalidPosition));
  EXPECT_CALL(screenMock, SetCursor(_)).Times(0);
  EXPECT_CALL(screenMock, PostEvent(ftxui::Event::Custom)).Times(0);

  EXPECT_THROW(screenRenderer.Update(cursorManagerMock), std::overflow_error);
}

TEST_F(ScreenRendererTests, Loop_Call_ScreenLoopCalled) {
  EXPECT_CALL(screenMock, Loop(_)).Times(1);

  screenRenderer.Loop();
}

TEST_F(ScreenRendererTests, Exit_Call_ScreenExitCalled) {
  EXPECT_CALL(screenMock, Exit()).Times(1);

  screenRenderer.Exit();
}
