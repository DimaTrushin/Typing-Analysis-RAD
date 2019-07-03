//---------------------------------------------------------------------------

#ifndef UnitStringFormatDefaultH
#define UnitStringFormatDefaultH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <Richedit.h>
#include <string>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Using
// ---------------------------------------------------------------------------

using CBasicString = std::wstring;
using CStringFormatWinAPI = CHARFORMAT2W;
// ---------------------------------------------------------------------------
// Declaration of CDefaultStringFormats
// ---------------------------------------------------------------------------

struct CDefaultStringFormats {
  static constexpr COLORREF MainTextColor =                   RGB(0, 0, 0);
  static constexpr COLORREF TextBackColor =                   RGB(192, 220, 192);
  static constexpr COLORREF DeletedTextAccidentalBackColor =  RGB(255, 180, 180);
  static constexpr COLORREF DeletedTextAccidentalColor =      RGB(0, 0, 0);
  static constexpr COLORREF DeletedTextRequiredBackColor =    RGB(255, 90, 90);
  static constexpr COLORREF DeletedTextRequiredColor =        RGB(0, 0, 0);
  static constexpr COLORREF MistakenSymbolColor =             RGB(180, 0, 0);
  static constexpr COLORREF MistakenBackColor =               RGB(255, 204, 153);
  static constexpr COLORREF SessionDelimiterColor =           RGB(0, 0, 255);
  static constexpr COLORREF SeanceDelimiterColor =            RGB(0, 150, 80);
  static constexpr COLORREF BackSpaceColor =                  RGB(180, 0, 0);
  static constexpr COLORREF SystemKeyColor =                  RGB(0, 190, 40);
  static constexpr COLORREF ShiftColor =                      RGB(0, 190, 40);
  static constexpr COLORREF EssentialShiftColor =             RGB(255, 120, 0);
  static constexpr COLORREF AltColor =                        RGB(0, 190, 40);
  static constexpr COLORREF CtrlColor =                       RGB(0, 190, 40);
  static constexpr COLORREF CapslockColor =                   RGB(0, 190, 40);
  static constexpr COLORREF EssentialCapslockColor =          RGB(255, 120, 0);
  static constexpr COLORREF EnterColor =                      RGB(0, 190, 40);
};
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
