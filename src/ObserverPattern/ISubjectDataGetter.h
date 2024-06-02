#pragma once

template <typename T>
class ISubjectDataGetter {
public:
  virtual ~ISubjectDataGetter() = default;

  virtual T GetData() const = 0;
};
