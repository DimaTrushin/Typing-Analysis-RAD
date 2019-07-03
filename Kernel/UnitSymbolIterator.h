//---------------------------------------------------------------------------

#ifndef UnitSymbolIteratorH
#define UnitSymbolIteratorH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitStringFormat.h"
#include "UnitTextDataTree.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Enum
// ---------------------------------------------------------------------------

enum class ESymbolIteratorStart {FromRoot, FromTextBegin};
// ---------------------------------------------------------------------------
// Declaration of CSymbolIterator
// ---------------------------------------------------------------------------

class CSymbolIterator {
public:
  CSymbolIterator( const CTextDataTree* pTree,
                            ETextMode mode,
                            ESymbolIteratorStart BeginFrom);
  ~CSymbolIterator() = default;

  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  unsigned short getVKCode() const;
  bool isValid() const;
  microseconds getPressingTime() const;
  microseconds getReleasingTime() const;
  void setNext();
  microseconds getPhysicalResponseTime() const;

  ESymbolStatus getSymbolStatus() const;

private:
  inline void setNextFull();
  inline void setNextNonFull();

  inline int getDepth() const;
  inline int getAccidentalDeletedDepth() const;
  inline int getAccidentalDeletedDepth(
        const CTextDataTree::CConstBasicIterator& Position) const;
  inline int getRequiredDeletedDepth() const;
  inline int getRequiredDeletedDepth(
        const CTextDataTree::CConstBasicIterator& Position) const;
  inline int getMistakeDepth() const;
  inline CTextDataTree::CConstBasicIterator getParentPosition(
        const CTextDataTree::CConstBasicIterator& Position) const;

  // Iterator settings
  const CTextDataTree* pHostTree;
  ETextMode IteratorMode;

  CTextDataTree::CConstBasicIterator CurrentPosition;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
