//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitModeReader.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {


//---------------------------------------------------------------------------
// Definition of CTextModeReader
//---------------------------------------------------------------------------

CTextModeReader::CTextModeReader()
  : pTextModeGroup(nullptr),
    pShiftModeGroup(nullptr),
    pCapslockModeGroup(nullptr) {
}
//---------------------------------------------------------------------------

void CTextModeReader::setModeGroups(
                    TRadioGroup* pNewTextModeGroup,
                    TRadioGroup* pNewShiftModeGroup,
                    TRadioGroup* pNewCapslockModeGroup) {
  pTextModeGroup = pNewTextModeGroup;
  pShiftModeGroup = pNewShiftModeGroup;
  pCapslockModeGroup = pNewCapslockModeGroup;
}
//---------------------------------------------------------------------------

void CTextModeReader::setTextMode(EOutputMode* pOutputMode,
                                  CTextMode* pTextMode) const {
  assert(pTextModeGroup != nullptr);
  assert(pShiftModeGroup != nullptr);
  assert(pCapslockModeGroup != nullptr);

  setOutputMode(pOutputMode);
  if (*pOutputMode == EOutputMode::Text)
    setTextMode(pTextMode);
}
//---------------------------------------------------------------------------

void CTextModeReader::setOutputMode(EOutputMode* pOutputMode) const {
  assert(pTextModeGroup != nullptr);
  if (pTextModeGroup->ItemIndex == 0)
    *pOutputMode = EOutputMode::Raw;
  else
    *pOutputMode = EOutputMode::Text;
}
//---------------------------------------------------------------------------

void CTextModeReader::setTextMode(CTextMode* pTextMode) const {
  setTextMode(&pTextMode->TextMode);
  setShiftMode(&pTextMode->ShiftMode);
  setCapslockMode(&pTextMode->CapslockMode);
}
//---------------------------------------------------------------------------

void CTextModeReader::setTextMode(ETextMode* pTextMode) const {
  assert(pTextModeGroup != nullptr);
  if (pTextModeGroup->ItemIndex == 1)
    *pTextMode = ETextMode::Full;
  if (pTextModeGroup->ItemIndex == 2)
   *pTextMode = ETextMode::Printed;
  assert(pTextModeGroup->ItemIndex != 0);
}
//---------------------------------------------------------------------------

void CTextModeReader::setShiftMode(ECapitalMode* pShiftMode) const {
  setCapitalMode(pShiftModeGroup, pShiftMode);
}
//---------------------------------------------------------------------------

void CTextModeReader::setCapslockMode(ECapitalMode* pCapslockMode) const {
  setCapitalMode(pCapslockModeGroup, pCapslockMode);
}
//---------------------------------------------------------------------------

void CTextModeReader::setCapitalMode( const TRadioGroup* pCapitalModeGroup,
                                      ECapitalMode* pCapitalMode) const {
  assert(pCapitalModeGroup != nullptr);
  if (pCapitalModeGroup->ItemIndex == 0)
    *pCapitalMode = ECapitalMode::Non;
  if (pCapitalModeGroup->ItemIndex == 1)
    *pCapitalMode = ECapitalMode::All;
  if (pCapitalModeGroup->ItemIndex == 2)
    *pCapitalMode = ECapitalMode::Essential;
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
