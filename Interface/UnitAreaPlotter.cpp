//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAreaPlotter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Definition of CAreaPlotter
//---------------------------------------------------------------------------

CAreaPlotter::CAreaPlotter()
  : pChart(nullptr),
    pMainPlot(nullptr),
    numberOfStaticSeries(0) {
}
//---------------------------------------------------------------------------

void CAreaPlotter::setAreaPlotter(TChart* Chart, TFastLineSeries* Series) {
  assert(Chart != nullptr);
  assert(Series != nullptr);
  pChart = Chart;
  pMainPlot = Series;
  numberOfStaticSeries = Chart->SeriesList->Count;
}
//---------------------------------------------------------------------------

void CAreaPlotter::changeVisibility() {
  size_t size = pChart->SeriesList->Count;
  for(int index = numberOfStaticSeries; index < size; ++index)
    pChart->Series[index]->Visible = pMainPlot->Visible;
}
//---------------------------------------------------------------------------

void CAreaPlotter::createNewSeries() {
  TAreaSeries* NewSeries;
  NewSeries = new TAreaSeries(pChart);
  NewSeries->ParentChart = pChart;
  NewSeries->Color = System::Uitypes::TColor(RGB(255, 128, 128));
  NewSeries->UseYOrigin = true;
  NewSeries->Transparency = 85;
  NewSeries->AreaLinesPen->Visible = false;
  NewSeries->Selected->Hover->Visible = false;
  NewSeries->Legend->Visible = false;
}
//---------------------------------------------------------------------------

void CAreaPlotter::Clear() {
  while (pChart->SeriesList->Count > numberOfStaticSeries)
    pChart->SeriesList->Last()->Free();
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
