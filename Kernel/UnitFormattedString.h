// ---------------------------------------------------------------------------

#ifndef UnitFormattedStringH
#define UnitFormattedStringH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <list>
#include "UnitStringFormat.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Declaration of CTextWithFormat
// ---------------------------------------------------------------------------

using CTextWithFormat = std::pair<CStringFormat, CBasicString>;
// ---------------------------------------------------------------------------
// Declaration of CFormattedString
// ---------------------------------------------------------------------------

class CFormattedString : public std::list<CTextWithFormat> {
  public:
  void AddText( const CStringFormat& TextFormat,
                const CBasicString& Text);
  void AddFormattedString(const CFormattedString& FormattedString);
  CBasicString getBasicString() const;
};
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif

