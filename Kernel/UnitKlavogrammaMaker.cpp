//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKlavogrammaMaker.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CKeyUnderConstruction
//---------------------------------------------------------------------------

CKeyUnderConstruction::CKeyUnderConstruction(
                                          const CAnyUIterator& AnyUIterator)
  : Key(AnyUIterator->getSymbol(),
        CTimer::MicroSecondsToMilliSeconds(
                  AnyUIterator->getPressingTime())),
    VKCode(AnyUIterator->getVKCode()),
    ReleasingTime(CTimer::MicroSecondsToMilliSeconds(
                            AnyUIterator->getReleasingTime())) {

}
//---------------------------------------------------------------------------
// Definition of CKeyUnderConstruction::CFirstReleasedOnTop
//---------------------------------------------------------------------------

bool CKeyUnderConstruction::CFirstReleasedOnTop::operator() (
                                const CKeyUnderConstruction& first,
                                const CKeyUnderConstruction& second) {
  return first.ReleasingTime > second.ReleasingTime;
}
//---------------------------------------------------------------------------
// Definition of CHeapOfKeysUnderConstruction
//---------------------------------------------------------------------------

milliseconds CHeapOfKeysUnderConstruction::getFirstReleasingTime() const {
  return top().ReleasingTime;
}
//---------------------------------------------------------------------------

bool CHeapOfKeysUnderConstruction::empty() const {
  return CBase::empty();
}
//---------------------------------------------------------------------------

CKeyUnderConstruction CHeapOfKeysUnderConstruction::getAndReleaseKey() {
  updateMultiplicities(top().ReleasingTime);
  CKeyUnderConstruction ReleasedKey(std::move(top()));
  pop_heap();
  return ReleasedKey;
}
//---------------------------------------------------------------------------

void CHeapOfKeysUnderConstruction::insertNewKey(
                                      const CAnyUIterator& AnyUIterator) {
  updateMultiplicities(
        CTimer::MicroSecondsToMilliSeconds(AnyUIterator->getPressingTime()));
  push_heap(CKeyUnderConstruction(AnyUIterator));
}
//---------------------------------------------------------------------------

void CHeapOfKeysUnderConstruction::updateMultiplicities(
                                                  milliseconds NewKeyTime) {
  for (auto& ConstructedKey : *this)
    ConstructedKey.Key.AddMultiplicitySegment(size(), NewKeyTime);
}
//---------------------------------------------------------------------------
// Definitions of CKlavogrammaMaker
//---------------------------------------------------------------------------

void CKlavogrammaMaker::constructKlavogramma(
                                          const CAnalysisData& AnalysisData,
                                          EOutputMode outputMode,
                                          const CTextMode& textMode,
                                          const CFingerLayout& Layout,
                                          CKlavogramma* target) {
  target->clear();
  insertKeys(Layout, target);
  milliseconds StartingTime;
  CAnalysisRover NextKeyRover;
  prepareInitialState(AnalysisData,
                      outputMode,
                      textMode,
                      &StartingTime,
                      &NextKeyRover);
  constructKlavogramma(Layout, StartingTime, &NextKeyRover, target);
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::prepareInitialState(
                                  const CAnalysisData& AnalysisData,
                                  EOutputMode outputMode,
                                  const CTextMode& textMode,
                                  milliseconds* pStartingTime,
                                  CAnalysisRover* pNextKeyRover) const {
  assert(AnalysisData.pSession != nullptr);
  if (outputMode == EOutputMode::Raw)
    pNextKeyRover->initialize(*AnalysisData.pSession);
  else
    pNextKeyRover->initialize(AnalysisData, textMode);
  assert(pStartingTime != nullptr);
  *pStartingTime = 0;
  if (!pNextKeyRover->empty())
    *pStartingTime = CTimer::
                        MicroSecondsToMilliSeconds(
                                pNextKeyRover->top()->getPressingTime());
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::constructKlavogramma(
                                          const CFingerLayout& Layout,
                                          milliseconds StartingTime,
                                          CAnalysisRover* pNextKeyRover,
                                          CKlavogramma* target) {
  while (!isWorkDone(*pNextKeyRover)) {
    if (isNextPressing(*pNextKeyRover))
      handlePressing(Layout, pNextKeyRover);
    else
      handleReleasing(Layout, target);
  }
  shiftKlavogrammaTime(StartingTime, target);
}
//---------------------------------------------------------------------------

bool CKlavogrammaMaker::isWorkDone(const CAnalysisRover& NextKeyRover) const {
  return NextKeyRover.empty() && KeysUnderConstruction.empty();
}
//---------------------------------------------------------------------------

bool CKlavogrammaMaker::isNextPressing(
                                    const CAnalysisRover& NextKeyRover) const {
  if (NextKeyRover.empty())
    return false;
  if (KeysUnderConstruction.empty())
    return true;
  return  CTimer::MicroSecondsToMilliSeconds(
                      NextKeyRover.top()->getPressingTime()) <
          KeysUnderConstruction.getFirstReleasingTime();
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::handlePressing( const CFingerLayout& Layout,
                                        CAnalysisRover* pNextKeyRover) {
  CFingerLayout::CFingerIterator itFinger;
  Layout.findFingerIteratorOfKey(pNextKeyRover->top()->getVKCode(), &itFinger);
  if (itFinger != Layout.end())
    KeysUnderConstruction.insertNewKey(pNextKeyRover->top());
  pNextKeyRover->setNext();
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::handleReleasing(const CFingerLayout& Layout,
                                        CKlavogramma* target) {
  auto ConstructedKey = KeysUnderConstruction.getAndReleaseKey();
  CFingerLayout::CFingerIterator itFinger;
  Layout.findFingerIteratorOfKey(ConstructedKey.VKCode, &itFinger);
  if (itFinger != Layout.end())
    (*target)[*itFinger].push_back(ConstructedKey.Key);
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::shiftKlavogrammaTime( milliseconds StartingTime,
                                              CKlavogramma* target) const {
  for (auto& FingerKG : *target)
    shiftFingerKlavogrammaTime(StartingTime, &(FingerKG.second));
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::shiftFingerKlavogrammaTime(
                                          milliseconds StartingTime,
                                          CFingerKlavogramma* target) const {
  for (auto& Key : *target)
    shiftKeyTime(StartingTime, &Key);
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::shiftKeyTime( milliseconds StartingTime,
                                      CKlavogrammaKey* target) const {
  target->PressingTime -= StartingTime;
  for (auto& Segment : target->MultiplicitySegments)
    shiftSegmentTime(StartingTime, &Segment);
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::shiftSegmentTime(
                                milliseconds StartingTime,
                                CMultiplicitySegment* target) const {
  target->SegmentEndingTime -= StartingTime;
}
//---------------------------------------------------------------------------

void CKlavogrammaMaker::insertKeys( const CFingerLayout& Layout,
                                    CKlavogramma* target) {
  for (const auto& Finger : Layout)
    (*target)[Finger] = CFingerKlavogramma();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
