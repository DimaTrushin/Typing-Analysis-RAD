//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAnalysisTypeReader.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Definition of CAnalysisTypeReader
//---------------------------------------------------------------------------

CAnalysisTypeReader::CAnalysisTypeReader()
  : pAnalysisTypeGroup(nullptr) {
}
//---------------------------------------------------------------------------

void CAnalysisTypeReader::
                  setAnalysisTypeGroup(TRadioGroup* pNewAnalysisTypeGroup) {
  pAnalysisTypeGroup = pNewAnalysisTypeGroup;
}
//---------------------------------------------------------------------------

void CAnalysisTypeReader::setAnalysisMode(EAnalysisType* pAnalysisType) const {
  assert(pAnalysisTypeGroup != nullptr);
  if (pAnalysisTypeGroup->ItemIndex == 0)
    *pAnalysisType = EAnalysisType::Physical;
  else
    *pAnalysisType = EAnalysisType::Symbolical;
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
