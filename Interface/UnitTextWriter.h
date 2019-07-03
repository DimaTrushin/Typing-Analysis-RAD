//---------------------------------------------------------------------------

#ifndef UnitTextWriterH
#define UnitTextWriterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vcl.h>
#include "../Kernel/UnitFormattedString.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CTextWriter
//---------------------------------------------------------------------------

class CTextWriter {
  using CFormattedString = NSKernel::CFormattedString;
  using CTextWithFormat = NSKernel::CTextWithFormat;
  using CStringFormat = NSKernel::CStringFormat;
public:
  CTextWriter(TRichEdit* pRichEdit = nullptr);

  bool isRichEditDefined() const;
  void setRichEdit(TRichEdit* pRichEdit);
  void Clear();
  // TO DO
  // Make UnicodeString to be CBasicString aka std::wstring
  void printPlaneText(const UnicodeString& Text);
  void printFormattedString(const CFormattedString& Text);
  void newLine();

private:
  inline void PrintPair(const CTextWithFormat& TextPair) const;
  inline void SetSelectedFormat(const CStringFormat& TextFormat) const;
  inline void moveSelectedToEnd();

  TRichEdit* pRichEditToPrint;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
