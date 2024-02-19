#include "Calculator.h"


template <Arithmetic T>
T Calculator<T>::Add(T lhs, T rhs) {
  return lhs + rhs;
}

template <Arithmetic T>
T Calculator<T>::Subtract(T lhs, T rhs) {
  return lhs - rhs;
}

template <Arithmetic T>
T Calculator<T>::Multiply(T lhs, T rhs) {
  return lhs * rhs;
}

template <Arithmetic T>
T Calculator<T>::Divide(T lhs, T rhs) {
  return lhs / rhs;
}

// Explicit instantiation of template classes
template class Calculator<int>;
template class Calculator<double>;
