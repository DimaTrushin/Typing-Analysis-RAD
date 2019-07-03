//---------------------------------------------------------------------------

#ifndef UnitAreaPlotterH
#define UnitAreaPlotterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vcl.h>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include "../Kernel/UnitFunctionGrid.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CAreaPlotter
//---------------------------------------------------------------------------

class CAreaPlotter {
  using CInterval = NSKernel::CInterval;
  using CMarkedIntervalContainer = NSKernel::CMarkedIntervalContainer;
public:
  CAreaPlotter();
  void setAreaPlotter(TChart* Chart, TFastLineSeries* Series);
  template<class TApproximation>
  void draw(const TApproximation& Approximation,
            const CMarkedIntervalContainer& MarkedIntervals);
  void changeVisibility();
private:
  void createNewSeries();
  template<class TApproximation>
  void writeAreaOnInterval( const TApproximation& Approximation,
                            const CInterval& Interval,
                            TChartSeries* Series);
  void Clear();
  TChart* pChart;
  TFastLineSeries* pMainPlot;
  size_t numberOfStaticSeries;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Definition of CAreaPlotter
//---------------------------------------------------------------------------

template<class TApproximation>
void CAreaPlotter::draw(const TApproximation& Approximation,
                        const CMarkedIntervalContainer& MarkedIntervals) {
  Clear();
  for (const auto& MInterval : MarkedIntervals) {
    createNewSeries();
    writeAreaOnInterval(Approximation, MInterval, pChart->SeriesList->Last());
  }
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CAreaPlotter::writeAreaOnInterval( const TApproximation& Approximation,
                                        const CInterval& Interval,
                                        TChartSeries* Series) {
  NSKernel::CFunctionGrid Grid;
  Grid.setApproximationGrid0(Approximation, Interval);
  Series->Clear();
  for (auto itGrid = Grid.begin(); itGrid != Grid.end(); ++itGrid)
    Series->AddXY(Grid.getPoint(itGrid),
                  Approximation.evaluate0(Grid.getPoint(itGrid)));
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
