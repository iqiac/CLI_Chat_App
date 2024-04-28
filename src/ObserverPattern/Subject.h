#pragma once

#include "ISubject.h"

class Subject : public ISubject {
public:
  void Attach(const std::string observerName, const UpdateFunction updateFunction) override;
  void Detach(const std::string observerName) override;
};
