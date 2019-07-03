//---------------------------------------------------------------------------

#ifndef UnitAnyGlobalAccessH
#define UnitAnyGlobalAccessH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <memory>
#include <utility>
#include <cassert>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CAnyGlobalAccess
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
class CAnyGlobalAccess {
public:
  using CStaticObjectType = std::unique_ptr<TAccessible>;
  CAnyGlobalAccess();
  template<class... TArg>
  CAnyGlobalAccess(TArg&&... Arg);
  inline TAccessible* operator->() const;
  inline TAccessible* ptr() const;
  inline TAccessible& ref() const;
private:
  static std::unique_ptr<TAccessible> gObject_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of statics of CAnyGlobalAccess
//---------------------------------------------------------------------------
// This definition must appear on any specialization of the template in cpp

//template<class TAccessible, class TID>
//std::unique_ptr<TAccessible>
//CAnyGlobalAccess<TAccessible, TID>::gObject_ = nullptr;
//---------------------------------------------------------------------------
// Definition of CAnyGlobalAccessible
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
CAnyGlobalAccess<TAccessible, TID>::CAnyGlobalAccess() {
  assert(gObject_);
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
template<class... TArg>
CAnyGlobalAccess<TAccessible, TID>::CAnyGlobalAccess(TArg&&... Arg) {
  // not thread safe
  if(!gObject_)
    gObject_ = std::make_unique<TAccessible>(std::forward<TArg>(Arg)...);
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
TAccessible* CAnyGlobalAccess<TAccessible, TID>::operator->() const {
  return ptr();
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
TAccessible* CAnyGlobalAccess<TAccessible, TID>::ptr() const {
  return gObject_.get();
}
//---------------------------------------------------------------------------

template<class TAccessible, class TID>
TAccessible& CAnyGlobalAccess<TAccessible, TID>::ref() const {
  return *gObject_;
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
