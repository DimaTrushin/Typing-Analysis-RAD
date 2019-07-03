//---------------------------------------------------------------------------

#ifndef UnitTimeDataFilterH
#define UnitTimeDataFilterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "../UnitTimer.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration CTimeDataFilter
//---------------------------------------------------------------------------
class CTimeDataFilter {
  public:
  bool isAcceptable(microseconds Time) const;
  // corresponds to 6000 symbols per minute = 60 000 000 / TimeLimit
  static constexpr microseconds kTimeDataLowerLimit = 10000;
  // corresponds to 10 symbols per minute = 60 000 000 / TimeLimit
  static constexpr microseconds kTimeDataUpperLimit = 6000000;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
