#include "moduleb.h"

namespace module {
  ModuleB::ModuleB() : mObject(nullptr), mCallback(nullptr), mClosure(nullptr) {}

  void ModuleB::SetCallback(void *obj, CallbackType cb, void *data) {
    mObject = obj;
    mCallback = cb;
    mClosure = data;
  }

  void ModuleB::DoAction() {
    if (mCallback) {
      (*mCallback)(mObject, "Hello World", mClosure);
    }
  }
}
