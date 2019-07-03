//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTreeViewWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Definition of CTreeViewWriter
//---------------------------------------------------------------------------

CTreeViewWriter::CTreeViewWriter( TTreeView* TreeView,
                                  unsigned int captionLength)
  : pTreeView(TreeView),
    CaptionLength(captionLength) {
}
//---------------------------------------------------------------------------

bool CTreeViewWriter::isDefined() const {
  return pTreeView != nullptr;
}
//---------------------------------------------------------------------------

void CTreeViewWriter::setTreeViewWriter(TTreeView* TreeView) {
  pTreeView = TreeView;
}
//---------------------------------------------------------------------------

void CTreeViewWriter::Clear() {
  if (!isDefined())
    return;
  pTreeView->Items->BeginUpdate();
  TTreeNode* Root = pTreeView->Items->GetFirstNode();
  Root->DeleteChildren();
  pTreeView->Items->EndUpdate();
}
//---------------------------------------------------------------------------
/*
void CTreeViewWriter::outputSeance(const CSeance& Seance) const {
  assert(pTreeView != nullptr);
  pTreeView->Items->BeginUpdate();
  TTreeNode* Root = pTreeView->Items->GetFirstNode();
  for (const auto& Session : Seance) {
    UnicodeString SessionCaption;
    getSessionText(Session, &SessionCaption);
    pTreeView->Items->AddChild(Root, SessionCaption.c_str());
  }
  pTreeView->Items->EndUpdate();
}*/
//---------------------------------------------------------------------------

void CTreeViewWriter::outputNewPartOfAugmentedSeance(
                                              const CSeance& Seance) const {
  assert(pTreeView != nullptr);
  pTreeView->Items->BeginUpdate();
  TTreeNode* Root = pTreeView->Items->GetFirstNode();
  size_t FirstNewPosition = Root->Count;

  for (auto index = FirstNewPosition; index < Seance.size(); ++index) {
    UnicodeString SessionCaption;
    getSessionText(Seance[index], &SessionCaption);
    // This place requires the address of each session remains the same
    // even if I add new elements to the current Seance
    pTreeView->Items->AddChildObject( Root,
                                      SessionCaption.c_str(),
                                      (void*)&(Seance[index]));

  }
  pTreeView->Items->EndUpdate();
}
//---------------------------------------------------------------------------

void CTreeViewWriter::expandSeance() {
  assert(pTreeView != nullptr);
  pTreeView->Items->GetFirstNode()->Expand(false);
}
//---------------------------------------------------------------------------

void CTreeViewWriter::setSelectedNode(TTreeNode* newSelectedNode) {
  pTreeView->Selected = newSelectedNode;
}
//---------------------------------------------------------------------------

void CTreeViewWriter::setSelectedNodeToLast() {
  TTreeNode* LastNode = pTreeView->Items->GetFirstNode()->GetLastChild();
  setSelectedNode(LastNode);
}
//---------------------------------------------------------------------------

void CTreeViewWriter::rebuildTreeView(const CSeance& Seance) {
  outputNewPartOfAugmentedSeance(Seance);
  expandSeance();
  setSelectedNodeToLast();
}
//---------------------------------------------------------------------------

bool CTreeViewWriter::isHitOnSessionItem(TTreeNode** pHitNode) const {
  TPoint MousePosition;
  ::GetCursorPos(&MousePosition);
  MousePosition = pTreeView->ScreenToClient(MousePosition);
  if (!pTreeView->GetHitTestInfoAt( MousePosition.x,
                                    MousePosition.y).
                                    Contains(htOnItem)) {
    *pHitNode = nullptr;
    return false;
  }
  // Here We have hit on Item
  *pHitNode = pTreeView->GetNodeAt(MousePosition.x, MousePosition.y);
  if (isHitOnRoot(*pHitNode))
    return false;
  return true;
}
//---------------------------------------------------------------------------

const NSKernel::CSession*
      CTreeViewWriter::getSelectedSession(TTreeNode* SelectedNode) const {
  return static_cast<const CSession*>(SelectedNode->Data);
}
//---------------------------------------------------------------------------

void CTreeViewWriter::getSessionText( const CSession& Session,
                                      UnicodeString* pText) const {
  NSKernel::CTextRover Rover(Session);
  *pText += NSKernel::kRootSymbol;
  for (size_t index = 0; index < CaptionLength; ++index) {
    if (Rover.empty())
      break;
    *pText += Rover.getSymbol();
    Rover.setNext();
  }
}
//---------------------------------------------------------------------------

bool CTreeViewWriter::isHitOnRoot(TTreeNode* const HitNode) const {
  return HitNode == pTreeView->Items->GetFirstNode();
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
