#ifndef __MODULE_B
#define __MODULE_B

#include <string>
#include <cstdlib>

namespace module {
  /*
  An object that can register a callback function and then
  invoke that callback when desired
  */
  class ModuleB {
  public:
    // A type for the function signature that is accepted as a callback
    typedef void(*CallbackType)(void *obj, const std::string &name, void *data);

    ModuleB();
    // Set the callback function . Only one callback can be registerd.
    void SetCallback(void *obj, CallbackType cb, void *data);
    // Call the callback function
    void DoAction();

  private:
    void         *mObject;
    CallbackType mCallback;
    void         *mClosure;
  };
}

#endif
