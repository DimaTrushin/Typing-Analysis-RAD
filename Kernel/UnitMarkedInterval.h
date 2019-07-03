//---------------------------------------------------------------------------

#ifndef UnitMarkedIntervalH
#define UnitMarkedIntervalH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitApproximation.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CInterval
// ---------------------------------------------------------------------------
// The class defines a closed segment [first, second]

class CInterval : public std::pair<double, double> {
public:
  CInterval(double first = 0.0, double second = 0.0);
  double getCenter() const;
  double getLength() const;
};
// ---------------------------------------------------------------------------
// Declaration of CIntervalContainer
// ---------------------------------------------------------------------------

class CIntervalContainer : public std::vector<CInterval> {
};
// ---------------------------------------------------------------------------
// Declaration of CRoughMaxMinPair
// ---------------------------------------------------------------------------
// first must be an interval with a maximum
// second must be an interval containing the minimum right after the maximum

class CRoughMaxMinPair : public std::pair<CInterval,
                                          CInterval> {
public:
  CRoughMaxMinPair( const CInterval& RoughMaxInterval,
                    const CInterval& RoughMinInterval);
  CRoughMaxMinPair(const std::pair< CInterval,
                                    CInterval>& pair);
};
// ---------------------------------------------------------------------------
// Declaration of CRoughMaxMinPairContainer
// ---------------------------------------------------------------------------

class CRoughMaxMinPairContainer : public std::vector<CRoughMaxMinPair> {
};
// ---------------------------------------------------------------------------
// Declaration of CMarkedInterval
// ---------------------------------------------------------------------------
// The class defines a closed segment [first, second] with a point inside

class CMarkedInterval : public CInterval {
public:
  CMarkedInterval();
  CMarkedInterval(const CInterval& Interval);
  double point;

  template<class TApproximation>
  class Comparator {
  public:
    Comparator(const TApproximation& Approximation);
    bool operator()(const CMarkedInterval& first,
                    const CMarkedInterval& second) const;

  private:
    const TApproximation* pApproximation;
  };
};
// ---------------------------------------------------------------------------
// Declaration of CMarkedIntervalContainer
// ---------------------------------------------------------------------------

class CMarkedIntervalContainer : public std::vector<CMarkedInterval> {
public:
  void setWithIntervalContainer(const CIntervalContainer& Intervals);
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------


namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CMarkedInterval::Comparator
// ---------------------------------------------------------------------------

template<class TApproximation>
CMarkedInterval::Comparator<TApproximation>::Comparator(
                            const TApproximation& Approximation)
  : pApproximation(&Approximation){
}
// ---------------------------------------------------------------------------

template<class TApproximation>
bool CMarkedInterval::Comparator<TApproximation>::operator()(
                                const CMarkedInterval& first,
                                const CMarkedInterval& second) const{
  return  pApproximation->evaluate0(first.point) >
          pApproximation->evaluate0(second.point);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
