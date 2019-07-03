//---------------------------------------------------------------------------

#ifndef UnitCapitalWithDependenciesIteratorH
#define UnitCapitalWithDependenciesIteratorH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitStringFormat.h"
#include "UnitAnalysisData.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CCapitalWithDependenciesIterator
// ---------------------------------------------------------------------------

class CCapitalWithDependenciesIterator {
public:
  CCapitalWithDependenciesIterator(
                const CCapitalWithDependenciesContainer* pCapitalContainer,
                const CSession* pSession,
                ETextMode textMode,
                ECapitalMode capitalMode,
                ECapitalType capitalType);
  ~CCapitalWithDependenciesIterator() = default;

  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  unsigned short getVKCode() const;
  bool isValid() const;
  microseconds getPressingTime() const;
  microseconds getReleasingTime() const;
  void setNext();
  microseconds getPhysicalResponseTime() const;

  bool isEssential() const;
  private:
  CCapitalWithDependenciesContainer::const_iterator getBegin() const;
  CCapitalWithDependenciesContainer::const_iterator
                                  getEssentialBegin() const;
  CCapitalWithDependenciesContainer::const_iterator getEnd() const;

  void moveUntilEssential(
          ETextMode TextMode,
          CCapitalWithDependenciesContainer::const_iterator* pIterator) const;
  int getDependencyNumber() const;
  // Iterator settings
  const CCapitalWithDependenciesContainer* pHostCapitalContainer;
  const CSession* pHostSession;
  ETextMode TextMode;
  ECapitalMode CapitalMode;
  ECapitalType CapitalType;

  CCapitalWithDependenciesContainer::const_iterator CurrentPosition;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
