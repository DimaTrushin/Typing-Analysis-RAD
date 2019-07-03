//---------------------------------------------------------------------------

#ifndef UnitStringFormatH
#define UnitStringFormatH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitStringFormatDefault.h"
#include "UnitColorManipulator.h"
#include <map>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Enum
// ---------------------------------------------------------------------------

enum class ETextFormat {
  MainText, DeletedTextAccidental, DeletedTextRequired,
  SystemKey, MistakenSymbol, SessionDelimiter, SeanceDelimiter,
  BackspaceFormat, ShiftFormat, EssentialShiftFormat, AltFormat,
  CtrlFormat, CapslockFormat, EssentialCapslockFormat, EnterFormat
};
// ---------------------------------------------------------------------------
// Declaration of Global Functions
// ---------------------------------------------------------------------------

CBasicString getETextFormat(ETextFormat TextFormat);
// ---------------------------------------------------------------------------
// Declaration of CStringFormat
// ---------------------------------------------------------------------------

class CStringFormat {
  public:
  CStringFormat(COLORREF newTextColor = CDefaultStringFormats::MainTextColor,
                COLORREF newBackColor = CDefaultStringFormats::TextBackColor);

  void makeBackDarker(int Depth);
  void makeBackLighter(int Depth);
  void makeTextDarker(int Depth);
  void makeTextLighter(int Depth);

  COLORREF TextColor;
  COLORREF BackColor;

  private:
};
// ---------------------------------------------------------------------------
// Declaration CFormatPool
// ---------------------------------------------------------------------------

class CFormatPool : public std::map<ETextFormat, CStringFormat> {
public:
  void setToDefault();
  CStringFormat getStringFormat(ETextFormat Format) const;
};
// ---------------------------------------------------------------------------
// Declaration of CFormatStructure
// ---------------------------------------------------------------------------

struct CFormatStructure{
  CFormatStructure( ETextFormat newTextFormat,
                    int newDepth);
  bool operator == (const CFormatStructure& other) const;

  ETextFormat TextFormat;
  int Depth;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
