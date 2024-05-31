#include "ISubject.h"

void ISubject::Attach(const std::string observerName, const UpdateFunction updateFunction) {
  _observerUpdateFunctions.insert({observerName, updateFunction});
  Notify();
}
void ISubject::Detach(const std::string observerName) {
  _observerUpdateFunctions.erase({observerName});
}
