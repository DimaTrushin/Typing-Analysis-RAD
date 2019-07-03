//---------------------------------------------------------------------------

#ifndef UnitModeReaderH
#define UnitModeReaderH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vcl.h>
#include "../Kernel/UnitTextMode.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CTextModeReader
//---------------------------------------------------------------------------

class CTextModeReader {
  using EOutputMode = NSKernel::EOutputMode;
  using CTextMode = NSKernel::CTextMode;
  using ETextMode = NSKernel::ETextMode;
  using ECapitalMode = NSKernel::ECapitalMode;
public:
  CTextModeReader();
  void setModeGroups( TRadioGroup* pNewTextModeGroup,
                      TRadioGroup* pNewShiftModeGroup,
                      TRadioGroup* pNewCapslockModeGroup);
  void setTextMode(EOutputMode* pOutputMode, CTextMode* pTextMode) const;
private:
  inline void setOutputMode(EOutputMode* pOutputMode) const;
  inline void setTextMode(CTextMode* pTextMode) const;
  inline void setTextMode(ETextMode* pTextMode) const;
  inline void setShiftMode(ECapitalMode* pShiftMode) const;
  inline void setCapslockMode(ECapitalMode* pCapslockMode) const;
  inline void setCapitalMode( const TRadioGroup* pCapitalModeGroup,
                              ECapitalMode* pCapitalMode) const;
  TRadioGroup* pTextModeGroup;
  TRadioGroup* pShiftModeGroup;
  TRadioGroup* pCapslockModeGroup;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
