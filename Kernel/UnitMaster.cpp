//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitMaster.h"
#include "UnitFileWriter.h"
#include "UnitFileReader.h"
#include "../UnitPerformanceLogger.h"

#if !defined(NDEBUG)
#include "../UnitStateLoggerAccess.h"
#endif
//---------------------------------------------------------------------------

#if !defined(__MASTER__DISABLE__)
namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Global Variable
//---------------------------------------------------------------------------

extern CGUIHandler GUIHandler;
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------

namespace NSKernel {
//---------------------------------------------------------------------------
// Global Variable
//---------------------------------------------------------------------------

using NSInterface::GUIHandler;
extern CUserEnvironment UserEnvironment;

// The object controlling the kernel
extern CMaster Master;
CMaster Master;
//---------------------------------------------------------------------------
// Definition of CMaster
//---------------------------------------------------------------------------

CMaster::CMaster()
  : CurrentOutputMode(EOutputMode::Text),
    CurrentTextMode(ETextMode::Full,
                    ECapitalMode::All,
                    ECapitalMode::All),
    CurrentAnalysisType(EAnalysisType::Physical),
    CurrentSpeedHistogramChunk(CSpeedApproximation::kHistogramChunk) {
}
//---------------------------------------------------------------------------

void CMaster::transferDataToUser(NSKeyboard::CRawEventContainer* RawBuffer) {
  if (RawBuffer->empty())
    return;
  CPerformanceLogger Performance;
  Performance->Log(this, L"transferBufferToSeance")->
                                transferBufferToSeance(RawBuffer);
  if (!UserEnvironment.Seance.empty())
    makeCurrentAnalysisDataForLastSession();
  setCurrentMode();
  GUIHandler.TreeViewWriter.rebuildTreeView(UserEnvironment.Seance);
  if (isCurrentAnalysisDataDefined()){
    makeCurrentKlavogramma();
    outputCurrentAnalysisDataOnGUI();
    outputCurrentKlavogrammaOnGUI();
  }
}
//---------------------------------------------------------------------------

bool CMaster::isCurrentAnalysisDataDefined() const {
  return CurrentAnalysisData.isDefined();
}
//---------------------------------------------------------------------------

void CMaster::makeCurrentAnalysisData(const CSession& session) {
  CPerformanceLogger Performance;
  auto actionLogger = Performance->LogBlock(L"makeCurrentAnalysisData");
  CSessionToAnalysisDataConverter Converter;
  Converter.convertData(session, &CurrentAnalysisData);
}
//---------------------------------------------------------------------------

void CMaster::makeCurrentSpeedApproximationData() {
  CSpeedApproximationDataMaker Maker;
  Maker.convert(CurrentAnalysisData,
                CurrentOutputMode,
                CurrentTextMode,
                CurrentAnalysisType,
                &SpeedApproximationData);
}
//---------------------------------------------------------------------------

void CMaster::makeCurrentKlavogramma() {
  CKlavogrammaMaker Maker;
  Maker.constructKlavogramma( CurrentAnalysisData,
                              CurrentOutputMode,
                              CurrentTextMode,
                              UserEnvironment.FingerLayout,
                              &CurrentKlavogramma);
}
//---------------------------------------------------------------------------

void CMaster::outputCurrentAnalysisDataOnGUI() const {
  CPerformanceLogger Performance;
  auto actionLogger = Performance->LogBlock(L"outputCurrentAnalysisDataOnGUI");
  GUIHandler.TextWriter.Clear();
  #if !defined(NDEBUG)
    printDebugInformation();
  #endif
  if (CurrentOutputMode == EOutputMode::Raw)
    printFormattedRawText();
  else
    printFormattedText();
  outputCurrentSeanceStatisticsOnGUI();
}
//---------------------------------------------------------------------------

void CMaster::outputCurrentSpeedApproximationDataOnGUI() const {
  CPerformanceLogger Performance;
  Performance->Log( &GUIHandler.SpeedDerivativePlotterUniform,
                    L"SpeedDerivativePlotterUniform")->
                                  draw(SpeedApproximationData.Approximation);
  Performance->Log( &GUIHandler.SpeedPlotterUniform,
                    L"SpeedPlotterUniform")->
                                  draw(SpeedApproximationData.Approximation);
  Performance->Log( &GUIHandler.SpeedDerivativePlotter,
                    L"SpeedDerivativePlotter")->
                                  draw(SpeedApproximationData.Approximation);
  Performance->Log( &GUIHandler.SpeedPlotter,
                    L"SpeedPlotter")->
                                  draw(SpeedApproximationData.Approximation);
  Performance->Log( &GUIHandler.SpeedStableZonesPlotter,
                    L"SpeedStableZonesPlotter")->
                                  draw( SpeedApproximationData.Approximation,
                                        SpeedApproximationData.StableZones);
}
//---------------------------------------------------------------------------

void CMaster::outputCurrentSpeedHistogramOnGUI() const {
  GUIHandler.SpeedHistogramPlotter.draw(SpeedApproximationData.Approximation,
                                        CurrentSpeedHistogramChunk);
}
//---------------------------------------------------------------------------

void CMaster::outputCurrentKlavogrammaOnGUI() const {
  CPerformanceLogger Performance;
  Performance->Log( &GUIHandler.KlavogrammaPlotter,
                    L"KlavogrammaPlotter")->
                                drawKlavogrammaParallel(CurrentKlavogramma);
}
//---------------------------------------------------------------------------

void CMaster::outputCurrentSeanceStatisticsOnGUI() const {
  CPerformanceLogger Performance;
  auto actionLogger =
            Performance->LogBlock(L"outputCurrentSeanceStatisticsOnGUI");
  CSeanceStatisticsData Data;
  prepareSeanceStatistics(&Data);
  GUIHandler.SeanceStatistics.Clear();
  GUIHandler.SeanceStatistics.addDataContiner(Data);
}
//---------------------------------------------------------------------------

void CMaster::outputStableZonesStatisticsOnGUI() const {
  //CPerformanceLogger Performance;
  //auto actionLogger =
  //          Performance->LogBlock(L"outputStableZonesStatisticsOnGUI");
  CStableZonesData Data;
  prepareStableZonesStatistics(&Data);
  GUIHandler.StableZonesStatistics.Clear();
  GUIHandler.StableZonesStatistics.addDataContiner(Data);
}
//---------------------------------------------------------------------------

void CMaster::setCurrentMode() {
  GUIHandler.TextModeReader.setTextMode(&CurrentOutputMode, &CurrentTextMode);
}
//---------------------------------------------------------------------------

void CMaster::setCurrentAnalysisType() {
  GUIHandler.AnalysisTypeReader.setAnalysisMode(&CurrentAnalysisType);
}
//---------------------------------------------------------------------------

void CMaster::setCurrentSpeedHistogramChunk() {
  GUIHandler.SpeedChunkHandler.setChunk(&CurrentSpeedHistogramChunk);
}
//---------------------------------------------------------------------------

void CMaster::writeUserEnvironmentToFile(const std::wstring& FileName) const {
  NSLibrary::CFileWriter FileWriter(FileName);
  CPerformanceLogger Performance;
  auto actionLogger = Performance->LogBlock(L"on Streaming To File");
  FileWriter.writeHeader();
  FileWriter << UserEnvironment;
}
//---------------------------------------------------------------------------

void CMaster::readUserEnvironmentFromFile(const std::wstring& FileName) {
  NSLibrary::CFileReader FileReader(FileName);
  CUserEnvironment tmpUserEnvironment;
  CPerformanceLogger Performance;
  auto actionLogger = Performance->LogBlock(L"on Streaming From File");
  FileReader.readHeader();
  FileReader >> tmpUserEnvironment;
  UserEnvironment = std::move(tmpUserEnvironment);
  actionLogger.stopLog();

  GUIHandler.TextWriter.Clear();
  GUIHandler.SeanceStatistics.Clear();
  GUIHandler.KlavogrammaPlotter.ClearKeys();
  if (!UserEnvironment.Seance.empty())
    makeCurrentAnalysisDataForLastSession();
  else
    clearCurrentAnalysisData();

  setCurrentMode();
  GUIHandler.TreeViewWriter.Clear();
  GUIHandler.TreeViewWriter.rebuildTreeView(UserEnvironment.Seance);
  if (isCurrentAnalysisDataDefined()){
    makeCurrentKlavogramma();
    outputCurrentAnalysisDataOnGUI();
    outputCurrentKlavogrammaOnGUI();
  }
}
//---------------------------------------------------------------------------

void CMaster::transferBufferToSeance(
                            NSKeyboard::CRawEventContainer* RawBuffer) {
  CRawBufferToSeanceConverter Converter;
  Converter.convert(RawBuffer, &UserEnvironment.Seance);
}
//---------------------------------------------------------------------------

void CMaster::makeCurrentAnalysisDataForLastSession() {
  makeCurrentAnalysisData(UserEnvironment.Seance.back());
}
//---------------------------------------------------------------------------
void CMaster::clearCurrentAnalysisData() {
  CurrentAnalysisData.clear();
}
//---------------------------------------------------------------------------

void CMaster::printFormattedRawText() const {
  CFormattedString Text;
  TextMaker.makeFormattedRawText(CurrentAnalysisData, &Text);
  #if !defined(NDEBUG)
    GUIHandler.TextWriter.printPlaneText(L"Raw Output:\n");
  #endif
  GUIHandler.TextWriter.printFormattedString(Text);
}
//---------------------------------------------------------------------------

void CMaster::printFormattedText() const {
  CFormattedString Text;
  TextMaker.makeFormattedText(CurrentAnalysisData, CurrentTextMode, &Text);
  #if !defined(NDEBUG)
    GUIHandler.TextWriter.printPlaneText(L"Text Output:\n");
  #endif
  GUIHandler.TextWriter.printFormattedString(Text);
  GUIHandler.TextWriter.newLine();
}
//---------------------------------------------------------------------------

void CMaster::prepareSeanceStatistics(CSeanceStatisticsData* pData) const {
  assert(pData != nullptr);
  addSeanceStatistics(pData);
  addCurrentSessionStatistics(pData);
  addTextTreeDataStatistics(pData);
  addAnalysisDataStatistics(pData);
}
//---------------------------------------------------------------------------

void CMaster::addSeanceStatistics(CSeanceStatisticsData* pData) const {
  UnicodeString Text = UserEnvironment.Seance.size();
  pData->push_back({L"Seance size", Text});
}
//---------------------------------------------------------------------------

void CMaster::addCurrentSessionStatistics(CSeanceStatisticsData* pData) const {
  const CSession& Session = *CurrentAnalysisData.pSession;
  UnicodeString Text = Session.size();
  pData->push_back({L"Session size", Text});
  Text = CTimer::MicroSecondsToMilliSeconds(Session.getDurationTime());
  pData->push_back({L"Session duration", Text});
}
//---------------------------------------------------------------------------

void CMaster::addTextTreeDataStatistics(CSeanceStatisticsData* pData) const {
  const CTextDataTree& Tree = CurrentAnalysisData.TextTree;
  pData->push_back({L"TextDataTree", L""});
  UnicodeString Text;
  Text = Tree.getTotalNumberOfSymbols();
  pData->push_back({L"Total Number Of Symbols", Text});
  Text = Tree.getNumberOfPlacesWithDeletion();
  pData->push_back({L"Number Of Places With Deletion", Text});
  Text = Tree.getNumberOfDeletionSeries();
  pData->push_back({L"Number Of Deletion Series", Text});
  Text = Tree.getNumberOfDeletedSymbols();
  pData->push_back({L"Number Of Deleted Symbols", Text});
  Text = Tree.getDeletionSeriesLengthSupremum();
  pData->push_back({L"Deletion Series Length Supremum", Text});
  Text = Tree.getNumberOfReturnPoints();
  pData->push_back({L"Number Of Return Points", Text});
  Text = Tree.getNumberOfMistakePlaces();
  pData->push_back({L"Number Of Mistake Places", Text});
  Text = Tree.getNumberOfMistakeRoutes();
  pData->push_back({L"Number Of Mistake Routes", Text});
  Text = Tree.getMistakeRoutesLengthSupremum();
  pData->push_back({L"Mistake Routes Length Supremum", Text});
  if (CurrentOutputMode != EOutputMode::Text)
    return;
  Text = CTimer::MicroSecondsToMilliSeconds(
                      Tree.getFirstPressingTime(CurrentTextMode.TextMode));
  pData->push_back({L"First Pressing Time", Text});
  Text = CTimer::MicroSecondsToMilliSeconds(
                      Tree.getLastPressingTime(CurrentTextMode.TextMode));
  pData->push_back({L"Last Pressing Time", Text});
  Text = CTimer::MicroSecondsToMilliSeconds(
                      Tree.getTextDurationTime(CurrentTextMode.TextMode));
  pData->push_back({L"Text Duration Time", Text});
  Text = Tree.getTextLength(CurrentTextMode.TextMode);
  pData->push_back({L"Text Length", Text});
}
//---------------------------------------------------------------------------

void CMaster::addAnalysisDataStatistics(CSeanceStatisticsData* pData) const {
  UnicodeString Text;
  pData->push_back({L"Analysis Data", L""});
  if (!CurrentAnalysisData.isDefined()) {
    Text = L"Is NOT defined";
    pData->push_back({L"Analysis Data", Text});
    return;
  }
  Text = CurrentAnalysisData.getRawLength();
  pData->push_back({L"Raw Length", Text});
  Text = CTimer::MicroSecondsToMilliSeconds(
                      CurrentAnalysisData.getRawDurationTime());
  pData->push_back({L"Raw Duration Time", Text});
  if (CurrentAnalysisData.getRawDurationTime() != 0) {
    Text = FloatToStrF(
              CurrentAnalysisData.getRawSpeed(),
              ffFixed,
              7,
              3);
    pData->push_back({L"Raw Speed", Text});
  }
  if (CurrentOutputMode == EOutputMode::Raw)
    return;
  Text = CurrentAnalysisData.getTextLength(CurrentTextMode);
  pData->push_back({L"Text Length", Text});
  Text = CTimer::MicroSecondsToMilliSeconds(
                CurrentAnalysisData.getTextDurationTime(CurrentTextMode));
  pData->push_back({L"Text Duration Time", Text});
  if (!CurrentAnalysisData.isTextEmpty(CurrentTextMode)) {
    Text = CTimer::MicroSecondsToMilliSeconds(
                  CurrentAnalysisData.getFirstPressingTime(CurrentTextMode));
    pData->push_back({L"First Pressing Time", Text});
    Text = CTimer::MicroSecondsToMilliSeconds(
                  CurrentAnalysisData.getLastPressingTime(CurrentTextMode));
    pData->push_back({L"Last Pressing Time", Text});
  }
  if (CurrentAnalysisData.getTextDurationTime(CurrentTextMode) != 0) {
    Text = FloatToStrF(
              CurrentAnalysisData.getTextSpeed(CurrentTextMode),
              ffFixed,
              7,
              3);
    pData->push_back({L"Text Speed", Text});
  }
}
//---------------------------------------------------------------------------

void CMaster::prepareStableZonesStatistics(CStableZonesData* pData) const {
  const auto& StableZones = SpeedApproximationData.StableZones;
  const auto& Approximation = SpeedApproximationData.Approximation;
  for (const auto& Zone : StableZones)
    addOneZoneStatistics(Zone, Approximation, pData);
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CMaster::addOneZoneStatistics( const CMarkedInterval& Zone,
                                    const TApproximation& Approximation,
                                    CStableZonesData* pData) const {
  UnicodeString Segment;
  UnicodeString LocalMaximum;
  UnicodeString Density;
  UnicodeString ZoneSize;
  makeSegment(Zone, &Segment);
  makeLocalMaximum(Zone, &LocalMaximum);
  makeDensityValue(Zone, Approximation, &Density);
  makeZoneSize(Zone, Approximation, &ZoneSize);
  pData->push_back({Segment, LocalMaximum, Density, ZoneSize});
}
//---------------------------------------------------------------------------

void CMaster::makeSegment(const CMarkedInterval& Zone,
                          UnicodeString* pSegment) const {
  UnicodeString& Segment = *pSegment;
  Segment = L"[";
  Segment += FloatToStrF( Zone.first, ffFixed, 7, 3);
  Segment += L", ";
  Segment += FloatToStrF( Zone.second, ffFixed, 7, 3);
  Segment += L"]";
}
//---------------------------------------------------------------------------

void CMaster::makeLocalMaximum( const CMarkedInterval& Zone,
                                UnicodeString* pLocalMaximum) const {
  UnicodeString& LocalMaximum = *pLocalMaximum;
  LocalMaximum = FloatToStrF( Zone.point, ffFixed, 7, 3);
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CMaster::makeDensityValue( const CMarkedInterval& Zone,
                                const TApproximation& Approximation,
                                UnicodeString* pDensity) const {
  UnicodeString& Density = *pDensity;
  Density = FloatToStrF(Approximation.evaluate0(Zone.point), ffFixed, 7, 6);
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CMaster::makeZoneSize( const CMarkedInterval& Zone,
                            const TApproximation& Approximation,
                            UnicodeString* pZoneSize) const {
  UnicodeString& ZoneSize = *pZoneSize;
  CFunctionGrid Grid;
  Grid.setApproximationGrid0(Approximation, Zone);
  ZoneSize = FloatToStrF(Grid.getArea(), ffFixed, 7, 3);
}
//---------------------------------------------------------------------------

#if !defined(NDEBUG)
//---------------------------------------------------------------------------
// Debug
//---------------------------------------------------------------------------

void CMaster::printDebugInformation() const {
  UnicodeString UText = L"# # # DEBUG # # #\n";
  GUIHandler.TextWriter.printPlaneText(UText);
  printFormattedRawText();
  GUIHandler.TextWriter.newLine();
  GUIHandler.TextWriter.printPlaneText(UText);
}
//---------------------------------------------------------------------------
// Debug End
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#pragma package(smart_init)
