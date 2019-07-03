//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitSessionIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CSessionIterator
// ---------------------------------------------------------------------------

CSessionIterator::CSessionIterator(const CSession& Session)
  : pSession(&Session),
    CurrentPosition(Session.begin()) {
  CurrentKeyboardState.setKeyboardState(Session.getKeyboardState());
  PressedKeys.push_heap(CurrentPosition);
}
// ---------------------------------------------------------------------------

ETextFormat CSessionIterator::getTextFormat() const {
  if (CurrentPosition->isSymbolOrSpace())
    return ETextFormat::MainText;
  if (CurrentPosition->isAnyShift())
    return ETextFormat::ShiftFormat;
  if (CurrentPosition->isAnyCtrl())
    return ETextFormat::CtrlFormat;
  if (CurrentPosition->isAnyAlt())
    return ETextFormat::AltFormat;
  if (CurrentPosition->isCapslock())
    return ETextFormat::CapslockFormat;
  if (CurrentPosition->isEnter())
    return ETextFormat::EnterFormat;
  if (CurrentPosition->isBackspace())
    return ETextFormat::BackspaceFormat;
  // any unknown key has MainText format
  return ETextFormat::MainText;
}
// ---------------------------------------------------------------------------

CFormatStructure CSessionIterator::getTextFormatStructure() const {
  return CFormatStructure(getTextFormat(), 0);
}
// ---------------------------------------------------------------------------

wchar_t CSessionIterator::getSymbol() const {
  if (CurrentPosition->isSymbolOrSpace())
    return CurrentPosition->getKeySymbol(CurrentKeyboardState);
  if (CurrentPosition->isSystemKey())
    return CurrentPosition->getSystemKeySymbol();
  // unknown symbol
  return L'?';
}
// ---------------------------------------------------------------------------

unsigned short CSessionIterator::getVKCode() const {
  return CurrentPosition->getVKCode();
}
// ---------------------------------------------------------------------------

bool CSessionIterator::isValid() const {
  return CurrentPosition != pSession->end();
}
// ---------------------------------------------------------------------------

microseconds CSessionIterator::getPressingTime() const {
  return CurrentPosition->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CSessionIterator::getReleasingTime() const {
  return CurrentPosition->getReleasingTime();
}
// ---------------------------------------------------------------------------

void CSessionIterator::setNext() {
  pressCurrentKeyOnKeyboardState(CurrentPosition);
  ++CurrentPosition;
  if (!isValid())
    return;
  releaseBefore(CurrentPosition->getPressingTime());
  PressedKeys.push_heap(CurrentPosition);
}
// ---------------------------------------------------------------------------

microseconds CSessionIterator::getPhysicalResponseTime() const {
  return pSession->getResponseTime(CurrentPosition);
}
// ---------------------------------------------------------------------------

void CSessionIterator::releaseBefore(microseconds Time) {
  PressedKeys.releaseBefore(Time, &CurrentKeyboardState);
}
// ---------------------------------------------------------------------------

void CSessionIterator::pressCurrentKeyOnKeyboardState(
                                const CSession::const_iterator& KeyIterator) {
  CurrentKeyboardState.PressKey(KeyIterator->getVKCode());
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
