#include "ScreenRenderer.h"

#include "CommonTypes.h"
#include "Mocks/ScreenMock.h"
#include "Mocks/SubjectMock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using namespace testing;

class ScreenRendererTests : public Test {
protected:
  const std::vector<Line> _defaultLines{"Line1", "Line2", "Line3"};
  const Position          _defaultPosition;

  const SubjectMock<std::vector<Line>> _textBufferMock{};
  const SubjectMock<Position>          _cursorManagerMock{};
  ScreenMock                           _screenMock{};

  ScreenRenderer _screenRenderer{_screenMock};
};

TEST_F(ScreenRendererTests, Update_CallWithTextBufferSubject_ScreenSetTextCalled) {
  EXPECT_CALL(_cursorManagerMock, GetData()).Times(0);
  EXPECT_CALL(_textBufferMock, GetData()).Times(1);
  EXPECT_CALL(_screenMock, SetText(_)).Times(1);

  _screenRenderer.Update(_textBufferMock);
}

TEST_F(ScreenRendererTests, Update_CallWithCursorManagerSubject_ScreenSetCursorCalled) {
  EXPECT_CALL(_textBufferMock, GetData()).Times(0);
  EXPECT_CALL(_cursorManagerMock, GetData()).Times(1);
  EXPECT_CALL(_screenMock, SetCursor(_)).Times(1);

  _screenRenderer.Update(_cursorManagerMock);
}

TEST_F(ScreenRendererTests, Loop_Call_ScreenLoopCalled) {
  EXPECT_CALL(_screenMock, Loop()).Times(1);

  _screenRenderer.Loop();
}

TEST_F(ScreenRendererTests, Exit_Call_ScreenExitCalled) {
  EXPECT_CALL(_screenMock, Exit()).Times(1);

  _screenRenderer.Exit();
}
