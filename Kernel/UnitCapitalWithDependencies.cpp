//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitCapitalWithDependencies.h"
//---------------------------------------------------------------------------

#if !defined(__CAPITAL_WITH_DEPENDENCIES__DISABLE__)
namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Definition CCapitalWithDependencies
// ---------------------------------------------------------------------------

CCapitalWithDependencies::CCapitalWithDependencies(
                            const CSession::const_iterator& Iterator,
                            unsigned int numberOfDependentPrintedKeys,
                            unsigned int numberOfDependentDeletedKeys)
  : KeyIterator(Iterator),
    NumberOfDependentKeysInPrintedMode(numberOfDependentPrintedKeys),
    NumberOfDependentKeysInFullMode(numberOfDependentPrintedKeys +
                              numberOfDependentDeletedKeys) {
}
// ---------------------------------------------------------------------------

unsigned int
  CCapitalWithDependencies::getNumberOfDependentPrintedKeys() const {
  return NumberOfDependentKeysInPrintedMode;
}
// ---------------------------------------------------------------------------

unsigned int CCapitalWithDependencies::getNumberOfDependentDeletedKeys() const {
  return  getNumberOfDependentFullKeys() -
          getNumberOfDependentPrintedKeys();
}
// ---------------------------------------------------------------------------

unsigned int CCapitalWithDependencies::getNumberOfDependentFullKeys() const {
  return NumberOfDependentKeysInFullMode;
}
// ---------------------------------------------------------------------------

unsigned int CCapitalWithDependencies::getNumberOfDependentKeys(
                                                    ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return getNumberOfDependentFullKeys();
  assert(TextMode == ETextMode::Printed);
  return getNumberOfDependentPrintedKeys();
}
// ---------------------------------------------------------------------------
void CCapitalWithDependencies::setNumberOfDependentKeys(
                                                ETextMode TextMode,
                                                unsigned int newValue) {
  if (TextMode == ETextMode::Full)
    NumberOfDependentKeysInFullMode = newValue;
  if (TextMode == ETextMode::Printed)
    NumberOfDependentKeysInPrintedMode = newValue;
  assert(TextMode == ETextMode::Full || TextMode == ETextMode::Printed);
}

// ---------------------------------------------------------------------------

const CSession::const_iterator& CCapitalWithDependencies::getIterator() const {
  return KeyIterator;
}
// ---------------------------------------------------------------------------

bool CCapitalWithDependencies::isPrintedEssential() const {
  return getNumberOfDependentPrintedKeys() > 0;
}
// ---------------------------------------------------------------------------

bool CCapitalWithDependencies::isFullEssential() const {
  return getNumberOfDependentFullKeys() > 0;
}
// ---------------------------------------------------------------------------

bool CCapitalWithDependencies::isEssential(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return isFullEssential();
  assert(TextMode == ETextMode::Printed);
  return isPrintedEssential();
}
// ---------------------------------------------------------------------------

void CCapitalWithDependencies::increasePrintedDependencies() {
  ++NumberOfDependentKeysInPrintedMode;
  ++NumberOfDependentKeysInFullMode;
}
// ---------------------------------------------------------------------------

void CCapitalWithDependencies::increaseDeletedDependencies(){
  ++NumberOfDependentKeysInFullMode;
}
// ---------------------------------------------------------------------------

void CCapitalWithDependencies::increaseNumberOfDependentKeysBy(
                                                      ETextMode TextMode,
                                                      unsigned int amount) {
  if (TextMode == ETextMode::Full)
    NumberOfDependentKeysInFullMode += amount;
  if (TextMode == ETextMode::Printed)
    NumberOfDependentKeysInPrintedMode += amount;
  assert(TextMode == ETextMode::Full || TextMode == ETextMode::Printed);
}
// ---------------------------------------------------------------------------

CSession::const_iterator& CCapitalWithDependencies::getIterator() {
  return KeyIterator;
}
// ---------------------------------------------------------------------------
// Definitions of CCapitalWithDependenciesContainer
// ---------------------------------------------------------------------------

int CCapitalWithDependenciesContainer::getSize(
                                          ETextMode TextMode,
                                          ECapitalMode CapitalMode) const {
  if (CapitalMode == ECapitalMode::Non)
    return 0;
  if (CapitalMode == ECapitalMode::All)
    return size();
  assert(CapitalMode == ECapitalMode::Essential);
  return getNumberOfEssential(TextMode);
}
// ---------------------------------------------------------------------------

bool CCapitalWithDependenciesContainer::isEmpty(ETextMode TextMode,
                                                ECapitalMode CapitalMode) const {
  return getSize(TextMode, CapitalMode) == 0;
}
// ---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
  CCapitalWithDependenciesContainer::getFirstCapital(
                                    ETextMode TextMode,
                                    ECapitalMode CapitalMode) const {
  if (CapitalMode == ECapitalMode::Non)
    return end();
  if (CapitalMode == ECapitalMode::All)
    return begin();
  assert(CapitalMode == ECapitalMode::Essential);
  return getFirstEssentialCapital(TextMode);
}
// ---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
  CCapitalWithDependenciesContainer::getLastCapital(
                                    ETextMode TextMode,
                                    ECapitalMode CapitalMode) const {
  if (CapitalMode == ECapitalMode::Non)
    return end();
  if (empty())
    return end();
  if (CapitalMode == ECapitalMode::All)
    return --end();
  assert(CapitalMode == ECapitalMode::Essential);
  return getLastEssentialCapital(TextMode);
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesContainer::getFirstPressingTime(
                                            ETextMode TextMode,
                                            ECapitalMode CapitalMode) const {
  const_iterator itFirstPressed = getFirstCapital(TextMode, CapitalMode);
  if (itFirstPressed == end())
    return -1;
  return itFirstPressed->getIterator()->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesContainer::getFirstReleasingTime(
                                            ETextMode TextMode,
                                            ECapitalMode CapitalMode) const {
  if (CapitalMode == ECapitalMode::Non)
    return -1;
  if (CapitalMode == ECapitalMode::All)
    return getFirstReleasingTime();
  assert(CapitalMode == ECapitalMode::Essential);
  return getFirstEssentialReleasingTime(TextMode);
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesContainer::getLastPressingTime(
                                            ETextMode TextMode,
                                            ECapitalMode CapitalMode) const {
  const_iterator itLastPressed = getLastCapital(TextMode, CapitalMode);
  if (itLastPressed == end())
    return -1;
  return itLastPressed->getIterator()->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesContainer::getLastReleasingTime(
                                            ETextMode TextMode,
                                            ECapitalMode CapitalMode) const {
  if (CapitalMode == ECapitalMode::Non)
    return -1;
  if (CapitalMode == ECapitalMode::All)
    return getLastReleasingTime();
  assert(CapitalMode == ECapitalMode::Essential);
  return getLastEssentialReleasingTime(TextMode);
}
// ---------------------------------------------------------------------------

int CCapitalWithDependenciesContainer::getNumberOfEssential(
                                                  ETextMode TextMode) const {
  int NumberOfEssential = 0;
  for (const auto& Capital : *this)
    if (Capital.isEssential(TextMode))
      ++NumberOfEssential;
  return NumberOfEssential;
}
// ---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
  CCapitalWithDependenciesContainer::getFirstEssentialCapital(
                                                    ETextMode TextMode) const {
  return std::find_if(begin(),
                      end(),
                      [&TextMode](const CCapitalWithDependencies& Capital){
                        return Capital.isEssential(TextMode);
                      });
}
// ---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
  CCapitalWithDependenciesContainer::getLastEssentialCapital(
                                                    ETextMode TextMode) const {
  if (empty())
    return end();
  const_iterator itLastCapital = end();
  do {
    --itLastCapital;
    if (itLastCapital->isEssential(TextMode))
      return itLastCapital;
  } while (itLastCapital != begin());
  return end();
}
// ---------------------------------------------------------------------------

microseconds CCapitalWithDependenciesContainer::getFirstReleasingTime() const {
  if (empty())
    return -1;
  microseconds CurrentReleasingTime =
                          begin()->getIterator()->getReleasingTime();
  for (const auto& Capital : *this)
    if (Capital.getIterator()->isPressedBefore(CurrentReleasingTime))
      CurrentReleasingTime = Capital.getIterator()->getReleasingTime();
  return CurrentReleasingTime;
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesContainer::
                  getFirstEssentialReleasingTime(ETextMode TextMode) const {
  const_iterator itCapital = getFirstEssentialCapital(TextMode);
  if (itCapital == end())
    return -1;
  microseconds CurrentReleasingTime =
                      itCapital->getIterator()->getReleasingTime();
  while (itCapital != end()) {
    if (itCapital->isEssential(TextMode) &&
        itCapital->getIterator()->isReleasedBefore(CurrentReleasingTime))
      CurrentReleasingTime = itCapital->getIterator()->getReleasingTime();
    ++itCapital;
  }
  return CurrentReleasingTime;
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesContainer::getLastReleasingTime() const {
  if (empty())
    return -1;
  microseconds CurrentReleasingTime =
                        begin()->getIterator()->getReleasingTime();
  for (const auto& Capital : *this)
    if (Capital.getIterator()->isReleasedAfter(CurrentReleasingTime))
      CurrentReleasingTime = Capital.getIterator()->getReleasingTime();
  return CurrentReleasingTime;
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesContainer::
                    getLastEssentialReleasingTime(ETextMode TextMode) const {
  const_iterator itCapital = getFirstEssentialCapital(TextMode);
  if (itCapital == end())
    return -1;
  microseconds
    CurrentReleasingTime =
                      itCapital->getIterator()->getReleasingTime();
  while (itCapital != end()) {
    if (itCapital->isEssential(TextMode) &&
        itCapital->getIterator()->isReleasedAfter(CurrentReleasingTime))
      CurrentReleasingTime = itCapital->getIterator()->getReleasingTime();
    ++itCapital;
  }
  return CurrentReleasingTime;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#pragma package(smart_init)
