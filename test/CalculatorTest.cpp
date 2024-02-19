#include "Calculator.h"

#include <gtest/gtest.h>


class SpyCalculator : public testing::Test {
protected:
  Calculator<int>    calculatorForInts{};
  Calculator<double> calculatorFoDoubles{};

  void SetUp() override {
  }

  void TearDown() override {
  }
};


TEST_F(SpyCalculator, Add_AddTwoIntegers_CorrectResult) {
  const int result{calculatorForInts.Add(4, 5)};

  EXPECT_EQ(9, result);
}
