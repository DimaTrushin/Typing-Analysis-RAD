//---------------------------------------------------------------------------

#ifndef UnitApproximationDataH
#define UnitApproximationDataH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitMarkedInterval.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration CApproximationData
//---------------------------------------------------------------------------

template<class TApproximation>
class CApproximationData {
public:
  using CApproximation = TApproximation;
  CApproximation Approximation;
  CMarkedIntervalContainer StableZones;

  double getLikelyHoodMaximum() const;

  double getDiscreteDensityBias() const;
  double getDiscreteNegativeBias() const;
  double getDiscretePositiveBias() const;

  double getDiscreteMean() const;
  double getDiscreteDeviation() const;
};
//---------------------------------------------------------------------------
// Declaration CSpeedApproximationData
//---------------------------------------------------------------------------

using CSpeedApproximationData = CApproximationData<CSpeedApproximation>;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

//---------------------------------------------------------------------------
// Definition CApproximationData
//---------------------------------------------------------------------------

template<class TApproximation>
double CApproximationData<TApproximation>::getLikelyHoodMaximum() const {
  if(StableZones.empty())
    return 0.0;
  return StableZones.begin()->point;
}
//---------------------------------------------------------------------------

template<class TApproximation>
double CApproximationData<TApproximation>::getDiscreteDensityBias() const {
  return 1.0 - 2.0 * getDiscreteNegativeBias();
}
//---------------------------------------------------------------------------

template<class TApproximation>
double CApproximationData<TApproximation>::getDiscreteNegativeBias() const {
  double MLHSpeed = getLikelyHoodMaximum();
  return
    static_cast<double>(Approximation.getNumberOfSamplesLessThan(MLHSpeed)) /
    static_cast<double>(Approximation.getNumberOfSamples());
}
//---------------------------------------------------------------------------

template<class TApproximation>
double CApproximationData<TApproximation>::getDiscretePositiveBias() const {
  return 1.0 - getDiscreteNegativeBias();
}
//---------------------------------------------------------------------------

template<class TApproximation>
double CApproximationData<TApproximation>::getDiscreteMean() const {
  return Approximation.getDiscreteMean();
}
//---------------------------------------------------------------------------

template<class TApproximation>
double CApproximationData<TApproximation>::getDiscreteDeviation() const {
  return Approximation.getDiscreteDeviation();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif

