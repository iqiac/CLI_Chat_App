#include <cmath>
#include <type_traits>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
class Calculator {
public:
  // Rule of five, not necessary in this case
  Calculator()                                       = default;
  Calculator(const Calculator& other)                = default;
  Calculator(Calculator&& other) noexcept            = default;
  Calculator& operator=(const Calculator& other)     = default;
  Calculator& operator=(Calculator&& other) noexcept = default;
  ~Calculator()                                      = default;

  T Add(T lhs, T rhs);
  T Subtract(T lhs, T rhs);
  T Multiply(T lhs, T rhs);
  T Divide(T lhs, T rhs);
};
