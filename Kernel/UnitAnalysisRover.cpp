//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAnalysisRover.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CAnalysisRover
// ---------------------------------------------------------------------------

CAnalysisRover::CAnalysisRover( const CAnalysisData& AnalysisData,
                                const CTextMode& textMode)
  : CTextRover(AnalysisData, textMode, ESymbolIteratorStart::FromTextBegin),
    PreviousKeyTime(0) {
/*  auto SymbolIterator = CSymbolIterator(&AnalysisData.TextTree,
                                        textMode.TextMode,
                                        ESymbolIteratorStart::FromTextBegin);
  if (SymbolIterator.isValid())
    push(std::move(SymbolIterator));
  auto ShiftIterator = CCapitalWithDependenciesIterator(
                                  &AnalysisData.ShiftsWithDependencies,
                                  AnalysisData.pSession,
                                  textMode.TextMode,
                                  textMode.ShiftMode,
                                  ECapitalType::Shift);
  if (ShiftIterator.isValid())
    push(std::move(ShiftIterator));
  auto CapslockIterator = CCapitalWithDependenciesIterator(
                                  &AnalysisData.CapslocksWithDependencies,
                                  AnalysisData.pSession,
                                  textMode.TextMode,
                                  textMode.CapslockMode,
                                  ECapitalType::Capslock);
  if (CapslockIterator.isValid())
    push(std::move(CapslockIterator));
*/
  if (!empty())
  // For the first symbol ResponseTime = PhysicalResponseTime
    PreviousKeyTime = top()->getPressingTime() -
                      top()->getPhysicalResponseTime();
}
// ---------------------------------------------------------------------------

CAnalysisRover::CAnalysisRover(const CSession& Session)
  : CTextRover(Session),
    PreviousKeyTime(0) {
  if (!empty())
  // For the first symbol ResponseTime = PhysicalResponseTime
    PreviousKeyTime = top()->getPressingTime() -
                      top()->getPhysicalResponseTime();
}
// ---------------------------------------------------------------------------

void CAnalysisRover::initialize(const CAnalysisData& AnalysisData,
                                const CTextMode& textMode) {
  CAnalysisRover tmpRover(AnalysisData, textMode);
  *this = std::move(tmpRover);
}
// ---------------------------------------------------------------------------

void CAnalysisRover::initialize(const CSession& Session) {
  CAnalysisRover tmpRover(Session);
  *this = std::move(tmpRover);
}
// ---------------------------------------------------------------------------

void CAnalysisRover::setNext() {
  PreviousKeyTime = top()->getPressingTime();
  CTextRover::setNext();
}
// ---------------------------------------------------------------------------

microseconds
  CAnalysisRover::getResponseTime(EAnalysisType AnalysisType) const {
  if (AnalysisType == EAnalysisType::Physical)
    return getPhysicalResponseTime();
  assert(AnalysisType == EAnalysisType::Symbolical);
  return getResponseTime();
}
// ---------------------------------------------------------------------------

microseconds CAnalysisRover::getPhysicalResponseTime() const {
  return top()->getPhysicalResponseTime();
}
// ---------------------------------------------------------------------------

microseconds CAnalysisRover::getResponseTime() const {
  return top()->getPressingTime() - PreviousKeyTime;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
