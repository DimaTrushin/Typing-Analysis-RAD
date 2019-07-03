//---------------------------------------------------------------------------

#ifndef UnitVectorHeapWithAccessH
#define UnitVectorHeapWithAccessH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vector>
#include <algorithm>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Declaration of CVectorHeapWithAccess
//---------------------------------------------------------------------------

template<class Type, class WhatOnTop>
class CVectorHeapWithAccess : protected std::vector<Type> {
  using CBase = std::vector<Type>;
public:
  inline void make_heap();
  inline void push_heap(const Type& Element);
  inline void push_heap(Type&& Element);
  inline void pop_heap();
  inline const Type& top() const;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CVectorHeapWithAccess
//---------------------------------------------------------------------------

template<class Type, class WhatOnTop>
void CVectorHeapWithAccess<Type, WhatOnTop>::make_heap() {
    WhatOnTop Comparator;
    std::make_heap(CBase::begin(), CBase::end(), Comparator);
}
//---------------------------------------------------------------------------

template<class Type, class WhatOnTop>
void CVectorHeapWithAccess<Type, WhatOnTop>::push_heap(const Type& Element) {
    CBase::push_back(Element);
    WhatOnTop Comparator;
    std::push_heap(CBase::begin(), CBase::end(), Comparator);
}
//---------------------------------------------------------------------------

template<class Type, class WhatOnTop>
void CVectorHeapWithAccess<Type, WhatOnTop>::push_heap(Type&& Element) {
    CBase::push_back(Element);
    WhatOnTop Comparator;
    std::push_heap(CBase::begin(), CBase::end(), Comparator);
}
//---------------------------------------------------------------------------

template<class Type, class WhatOnTop>
void CVectorHeapWithAccess<Type, WhatOnTop>::pop_heap() {
    WhatOnTop Comparator;
    std::pop_heap(CBase::begin(), CBase::end(), Comparator);
    CBase::pop_back();
}
//---------------------------------------------------------------------------

template<class Type, class WhatOnTop>
const Type& CVectorHeapWithAccess<Type, WhatOnTop>::top() const {
    return CBase::front();
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
