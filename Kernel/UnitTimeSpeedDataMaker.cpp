//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTimeSpeedDataMaker.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

//---------------------------------------------------------------------------
// Definition CTimeSpeedDataMaker
//---------------------------------------------------------------------------

void CTimeSpeedDataMaker::prepareTimeData(
                              const CAnalysisData& AnalysisData,
                              const CTextMode& TextMode,
                              EAnalysisType AnalysisType,
                              std::vector<microseconds>* pTimeVector) const {
  //pTimeVector->clear();
  if(!AnalysisData.isDefined())
    return;
  CAnalysisRover DataRover(AnalysisData, TextMode);
  while (!DataRover.empty()) {
    microseconds ResponseTime = DataRover.getResponseTime(AnalysisType);

    if (isAcceptable(ResponseTime))
      pTimeVector->push_back(ResponseTime);
    DataRover.setNext();
  }
}
//---------------------------------------------------------------------------

void CTimeSpeedDataMaker::prepareRawTimeData(
                                const CAnalysisData& AnalysisData,
                                std::vector<microseconds>* pTimeVector) const {
  //pTimeVector->clear();
  if(!AnalysisData.isDefined())
    return;
  assert(AnalysisData.pSession != nullptr);
  auto& Session = *AnalysisData.pSession;
  EAnalysisType AnalysisType = EAnalysisType::Symbolical;

  CAnalysisRover DataRover(Session);
  while (!DataRover.empty()) {
    microseconds ResponseTime = DataRover.getResponseTime(AnalysisType);

    if (isAcceptable(ResponseTime))
      pTimeVector->push_back(ResponseTime);
    DataRover.setNext();
  }
}

//---------------------------------------------------------------------------

void CTimeSpeedDataMaker::prepareSpeedData(
                          const CAnalysisData& AnalysisData,
                          const CTextMode& TextMode,
                          EAnalysisType AnalysisType,
                          std::vector<symbolsPerMinute>* pSpeedVector) const {
  std::vector<microseconds> TimeVector;
  prepareTimeData(AnalysisData, TextMode, AnalysisType, &TimeVector);
  convertTimeToSpeed(TimeVector, pSpeedVector);
}
//---------------------------------------------------------------------------

void CTimeSpeedDataMaker::prepareRawSpeedData(
                            const CAnalysisData& AnalysisData,
                            std::vector<symbolsPerMinute>* pSpeedVector) const {
  std::vector<microseconds> TimeVector;
  prepareRawTimeData(AnalysisData, &TimeVector);
  convertTimeToSpeed(TimeVector, pSpeedVector);
}
//---------------------------------------------------------------------------

void CTimeSpeedDataMaker::convertTimeToSpeed(
                          const std::vector<microseconds>& TimeVector,
                          std::vector<symbolsPerMinute>* pSpeedVector) const {
  //pSpeedVector->clear();
  for (const auto& Time : TimeVector)
    pSpeedVector->push_back(CTimer::convertTimeToSpeed(Time));
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
