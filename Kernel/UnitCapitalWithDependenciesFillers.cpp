//---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitCapitalWithDependenciesFillers.h"
//#include "../Debug/UnitDisabler.h"
// ---------------------------------------------------------------------------

#if !defined(__CAPITAL_WITH_DEPENDENCIES_FILLERS__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition CCapitalWithDependenciesBeingPressed
// ---------------------------------------------------------------------------

void CCapitalWithDependenciesBeingPressed::increasePrintedDependencies() {
  for (auto& Key : *this)
    Key->increasePrintedDependencies();
}
// ---------------------------------------------------------------------------

void CCapitalWithDependenciesBeingPressed::increaseDeletedDependencies() {
  for (auto& Key : *this)
    Key->increaseDeletedDependencies();
}

// ---------------------------------------------------------------------------
// Definition CShiftsWithDependenciesFiller
// ---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::fill(
                                const CSession& Session,
                                const CTextDataTree& TextTree,
                                CCapitalWithDependenciesContainer* pShifts) {
  if (!initialize(Session, TextTree, pShifts))
    return;

  while (isThereSymbolAndShift(TextTree, pShifts)) {
    setPressedShifts(pShifts);
    if (itCurrentSymbol->isAffectedByShift())
      updateDependencies();
    ++itCurrentSymbol;
  }
}
// ---------------------------------------------------------------------------

bool CShiftsWithDependenciesFiller::isThereSymbolAndShift(
                      const CTextDataTree& TextTree,
                      CCapitalWithDependenciesContainer* pShifts) const {
  return itCurrentSymbol != TextTree.endText(ETextMode::Full) &&
          (!PressedShifts.empty() || itNextShift != pShifts->end());
}
// ---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::updateDependencies() {
  if (itCurrentSymbol->isAnyPrinted())
    PressedShifts.increasePrintedDependencies();
  else if (itCurrentSymbol->isAnyDeleted())
    PressedShifts.increaseDeletedDependencies();
  else
    // Попали в корень!
    return;
}
// ---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::fillWithoutDependencies(
                                const CSession& Session,
                                CCapitalWithDependenciesContainer* pShifts) {
  pShifts->clear();
  for ( auto itSymbol = Session.begin();
        itSymbol != Session.end();
        ++itSymbol)
    if (itSymbol->isAnyShift())
      pShifts->push_back(itSymbol);
}
// ---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::setPressedShifts(
                          CCapitalWithDependenciesContainer* pShifts) {
  pressCurrentShifts(pShifts);
  removeReleasedShifts();
}
// ---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::pressCurrentShifts(
                    CCapitalWithDependenciesContainer* pShifts) {
  while ( itNextShift != pShifts->end() &&
          !(itNextShift->
              getIterator()->
                isPressedAfter(itCurrentSymbol->getPressingTime()))) {
    PressedShifts.push_back(itNextShift);
    ++itNextShift;
  }
}
// ---------------------------------------------------------------------------

void CShiftsWithDependenciesFiller::removeReleasedShifts() {
  CCapitalWithDependenciesBeingPressed::iterator
      itPressedShift = PressedShifts.begin();
  while (itPressedShift != PressedShifts.end()) {
    if ((*itPressedShift)->
                getIterator()->
                    isReleasedBefore(itCurrentSymbol->getPressingTime())) {
      itPressedShift = PressedShifts.erase(itPressedShift);
      continue;
    }
    ++itPressedShift;
  }
}
// ---------------------------------------------------------------------------

bool CShiftsWithDependenciesFiller::initialize(
                          const CSession& Session,
                          const CTextDataTree& TextTree,
                          CCapitalWithDependenciesContainer* pShifts) {
  fillWithoutDependencies(Session, pShifts);
  if (pShifts->empty())
    return false;
  // Теперь есть shift-ы
  itCurrentSymbol = TextTree.beginText(ETextMode::Full);
  itNextShift = pShifts->begin();
  if (!PressedShifts.empty())
    PressedShifts.clear();
  return true;
}
// ---------------------------------------------------------------------------
// Definition CCapslocksWithDependenciesFiller
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::fill(
                              const CSession& Session,
                              const CTextDataTree& TextTree,
                              CCapitalWithDependenciesContainer* pCapslocks) {
  if (!initialize(Session, TextTree, pCapslocks))
    return;
  while ( itCurrentSymbol != TextTree.endText(ETextMode::Full) &&
          itCurrentCapslock != pCapslocks->end()) {
    setNearestCapslock(pCapslocks);
    if (itCurrentSymbol->isAffectedByCapsLock())
      updateDependencies();
    ++itCurrentSymbol;
  }
  correctDependencies(pCapslocks);
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::correctDependencies(
                            CCapitalWithDependenciesContainer* pCapslocks) {
  correctDependencies(ETextMode::Full, pCapslocks);
  correctDependencies(ETextMode::Printed, pCapslocks);
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::correctDependencies(
                            ETextMode TextMode,
                            CCapitalWithDependenciesContainer* pCapslocks) {
  CCapitalWithDependenciesContainer::iterator
                    itCapslock = pCapslocks->begin();
  while (itCapslock != pCapslocks->end()) {
    correctDependenciesOfOneCapslock(TextMode, itCapslock, pCapslocks);
    ++itCapslock;
  }
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::correctDependenciesOfOneCapslock(
                  ETextMode TextMode,
                  CCapitalWithDependenciesContainer::iterator itCapslock,
                  CCapitalWithDependenciesContainer* pCapslocks) {
  if (needToUseCorrector(TextMode, itCapslock, pCapslocks)) {

    CCorrector CapslockCorrector(itCapslock);
    CapslockCorrector.setToCorrectionPlace(TextMode, pCapslocks);
    if (!CapslockCorrector.needCorrection())
      return;

    unsigned int NumberOfDependencies =
                      itCapslock->getNumberOfDependentKeys(TextMode);
    itCapslock->setNumberOfDependentKeys(TextMode, 0);
    if (CapslockCorrector.getPosition() != pCapslocks->end())
      CapslockCorrector.
        getPosition()->
          increaseNumberOfDependentKeysBy(TextMode, NumberOfDependencies);
  }
}
// ---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::needToUseCorrector(
                      ETextMode TextMode,
                      CCapitalWithDependenciesContainer::iterator itCapslock,
                      CCapitalWithDependenciesContainer* pCapslocks) const {
  if (itCapslock->getNumberOfDependentKeys(TextMode) == 0)
    return false;
  if (itCapslock == pCapslocks->begin())
    return false;
    CCapitalWithDependenciesContainer::iterator itPrevious = itCapslock;
    --itPrevious;
  if (itPrevious->getNumberOfDependentKeys(TextMode) == 0)
    return true;
  return false;
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::setNearestCapslock(
                            CCapitalWithDependenciesContainer* pCapslocks) {
  CCapitalWithDependenciesContainer::iterator
      itNextCapslock = itCurrentCapslock;
  ++itNextCapslock;
  while (true) {
    if (itNextCapslock == pCapslocks->end())
      return;
    if (itNextCapslock->
            getIterator()->
                isPressedAfter(itCurrentSymbol->getPressingTime()))
      return;
    itCurrentCapslock = itNextCapslock;
    ++itNextCapslock;
  }
}
// ---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::initialize(
                          const CSession& Session,
                          const CTextDataTree& TextTree,
                          CCapitalWithDependenciesContainer* pCapslocks) {
  fillWithoutDependencies(Session, pCapslocks);
  if (pCapslocks->empty())
    return false;
  itCurrentSymbol = TextTree.beginText(ETextMode::Full);
  itCurrentCapslock = pCapslocks->begin();
  moveCurrentSymbolAfterCurrentCapslock(TextTree);
  return true;
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::
      moveCurrentSymbolAfterCurrentCapslock(const CTextDataTree& TextTree) {
  while ( itCurrentSymbol != TextTree.endText(ETextMode::Full) &&
          itCurrentCapslock->
            getIterator()->
                isPressedAfter(itCurrentSymbol->getPressingTime())) {
    ++itCurrentSymbol;
  }
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::updateDependencies() {
  if (itCurrentSymbol->isAnyPrinted())
    itCurrentCapslock->increasePrintedDependencies();
  else if (itCurrentSymbol->isAnyDeleted())
    itCurrentCapslock->increaseDeletedDependencies();
  else
    // Попали в корень!
    return;
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::fillWithoutDependencies(
                              const CSession& Session,
                              CCapitalWithDependenciesContainer* pCapslocks) {
  pCapslocks->clear();
  CSession::const_iterator itSymbol = Session.begin();
  while (itSymbol != Session.end()) {
    if (itSymbol->isCapslock())
      pCapslocks->push_back(itSymbol);
    ++itSymbol;
  }
}
// ---------------------------------------------------------------------------
// Definitions of CCapslocksWithDependenciesFiller::CCorrector
// ---------------------------------------------------------------------------

CCapslocksWithDependenciesFiller::CCorrector::CCorrector(
      const CCapitalWithDependenciesContainer::iterator& itInitialPosition)
  : itCorrectionPosition(itInitialPosition),
    NumberOfSkippedCapslocks(0) {
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::
                    CCorrector::setToCorrectionPlace(
                          ETextMode TextMode,
                          CCapitalWithDependenciesContainer* pCapitals) {
  if (itCorrectionPosition == pCapitals->begin())
    return;
  moveLeft();

  while (itCorrectionPosition != pCapitals->begin()){
    if(!needToMove(TextMode))
      return;
    moveLeft();
  }

  if(needToMove(TextMode))
    makeExceptionalMoveLeft(pCapitals);
}
// ---------------------------------------------------------------------------
CCapitalWithDependenciesContainer::iterator&
            CCapslocksWithDependenciesFiller::CCorrector::getPosition() {
  return itCorrectionPosition;
}
// ---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::CCorrector::needCorrection() const {
  return (NumberOfSkippedCapslocks % 2) == 0;
}
// ---------------------------------------------------------------------------

bool CCapslocksWithDependenciesFiller::
                          CCorrector::needToMove(ETextMode TextMode) const {
  if (itCorrectionPosition->getNumberOfDependentKeys(TextMode) == 0)
    return true;
  return false;
}
// ---------------------------------------------------------------------------

void CCapslocksWithDependenciesFiller::CCorrector::moveLeft() {
  --itCorrectionPosition;
  ++NumberOfSkippedCapslocks;
}
// ---------------------------------------------------------------------------
void CCapslocksWithDependenciesFiller::CCorrector::makeExceptionalMoveLeft(
                              CCapitalWithDependenciesContainer* pCapitals) {
  itCorrectionPosition = pCapitals->end();
  ++NumberOfSkippedCapslocks;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#pragma package(smart_init)
