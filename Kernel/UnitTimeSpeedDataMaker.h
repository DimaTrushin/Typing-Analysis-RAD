//---------------------------------------------------------------------------

#ifndef UnitTimeSpeedDataMakerH
#define UnitTimeSpeedDataMakerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTimeDataFilter.h"
#include "UnitAnalysisRover.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration CTimeSpeedDataMaker
//---------------------------------------------------------------------------

// TO DO
// need a template version:
// - time/speed
// - response/duration
class CTimeSpeedDataMaker : private CTimeDataFilter {
  public:
  void prepareTimeData( const CAnalysisData& AnalysisData,
                        const CTextMode& TextMode,
                        EAnalysisType AnalysisType,
                        std::vector<microseconds>* pTimeVector) const;
  void prepareRawTimeData(const CAnalysisData& AnalysisData,
                          std::vector<microseconds>* pTimeVector) const;
  void prepareSpeedData(const CAnalysisData& AnalysisData,
                        const CTextMode& TextMode,
                        EAnalysisType AnalysisType,
                        std::vector<symbolsPerMinute>* pSpeedVector) const;
  void prepareRawSpeedData( const CAnalysisData& AnalysisData,
                            std::vector<symbolsPerMinute>* pSpeedVector) const;
  private:
  void convertTimeToSpeed(const std::vector<microseconds>& TimeVector,
                          std::vector<symbolsPerMinute>* pSpeedVector) const;
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
