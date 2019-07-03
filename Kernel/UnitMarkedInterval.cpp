//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitMarkedInterval.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CInterval
// ---------------------------------------------------------------------------

CInterval::CInterval(double first, double second)
  : std::pair<double, double>(first, second){
}
// ---------------------------------------------------------------------------

double CInterval::getCenter() const{
  return (first + second) / 2.0;
}
// ---------------------------------------------------------------------------

double CInterval::getLength() const{
  return second - first;
}
// ---------------------------------------------------------------------------
// Definition of CMarkedInterval
// ---------------------------------------------------------------------------

CMarkedInterval::CMarkedInterval()
  : CInterval(),
    point(0.0) {
}
// ---------------------------------------------------------------------------

CMarkedInterval::CMarkedInterval( const CInterval& Interval)
  : CInterval(Interval), point(Interval.getCenter()){
}
// ---------------------------------------------------------------------------
// Definition of CMarkedIntervalContainer
// ---------------------------------------------------------------------------

void CMarkedIntervalContainer::setWithIntervalContainer(
                                  const CIntervalContainer& Intervals){
  clear();
  size_t size = Intervals.size();
  resize(size);
  for (size_t index = 0; index < size; ++index)
    (*this)[index] = CMarkedInterval(Intervals[index]);
}
// ---------------------------------------------------------------------------
// Definitions of CRoughMaxMinPair
// ---------------------------------------------------------------------------

CRoughMaxMinPair::CRoughMaxMinPair(
                              const CInterval& RoughMaxInterval,
                              const CInterval& RoughMinInterval)
  : std::pair<CInterval, CInterval>(RoughMaxInterval,
                                    RoughMinInterval){
}
// ---------------------------------------------------------------------------

CRoughMaxMinPair::CRoughMaxMinPair(
                    const std::pair<CInterval, CInterval>& pair)
  : std::pair<CInterval, CInterval>(pair) {
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
