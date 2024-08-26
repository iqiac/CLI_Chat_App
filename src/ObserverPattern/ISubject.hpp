#pragma once

#include "CommonTypes.hpp"
#include "IObserver.hpp"

#include <memory>
#include <set>

template <typename T>
class ISubject {
public:
  virtual ~ISubject() = default;

  virtual void Attach(std::shared_ptr<IObserver<T>> observer) {
    _observers.insert(observer);
    observer->Update(*this);
  }

  virtual void Detach(std::shared_ptr<IObserver<T>> observer) {
    _observers.erase(observer);
  }

  virtual void Notify() const {
    for (auto& observer : _observers) {
      observer->Update(*this);
    }
  }

  [[nodiscard]] virtual T GetData() const = 0;

protected:
  std::set<std::shared_ptr<IObserver<T>>> _observers;
};
