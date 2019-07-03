//---------------------------------------------------------------------------

#ifndef UnitColorManipulatorH
#define UnitColorManipulatorH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <windows.h>
#include <algorithm>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CColorManipulator
// ---------------------------------------------------------------------------

class CColorManipulator {
  public:
  static COLORREF makeColorDarker(COLORREF Color, int Depth);
  static COLORREF makeColorLighter(COLORREF Color, int Depth);
  static COLORREF mixColor(COLORREF MainColor,
                            COLORREF AddingColor,
                            double Weight);
  static COLORREF shiftColorToAnother(COLORREF MainColor,
                                      COLORREF AddingColor,
                                      int Depth);
  // These functions are bad. They slightly change the brightness
  // if OneColor is small and significantly change the brightness
  // if OneColor is large
  static BYTE makeOneColorDarker(BYTE OneColor, int Depth);
  static BYTE makeOneColorLighter(BYTE OneColor, int Depth);
  static BYTE mixOneColor(BYTE MainColor,
                          BYTE AddingColor,
                          double Weight);
  static BYTE shiftOneColorToAnother( BYTE MainColor,
                                      BYTE AddingColor,
                                      int Depth);
private:
  static constexpr int kMaxColorSteps = 10;
  static constexpr double kDarkeningCoefficient = 1.1;
  static constexpr double kLighteningCoefficient = 1.1;
  static constexpr double kShiftingCoefficient = 0.1;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
