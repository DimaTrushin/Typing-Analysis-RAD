//---------------------------------------------------------------------------

#ifndef UnitAnalysisModeH
#define UnitAnalysisModeH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "../Debug/UnitDisabler.h"
//---------------------------------------------------------------------------

#if !defined(__ANALYSIS_MODE__DISABLE__)
namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of EAnalysisType
//---------------------------------------------------------------------------

enum class EAnalysisType {
  Physical, Symbolical
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
