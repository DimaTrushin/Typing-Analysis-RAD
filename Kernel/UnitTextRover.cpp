// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitTextRover.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CTextRover
// ---------------------------------------------------------------------------

CTextRover::CTextRover( const CAnalysisData& AnalysisData,
                        const CTextMode& textMode,
                        ESymbolIteratorStart SymbolStartFrom) {

  auto SymbolIterator = CSymbolIterator(&AnalysisData.TextTree,
                                        textMode.TextMode,
                                        SymbolStartFrom);
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
}
//---------------------------------------------------------------------------

CTextRover::CTextRover(const CSession& Session) {
  auto SessionIterator = CSessionIterator(Session);
  if (SessionIterator.isValid())
    push(std::move(SessionIterator));
}
//---------------------------------------------------------------------------

void CTextRover::initialize(const CAnalysisData& AnalysisData,
                            const CTextMode& textMode,
                            ESymbolIteratorStart SymbolStartFrom) {
  CTextRover tmpRover(AnalysisData, textMode, SymbolStartFrom);
  // TO DO
  // Check if it actually moves
  // Do I need an explicite move assignment operator?
  *this = std::move(tmpRover);
}
//---------------------------------------------------------------------------

void CTextRover::initialize(const CSession& Session) {
  CTextRover tmpRover(Session);
  // TO DO
  // Check if it actually moves
  // Do I need an explicite move assignment operator?
  *this = std::move(tmpRover);
}
//----------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
