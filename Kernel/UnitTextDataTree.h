// ---------------------------------------------------------------------------

#ifndef UnitTextDataTreeH
#define UnitTextDataTreeH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitTextRelatedDefinitions.h"
#include "UnitTextMode.h"
//#include "../Library/UnitTree.h"
#include "../Library/UnitVTree.h"
#include "../UnitTimer.h"
#include "UnitKeyEvent.h"
// ---------------------------------------------------------------------------

#if !defined(__TEXT_DATA_TREE__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Enum
// ---------------------------------------------------------------------------

// RootSymbol -- symbol stored in the root of the tree
// DeletedSymbolAccidental -- deleted symbol that is NOT mistake
// DeletedSymbolRequired -- deleted symbol that is mistake
// TextSymbol -- printed symbol that is NOT the one where we made a mistake
// MistakeSymbol -- printed symbol that is the one where we made a mistake
enum class ESymbolStatus {
  TextSymbol, DeletedSymbolAccidental, DeletedSymbolRequired,
  MistakeSymbol, RootSymbol
};
// ---------------------------------------------------------------------------
// Forward Declaration of CTextData
// ---------------------------------------------------------------------------

class CTextData;
// ---------------------------------------------------------------------------
// Declaration of CTextDataTree
// ---------------------------------------------------------------------------

// The TextDataTree always has a root with the predefined data:
// Symbol = kRootSymbol
// VKCode = kRootVKCode
// ResponseTime = 0
// DurationTime = 0
class CTextDataTree : protected NSLibrary::CVTree<CTextData> {
public:
  using CBase = NSLibrary::CVTree<CTextData>;
  using CConstFullTextIterator = CBase::CConstPreOrderIterator;
  using CFullTextIterator = CBase::CPreOrderIterator;
  using CConstTextIterator = CBase::CConstLastSonIterator;
  using CTextIterator = CBase::CLastSonIterator;
  // These two iterators do not have travel logic
  // They denote begin and end of a text
  // with a chosen TextMode
  using CConstBasicIterator = CBase::CConstBasicIterator;
  using CBasicIterator = CBase::CBasicIterator;


  CTextDataTree();
  CTextDataTree(const CTextDataTree& other);
  CTextDataTree(CTextDataTree&& other) = default;
  CTextDataTree& operator=(const CTextDataTree& other);
  CTextDataTree& operator=(CTextDataTree&& other) = default;

  void clear();
  void addData(const CTextData& TextData);
  void addData(CTextData&& TextData);
  // On Backspace
  void deleteLastData();
  // On Ctrl + Backspace
  void deleteLastBlock();

  size_t getNumberOfPlacesWithDeletion() const;
  size_t getNumberOfDeletionSeries() const;
  size_t getNumberOfDeletedSymbols() const;
  // The number of times text deleting begins
  size_t getNumberOfReturnPoints() const;
  // including the root symbol
  size_t getTotalNumberOfSymbols() const;

  size_t getTextLength(ETextMode TextMode) const;
  size_t getDeletionSeriesLengthSupremum() const;
  size_t getNumberOfMistakePlaces() const;
  size_t getNumberOfMistakeRoutes() const;
  size_t getMistakeRoutesLengthSupremum() const;

  bool isTextEmpty(ETextMode TextMode) const;
  microseconds getFirstPressingTime(ETextMode TextMode) const;
  microseconds getLastPressingTime(ETextMode TextMode) const;
  microseconds getTextDurationTime(ETextMode TextMode) const;

  CConstBasicIterator beginText(ETextMode TextMode) const;
  CBasicIterator beginText(ETextMode TextMode);
  CConstBasicIterator endText(ETextMode TextMode) const;
  CBasicIterator endText(ETextMode TextMode);
  CConstBasicIterator beginFromRoot() const;
  CBasicIterator beginFromRoot();

  void setMistakeInformation();
  void reSetMistakeInformation();
  // ---------------------------------------------------------------------------
  // CTextDataTree public data
  // ---------------------------------------------------------------------------

  CTextIterator FinalElement;

private:
  microseconds getLastPrintedTextPressingTime() const;
  microseconds getLastFullTextPressingTime() const;

  CConstTextIterator beginPrintedText() const;
  CTextIterator beginPrintedText();
  CConstFullTextIterator beginFullText() const;
  CFullTextIterator beginFullText();
  CConstTextIterator endPrintedText() const;
  CTextIterator endPrintedText();
  CConstFullTextIterator endFullText() const;
  CFullTextIterator endFullText();

  void setFinalElement(const CTextDataTree& Tree);
  size_t getPrintedTextLength() const;
  size_t getFullTextLength() const;

  void deleteLastTextDelimiterBlock();
  void deleteLastSymbolBlock();

  void clearMistakeRoutes();
  void reSetMistakeRoutes();
  void setMistakeRoutes();

  void reAssignMistakeRoutes(const CTextIterator& currentPosition);
  void assignNewMistakeRoutes(const CTextIterator& currentPosition);
  void assignMistakeRoutesForFinalElement();
  void reAssignChildernTo(const CTextIterator& source,
                          CTextIterator* target);


  // These two functions assume that MistakeRoutes are already assigned,
  // that is, setMistakeRoutes() was already called
  void setRequiredDeleted();
  void setMistakeSymbols();

  // This function assumes that MistakeRoutes are already assigned,
  // that is, setMistakeRoutes() was already called
  void setRequiredDeletedFrom(const CSiblingIterator& currentNode);
};
// ---------------------------------------------------------------------------
// Using
// ---------------------------------------------------------------------------

using CMistakeRoutesContainer = std::list<CTextDataTree::CFullTextIterator>;
// ---------------------------------------------------------------------------
// Declaration of CTextData
// ---------------------------------------------------------------------------

class CTextData {
public:
  // Root node is created by default
  CTextData();
  CTextData(wchar_t dataSymbol,
            microseconds dataResponseTime,
            const CKeyEvent* pKeyEvent,
            ESymbolStatus symbolStatus = ESymbolStatus::TextSymbol);

  // Need a constructor from CKeyEvent
  //CTextData(const CKeyEvent& KeyEvent);
  bool isAffectedByShift() const;
  bool isAffectedByCapsLock() const;
  // All symbols are divided into "Symbols" and "TextDelimiters"
  // the first ones are symbols that can be printed
  // the second ones are Space and Enter
  bool isTextDelimiter() const;
  bool isSymbol() const;
  bool isAnyDeleted() const;
  bool isAnyPrinted() const;

  microseconds getPressingTime() const;
  microseconds getReleasingTime() const;
  microseconds getResponseTime() const;
  microseconds getDurationTime() const;

  wchar_t getSymbol() const;
  ESymbolStatus getSymbolStatus() const;
  void setSymbolStatus(ESymbolStatus newStatus);
  unsigned short getVKCode() const;

  // Data for smart mistake counting
  CMistakeRoutesContainer MistakeRoutes;

private:
  wchar_t Symbol;
  microseconds ResponseTime;
  const CKeyEvent* pKeyEvent_;
  ESymbolStatus SymbolStatus;
};
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
#endif
