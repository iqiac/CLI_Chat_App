#pragma once

#include "CommonTypes.h"
#include "IObserver.h"
#include "ISubjectDataGetter.h"

#include <functional>
#include <memory>
#include <set>
#include <string>

template <typename T>
class ISubject : public ISubjectDataGetter<T> {
public:
  virtual ~ISubject() = default;

  virtual void Attach(std::shared_ptr<IObserver<T>> observer) {
    _observers.insert(observer);
    observer->Update(dynamic_cast<ISubjectDataGetter<T>&>(*this));
  }

  virtual void Detach(std::shared_ptr<IObserver<T>> observer) {
    _observers.erase(observer);
  }

  virtual void Notify() const {
    for (auto& observer : _observers) {
      observer->Update(dynamic_cast<const ISubjectDataGetter<T>&>(*this));
    }
  }

  virtual T GetData() const = 0;

protected:
  std::set<std::shared_ptr<IObserver<T>>> _observers;
};
