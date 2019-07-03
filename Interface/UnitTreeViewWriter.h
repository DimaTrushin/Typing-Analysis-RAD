//---------------------------------------------------------------------------

#ifndef UnitTreeViewWriterH
#define UnitTreeViewWriterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vcl.h>
#include "../Kernel/UnitTextRover.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CTreeViewWriter
//---------------------------------------------------------------------------

class CTreeViewWriter {
  using CSession = NSKernel::CSession;
  using CSeance = NSKernel::CSeance;
public:
  CTreeViewWriter(TTreeView* TreeView = nullptr,
                  unsigned int captionLength = kMaximalCaptionLength);

  bool isDefined() const;
  void setTreeViewWriter(TTreeView* TreeView);
  void Clear();
  //void outputSeance(const CSeance& Seance) const;
  void outputNewPartOfAugmentedSeance(const CSeance& Seance) const;
  void expandSeance();
  void setSelectedNode(TTreeNode* newSelectedNode);
  void setSelectedNodeToLast();
  void rebuildTreeView(const CSeance& Seance);
  bool isHitOnSessionItem(TTreeNode** pHitNode) const;
  const CSession* getSelectedSession(TTreeNode* SelectedNode) const;

private:
  inline void getSessionText( const CSession& Session,
                              UnicodeString* pText) const;
  inline bool isHitOnRoot(TTreeNode* const HitNode) const;

  TTreeView* pTreeView;
  unsigned int CaptionLength;

  static constexpr unsigned int kMaximalCaptionLength = 16;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
