//---------------------------------------------------------------------------

#ifndef UnitMasterH
#define UnitMasterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitRawBufferToSeanceConverter.h"
#include "UnitUserEnvironment.h"
#include "UnitApproximationDataMaker.h"
#include "UnitKlavogrammaMaker.h"
#include "UnitTextMaker.h"
#include "../Interface/UnitGUIHandler.h"
#include "../UnitTimeLogger.h"
#include <array>
//---------------------------------------------------------------------------

#if !defined(__MASTER__DISABLE__)
namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CMaster
//---------------------------------------------------------------------------

class CMaster {
  using CSeanceStatisticsDatum = std::array<UnicodeString, 2>;
  using CSeanceStatisticsData = std::vector<CSeanceStatisticsDatum>;
  using CStableZonesDatum = std::array<UnicodeString, 4>;
  using CStableZonesData = std::vector<CStableZonesDatum>;
public:
  CMaster();
  CMaster(const CMaster&) = delete;
  CMaster(CMaster&&) = delete;
  CMaster& operator=(const CMaster&) = delete;
  CMaster& operator=(CMaster&&) = delete;

  void transferDataToUser(NSKeyboard::CRawEventContainer* RawBuffer);
  bool isCurrentAnalysisDataDefined() const;
  void makeCurrentAnalysisData(const CSession& session);
  void makeCurrentSpeedApproximationData();
  void makeCurrentKlavogramma();

  void outputCurrentAnalysisDataOnGUI() const;
  void outputCurrentSpeedApproximationDataOnGUI() const;
  void outputCurrentSpeedHistogramOnGUI() const;
  void outputCurrentKlavogrammaOnGUI() const;
  void outputCurrentSeanceStatisticsOnGUI() const;
  void outputStableZonesStatisticsOnGUI() const;

  void setCurrentMode();
  void setCurrentAnalysisType();
  void setCurrentSpeedHistogramChunk();

  void writeUserEnvironmentToFile(const std::wstring& FileName) const;
  void readUserEnvironmentFromFile(const std::wstring& FileName);

private:
  inline void transferBufferToSeance(NSKeyboard::CRawEventContainer* RawBuffer);
  inline void makeCurrentAnalysisDataForLastSession();
  inline void clearCurrentAnalysisData();
  inline void printFormattedRawText() const;
  inline void printFormattedText() const;
  inline void prepareSeanceStatistics(CSeanceStatisticsData* pData) const;
  inline void addSeanceStatistics(CSeanceStatisticsData* pData) const;
  inline void addCurrentSessionStatistics(CSeanceStatisticsData* pData) const;
  inline void addTextTreeDataStatistics(CSeanceStatisticsData* pData) const;
  inline void addAnalysisDataStatistics(CSeanceStatisticsData* pData) const;
  inline void prepareStableZonesStatistics(CStableZonesData* pData) const;

  template<class TApproximation>
  inline void addOneZoneStatistics( const CMarkedInterval& Zone,
                                    const TApproximation& Approximation,
                                    CStableZonesData* pData) const ;
  inline void makeSegment(const CMarkedInterval& Zone,
                          UnicodeString* pSegment) const;
  inline void makeLocalMaximum( const CMarkedInterval& Zone,
                                UnicodeString* pLocalMaximum) const;
  template<class TApproximation>
  inline void makeDensityValue( const CMarkedInterval& Zone,
                                const TApproximation& Approximation,
                                UnicodeString* pDensity) const;
  template<class TApproximation>
  inline void makeZoneSize( const CMarkedInterval& Zone,
                            const TApproximation& Approximation,
                            UnicodeString* pZoneSize) const;

  #if !defined(NDEBUG)
    inline void printDebugInformation() const;
  #endif

  CAnalysisData CurrentAnalysisData;
  CSpeedApproximationData SpeedApproximationData;
  // TO DO
  // I need to exclude FormatPool from CTextMaker and make it
  // a member of the Master
  // CTextMaker must NOT be a member of the Master!
  CTextMaker TextMaker;
  EOutputMode CurrentOutputMode;
  CTextMode CurrentTextMode;
  EAnalysisType CurrentAnalysisType;
  double CurrentSpeedHistogramChunk;
  CKlavogramma CurrentKlavogramma;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
