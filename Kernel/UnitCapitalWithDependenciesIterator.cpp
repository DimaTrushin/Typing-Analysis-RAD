//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitCapitalWithDependenciesIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Definitions of CCapitalWithDependenciesIterator
// ---------------------------------------------------------------------------

CCapitalWithDependenciesIterator::
        CCapitalWithDependenciesIterator(
                const CCapitalWithDependenciesContainer* pCapitalContainer,
                const CSession* pSession,
                ETextMode textMode,
                ECapitalMode capitalMode,
                ECapitalType capitalType)
  : pHostCapitalContainer(pCapitalContainer),
    pHostSession(pSession),
    TextMode(textMode),
    CapitalMode(capitalMode),
    CapitalType(capitalType),
    CurrentPosition(getBegin()){
}
// ---------------------------------------------------------------------------

ETextFormat CCapitalWithDependenciesIterator::getTextFormat() const {
  if (CapitalType == ECapitalType::Shift) {
    if (isEssential())
      return ETextFormat::EssentialShiftFormat;
    return ETextFormat::ShiftFormat;
  }
  if (CapitalType == ECapitalType::Capslock) {
    if (isEssential())
      return ETextFormat::EssentialCapslockFormat;
    return ETextFormat::CapslockFormat;
  }
  return ETextFormat::SystemKey;
}
// ---------------------------------------------------------------------------

CFormatStructure
  CCapitalWithDependenciesIterator::getTextFormatStructure() const {
  return CFormatStructure(getTextFormat(), getDependencyNumber());
}
// ---------------------------------------------------------------------------

wchar_t CCapitalWithDependenciesIterator::getSymbol() const {
  return CurrentPosition->getIterator()->getSystemKeySymbol();
}
// ---------------------------------------------------------------------------

unsigned short CCapitalWithDependenciesIterator::getVKCode() const {
  return CurrentPosition->getIterator()->getVKCode();
}
// ---------------------------------------------------------------------------

bool CCapitalWithDependenciesIterator::isValid() const {
  if (pHostCapitalContainer == nullptr)
    return false;
  return CurrentPosition != getEnd();
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesIterator::getPressingTime() const {
  return CurrentPosition->getIterator()->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesIterator::getReleasingTime() const {
  return CurrentPosition->getIterator()->getReleasingTime();
}
// ---------------------------------------------------------------------------

void CCapitalWithDependenciesIterator::setNext() {
  if (CapitalMode == ECapitalMode::Non)
    return;
  ++CurrentPosition;
  if (CapitalMode == ECapitalMode::All)
    return;
  assert(CapitalMode == ECapitalMode::Essential);
  moveUntilEssential(TextMode, &CurrentPosition);
}
// ---------------------------------------------------------------------------

microseconds
  CCapitalWithDependenciesIterator::
                                      getPhysicalResponseTime() const {
  return pHostSession->getResponseTime(CurrentPosition->getIterator());
}
// ---------------------------------------------------------------------------

bool CCapitalWithDependenciesIterator::isEssential() const {
  return CurrentPosition->isEssential(TextMode);
}
// ---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
        CCapitalWithDependenciesIterator::getBegin() const {
  if (CapitalMode == ECapitalMode::All)
    return pHostCapitalContainer->begin();
  if (CapitalMode == ECapitalMode::Non)
    return pHostCapitalContainer->end();
  assert(CapitalMode == ECapitalMode::Essential);
  return getEssentialBegin();
}
// ---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
  CCapitalWithDependenciesIterator::getEssentialBegin() const {
  CCapitalWithDependenciesContainer::const_iterator
    itBegin = pHostCapitalContainer->begin();
  moveUntilEssential(TextMode, &itBegin);
  return itBegin;
}
// ---------------------------------------------------------------------------

CCapitalWithDependenciesContainer::const_iterator
        CCapitalWithDependenciesIterator::getEnd() const {
  return pHostCapitalContainer->end();
}
// ---------------------------------------------------------------------------

void CCapitalWithDependenciesIterator::moveUntilEssential(
          ETextMode TextMode,
          CCapitalWithDependenciesContainer::const_iterator* pIterator) const {
  CCapitalWithDependenciesContainer::const_iterator&
    Iterator = *pIterator;
  while (Iterator != getEnd()) {
    if (Iterator->isEssential(TextMode))
      break;
    ++Iterator;
  }
}
// ---------------------------------------------------------------------------

int CCapitalWithDependenciesIterator::getDependencyNumber() const {
  if (TextMode == ETextMode::Full)
    return CurrentPosition->getNumberOfDependentFullKeys();
  assert(TextMode == ETextMode::Printed);
  return CurrentPosition->getNumberOfDependentPrintedKeys();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
