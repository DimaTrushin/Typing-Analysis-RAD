//---------------------------------------------------------------------------

#ifndef UnitApproximationDataMakerH
#define UnitApproximationDataMakerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTimeSpeedDataMaker.h"
#include "UnitApproximationData.h"
#include "UnitStableZonesFiller.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration CSpeedApproximationDataMaker
//---------------------------------------------------------------------------

class CSpeedApproximationDataMaker {
  using CApproximation = CSpeedApproximationData::CApproximation;
public:
  void convert( const CAnalysisData& AnalysisData,
                EOutputMode OutputMode,
                const CTextMode& TextMode,
                EAnalysisType AnalysisType,
                CSpeedApproximationData* pApproximationData) const;
private:
  void fillApproximation( const CAnalysisData& AnalysisData,
                          EOutputMode OutputMode,
                          const CTextMode& TextMode,
                          EAnalysisType AnalysisType,
                          CApproximation* pApproximation) const;
  void fillWithRawData( const CAnalysisData& AnalysisData,
                        CApproximation* pApproximation) const;
  void fillWithTextData(const CAnalysisData& AnalysisData,
                        const CTextMode& TextMode,
                        EAnalysisType AnalysisType,
                        CApproximation* pApproximation) const;

  void fillStableZones( const CApproximation& Approximation,
                        CMarkedIntervalContainer* pStableZones) const;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
