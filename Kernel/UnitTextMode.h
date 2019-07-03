//---------------------------------------------------------------------------

#ifndef UnitTextModeH
#define UnitTextModeH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "../Debug/UnitDisabler.h"
//---------------------------------------------------------------------------

#if !defined(__TEXT_MODE__DISABLE__)
namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Enum
// ---------------------------------------------------------------------------

// Full -- text mode including all symbols with deleted ones
// Printed -- text mode including printed symbols only
enum class ETextMode {
  Full, Printed
};
// ---------------------------------------------------------------------------

// Raw -- output the content of session
// Text -- output with respect to CTextMode
enum class EOutputMode {
  Raw, Text
};
// ---------------------------------------------------------------------------

enum class ECapitalMode {
  Non, Essential, All
};
// ---------------------------------------------------------------------------

enum class ECapitalType {
  Shift, Capslock
};
// ---------------------------------------------------------------------------
// Declaration CTextMode
// ---------------------------------------------------------------------------

class CTextMode {
  public:
  CTextMode(ETextMode textMode = ETextMode::Full,
            ECapitalMode shiftMode = ECapitalMode::All,
            ECapitalMode capslockMode = ECapitalMode::All);

  ETextMode TextMode;
  ECapitalMode ShiftMode;
  ECapitalMode CapslockMode;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
