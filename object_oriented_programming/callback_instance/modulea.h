#ifndef __MODULE_A
#define __MODULE_A

#include <string>

namespace module {
  /*
  An object that wishes to receive a callback from another module.
  To simplify calling an member function for a specific instance of this class,
  a static wrapper function can be used for the callback.
  This essentially accepts the object instance as an additional parameter.
  */
  class ModuleA {
  public:
    // A static function that lets you call a member function
    static void StaticWrapper(void *obj, const std::string &name, void *data);

    // The member function callback
    void InstanceMethod(const std::string &name, void *data);
  };
}

#endif
