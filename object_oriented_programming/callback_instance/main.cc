#include "modulea.h"
#include "moduleb.h"

int main() {
  module::ModuleA a;
  module::ModuleB b;

  int closure = 42;

  b.SetCallback(&a, module::ModuleA::StaticWrapper, &closure);
  b.DoAction();
}
