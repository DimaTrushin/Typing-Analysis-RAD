//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKlavogramma.h"
//---------------------------------------------------------------------------
namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definitions of CMultiplicityTime
//---------------------------------------------------------------------------

CMultiplicitySegment::CMultiplicitySegment( unsigned int multiplicity,
                                            milliseconds segmentEndingTime)
  : Multiplicity(multiplicity),
    SegmentEndingTime(segmentEndingTime) {
}
//---------------------------------------------------------------------------
// Definitions of CKlavogrammaKey
//---------------------------------------------------------------------------

CKlavogrammaKey::CKlavogrammaKey( wchar_t symbol,
                                  milliseconds pressingTime)
  : Symbol(symbol),
    PressingTime(pressingTime) {
}
//---------------------------------------------------------------------------

void CKlavogrammaKey::AddMultiplicitySegment(
                                        unsigned int Multiplicity,
                                        milliseconds SegmentEndingTime){
  MultiplicitySegments.
    push_back(CMultiplicitySegment( Multiplicity,
                                    SegmentEndingTime));
}
//---------------------------------------------------------------------------

unsigned int CKlavogrammaKey::getNumberOfSegments() const {
  return MultiplicitySegments.size();
}
//---------------------------------------------------------------------------

milliseconds CKlavogrammaKey::getPressingTime() const {
  return PressingTime;
}
//---------------------------------------------------------------------------

milliseconds CKlavogrammaKey::getReleasingTime() const {
  if (MultiplicitySegments.empty())
    return getPressingTime();
  return MultiplicitySegments.back().SegmentEndingTime;
}
//---------------------------------------------------------------------------
// Definition of CKlavogramma
//---------------------------------------------------------------------------

size_t CKlavogramma::getNumberOfFingers() const {
  return size();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
