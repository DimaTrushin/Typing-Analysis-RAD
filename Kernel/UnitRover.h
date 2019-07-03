//---------------------------------------------------------------------------

#ifndef UnitRoverH
#define UnitRoverH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <queue>
#include <vector>
#include "UnitAnyUIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CFirstPressedHeap
//---------------------------------------------------------------------------


using CFirstPressedHeap = std::priority_queue<
                                CAnyUIterator,
                                std::vector<CAnyUIterator>,
                                CAnyUIterator::CFirstPressedOnTop>;
//---------------------------------------------------------------------------
// Declaration of CRoverBase
//---------------------------------------------------------------------------

class CRoverBase : protected CFirstPressedHeap {
public:
  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  void setNext();
  using CFirstPressedHeap::empty;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
