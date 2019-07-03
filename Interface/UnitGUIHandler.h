//---------------------------------------------------------------------------

#ifndef UnitGUIHandlerH
#define UnitGUIHandlerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTextWriter.h"
#include "UnitModeReader.h"
#include "UnitAnalysisTypeReader.h"
#include "UnitTreeViewWriter.h"
#include "UnitPlotter.h"
#include "UnitAreaPlotter.h"
#include "UnitStaticPlotter.h"
#include "UnitHistogramChunkHandler.h"
#include "UnitKlavogrammaPlotter.h"
#include "UnitListViewWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Declaration of CGUIHandler
//---------------------------------------------------------------------------

class CGUIHandler {
public:
  CTextWriter TextWriter;
  CTextWriter LogWriter;
  CTextWriter ThreadLogWriter;
  CTextWriter StateLogWriter;
  CTextWriter LogWriter2;

  CListViewWriter2 SeanceStatistics;
  CListViewWriter4 StableZonesStatistics;

  CTextModeReader TextModeReader;
  CAnalysisTypeReader AnalysisTypeReader;
  CTreeViewWriter TreeViewWriter;

  CSpeedHistogramPlotter SpeedHistogramPlotter;
  CSpeedHistogramChunkHandler SpeedChunkHandler;

  CParallelSpeedPlotter SpeedPlotter;
  CParallelSpeedDerivativePlotter SpeedDerivativePlotter;
  CParallelSpeedPlotterUniform SpeedPlotterUniform;
  CParallelSpeedDerivativePlotterUniform SpeedDerivativePlotterUniform;
  CAreaPlotter SpeedStableZonesPlotter;

  CStaticSpeedDerivativePlotter StandardSpeedDerivativePlotter;
  CStaticSpeedPlotter StandardSpeedPlotter;
  CKlavogrammaPlotter KlavogrammaPlotter;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
