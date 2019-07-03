//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitSessionToAnalysisDataConverter.h"
//---------------------------------------------------------------------------

#if !defined(__SESSION_TO_ANALYSIS_DATA_CONVERTER__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CSessionToAnalysisDataConverter
// ---------------------------------------------------------------------------

void CSessionToAnalysisDataConverter::convertData(
                                  const CSession& source,
                                  CAnalysisData* target) {
  if (source.empty())
    return;
  target->pSession = &source;
  convert(source, &target->TextTree);
  target->fillShiftsWithDependencies();
  target->fillCapslocksWithDependencies();
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#pragma package(smart_init)
