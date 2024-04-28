#include "Subject.h"

void Subject::Attach(const std::string observerName, const UpdateFunction updateFunction) {
  _observerUpdateFunctions.insert({observerName, updateFunction});
  Notify();
}

void Subject::Detach(const std::string observerName) {
  _observerUpdateFunctions.erase(observerName);
}
