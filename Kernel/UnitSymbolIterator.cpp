//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitSymbolIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CSymbolIterator
// ---------------------------------------------------------------------------

CSymbolIterator::CSymbolIterator(
                            const CTextDataTree* pTree,
                            ETextMode mode,
                            ESymbolIteratorStart BeginFrom)
  : pHostTree(pTree),
    IteratorMode(mode),
    CurrentPosition(pTree->beginFromRoot()) {
  if (BeginFrom == ESymbolIteratorStart::FromTextBegin)
    CurrentPosition = pTree->beginText(mode);
}
// ---------------------------------------------------------------------------

ETextFormat CSymbolIterator::getTextFormat() const {
  if (getSymbolStatus() == ESymbolStatus::TextSymbol)
    return ETextFormat::MainText;
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolAccidental)
    return ETextFormat::DeletedTextAccidental;
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolRequired)
    return ETextFormat::DeletedTextRequired;
  if (getSymbolStatus() == ESymbolStatus::MistakeSymbol)
    return ETextFormat::MistakenSymbol;
  if (getSymbolStatus() == ESymbolStatus::RootSymbol)
    return ETextFormat::SessionDelimiter;
  return ETextFormat::MainText;
}
// ---------------------------------------------------------------------------

CFormatStructure CSymbolIterator::getTextFormatStructure() const {
  return CFormatStructure(getTextFormat(), getDepth());
}
// ---------------------------------------------------------------------------

wchar_t CSymbolIterator::getSymbol() const {
  return CurrentPosition->getSymbol();
}
// ---------------------------------------------------------------------------

unsigned short CSymbolIterator::getVKCode() const {
  return CurrentPosition->getVKCode();
}
// ---------------------------------------------------------------------------

bool CSymbolIterator::isValid() const {
  if (pHostTree == nullptr)
    return false;
  return CurrentPosition != pHostTree->endText(IteratorMode);
}
// ---------------------------------------------------------------------------

microseconds CSymbolIterator::getPressingTime() const {
  return CurrentPosition->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CSymbolIterator::getReleasingTime() const {
  return CurrentPosition->getReleasingTime();
}
// ---------------------------------------------------------------------------

void CSymbolIterator::setNext() {
  if (IteratorMode == ETextMode::Full)
    setNextFull();
  else {
    assert(IteratorMode == ETextMode::Printed);
    setNextNonFull();
  }
}
// ---------------------------------------------------------------------------

microseconds CSymbolIterator::getPhysicalResponseTime() const {
  return CurrentPosition->getResponseTime();
}
// ---------------------------------------------------------------------------

void CSymbolIterator::setNextFull() {
  CTextDataTree::CConstFullTextIterator next(CurrentPosition);
  ++next;
  CurrentPosition = next;
}
// ---------------------------------------------------------------------------

void CSymbolIterator::setNextNonFull() {
  CTextDataTree::CConstTextIterator next(CurrentPosition);
  ++next;
  CurrentPosition = next;
}
// ---------------------------------------------------------------------------

ESymbolStatus CSymbolIterator::getSymbolStatus() const {
  return CurrentPosition->getSymbolStatus();
}
// ---------------------------------------------------------------------------

int CSymbolIterator::getDepth() const {
  if (getSymbolStatus() == ESymbolStatus::RootSymbol ||
      getSymbolStatus() == ESymbolStatus::TextSymbol)
    return 0;
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolAccidental)
    return getAccidentalDeletedDepth();
  if (getSymbolStatus() == ESymbolStatus::DeletedSymbolRequired)
    return getRequiredDeletedDepth();
  assert(getSymbolStatus() == ESymbolStatus::MistakeSymbol);
  return getMistakeDepth();
}
// ---------------------------------------------------------------------------

int CSymbolIterator::getAccidentalDeletedDepth() const {
  return getAccidentalDeletedDepth(CurrentPosition);
}
// ---------------------------------------------------------------------------

int CSymbolIterator::getAccidentalDeletedDepth(
              const CTextDataTree::CConstBasicIterator& Position) const {
  auto Parent = getParentPosition(Position);
  assert(Parent.isDefined());
  if( Parent->getSymbolStatus() !=
      ESymbolStatus::DeletedSymbolAccidental)
    return  0;
  return getAccidentalDeletedDepth(Parent) + 1;
}
// ---------------------------------------------------------------------------

int CSymbolIterator::getRequiredDeletedDepth() const {
  return getRequiredDeletedDepth(CurrentPosition);
}
// ---------------------------------------------------------------------------

int CSymbolIterator::getRequiredDeletedDepth(
              const CTextDataTree::CConstBasicIterator& Position) const {
  auto Parent = getParentPosition(Position);
  assert(Parent.isDefined());
  if(Parent->getSymbolStatus() != ESymbolStatus::DeletedSymbolRequired)
    return  0;
  return getRequiredDeletedDepth(Parent) + 1;
}
// ---------------------------------------------------------------------------

int CSymbolIterator::getMistakeDepth() const {
  return getParentPosition(CurrentPosition)->MistakeRoutes.size() - 1;
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator
  CSymbolIterator::getParentPosition(
              const CTextDataTree::CConstBasicIterator& Position) const {
  auto Parent = Position;
  Parent.setToParent();
  return Parent;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
