//---------------------------------------------------------------------------

#ifndef UnitStaticPlotterH
#define UnitStaticPlotterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vcl.h>
#include <VCLTee.Series.hpp>
#include "UnitFunctionGridDefault.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CStaticSpeedPlotterBase
//---------------------------------------------------------------------------

class CStaticSpeedPlotterBase {
public:
  CStaticSpeedPlotterBase();
protected:
  TFastLineSeries* pSeries;
};
//---------------------------------------------------------------------------
// Declaration of CStaticSpeedDerivativePlotter
//---------------------------------------------------------------------------

class CStaticSpeedDerivativePlotter : public CStaticSpeedPlotterBase {
  using CBase = CStaticSpeedPlotterBase;
public:
  using CBase::CBase;
  void setPlotter(TFastLineSeries* pNewSeries);
};
//---------------------------------------------------------------------------
// Declaration of CStaticSpeedPlotter
//---------------------------------------------------------------------------

class CStaticSpeedPlotter : public CStaticSpeedPlotterBase {
  using CBase = CStaticSpeedPlotterBase;
public:
  using CBase::CBase;
  void setPlotter(TFastLineSeries* pNewSeries);
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
