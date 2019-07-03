// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------
#include <vcl.h>
#include "UnitTree.h"
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

/*
class CTreeNodeTester {
public:
  using CTreeNodeInt = CTreeNode<int>;
  CTreeNodeTester()
    : Text(L"CTreeNode Debug:\n") {
    CTreeNodeInt EmptyNode;
    CTreeNodeInt One(1);
    CTreeNodeInt Two(2);
    CTreeNodeInt Three(3);
    CTreeNodeInt Four(4);

    Two.Children.push_back(Four.cloneWithoutParent());
    Two.Children.back()->Parent = &Two;

    One.Children.push_back(Two.cloneWithoutParent());
    One.Children.back()->Parent = &One;
    One.Children.push_back(Three.cloneWithoutParent());
    One.Children.back()->Parent = &One;

    auto& child = *One.Children.back();
    child.Children.push_back(Two.cloneWithoutParent());
    child.Children.back()->Parent = &child;
    child.Children.push_back(Four.cloneWithoutParent());
    child.Children.back()->Parent = &child;
    print(One);
    child.addLastChild(5);
    print(One);

    auto pNode = &One;
    while (pNode != nullptr) {
      printNodeData(*pNode);
      pNode = pNode->getNextPreOrderNode();
    }
    pNode = One.getPreOrderLastNode();
    while (pNode != nullptr) {
      printNodeData(*pNode);
      pNode = pNode->getPreviousPreOrderNode();
    }
    //child.moveChildrenToBeginOf(child.getPreviousSibling());
    //child.splitRight();
    //print(One);
    //printNode(*child.getFirstChild());
    //printNode(*child.getLastChild());
    //printNode(*child.getPreviousSibling());
    //printNode(One);
    //printNode(*child.Children.back());
    ShowMessage(Text.c_str());
  }
  void print(const CTreeNodeInt& Node, int indent = 0) {
    for (int index = 0; index < indent; ++index)
      Text += L' ';
    Text += Node.Data;
    Text += L'\r';
    for (const auto& child : Node.Children) {
      print(*child, indent + 2);
    }
  }
  void printNodeData(const CTreeNodeInt& Node) {
    Text += L"Node.Data = ";
    Text += Node.Data;
    Text += L'\r';
  }
  void printNode(const CTreeNodeInt& child) {
    Text += L'\r';
    Text += L"child.Data = ";
    Text += child.Data;
    Text += L'\r';
    Text += L"child.isLeaf() = ";
    Text += child.isLeaf();
    Text += L'\r';
    Text += L"child.isRoot() = ";
    Text += child.isRoot();
    Text += L'\r';
    Text += L"child.isThereChild() = ";
    Text += child.isThereChild();
    Text += L'\r';
    Text += L"child.isThereNextSibling() = ";
    Text += child.isThereNextSibling();
    Text += L'\r';
    Text += L"child.isThereParent() = ";
    Text += child.isThereParent();
    Text += L'\r';
    Text += L"child.isTherePreviousSibling() = ";
    Text += child.isTherePreviousSibling();
    Text += L'\r';
    Text += L"child.getNumberOfChildren() = ";
    Text += child.getNumberOfChildren();
    Text += L'\r';
    Text += L"child.getSizeOfSubTree() = ";
    Text += child.getSizeOfSubTree();
    Text += L'\r';
    Text += L"child.getNumberOfSiblings() = ";
    Text += child.getNumberOfSiblings();
    Text += L'\r';
    Text += L"child.getLengthOfSubTree() = ";
    Text += child.getLengthOfSubTree();
    Text += L'\r';
    Text += L"child.getNumberOfLeaves() = ";
    Text += child.getNumberOfLeaves();
    Text += L'\r';
  }
  UnicodeString Text;
};
//CTreeNodeTester TreeNodeTester;*/

class CTreeTester {
public:
  using CNodeInt = CTreeNode<int>;
  using CTreeInt = CTree<int>;
  using CConstBaseIterator = CTreeInt::CBaseIterator<CTreeInt::CConstIteratorDefines>;
  using CBaseIterator = CTreeInt::CBaseIterator<CTreeInt::CIteratorDefines>;
  using CConstPreOrderIterator = CTreeInt::CConstPreOrderIterator;
  using CPreOrderIterator = CTreeInt::CPreOrderIterator;
  using CConstLastSonIterator = CTreeInt::CConstLastSonIterator;
  using CLastSonIterator = CTreeInt::CLastSonIterator;
  using CConstBasicIterator = CTreeInt::CConstBasicIterator;
  using CBasicIterator = CTreeInt::CBasicIterator;
  using CConstSiblingIterator = CTreeInt::CConstSiblingIterator;
  using CSiblingIterator = CTreeInt::CSiblingIterator;
  CTreeTester()
    : Text(L"CTree Debug Log:\n") {
    CTreeInt Tree(1);
    Tree.getRootPtr()->addLastChild(2);
    Tree.getRootPtr()->addLastChild(3);
    Tree.getRootPtr()->getLastChild()->addLastChild(4);
    Tree.getRootPtr()->getLastChild()->addLastChild(5);
    CNodeInt& One = *Tree.getRootPtr();
    CNodeInt& Two = *Tree.getRootPtr()->getFirstChild();
    CNodeInt& Three = *Tree.getRootPtr()->getLastChild();
    CNodeInt& Four = *Three.getFirstChild();
    CNodeInt& Five = *Three.getLastChild();
    /*
    for (auto FIt = Tree.begin(); FIt != Tree.end(); ++FIt) {
      for (auto SIt = Tree.begin(); SIt != Tree.end(); ++SIt) {
        printIteratorDifference(FIt, SIt);
      }
    }*/


    //printComparison(One, One);
    //printComparison(One, Two);
    //printComparison(Two, One);
    //printComparison(Two, Two);
    //printComparison(Two, Four);
    //printComparison(Five, Four);
    //printComparison(Four, Five);

    //CTreeInt Tree2(Tree);
    //CTreeInt Tree3;
    //printTree(Tree2);
    //Tree3 = Tree2;
    //printTree(Tree3);

    CPreOrderIterator POIterator1(&Tree, Tree.getRootPtr());
    CConstPreOrderIterator CPOIterator1(&Tree, Tree.getRootPtr());
    CConstPreOrderIterator CPOIterator2(CPOIterator1);
    CPreOrderIterator POIterator2(POIterator1);
    CPOIterator2 = POIterator2;
    CPOIterator2 = std::move(POIterator2);
    CBasicIterator BIter(POIterator1);
    CConstBasicIterator CBIter(CPOIterator2);
    CConstBasicIterator CBIter2(BIter);

    CConstSiblingIterator CSIterator1(CPOIterator1.FirstChild());
    CSiblingIterator SIterator1(POIterator1.FirstChild());
    printIterData(CSIterator1);
    printIterData(++CSIterator1);
    CConstSiblingIterator CSIterator2 = CSIterator1.FirstChild();
    while (CSIterator2 < CSIterator1.LastChild()) {
      printIterData(CSIterator2);
      ++CSIterator2;
    }
    printIterData(CSIterator2);
    while (CSIterator2 > CSIterator1.FirstChild()) {
      printIterData(CSIterator2);
      --CSIterator2;
    }
    printIterData(CSIterator2);
    /*
    auto iter = Tree.beginPreOrder();
    while (iter != Tree.endPreOrder()) {
      printIterData(iter);
      ++iter;
    }
    do {
      --iter;
      printIterData(iter);
    } while (iter != Tree.beginPreOrder());
    for (const auto& element : Tree) {
      Text += L"\nelement = ";
      Text += element;
    }*/


    //compare(It1, It3);
    //compare(It1, It2);
    ShowMessage(Text.c_str());
  }
  template<class CIterator>
  void printIteratorDifference( const CIterator& First,
                                const CIterator& Second) {
    Text += L"(";
    Text += *First;
    Text += L") - (";
    Text += *Second;
    Text += L") = ";
    Text += First - Second;
    Text += L"\n";
  }
  template<class CIterator>
  void printIteratorComparison( const CIterator& First,
                                const CIterator& Second) {
    Text += L"(";
    Text += *First;
    Text += L") < (";
    Text += *Second;
    Text += L") is ";
    Text += First < Second;
    Text += L"\n";
  }
  void printComparison(const CNodeInt& First, const CNodeInt& Second) {
    Text += L"(";
    Text += First.Data;
    Text += L") < (";
    Text += Second.Data;
    Text += L") is ";
    Text += isPreOrderLess(First, Second);
    Text += L"\n";
  }
  void printTree(const CTreeInt& Tree) {
    auto iter = Tree.beginPreOrder();
    while (iter != Tree.endPreOrder()) {
      printIterData(iter);
      ++iter;
    }
  }
  void compare(const CBaseIterator& Iter1, const CBaseIterator& Iter2) {
    Text += L"Iter1 == Iter2 is ";
    Text += Iter1 == Iter2;
    Text += L"\nIter1 != Iter2 is ";
    Text += Iter1 != Iter2;
    Text += L"\n";

  }
  template<class CIterator>
  void printIterData(const CIterator& Iter) {
    Text += L"*Iter = ";
    Text += *Iter;
    Text += L"\nIter-> = ";
    Text += int(Iter.operator->());
    Text += L"\n";
  }
  template<class CIterator>
  void printIter(const CIterator& Iter) {
    Text += L"Iterator:\n";
    Text += L"pCurrent = ";
    Text += int(Iter.pCurrent);
    Text += L"\npHost = ";
    Text += int(Iter.pHost);
    if (Iter.isDefined()) {
      Text += L"\n*Iter = ";
      Text += *Iter;
      Text += L"\nIter-> = ";
      Text += int(Iter.operator->());
    }
    Text += L"\nIter.isDefined() = ";
    Text += Iter.isDefined();
    Text += L"\nIter.isRoot() = ";
    Text += Iter.isRoot();
    Text += L"\nIter.isLeaf() = ";
    Text += Iter.isLeaf();
    Text += L"\nIter.isThereParent() = ";
    Text += Iter.isThereParent();
    Text += L"\nIter.isThereChild() = ";
    Text += Iter.isThereChild();
    Text += L"\nIter.isThereNextSibling() = ";
    Text += Iter.isThereNextSibling();
    Text += L"\nIter.isTherePreviousSibling() = ";
    Text += Iter.isTherePreviousSibling();
    Text += L"\nIter.getNumberOfChildren() = ";
    Text += Iter.getNumberOfChildren();
    Text += L"\nIter.getSizeOfSubTree() = ";
    Text += Iter.getSizeOfSubTree();
    Text += L"\nIter.getNumberOfSiblings() = ";
    Text += Iter.getNumberOfSiblings();
    Text += L"\nIter.getLengthOfSubTree() = ";
    Text += Iter.getLengthOfSubTree();
    Text += L"\nIter.getNumberOfLeaves() = ";
    Text += Iter.getNumberOfLeaves();
    Text += L"\nDistToRoot = ";
    Text += Iter.getDistanceToRoot();
    Text += L"\n";
  }
  void printTreeInfo(const CTreeInt& Tree) {
    Text += L"Tree Info:\n";
    Text += L"Tree.empty() = ";
    Text += Tree.empty();
    Text += L"\nTree size = ";
    Text += Tree.size();
    Text += L"\nRoot Ptr = ";
    Text += int(Tree.getRootPtr());
    Text += L"\n";
  }
  UnicodeString Text;
};
//CTreeTester TreeTester;



// ---------------------------------------------------------------------------
} // NSLibrary
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
// #pragma package(smart_init)
