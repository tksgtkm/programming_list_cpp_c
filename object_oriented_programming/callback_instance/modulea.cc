#include <iostream>
#include "modulea.h"

namespace module {
  void ModuleA::StaticWrapper(void *obj, const std::string &name, void *data) {
    ModuleA *self = static_cast<ModuleA *>(obj);
    self->InstanceMethod(name, data);
  }

  void ModuleA::InstanceMethod(const std::string &name, void *data) {
    int closure = *static_cast<int *>(data);
    std::cout << "In instance callback: '" << name << "' (closure=" << closure << ")" << std::endl;
  }
}
