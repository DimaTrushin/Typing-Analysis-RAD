//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitStringFormat.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Definition of Global Functions
// ---------------------------------------------------------------------------

CBasicString getETextFormat(ETextFormat TextFormat) {
  if (TextFormat == ETextFormat::MainText)
    return L"MainText";
  if (TextFormat == ETextFormat::DeletedTextAccidental)
    return L"DeletedTextAccidental";
  if (TextFormat == ETextFormat::DeletedTextRequired)
    return L"DeletedTextRequired";
  if (TextFormat == ETextFormat::SystemKey)
    return L"SystemKey";
  if (TextFormat == ETextFormat::MistakenSymbol)
    return L"Mistake";
  if (TextFormat == ETextFormat::SessionDelimiter)
    return L"SessionDelimiter";
  if (TextFormat == ETextFormat::SeanceDelimiter)
    return L"SeanceDelimiter";
  if (TextFormat == ETextFormat::BackspaceFormat)
    return L"Backspace";
  if (TextFormat == ETextFormat::ShiftFormat)
    return L"Shift";
  if (TextFormat == ETextFormat::EssentialShiftFormat)
    return L"EssShift";
  if (TextFormat == ETextFormat::AltFormat)
    return L"Alt";
  if (TextFormat == ETextFormat::CtrlFormat)
    return L"Ctrl";
  if (TextFormat == ETextFormat::CapslockFormat)
    return L"Capslock";
  if (TextFormat == ETextFormat::EssentialCapslockFormat)
    return L"EssCapslock";
  if (TextFormat == ETextFormat::EnterFormat)
    return L"Enter";
  return L"Unknown";
}
// ---------------------------------------------------------------------------
// Definition of CStringFormat
// ---------------------------------------------------------------------------

CStringFormat::CStringFormat( COLORREF newTextColor,
                              COLORREF newBackColor)
  : TextColor(newTextColor),
    BackColor(newBackColor) {
}
// ---------------------------------------------------------------------------

void CStringFormat::makeBackDarker(int Depth){
  BackColor = CColorManipulator::makeColorDarker(BackColor, Depth);
}
// ---------------------------------------------------------------------------

void CStringFormat::makeBackLighter(int Depth){
  BackColor = CColorManipulator::makeColorLighter(BackColor, Depth);
}
// ---------------------------------------------------------------------------

void CStringFormat::makeTextDarker(int Depth){
  TextColor = CColorManipulator::makeColorDarker(TextColor, Depth);
}
// ---------------------------------------------------------------------------

void CStringFormat::makeTextLighter(int Depth){
  TextColor = CColorManipulator::makeColorLighter(TextColor, Depth);
}
// ---------------------------------------------------------------------------
// Definition CFormatPool
// ---------------------------------------------------------------------------

void CFormatPool::setToDefault() {
  (*this)[ETextFormat::MainText] = CStringFormat();
  (*this)[ETextFormat::DeletedTextAccidental] = CStringFormat(
                        CDefaultStringFormats::DeletedTextAccidentalColor,
                        CDefaultStringFormats::DeletedTextAccidentalBackColor);
  (*this)[ETextFormat::DeletedTextRequired] = CStringFormat(
                        CDefaultStringFormats::DeletedTextRequiredColor,
                        CDefaultStringFormats::DeletedTextRequiredBackColor);
  (*this)[ETextFormat::SystemKey] = CStringFormat(
                        CDefaultStringFormats::SystemKeyColor);
  (*this)[ETextFormat::MistakenSymbol] = CStringFormat(
                        CDefaultStringFormats::MistakenSymbolColor,
                        CDefaultStringFormats::MistakenBackColor);
  (*this)[ETextFormat::SessionDelimiter] = CStringFormat(
                        CDefaultStringFormats::SessionDelimiterColor);
  (*this)[ETextFormat::SeanceDelimiter] = CStringFormat(
                        CDefaultStringFormats::SeanceDelimiterColor);
  (*this)[ETextFormat::BackspaceFormat] = CStringFormat(
                        CDefaultStringFormats::BackSpaceColor);
  (*this)[ETextFormat::ShiftFormat] = CStringFormat(
                        CDefaultStringFormats::ShiftColor);
  (*this)[ETextFormat::EssentialShiftFormat] = CStringFormat(
                        CDefaultStringFormats::EssentialShiftColor);
  (*this)[ETextFormat::AltFormat] = CStringFormat(
                        CDefaultStringFormats::AltColor);
  (*this)[ETextFormat::CtrlFormat] = CStringFormat(
                        CDefaultStringFormats::CtrlColor);
  (*this)[ETextFormat::CapslockFormat] = CStringFormat(
                        CDefaultStringFormats::CapslockColor);
  (*this)[ETextFormat::EssentialCapslockFormat] = CStringFormat(
                        CDefaultStringFormats::EssentialCapslockColor);
  (*this)[ETextFormat::EnterFormat] = CStringFormat(
                        CDefaultStringFormats::EnterColor);
}
// ---------------------------------------------------------------------------

CStringFormat CFormatPool::getStringFormat(ETextFormat Format) const {
  if (find(Format) == end())
    return CStringFormat();
  return find(Format)->second;
}
// ---------------------------------------------------------------------------
// Definition of CFormatStructure
// ---------------------------------------------------------------------------

CFormatStructure::CFormatStructure( ETextFormat newTextFormat,
                                    int newDepth)
  : TextFormat(newTextFormat),
    Depth(newDepth) {
}
// ---------------------------------------------------------------------------

bool CFormatStructure::operator == (const CFormatStructure& other) const {
  return  TextFormat == other.TextFormat &&
          Depth == other.Depth;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
