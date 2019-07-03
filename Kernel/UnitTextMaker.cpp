// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitTextMaker.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Definitions of CTextMaker
// ---------------------------------------------------------------------------

CTextMaker::CTextMaker() {
  FormatPool.setToDefault();
}
// ---------------------------------------------------------------------------

void CTextMaker::makeFormattedRawText(
                                const CAnalysisData& source,
                                CFormattedString* target) const {
  makeFormattedRawText(*source.pSession, target);
}
// ---------------------------------------------------------------------------

void CTextMaker::makeFormattedRawText(
                                  const CSession& source,
                                  CFormattedString* target) const {
  // I assume that target is clear
  CTextRover Rover(source);
  CFormatStructure InitialFormat(ETextFormat::SessionDelimiter, 0);
  CBasicString Buffer;
  Buffer += kRootSymbol;
  makeFormatedTextWithRover(&InitialFormat, &Buffer, &Rover, target);
}
// ---------------------------------------------------------------------------

void CTextMaker::makeFormattedText( const CAnalysisData& source,
                                    const CTextMode& TextMode,
                                    CFormattedString* target) const {
  // I assume that target is clear
  CTextRover Rover(source, TextMode);
  CFormatStructure InitialFormat = Rover.getTextFormatStructure();
  CBasicString Buffer;
  Buffer += Rover.getSymbol();
  Rover.setNext();
  makeFormatedTextWithRover(&InitialFormat, &Buffer, &Rover, target);
}
// ---------------------------------------------------------------------------

CStringFormat CTextMaker::getStringFormat(
                    const CFormatStructure& FormatStructure) const {
  if (FormatStructure.TextFormat == ETextFormat::DeletedTextAccidental ||
      FormatStructure.TextFormat == ETextFormat::DeletedTextRequired ||
      FormatStructure.TextFormat == ETextFormat::MistakenSymbol) {
    CStringFormat StringFormat =
            FormatPool.getStringFormat(FormatStructure.TextFormat);
    StringFormat.makeBackDarker(FormatStructure.Depth);
    return StringFormat;
  }
  if (FormatStructure.TextFormat == ETextFormat::EssentialShiftFormat ||
      FormatStructure.TextFormat == ETextFormat::EssentialCapslockFormat) {
    CStringFormat StringFormat =
            FormatPool.getStringFormat(FormatStructure.TextFormat);
    StringFormat.makeBackDarker(FormatStructure.Depth - 1);
    return StringFormat;
  }
  return FormatPool.getStringFormat(FormatStructure.TextFormat);
}
// ---------------------------------------------------------------------------

void CTextMaker::makeFormatedTextWithRover( CFormatStructure* pInitialFormat,
                                            CBasicString* pBuffer,
                                            CTextRover* pRover,
                                            CFormattedString* target) const {
  auto& CurrentFormat = *pInitialFormat;
  while (!pRover->empty()) {
    if (CurrentFormat == pRover->getTextFormatStructure())
      *pBuffer += pRover->getSymbol();
    else {
      target->AddText(getStringFormat(CurrentFormat), *pBuffer);
      CurrentFormat = pRover->getTextFormatStructure();
      *pBuffer = pRover->getSymbol();
    }
    pRover->setNext();
  }
  target->AddText(getStringFormat(CurrentFormat), *pBuffer);
}
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#pragma package(smart_init)
