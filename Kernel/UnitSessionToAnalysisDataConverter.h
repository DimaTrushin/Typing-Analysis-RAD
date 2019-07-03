//---------------------------------------------------------------------------

#ifndef UnitSessionToAnalysisDataConverterH
#define UnitSessionToAnalysisDataConverterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitSessionToTreeConverter.h"
#include "UnitAnalysisData.h"
//#include "../Debug/UnitDisabler.h"
//---------------------------------------------------------------------------

#if !defined(__SESSION_TO_ANALYSIS_DATA_CONVERTER__DISABLE__)
namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Declaration of CSessionToAnalysisDataConverter
// ---------------------------------------------------------------------------

class CSessionToAnalysisDataConverter : protected CSessionToTreeConverter {
public:
  void convertData( const CSession& source,
                    CAnalysisData* target);
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
