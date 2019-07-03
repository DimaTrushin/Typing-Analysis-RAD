// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitFormattedString.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Definition of CFormattedString
// ---------------------------------------------------------------------------

void CFormattedString::AddText( const CStringFormat& TextFormat,
                                const CBasicString& Text) {
  emplace_back(TextFormat, Text);
}
// ---------------------------------------------------------------------------

void CFormattedString::AddFormattedString(
                          const CFormattedString& FormattedString) {
  insert(end(), FormattedString.begin(), FormattedString.end());
}
// ---------------------------------------------------------------------------

CBasicString CFormattedString::getBasicString() const {
  CBasicString Text = L"";
  for (const auto& Pair : *this)
    Text += Pair.second;
  return Text;
}
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#pragma package(smart_init)

