//---------------------------------------------------------------------------

#ifndef UnitAnalysisTypeReaderH
#define UnitAnalysisTypeReaderH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAnalysisMode.h"
#include <vcl.h>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CAnalysisTypeReader
//---------------------------------------------------------------------------

class CAnalysisTypeReader {
  using EAnalysisType = NSKernel::EAnalysisType;
public:
  CAnalysisTypeReader();
  void setAnalysisTypeGroup(TRadioGroup* pNewAnalysisTypeGroup);
  void setAnalysisMode(EAnalysisType* pAnalysisType) const;
private:
  TRadioGroup* pAnalysisTypeGroup;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
