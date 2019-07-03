// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitTextDataTree.h"
// ---------------------------------------------------------------------------
/*
#include "vcl.h"
namespace NSApplication {
namespace NSKernel {

class CTextDataTester {
public:
  using CConstTextIterator = CTextDataTree::CConstTextIterator;
  using CConstFullTextIterator = CTextDataTree::CConstFullTextIterator;
  CTextDataTester()
    : Text(L"CTextData Debug Log:\n") {

    CTextDataTree TextTree;
    createTree(&TextTree);
    TextTree.clear();
    createTree(&TextTree);
    printFullTree(TextTree);
    printPrintedTree(TextTree);
    printMistakeRoutesInfo(TextTree);
    printTreeInfo(TextTree);
    ShowMessage(Text.c_str());
  }
private:
  void createTree(CTextDataTree* pTextTree) {
    CTextDataTree& TextTree = *pTextTree;
    TextTree.addData(CTextData(L'2', 0, 0, 0, 0));
    TextTree.deleteLastData();
    TextTree.addData(CTextData(L'1', 0, 0, 0, 0));
    TextTree.addData(CTextData(L'2', 0, 0, 0, 0));
    TextTree.addData(CTextData(L'4', 0, 0, 0, 0));
    TextTree.deleteLastData();
    TextTree.addData(CTextData(L'3', 0, 0, 0, 0));
    TextTree.addData(CTextData(L'5', 0, 0, 0, 0));
    TextTree.deleteLastData();
    TextTree.addData(CTextData(L'4', 0, 0, 0, 0));
    TextTree.deleteLastData();
    TextTree.deleteLastData();
    TextTree.addData(CTextData(L'3', 0, 0, 0, 0));
    TextTree.addData(CTextData(L'4', 0, 0, 0, 0));
    TextTree.addData(CTextData(L'5', 0, 0, 0, 0));
    TextTree.deleteLastData();
    TextTree.setMistakeInformation();
  }
  void printFullTree(const CTextDataTree& TextTree) {
    Text += L"Full Tree:\n";
    for ( CConstFullTextIterator itSymbol = TextTree.beginFromRoot();
          itSymbol != TextTree.endFullText();
          ++itSymbol) {
      Text += itSymbol->getSymbol();
    }
    Text += L'\n';
  }
  void printPrintedTree(const CTextDataTree& TextTree) {
    Text += L"Printed Tree:\n";
    for ( auto itSymbol = TextTree.beginPrintedText();
          itSymbol != TextTree.endPrintedText();
          ++itSymbol) {
      Text += itSymbol->getSymbol();
    }
    Text += L'\n';
  }
  void printMistakeRoutesInfo(const CTextDataTree& TextTree) {
    Text += L"Mistake Routes Info:\n";
    for ( CConstTextIterator itSymbol = TextTree.beginFromRoot();
          itSymbol != TextTree.endPrintedText();
          ++itSymbol) {
      Text += itSymbol->MistakeRoutes.size();
    }
    Text += L'\n';
  }
  void printTreeInfo(const CTextDataTree& TextTree) {
    Text += L"Tree Info:";
    Text += L"\ngetNumberOfPlacesWithDeletion() = ";
    Text += TextTree.getNumberOfPlacesWithDeletion();
    Text += L"\ngetNumberOfDeletionSeries() = ";
    Text += TextTree.getNumberOfDeletionSeries();
    Text += L"\ngetNumberOfDeletedSymbols() = ";
    Text += TextTree.getNumberOfDeletedSymbols();
    Text += L"\ngetNumberOfReturnPoints() = ";
    Text += TextTree.getNumberOfReturnPoints();
    Text += L"\ngetTotalNumberOfSymbols() = ";
    Text += TextTree.getTotalNumberOfSymbols();
    Text += L"\ngetFullTextLength() = ";
    Text += TextTree.getFullTextLength();
    // ”пс, тут ошибка при вычитании итераторов!!
    Text += L"\ngetPrintedTextLength() = ";
    Text += TextTree.getPrintedTextLength();
    //getTextLength(ETextMode TextMode) const;
    Text += L"\ngetDeletionSeriesLengthSupremum() = ";
    Text += TextTree.getDeletionSeriesLengthSupremum();
    Text += L"\ngetNumberOfMistakePlaces() = ";
    Text += TextTree.getNumberOfMistakePlaces();
    Text += L"\ngetNumberOfMistakeRoutes() = ";
    Text += TextTree.getNumberOfMistakeRoutes();
    Text += L"\ngetMistakeRoutesLengthSupremum() = ";
    Text += TextTree.getMistakeRoutesLengthSupremum();
    Text += L'\n';
  }
  UnicodeString Text;
};
CTextDataTester TextDataTester;
}
}*/
// ---------------------------------------------------------------------------

#if !defined(__TEXT_DATA_TREE__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------------------

CTextDataTree TextTree;
// ---------------------------------------------------------------------------
// Definitions of CTextDataTree
// ---------------------------------------------------------------------------

CTextDataTree::CTextDataTree()
  : CVTree<CTextData>(CTextData()),
    FinalElement(beginFromRoot()) {
}
// ---------------------------------------------------------------------------

CTextDataTree::CTextDataTree(const CTextDataTree& Tree)
  : CVTree<CTextData>(Tree) {
  setFinalElement(Tree);
  reSetMistakeRoutes();
}
// ---------------------------------------------------------------------------

CTextDataTree& CTextDataTree:: operator=(const CTextDataTree & Tree) {
  return *this = CTextDataTree(Tree);
}
// ---------------------------------------------------------------------------

void CTextDataTree::clear() {
  destroyExceptRoot();
  getRootNode().Data_.MistakeRoutes.clear();
  FinalElement = beginFromRoot();
}
// ---------------------------------------------------------------------------

void CTextDataTree::addData(const CTextData& TextData) {
  FinalElement.addLastChild(TextData);
  ++FinalElement;
}
// ---------------------------------------------------------------------------

void CTextDataTree::addData(CTextData&& TextData) {
  FinalElement.addLastChild(TextData);
  ++FinalElement;
}
// ---------------------------------------------------------------------------

void CTextDataTree::deleteLastData() {
  if (FinalElement.isRoot())
    return;
  FinalElement->setSymbolStatus(ESymbolStatus::DeletedSymbolAccidental);
  --FinalElement;
}
// ---------------------------------------------------------------------------

void CTextDataTree::deleteLastBlock() {
  deleteLastTextDelimiterBlock();
  deleteLastSymbolBlock();
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfPlacesWithDeletion() const {
  if (size() == 1)
    return 0;
  CConstTextIterator index;
  index = beginFromRoot();
  size_t places = 0;
  while (index != FinalElement) {
    if (index.getNumberOfChildren() > 1)
      places += 1;
    ++index;
  }
  if (index.getNumberOfChildren() > 0)
    places += 1;
  return places;
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfDeletionSeries() const {
  if (size() == 1)
    return 0;
  CConstTextIterator index;
  index = beginFromRoot();
  size_t places = 0;
  while (index != FinalElement) {
    places += index.getNumberOfChildren() - 1;
    ++index;
  }
  places += index.getNumberOfChildren();
  return places;
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfDeletedSymbols() const {
  size_t numberOfDeletedSymbols = 0;
  for ( CConstTextIterator itCurrentSymbol = beginFromRoot();
        itCurrentSymbol != FinalElement;
        ++itCurrentSymbol)
    for ( auto child = itCurrentSymbol.FirstChild();
          child != itCurrentSymbol.LastChild();
          ++child)
            numberOfDeletedSymbols += child.getSizeOfSubTree();
  numberOfDeletedSymbols += FinalElement.getSizeOfSubTree() - 1;
  return numberOfDeletedSymbols;
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getNumberOfReturnPoints() const {
  if (FinalElement.isThereChild())
    return beginFromRoot().getNumberOfLeaves();
  return beginFromRoot().getNumberOfLeaves() - 1;
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getTotalNumberOfSymbols() const {
  return size();
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getTextLength(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return getFullTextLength();
  assert(TextMode == ETextMode::Printed);
  return getPrintedTextLength();
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getDeletionSeriesLengthSupremum() const {
  size_t lengthsup = 0;
  for ( CConstTextIterator itCurrentSymbol = beginFromRoot();
        itCurrentSymbol != FinalElement;
        ++itCurrentSymbol)
    for ( auto child = itCurrentSymbol.FirstChild();
          child != itCurrentSymbol.LastChild();
          ++child)
      lengthsup = std::max(lengthsup, child.getLengthOfSubTree());
  lengthsup = std::max( lengthsup,
                        FinalElement.getLengthOfSubTree() - 1);
  return lengthsup;
}
// ---------------------------------------------------------------------------

// symbols deleted at the end are assumed to be mistakes
size_t CTextDataTree::getNumberOfMistakePlaces() const {
  size_t mistakePlaces = 0;
  for ( CConstTextIterator index = beginFromRoot();
        index != endPrintedText();
        ++index)
    if (!index->MistakeRoutes.empty())
      ++mistakePlaces;
  return mistakePlaces;
}
// ---------------------------------------------------------------------------

// symbols deleted at the end are assumed to be mistakes
size_t CTextDataTree::getNumberOfMistakeRoutes() const {
  size_t mistakes = 0;
  for ( CConstTextIterator index = beginFromRoot();
        index != endPrintedText();
        ++index)
    mistakes += index->MistakeRoutes.size();
  return mistakes;
}
// ---------------------------------------------------------------------------

// symbols deleted at the end are assumed to be mistakes
size_t CTextDataTree::getMistakeRoutesLengthSupremum() const {
  size_t lengthSupremum = 0;
  for ( CConstTextIterator index = beginFromRoot();
        index != endPrintedText();
        ++index)
    for ( auto itMistakeRoute = index->MistakeRoutes.cbegin();
          itMistakeRoute != index->MistakeRoutes.end();
          ++itMistakeRoute)
      lengthSupremum = std::max(lengthSupremum,
                                itMistakeRoute->getLengthOfSubTree());
  return lengthSupremum;
}
// ---------------------------------------------------------------------------

bool CTextDataTree::isTextEmpty(ETextMode TextMode) const {
  if (getTextLength(TextMode) == 0)
    return true;
  return false;
}
// ---------------------------------------------------------------------------

microseconds CTextDataTree::getFirstPressingTime(ETextMode TextMode) const {
  if (isTextEmpty(TextMode))
    return 0;//-1;
  return beginText(TextMode)->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CTextDataTree::getLastPressingTime(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return getLastFullTextPressingTime();
  assert(TextMode == ETextMode::Printed);
  return getLastPrintedTextPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CTextDataTree::getTextDurationTime(ETextMode TextMode) const {
  if (isTextEmpty(TextMode))
    return 0;
  return getLastPressingTime(TextMode) - getFirstPressingTime(TextMode);
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator
                    CTextDataTree::beginText(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return beginFullText();
  assert(TextMode == ETextMode::Printed);
  return beginPrintedText();
}
// ---------------------------------------------------------------------------

CTextDataTree::CBasicIterator
                    CTextDataTree::beginText(ETextMode TextMode) {
  if (TextMode == ETextMode::Full)
    return beginFullText();
  assert(TextMode == ETextMode::Printed);
  return beginPrintedText();
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator
                    CTextDataTree::endText(ETextMode TextMode) const {
  if (TextMode == ETextMode::Full)
    return endFullText();
  assert(TextMode == ETextMode::Printed);
  return endPrintedText();
}
// ---------------------------------------------------------------------------

CTextDataTree::CBasicIterator
                    CTextDataTree::endText(ETextMode TextMode) {
  if (TextMode == ETextMode::Full)
    return endFullText();
  assert(TextMode == ETextMode::Printed);
  return endPrintedText();
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstBasicIterator CTextDataTree::beginFromRoot() const {
  return begin();
}
// ---------------------------------------------------------------------------

CTextDataTree::CBasicIterator CTextDataTree::beginFromRoot() {
  return begin();
}
// ---------------------------------------------------------------------------

void CTextDataTree::setMistakeInformation(){
  setMistakeRoutes();
  setMistakeSymbols();
  setRequiredDeleted();
}
// ---------------------------------------------------------------------------

void CTextDataTree::reSetMistakeInformation(){
  clearMistakeRoutes();
  setMistakeInformation();
}
// ---------------------------------------------------------------------------

microseconds CTextDataTree::getLastPrintedTextPressingTime() const {
  if (isTextEmpty(ETextMode::Printed))
    return 0;//-1;
  return FinalElement->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CTextDataTree::getLastFullTextPressingTime() const {
  if (isTextEmpty(ETextMode::Full))
    return 0;//-1;
  return (--endPreOrder())->getPressingTime();
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstTextIterator CTextDataTree::beginPrintedText() const {
  CConstTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
// ---------------------------------------------------------------------------

CTextDataTree::CTextIterator CTextDataTree::beginPrintedText() {
  CTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstFullTextIterator CTextDataTree::beginFullText() const {
  CConstFullTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
// ---------------------------------------------------------------------------

CTextDataTree::CFullTextIterator CTextDataTree::beginFullText() {
  CFullTextIterator TextBeginning = beginFromRoot();
  return ++TextBeginning;
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstTextIterator CTextDataTree::endPrintedText() const {
  CConstTextIterator TextEnding = FinalElement;
  return ++TextEnding;
}
// ---------------------------------------------------------------------------

CTextDataTree::CTextIterator CTextDataTree::endPrintedText() {
  CTextIterator TextEnding = FinalElement;
  return ++TextEnding;
}
// ---------------------------------------------------------------------------

CTextDataTree::CConstFullTextIterator CTextDataTree::endFullText() const {
  return endPreOrder();
}
// ---------------------------------------------------------------------------

CTextDataTree::CFullTextIterator CTextDataTree::endFullText() {
  return endPreOrder();
}
// ---------------------------------------------------------------------------

void CTextDataTree::setFinalElement(const CTextDataTree& Tree) {
  size_t difference = Tree.FinalElement -
                      CConstTextIterator(Tree.beginFromRoot());
  FinalElement = beginFromRoot();
  FinalElement += difference;
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getPrintedTextLength() const {
  return endPrintedText() - beginPrintedText();
}
// ---------------------------------------------------------------------------

size_t CTextDataTree::getFullTextLength() const {
  return size() - 1;
}
// ---------------------------------------------------------------------------

void CTextDataTree::deleteLastTextDelimiterBlock(){
  while (FinalElement->isTextDelimiter())
    deleteLastData();
}
// ---------------------------------------------------------------------------

void CTextDataTree::deleteLastSymbolBlock(){
  while (FinalElement->isSymbol())
    deleteLastData();
}
// ---------------------------------------------------------------------------

void CTextDataTree::clearMistakeRoutes() {
  for ( CTextIterator Node = beginFromRoot();
        Node != endPrintedText();
        ++Node)
    Node->MistakeRoutes.clear();
}
// ---------------------------------------------------------------------------

void CTextDataTree::reSetMistakeRoutes() {
  clearMistakeRoutes();
  setMistakeRoutes();
}
// ---------------------------------------------------------------------------

void CTextDataTree::setMistakeRoutes() {
  for ( CTextIterator currentPosition = beginFromRoot();
        currentPosition != FinalElement;
        ++currentPosition) {
    reAssignMistakeRoutes(currentPosition);
    assignNewMistakeRoutes(currentPosition);
  }
  assignMistakeRoutesForFinalElement();
}
// ---------------------------------------------------------------------------

void CTextDataTree::reAssignMistakeRoutes(
                              const CTextIterator& currentPosition){
  auto itMistakeRoute = currentPosition->MistakeRoutes.begin();
  CTextIterator next = currentPosition;
  ++next;
  while (itMistakeRoute != currentPosition->MistakeRoutes.end()) {
    if (next->getSymbol() == (*itMistakeRoute)->getSymbol()) {
      // we did not make a mistake in the next symbol
      // need to pass mistake routes to the node with the next symbol
      if (itMistakeRoute->isThereChild()) {
        // if there are mistake routes
        reAssignChildernTo(*itMistakeRoute, &next);
      }
      // remove itMistakeRoute from the current node of the tree
      itMistakeRoute =
          currentPosition->MistakeRoutes.erase(itMistakeRoute);
      continue;
    }
    ++itMistakeRoute;
  }
}
// ---------------------------------------------------------------------------

void CTextDataTree::assignNewMistakeRoutes(
                            const CTextIterator& currentPosition){
  CTextIterator currentNode(currentPosition);
  auto itMistakeRoute = currentNode.FirstChild();

  CTextIterator nextNode = currentPosition;
  ++nextNode;
  while (itMistakeRoute != currentNode.LastChild()) {
    if (nextNode->getSymbol() == itMistakeRoute->getSymbol()) {
      // If the symbol is the same, we did NOT make a mistake in the next symbol
      // if there are children, send them to the nextNode's MistakeRoutes
      if (itMistakeRoute.isThereChild()) {
        reAssignChildernTo(itMistakeRoute, &nextNode);
      }
    }
    else {
      // if the symbol is NOT the same, we made a mistake in the next symbol
      // need to write the current route to the MistakeRoutes of the currentNode
      currentPosition->
          MistakeRoutes.
                push_back(itMistakeRoute);
    }
    ++itMistakeRoute;
  }
}

// ---------------------------------------------------------------------------

void CTextDataTree::assignMistakeRoutesForFinalElement() {
  if (!FinalElement.isThereChild())
    return;
  for ( auto itMistakeRoute = FinalElement.FirstChild();
        itMistakeRoute != FinalElement.LastChild();
        ++itMistakeRoute)
    FinalElement->MistakeRoutes.push_back(itMistakeRoute);
  FinalElement->MistakeRoutes.push_back(FinalElement.LastChild());
}
// ---------------------------------------------------------------------------

void CTextDataTree::reAssignChildernTo( const CTextIterator& source,
                                        CTextIterator* target) {
  for ( auto itChild = source.FirstChild();
        itChild != source.LastChild();
        ++itChild)
    (*target)->MistakeRoutes.push_back(itChild);
  (*target)->MistakeRoutes.push_back(source.LastChild());
}
// ---------------------------------------------------------------------------

void CTextDataTree::setRequiredDeleted(){
  for ( CTextIterator currentPosition = beginFromRoot();
        currentPosition != endPrintedText();
        ++currentPosition)
    for ( auto itMistakeRoute = currentPosition->MistakeRoutes.begin();
          itMistakeRoute != currentPosition->MistakeRoutes.end();
          ++itMistakeRoute)
        setRequiredDeletedFrom(*itMistakeRoute);
}
// ---------------------------------------------------------------------------

void CTextDataTree::setMistakeSymbols(){
  for ( CTextIterator itCurrentSymbol = beginFromRoot();
        itCurrentSymbol != FinalElement;
        ++itCurrentSymbol)
    if (!itCurrentSymbol->MistakeRoutes.empty())
      itCurrentSymbol.LastChild()->setSymbolStatus(ESymbolStatus::MistakeSymbol);
}
// ---------------------------------------------------------------------------

void CTextDataTree::setRequiredDeletedFrom(
                                    const CSiblingIterator& currentNode) {
  currentNode->setSymbolStatus(ESymbolStatus::DeletedSymbolRequired);

  if (!currentNode.isThereChild())
    return;
  for ( auto itChild = currentNode.FirstChild();
        itChild != currentNode.LastChild();
        ++itChild)
    setRequiredDeletedFrom(itChild);
  setRequiredDeletedFrom(currentNode.LastChild());
}
// ---------------------------------------------------------------------------
// Definitions of CTextData
// ---------------------------------------------------------------------------

CTextData::CTextData()
  : Symbol(kRootSymbol),
    ResponseTime(0),
    pKeyEvent_(nullptr),
    SymbolStatus(ESymbolStatus::RootSymbol) {
}
// ---------------------------------------------------------------------------

CTextData::CTextData( wchar_t dataSymbol,
                      microseconds dataResponseTime,
                      const CKeyEvent* pKeyEvent,
                      ESymbolStatus symbolStatus)
  : Symbol(dataSymbol),
    ResponseTime(dataResponseTime),
    pKeyEvent_(pKeyEvent),
    SymbolStatus(symbolStatus) {
}
// ---------------------------------------------------------------------------

bool CTextData::isAffectedByShift() const {
  return isSymbol();
}
// ---------------------------------------------------------------------------

bool CTextData::isAffectedByCapsLock() const {
  return isAffectedByShift();
}
// ---------------------------------------------------------------------------

bool CTextData::isTextDelimiter() const {
  return  (pKeyEvent_ != nullptr) &&
          (pKeyEvent_->isSpacebar() || pKeyEvent_->isEnter());
}
// ---------------------------------------------------------------------------

bool CTextData::isSymbol() const {
  return (pKeyEvent_ != nullptr) && pKeyEvent_->isSymbolKey();
}
// ---------------------------------------------------------------------------

bool CTextData::isAnyDeleted() const {
  return  SymbolStatus == ESymbolStatus::DeletedSymbolAccidental ||
          SymbolStatus == ESymbolStatus::DeletedSymbolRequired;
}
// ---------------------------------------------------------------------------

bool CTextData::isAnyPrinted() const {
  return  SymbolStatus == ESymbolStatus::TextSymbol ||
          SymbolStatus == ESymbolStatus::MistakeSymbol;
}
// ---------------------------------------------------------------------------

microseconds CTextData::getPressingTime() const {
  if (pKeyEvent_ == nullptr)
    return 0;
  return pKeyEvent_->getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CTextData::getReleasingTime() const {
  if (pKeyEvent_ == nullptr)
    return 0;
  return pKeyEvent_->getReleasingTime();
}
// ---------------------------------------------------------------------------

microseconds CTextData::getResponseTime() const {
  return ResponseTime;
}
// ---------------------------------------------------------------------------

microseconds CTextData::getDurationTime() const {
  if (pKeyEvent_ == nullptr)
    return 0;
  return pKeyEvent_->getDurationTime();
}
// ---------------------------------------------------------------------------

wchar_t CTextData::getSymbol() const {
  return Symbol;
}
// ---------------------------------------------------------------------------

ESymbolStatus CTextData::getSymbolStatus() const {
  return SymbolStatus;
}
// ---------------------------------------------------------------------------

void CTextData::setSymbolStatus(ESymbolStatus newStatus) {
  SymbolStatus = newStatus;
}
// ---------------------------------------------------------------------------

unsigned short CTextData::getVKCode() const {
  if (pKeyEvent_ == nullptr)
    return 0;
  return pKeyEvent_->getVKCode();
}
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
#pragma package(smart_init)
