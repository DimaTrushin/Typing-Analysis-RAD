// ---------------------------------------------------------------------------

#ifndef UnitTextRoverH
#define UnitTextRoverH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitRover.h"
#include "UnitSymbolIterator.h"
#include "UnitCapitalWithDependenciesIterator.h"
#include "UnitSessionIterator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CTextRover
// ---------------------------------------------------------------------------

class CTextRover : public CRoverBase {
public:
  CTextRover() = default;
  CTextRover( const CAnalysisData& AnalysisData,
              const CTextMode& textMode,
              ESymbolIteratorStart SymbolStartFrom =
                                          ESymbolIteratorStart::FromRoot);
  CTextRover(const CSession& Session);
  CTextRover(CTextRover&&) = default;
  CTextRover& operator=(CTextRover&&) = default;

  void initialize(const CAnalysisData& AnalysisData,
                  const CTextMode& textMode,
                  ESymbolIteratorStart SymbolStartFrom =
                                          ESymbolIteratorStart::FromRoot);
  void initialize(const CSession& Session);
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
