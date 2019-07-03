//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitColorManipulator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CColorManipulator
//---------------------------------------------------------------------------

constexpr int CColorManipulator::kMaxColorSteps;
//---------------------------------------------------------------------------

constexpr double CColorManipulator::kDarkeningCoefficient;
//---------------------------------------------------------------------------

constexpr double CColorManipulator::kLighteningCoefficient;
//---------------------------------------------------------------------------

constexpr double CColorManipulator::kShiftingCoefficient;
// ---------------------------------------------------------------------------

COLORREF CColorManipulator::makeColorDarker(COLORREF Color, int Depth){
  BYTE RColor = makeOneColorDarker(GetRValue(Color), Depth);
  BYTE GColor = makeOneColorDarker(GetGValue(Color), Depth);
  BYTE BColor = makeOneColorDarker(GetBValue(Color), Depth);
  return RGB(RColor, GColor, BColor);
}
// ---------------------------------------------------------------------------

COLORREF CColorManipulator::makeColorLighter(COLORREF Color, int Depth){
  BYTE RColor = makeOneColorLighter(GetRValue(Color), Depth);
  BYTE GColor = makeOneColorLighter(GetGValue(Color), Depth);
  BYTE BColor = makeOneColorLighter(GetBValue(Color), Depth);
  return RGB(RColor, GColor, BColor);
}
// ---------------------------------------------------------------------------

COLORREF CColorManipulator::mixColor( COLORREF MainColor,
                                      COLORREF AddingColor,
                                      double Weight) {
  BYTE RColor = mixOneColor(GetRValue(MainColor),
                            GetRValue(AddingColor),
                            Weight);
  BYTE BColor = mixOneColor(GetBValue(MainColor),
                            GetBValue(AddingColor),
                            Weight);
  BYTE GColor = mixOneColor(GetGValue(MainColor),
                            GetGValue(AddingColor),
                            Weight);
  return RGB(RColor, GColor, BColor);
}
// ---------------------------------------------------------------------------

COLORREF CColorManipulator::shiftColorToAnother(COLORREF MainColor,
                                                COLORREF AddingColor,
                                                int Depth) {
  BYTE RColor = shiftOneColorToAnother( GetRValue(MainColor),
                                        GetRValue(AddingColor),
                                        Depth);
  BYTE BColor = shiftOneColorToAnother( GetBValue(MainColor),
                                        GetBValue(AddingColor),
                                        Depth);
  BYTE GColor = shiftOneColorToAnother( GetGValue(MainColor),
                                        GetGValue(AddingColor),
                                        Depth);
  return RGB(RColor, GColor, BColor);
}
// ---------------------------------------------------------------------------

BYTE CColorManipulator::makeOneColorLighter(BYTE OneColor, int Depth){
  int Steps = std::min(Depth, kMaxColorSteps);
  if (OneColor == 0)
    OneColor = 1;
  OneColor = std::min(int(double(OneColor) *
                          std::pow(kLighteningCoefficient, Steps)),
                      255);
  return OneColor;
}
// ---------------------------------------------------------------------------

BYTE CColorManipulator::makeOneColorDarker(BYTE OneColor, int Depth){
  int Steps = std::min(Depth, kMaxColorSteps);
  OneColor = int( double(OneColor) /
                  std::pow(kDarkeningCoefficient, Steps));
  return OneColor;
}
// ---------------------------------------------------------------------------

BYTE CColorManipulator::mixOneColor(BYTE MainColor,
                                    BYTE AddingColor,
                                    double Weight) {
  Weight = std::max(Weight, 0.0);
  Weight = std::min(Weight, 1.0);
  return int((1 - Weight) * double(MainColor) +
              Weight * double(AddingColor));
}
// ---------------------------------------------------------------------------

BYTE CColorManipulator::shiftOneColorToAnother( BYTE MainColor,
                                                BYTE AddingColor,
                                                int Depth) {
  double Weight = std::pow(1.0 + kShiftingCoefficient, double(Depth)) - 1.0;
  return mixOneColor(MainColor, AddingColor, Weight);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
