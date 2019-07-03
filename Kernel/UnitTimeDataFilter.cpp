//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTimeDataFilter.h"
//---------------------------------------------------------------------------
namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition CTimeDataFilter
//---------------------------------------------------------------------------

bool CTimeDataFilter::isAcceptable(microseconds Time) const {
  return  Time >= kTimeDataLowerLimit &&
          Time <= kTimeDataUpperLimit;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
