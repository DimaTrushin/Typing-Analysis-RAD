//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitApproximationDataMaker.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition CSpeedApproximationDataMaker
//---------------------------------------------------------------------------

void CSpeedApproximationDataMaker::convert(
                          const CAnalysisData& AnalysisData,
                          EOutputMode OutputMode,
                          const CTextMode& TextMode,
                          EAnalysisType AnalysisType,
                          CSpeedApproximationData* pApproximationData) const {
  if (!AnalysisData.isDefined())
    return;
  fillApproximation(AnalysisData,
                    OutputMode,
                    TextMode,
                    AnalysisType,
                    &pApproximationData->Approximation);
  fillStableZones(pApproximationData->Approximation,
                  &pApproximationData->StableZones);
}
//---------------------------------------------------------------------------

void CSpeedApproximationDataMaker::fillApproximation(
                          const CAnalysisData& AnalysisData,
                          EOutputMode OutputMode,
                          const CTextMode& TextMode,
                          EAnalysisType AnalysisType,
                          CApproximation* pApproximation) const {
  if (OutputMode == EOutputMode::Raw) {
    fillWithRawData(AnalysisData, pApproximation);
  } else {
    assert(OutputMode == EOutputMode::Text);
    fillWithTextData(AnalysisData, TextMode, AnalysisType, pApproximation);
  }
}
//---------------------------------------------------------------------------

void CSpeedApproximationDataMaker::fillWithRawData(
                                const CAnalysisData& AnalysisData,
                                CApproximation* pApproximation) const {
  std::vector<symbolsPerMinute> DataPool;
  CTimeSpeedDataMaker Maker;
  Maker.prepareRawSpeedData(AnalysisData, &DataPool);
  pApproximation->setApproximation(DataPool);
}
//---------------------------------------------------------------------------

void CSpeedApproximationDataMaker::fillWithTextData(
                                const CAnalysisData& AnalysisData,
                                const CTextMode& TextMode,
                                EAnalysisType AnalysisType,
                                CApproximation* pApproximation) const {
  std::vector<symbolsPerMinute> DataPool;
  CTimeSpeedDataMaker Maker;
  Maker.prepareSpeedData(AnalysisData, TextMode, AnalysisType, &DataPool);
  pApproximation->setApproximation(DataPool);
}
//---------------------------------------------------------------------------

void CSpeedApproximationDataMaker::fillStableZones(
                        const CApproximation& Approximation,
                        CMarkedIntervalContainer* pStableZones) const {
  CStableZonesFiller Filler;
  Filler.computeMarkedIntervals(Approximation, pStableZones);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
