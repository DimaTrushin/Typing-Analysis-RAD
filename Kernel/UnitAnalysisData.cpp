//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAnalysisData.h"
//---------------------------------------------------------------------------

#if !defined(__ANALYSIS_DATA__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CAnalysisData
// ---------------------------------------------------------------------------

CAnalysisData::CAnalysisData()
  : pSession(nullptr) {
}
// ---------------------------------------------------------------------------

CAnalysisData::CAnalysisData(const CSession& source)
    : pSession(&source) {
}
// ---------------------------------------------------------------------------

void CAnalysisData::clear() {
  pSession = nullptr;
  TextTree.clear();
  ShiftsWithDependencies.clear();
  CapslocksWithDependencies.clear();
}
// ---------------------------------------------------------------------------

size_t CAnalysisData::getRawLength() const{
  if (!isDefined())
    return 0;
  return pSession->size();
}
// ---------------------------------------------------------------------------

size_t CAnalysisData::getTextLength(const CTextMode& TextMode) const {
  return  TextTree.getTextLength(TextMode.TextMode) +
          ShiftsWithDependencies.getSize( TextMode.TextMode,
                                          TextMode.ShiftMode) +
          CapslocksWithDependencies.getSize(TextMode.TextMode,
                                            TextMode.CapslockMode);
}
// ---------------------------------------------------------------------------

size_t CAnalysisData::getAmountOfShifts(const CTextMode& TextMode) const {
  return ShiftsWithDependencies.getSize(TextMode.TextMode,
                                        TextMode.ShiftMode);
}
// ---------------------------------------------------------------------------

size_t CAnalysisData::getAmountOfCapslocks(const CTextMode& TextMode) const {
  return CapslocksWithDependencies.getSize( TextMode.TextMode,
                                            TextMode.CapslockMode);
}
// ---------------------------------------------------------------------------

bool CAnalysisData::isDefined() const {
  return pSession != nullptr;
}
// ---------------------------------------------------------------------------

bool CAnalysisData::isSessionEmpty() const{
  if (!isDefined())
    return true;
  return pSession->empty();
}
// ---------------------------------------------------------------------------

bool CAnalysisData::isTextEmpty(const CTextMode& TextMode) const {
  return  ShiftsWithDependencies.isEmpty( TextMode.TextMode,
                                          TextMode.ShiftMode) &&
          CapslocksWithDependencies.isEmpty(TextMode.TextMode,
                                            TextMode.CapslockMode) &&
          TextTree.isTextEmpty(TextMode.TextMode);
}
// ---------------------------------------------------------------------------

microseconds CAnalysisData::getRawDurationTime() const {
  if(!isDefined())
    return 0;
  return pSession->getDurationTime();
}
// ---------------------------------------------------------------------------

microseconds CAnalysisData::getTextDurationTime(
                                          const CTextMode& TextMode) const {
  if (isTextEmpty(TextMode))
    return 0;
  return  getLastPressingTime(TextMode) -
          getFirstPressingTime(TextMode);
}
// ---------------------------------------------------------------------------

microseconds CAnalysisData::getFirstPressingTime(
                                            const CTextMode& TextMode) const {
  std::priority_queue<microseconds,
                      std::vector<microseconds>,
                      std::greater<microseconds> > PressingTimes;
  if (!ShiftsWithDependencies.isEmpty(TextMode.TextMode,
                                      TextMode.ShiftMode))
    PressingTimes.push(ShiftsWithDependencies.
                                getFirstPressingTime(TextMode.TextMode,
                                                    TextMode.ShiftMode));
  if (!CapslocksWithDependencies.isEmpty( TextMode.TextMode,
                                          TextMode.CapslockMode))
    PressingTimes.push(CapslocksWithDependencies.
                                getFirstPressingTime(TextMode.TextMode,
                                                    TextMode.CapslockMode));
  if (!TextTree.isTextEmpty(TextMode.TextMode))
    PressingTimes.push(TextTree.getFirstPressingTime(TextMode.TextMode));

  assert(!PressingTimes.empty());
  if (PressingTimes.empty())
    return -1;
  return PressingTimes.top();
}
// ---------------------------------------------------------------------------

microseconds CAnalysisData::getLastPressingTime(
                                          const CTextMode& TextMode) const {
  std::priority_queue<microseconds,
                      std::vector<microseconds>,
                      std::less<microseconds> > PressingTimes;
  if (!ShiftsWithDependencies.isEmpty(TextMode.TextMode,
                                      TextMode.ShiftMode))
    PressingTimes.push(ShiftsWithDependencies.
                                getLastPressingTime( TextMode.TextMode,
                                                    TextMode.ShiftMode));
  if (!CapslocksWithDependencies.isEmpty( TextMode.TextMode,
                                          TextMode.CapslockMode))
    PressingTimes.push(CapslocksWithDependencies.
                                getLastPressingTime( TextMode.TextMode,
                                                    TextMode.CapslockMode));
  if (!TextTree.isTextEmpty(TextMode.TextMode))
    PressingTimes.push(TextTree.getLastPressingTime(TextMode.TextMode));

  assert(!PressingTimes.empty());
  if (PressingTimes.empty())
    return -1;
  return PressingTimes.top();
}
// ---------------------------------------------------------------------------

symbolsPerMinute CAnalysisData::getRawSpeed() const {
  assert(getRawDurationTime() != 0);
  return getRawLength() / CTimer::MicroSecondsToMinutes(getRawDurationTime());
}
// ---------------------------------------------------------------------------

symbolsPerMinute CAnalysisData::getTextSpeed(const CTextMode& TextMode) const {
  assert(getTextDurationTime(TextMode) != 0);
  return  getTextLength(TextMode) /
          CTimer::MicroSecondsToMinutes(getTextDurationTime(TextMode));
}
// ---------------------------------------------------------------------------

void CAnalysisData::fillShiftsWithDependencies() {
  CShiftsWithDependenciesFiller ShiftFiller;
  assert(isDefined());
  ShiftFiller.fill(*pSession, TextTree, &ShiftsWithDependencies);
}
// ---------------------------------------------------------------------------

void CAnalysisData::fillCapslocksWithDependencies() {
  CCapslocksWithDependenciesFiller CapslockFiller;
  assert(isDefined());
  CapslockFiller.fill(*pSession, TextTree, &CapslocksWithDependencies);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#pragma package(smart_init)
