// ---------------------------------------------------------------------------

#ifndef UnitTextMakerH
#define UnitTextMakerH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitTextRover.h"
#include "UnitSessionToAnalysisDataConverter.h"
#include "UnitFormattedString.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Declaration of CTextMaker
// ---------------------------------------------------------------------------

class CTextMaker {
public:
  CTextMaker();
  void makeFormattedRawText(const CAnalysisData& source,
                            CFormattedString* target) const;
  void makeFormattedRawText(const CSession& source,
                            CFormattedString* target) const;

  void makeFormattedText( const CAnalysisData& source,
                          const CTextMode& TextMode,
                          CFormattedString* target) const;

private:
  inline CStringFormat getStringFormat(
                    const CFormatStructure& FormatStructure) const;
  inline void makeFormatedTextWithRover(
                                  CFormatStructure* pInitialFormat,
                                  CBasicString* pBuffer,
                                  CTextRover* pRover,
                                  CFormattedString* target) const;
  CFormatPool FormatPool;
};
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
