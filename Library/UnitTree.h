// ---------------------------------------------------------------------------

#ifndef UnitTreeH
#define UnitTreeH
// ---------------------------------------------------------------------------
// Debug Include
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <list>
#include <algorithm>
#include <memory>
#include <cassert>
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

// ---------------------------------------------------------------------------
// Forward Declaration of CTreeNode<Type>
// ---------------------------------------------------------------------------

template<class Type>
class CTreeNode;
// ---------------------------------------------------------------------------
// Forward Declaration of CTreeNode<Type> Friends
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderLess(const CTreeNode<Type>& first,
                    const CTreeNode<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderGreater( const CTreeNode<Type>& first,
                        const CTreeNode<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderLessOrEqual( const CTreeNode<Type>& first,
                            const CTreeNode<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderGreaterOrEqual(const CTreeNode<Type>& first,
                              const CTreeNode<Type>& second);
// ---------------------------------------------------------------------------
// Declaration of CTreeNode<Type>
// ---------------------------------------------------------------------------

template<class Type>
class CTreeNode {
public:
  using CNodePtr = CTreeNode*;
  using CConstNodePtr = const CTreeNode*;
  using CNodeUPtr = std::unique_ptr<CTreeNode>;
  using CChildrenStr = std::list<CNodeUPtr>;

  CTreeNode();
  CTreeNode(const Type& NodeData);
  CNodeUPtr cloneWithoutParent() const;

  bool isRoot() const;
  bool isLeaf() const;
  bool isThereParent() const;
  bool isThereChild() const;
  bool isThereNextSibling() const;
  bool isTherePreviousSibling() const;

  CNodePtr getFirstChild();
  CConstNodePtr getFirstChild() const;
  CNodePtr getLastChild();
  CConstNodePtr getLastChild() const;
  CNodePtr getNextSibling();
  CConstNodePtr getNextSibling() const;
  CNodePtr getPreviousSibling();
  CConstNodePtr getPreviousSibling() const;

  size_t getNumberOfChildren() const;
  size_t getSizeOfSubTree() const;
  size_t getNumberOfSiblings() const;
  size_t getLengthOfSubTree() const;
  size_t getNumberOfLeaves() const;
  size_t getDistanceToRoot() const;

  void moveChildrenTo(CNodePtr pReceiver);
  void moveChildrenToBeginOf(CNodePtr pReceiver);
  void moveChildrenToEndOf(CNodePtr pReceiver);

  void splitRight();
  void addLastChild();
  void addLastChild(const Type& NodeData);

  CNodePtr getNextPreOrderNode();
  CConstNodePtr getNextPreOrderNode() const;
  CNodePtr getPreviousPreOrderNode();
  CConstNodePtr getPreviousPreOrderNode() const;
  CNodePtr getPreOrderLastNode();
  CConstNodePtr getPreOrderLastNode() const;

  friend bool isPreOrderLess<Type>( const CTreeNode& first,
                                    const CTreeNode& second);
  friend bool isPreOrderGreater<Type>(const CTreeNode& first,
                                      const CTreeNode& second);
  friend bool isPreOrderLessOrEqual<Type>(const CTreeNode& first,
                                          const CTreeNode& second);
  friend bool isPreOrderGreaterOrEqual<Type>( const CTreeNode& first,
                                              const CTreeNode& second);

  Type Data;
  CNodePtr Parent;
  CChildrenStr Children;
};
// ---------------------------------------------------------------------------
// Declaration of CTree<Type>
// ---------------------------------------------------------------------------

template<class Type>
class CTree {
public:
  friend class CTreeTester;
  using DataType = Type;

  // The following redefinitions are because of RAD Studio
  // When I use the following code:
  // class CTextData;
  // class CTextDataTree : public CTree<CTextData> {};
  // class CTextData{};
  // I get "field has incomplete type" error
  // If I replace unique_ptr to the Root by the usual pointer
  // the problem disappears but I do not want to manage
  // the life time of the Root
  // The problem appears when I read using-s from
  // the class CTreeNode<Type>, e.g., CTreeNode<Type>::CNodePtr
  // causes the error
  // Hence, I have to use the direct using-s instead

  //using MyNode = CTreeNode<Type>;
  //using CNodePtr = typename MyNode::CNodePtr;
  //using CConstNodePtr = typename MyNode::CConstNodePtr;
  //using CNodeUPtr = typename MyNode::CNodeUPtr;
  //using CChildrenStr = typename MyNode::CChildrenStr;
  using CMyNode = CTreeNode<Type>;
  using CConstMyNode = const CTreeNode<Type>;
  using CNodePtr = CMyNode*;
  using CConstNodePtr = CConstMyNode*;
  using CNodeUPtr = std::unique_ptr<CMyNode>;
  using CChildrenStr = std::list<CNodeUPtr>;
  using CDeletionList = std::list<CNodePtr>;

  CTree();
  // The problem mentioned above needed the explicit destructor definition
  // This was a surprise!
  // The second reason of using a custom destructor is
  // avoiding the stack overflow issue,
  // which happens if the tree height >= 2000
  ~CTree();
  CTree(const DataType& Data);
  CTree(const CTree& Tree);
  CTree(CTree&& Tree) = default;
  CTree& operator=(const CTree& Tree);
  // The explicit definition of move assignment is because of
  // RAD Studio. See description above near the using statements
  // This particular issue is very surprising! RAD Studio is just awful.
  //CTree& operator=(CTree&& Tree) = default;
  CTree& operator=(CTree&& Tree);


  void destroyExceptRoot();
  bool empty() const;
  size_t size() const;
  void clear();
protected:
  //---------------------------------------------------------------------------
  // Declaration of CConstIteratorDefines
  //---------------------------------------------------------------------------

  class CConstIteratorDefines {
  public:
    using value_type = const DataType;
    using difference_type = int;
    using pointer = value_type*;
    using reference = value_type&;
    using CIteratorNodePtr = CConstNodePtr;
    using CMyNodeRef = const CMyNode&;
    using CHostTreePtr = const CTree<DataType>*;
  protected:
    ~CConstIteratorDefines() = default;
  };
  //---------------------------------------------------------------------------
  // Declaration of CIteratorDefines
  //---------------------------------------------------------------------------

  class CIteratorDefines {
  public:
    using value_type = DataType;
    using difference_type = int;
    using pointer = value_type*;
    using reference = value_type&;
    using CIteratorNodePtr = CNodePtr;
    using CMyNodeRef = CMyNode&;
    using CHostTreePtr = CTree<DataType>*;
  protected:
    ~CIteratorDefines() = default;
  };
  // ---------------------------------------------------------------------------
  // Declaration of CBaseIterator
  // ---------------------------------------------------------------------------

  template<class TIteratorDefines>
  class CBaseIterator : public TIteratorDefines {
  public:
    friend class CTreeTester;
    template<class TOtherIteratorDefines>
    friend class CBaseIterator;
    using value_type = typename TIteratorDefines::value_type;
    using difference_type = typename TIteratorDefines::difference_type;
    using pointer = typename TIteratorDefines::pointer;
    using reference = typename TIteratorDefines::reference;
    using CIteratorNodePtr = typename TIteratorDefines::CIteratorNodePtr;
    using CHostTreePtr = typename TIteratorDefines::CHostTreePtr;

    CBaseIterator();
    CBaseIterator(CHostTreePtr HostTree,
                  const CIteratorNodePtr& CurrentPtr);
    CBaseIterator(const CBaseIterator& other);
    CBaseIterator(CBaseIterator&& other);
    CBaseIterator& operator=(const CBaseIterator& other);
    CBaseIterator& operator=(CBaseIterator&& other);

    template<class TOtherIteratorDefines>
    bool operator==(const CBaseIterator<TOtherIteratorDefines>& Iterator) const;
    template<class TOtherIteratorDefines>
    bool operator!=(const CBaseIterator<TOtherIteratorDefines>& Iterator) const;

    bool isDefined() const;
    bool isRoot() const;
    bool isLeaf() const;
    bool isThereParent() const;
    bool isThereChild() const;
    bool isThereNextSibling() const;
    bool isTherePreviousSibling() const;

    size_t getNumberOfChildren() const;
    size_t getSizeOfSubTree() const;
    size_t getNumberOfSiblings() const;
    size_t getLengthOfSubTree() const;
    size_t getNumberOfLeaves() const;
    size_t getDistanceToRoot() const;

    void setToParent();
    void setToFirstChild();
    void setToLastChild();
    void setToNextSibling();
    void setToPreviousSibling();

    void addLastChild(const Type& NodeData); // value_type instead of Type
  protected:
    ~CBaseIterator() = default;
    CHostTreePtr pHost;
    CIteratorNodePtr pCurrent;
  };
  // ---------------------------------------------------------------------------
  // Forward Declaration of CNodeReference
  // ---------------------------------------------------------------------------

  template<class TBaseIterator>
  class CNodeReference;
  // ---------------------------------------------------------------------------
  // Declaration of CDataReference
  // ---------------------------------------------------------------------------

  template<class TBaseIterator>
  class CDataReference : public TBaseIterator {
    public:
    using CBase = TBaseIterator;
    using reference = typename CBase::reference;
    using pointer = typename CBase::pointer;

    template<class TOtherBaseIterator>
    friend class CDataReference;
    template<class TOtherBaseIterator>
    CDataReference(const CDataReference<TOtherBaseIterator>& other);

    template<class TOtherBaseIterator>
    friend class CNodeReference;

    using CBase::CBase;
    CDataReference() = default;
    ~CDataReference() = default;
    CDataReference(const CDataReference& other) = default;
    CDataReference(CDataReference&& other) = default;
    CDataReference& operator=(const CDataReference& other) = default;
    CDataReference& operator=(CDataReference&& other) = default;

    reference operator*() const;
    pointer operator->() const;

    protected:
  };
  // ---------------------------------------------------------------------------
  // Declaration of CConstBasicIterator
  // ---------------------------------------------------------------------------

  using CConstBasicIterator =
            CDataReference<CBaseIterator<CConstIteratorDefines>>;
  // ---------------------------------------------------------------------------
  // Declaration of CBasicIterator
  // ---------------------------------------------------------------------------

  using CBasicIterator = CDataReference<CBaseIterator<CIteratorDefines>>;
  // ---------------------------------------------------------------------------
  // Declaration of CNodeReference
  // ---------------------------------------------------------------------------

  template<class TBaseIterator>
  class CNodeReference : public TBaseIterator {
    public:
    using CBase = TBaseIterator;
    using CMyNodeRef = typename CBase::CMyNodeRef;
    using CIteratorNodePtr = typename CBase::CIteratorNodePtr;

    using CBase::CBase;
    CNodeReference() = default;
    ~CNodeReference() = default;
    CNodeReference(const CNodeReference& other) = default;
    CNodeReference(CNodeReference&& other) = default;
    CNodeReference& operator=(const CNodeReference& other) = default;
    CNodeReference& operator=(CNodeReference&& other) = default;

    CNodeReference(const CDataReference<TBaseIterator>& other);

    CMyNodeRef operator*() const;
    CIteratorNodePtr operator->() const;

    protected:
  };
  // ---------------------------------------------------------------------------
  // Declaration of CPreOrderLogic
  // ---------------------------------------------------------------------------

  template<class TIteratorWithDereferencing>
  class CPreOrderLogic : public TIteratorWithDereferencing {
  public:
    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    using CIteratorNodePtr = typename CBase::CIteratorNodePtr;
    using CBase::CBase;
    CPreOrderLogic() = default;
    CPreOrderLogic(const CPreOrderLogic& other) = default;
    CPreOrderLogic(CPreOrderLogic&& other) = default;
    CPreOrderLogic& operator=(const CPreOrderLogic& other) = default;
    CPreOrderLogic& operator=(CPreOrderLogic&& other) = default;

    template<class TOtherIteratorWithDereferencing>
    bool operator<(const CPreOrderLogic<
                            TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator<=(const CPreOrderLogic<
                            TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>(const CPreOrderLogic<
                            TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>=(const CPreOrderLogic<
                            TOtherIteratorWithDereferencing>& other) const;

  protected:
    void setToNext();
    void setToPrevious();
    ~CPreOrderLogic() = default;
  };
  template<class TIteratorWithDereferencing>
  friend class CPreOrderLogic;
  // ---------------------------------------------------------------------------
  // Declaration of CLastSonLogic
  // ---------------------------------------------------------------------------

  template<class TIteratorWithDereferencing>
  class CLastSonLogic : public TIteratorWithDereferencing {
  public:
    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    using CIteratorNodePtr = typename CBase::CIteratorNodePtr;
    using CBase::CBase;
    CLastSonLogic() = default;
    CLastSonLogic(const CLastSonLogic& other) = default;
    CLastSonLogic(CLastSonLogic&& other) = default;
    CLastSonLogic& operator=(const CLastSonLogic& other) = default;
    CLastSonLogic& operator=(CLastSonLogic&& other) = default;

    template<class TOtherIteratorWithDereferencing>
    bool operator<(const CLastSonLogic<
                              TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator<=(const CLastSonLogic<
                              TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>(const CLastSonLogic<
                              TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>=(const CLastSonLogic<
                              TOtherIteratorWithDereferencing>& other) const;
  protected:
    void setToNext();
    void setToPrevious();
    ~CLastSonLogic() = default;
  };
  template<class TIteratorWithDereferencing>
  friend class CLastSonLogic;
  // ---------------------------------------------------------------------------
  // Declaration of CSiblingLogic
  // ---------------------------------------------------------------------------

  template<class TIteratorWithDereferencing>
  class CSiblingLogic : public TIteratorWithDereferencing {
  public:
    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    using CIteratorNodePtr = typename CBase::CIteratorNodePtr;
    using CBase::CBase;
    CSiblingLogic() = default;
    CSiblingLogic(const CSiblingLogic& other) = default;
    CSiblingLogic(CSiblingLogic&& other) = default;
    CSiblingLogic& operator=(const CSiblingLogic& other) = default;
    CSiblingLogic& operator=(CSiblingLogic&& other) = default;

    template<class TOtherIteratorWithDereferencing>
    bool operator<(const CSiblingLogic<
                              TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator<=(const CSiblingLogic<
                              TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>(const CSiblingLogic<
                              TOtherIteratorWithDereferencing>& other) const;
    template<class TOtherIteratorWithDereferencing>
    bool operator>=(const CSiblingLogic<
                              TOtherIteratorWithDereferencing>& other) const;
  protected:
    void setToNext();
    void setToPrevious();
    ~CSiblingLogic() = default;
  };
  template<class TIteratorWithDereferencing>
  friend class CSiblingLogic;
  // ---------------------------------------------------------------------------
  // Forward Declaration of CIteratorTemplate
  // ---------------------------------------------------------------------------
  template <template<class> class TReferenceLogic,
            template<class> class TTravellingLogic,
            class TIteratorDefines>
  class CIteratorTemplate;
  // ---------------------------------------------------------------------------
  // Declaration of CConstSiblingIterator
  // ---------------------------------------------------------------------------
  using CConstSiblingIterator =
          CIteratorTemplate<CDataReference,
                            CSiblingLogic,
                            CConstIteratorDefines>;
  // ---------------------------------------------------------------------------
  // Declaration of CSiblingIterator
  // ---------------------------------------------------------------------------
  using CSiblingIterator =
          CIteratorTemplate<CDataReference,
                            CSiblingLogic,
                            CIteratorDefines>;
  // ---------------------------------------------------------------------------
  // Declaration of CIteratorChildren
  // ---------------------------------------------------------------------------

  template <class TIteratorWithTravellingLogic,
            class TIteratorDefines>
  class CIteratorChildren;
  // ---------------------------------------------------------------------------

  template <class TIteratorWithTravellingLogic>
  class CIteratorChildren<TIteratorWithTravellingLogic, CIteratorDefines> :
    public TIteratorWithTravellingLogic {
  public:
    using CChildIterator = CSiblingIterator;
    using CBase = TIteratorWithTravellingLogic;
    using CBase::CBase;
  };
  // ---------------------------------------------------------------------------

  template <class TIteratorWithTravellingLogic>
  class CIteratorChildren<TIteratorWithTravellingLogic, CConstIteratorDefines> :
    public TIteratorWithTravellingLogic {
  public:
    using CChildIterator = CConstSiblingIterator;
    using CBase = TIteratorWithTravellingLogic;
    using CBase::CBase;
  };
  // ---------------------------------------------------------------------------
  // Declaration of CIteratorTemplate
  // ---------------------------------------------------------------------------

  template <template<class> class TReferenceLogic,
            template<class> class TTravellingLogic,
            class TIteratorDefines>
  class CIteratorTemplate :
    public CIteratorChildren<
            TTravellingLogic<
              TReferenceLogic<
                CBaseIterator<
                  TIteratorDefines>>>,
            TIteratorDefines> {
  public:
    friend class CTreeTester;
    friend CTree;
    using CBase =
      CIteratorChildren<
            TTravellingLogic<
              TReferenceLogic<
                CBaseIterator<
                  TIteratorDefines>>>,
            TIteratorDefines>;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    using CIteratorNodePtr = typename CBase::CIteratorNodePtr;
    using difference_type = typename CBase::difference_type;
    using CChildIterator = typename CBase::CChildIterator;

    template <template<class> class TOtherReferenceLogic,
              template<class> class TOtherTravellingLogic,
              class TOtherIteratorDefines>
    friend class CIteratorTemplate;
    template <template<class> class TOtherReferenceLogic,
              template<class> class TOtherTravellingLogic,
              class TOtherIteratorDefines>
    CIteratorTemplate(
          const CIteratorTemplate<TOtherReferenceLogic,
                                  TOtherTravellingLogic,
                                  TOtherIteratorDefines>& other);
    using CBase::CBase;
    CIteratorTemplate() = default;
  protected:
    CIteratorTemplate(CHostTreePtr HostTree,
                      const CIteratorNodePtr& CurrentPtr);
  public:
    CIteratorTemplate& operator++();
    CIteratorTemplate operator++(int);
    CIteratorTemplate& operator+=(difference_type Difference);
    CIteratorTemplate& operator--();
    CIteratorTemplate operator--(int);
    CIteratorTemplate& operator-=(difference_type Difference);

    template <template<class> class TOtherReferenceLogic,
              class TOtherIteratorDefines>
    difference_type
      operator-(const CIteratorTemplate<
                                  TOtherReferenceLogic,
                                  TTravellingLogic,
                                  TOtherIteratorDefines>& other) const;
    CChildIterator FirstChild() const;
    CChildIterator LastChild() const;
  protected:
  private:
    template <template<class> class TOtherReferenceLogic,
              class TOtherIteratorDefines>
    difference_type
          subtractSmaller(const CIteratorTemplate<
                                  TOtherReferenceLogic,
                                  TTravellingLogic,
                                  TOtherIteratorDefines>& smaller) const;
  };
  template <template<class> class TReferenceLogic,
            template<class> class TTravellingLogic,
            class TIteratorDefines>
  friend class CIteratorTemplate;
public:
  // ---------------------------------------------------------------------------
  // Declaration of CConstPreOrderIterator
  // ---------------------------------------------------------------------------
  using CConstPreOrderIterator =
          CIteratorTemplate<CDataReference,
                            CPreOrderLogic,
                            CConstIteratorDefines>;
  // ---------------------------------------------------------------------------
  // Declaration of CPreOrderIterator
  // ---------------------------------------------------------------------------
  using CPreOrderIterator =
          CIteratorTemplate<CDataReference,
                            CPreOrderLogic,
                            CIteratorDefines>;
  // ---------------------------------------------------------------------------
  // Declaration of CConstLastSonIterator
  // ---------------------------------------------------------------------------
  using CConstLastSonIterator =
          CIteratorTemplate<CDataReference,
                            CLastSonLogic,
                            CConstIteratorDefines>;
  // ---------------------------------------------------------------------------
  // Declaration of CLastSonIterator
  // ---------------------------------------------------------------------------
  using CLastSonIterator =
          CIteratorTemplate<CDataReference,
                            CLastSonLogic,
                            CIteratorDefines>;
  // ---------------------------------------------------------------------------
  // Declaration of CConstLastSonNodIterator
  // ---------------------------------------------------------------------------
  using CConstLastSonNodeIterator =
          CIteratorTemplate<CNodeReference,
                            CLastSonLogic,
                            CConstIteratorDefines>;
  // ---------------------------------------------------------------------------
  CConstPreOrderIterator beginPreOrder() const;
  CConstPreOrderIterator endPreOrder() const;
  CConstPreOrderIterator cbeginPreOrder() const;
  CConstPreOrderIterator cendPreOrder() const;
  CPreOrderIterator beginPreOrder();
  CPreOrderIterator endPreOrder();

  CConstLastSonIterator beginLastSon() const;
  CConstLastSonIterator endLastSon() const;
  CConstLastSonIterator cbeginLastSon() const;
  CConstLastSonIterator cendLastSon() const;
  CLastSonIterator beginLastSon();
  CLastSonIterator endLastSon();
  // ---------------------------------------------------------------------------
  // Declarations for STL compatability
  // ---------------------------------------------------------------------------
  using const_iterator = CConstPreOrderIterator;
  using iterator = CPreOrderIterator;
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  iterator begin();
  iterator end();

protected:
  CConstNodePtr getRootPtr() const;
  CNodePtr getRootPtr();
  void moveLastChildToFirst(CChildrenStr* pSource, CDeletionList* pTarget);
  void moveAllChildren(CChildrenStr* pSource, CDeletionList* pTarget);
  void clearDeletionList(CDeletionList* pDeletionList);
private:
  CNodeUPtr Root;
};
// ---------------------------------------------------------------------------
} // NSLibrary
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
// ---------------------------------------------------------------------------
// Definitions of CTreeNode<Type>
// ---------------------------------------------------------------------------

template<class Type>
CTreeNode<Type>::CTreeNode() : Parent(nullptr) {
}
// ---------------------------------------------------------------------------

template<class Type>
CTreeNode<Type>::CTreeNode(const Type& NodeData)
  : Parent(nullptr),
    Data(NodeData) {
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodeUPtr
                    CTreeNode<Type>::cloneWithoutParent() const {
  CNodeUPtr newNodeHolder(new CTreeNode(Data));
  for (const auto& childNode : Children) {
    newNodeHolder->Children.push_back(std::move(childNode->cloneWithoutParent()));
    newNodeHolder->Children.back()->Parent = newNodeHolder.get();
  }
  return std::move(newNodeHolder);
}
// ---------------------------------------------------------------------------

template<class Type>
bool CTreeNode<Type>::isRoot() const {
  return !isThereParent();
}
// ---------------------------------------------------------------------------

template<class Type>
bool CTreeNode<Type>::isLeaf() const {
  return !isThereChild();
}
// ---------------------------------------------------------------------------

template<class Type>
bool CTreeNode<Type>::isThereParent() const {
  return Parent != nullptr;
}
// ---------------------------------------------------------------------------

template<class Type>
bool CTreeNode<Type>::isThereChild() const {
  return !Children.empty();
}
// ---------------------------------------------------------------------------

template<class Type>
bool CTreeNode<Type>::isThereNextSibling() const {
  if (!isThereParent())
    return false;
  return Parent->getLastChild() != this;
}
// ---------------------------------------------------------------------------

template<class Type>
bool CTreeNode<Type>::isTherePreviousSibling() const {
  if (!isThereParent())
    return false;
  return Parent->getFirstChild() != this;
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodePtr
                    CTreeNode<Type>::getFirstChild() {
  return Children.front().get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CConstNodePtr
                    CTreeNode<Type>::getFirstChild() const {
  return Children.front().get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodePtr
                    CTreeNode<Type>::getLastChild() {
  return Children.back().get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CConstNodePtr
                    CTreeNode<Type>::getLastChild() const {
  return Children.back().get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodePtr
                    CTreeNode<Type>::getNextSibling() {
  auto itOnMe = std::find_if( Parent->Children.begin(),
                              Parent->Children.end(),
                              [this](const CNodeUPtr& current){
                                return current.get() == this;
                              });
  ++itOnMe;
  return itOnMe->get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CConstNodePtr
                    CTreeNode<Type>::getNextSibling() const {
  auto itOnMe = std::find_if( Parent->Children.begin(),
                              Parent->Children.end(),
                              [this](const CNodeUPtr& current){
                                return current.get() == this;
                              });
  ++itOnMe;
  return itOnMe->get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodePtr
                    CTreeNode<Type>::getPreviousSibling() {
  auto itOnMe = std::find_if( Parent->Children.begin(),
                              Parent->Children.end(),
                              [this](const CNodeUPtr& current){
                                return current.get() == this;
                              });
  --itOnMe;
  return itOnMe->get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CConstNodePtr
                    CTreeNode<Type>::getPreviousSibling() const {
  auto itOnMe = std::find_if( Parent->Children.begin(),
                              Parent->Children.end(),
                              [this](const CNodeUPtr& current){
                                return current.get() == this;
                              });
  --itOnMe;
  return itOnMe->get();
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CTreeNode<Type>::getNumberOfChildren() const {
  return Children.size();
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CTreeNode<Type>::getSizeOfSubTree() const {
  size_t SubTreeSize = 1;
  for (const auto& child : Children)
    SubTreeSize += child->getSizeOfSubTree();
  return SubTreeSize;
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CTreeNode<Type>::getNumberOfSiblings() const {
  if (!isThereParent())
    return 0;
  return Parent->Children.size() - 1;
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CTreeNode<Type>::getLengthOfSubTree() const {
  size_t SubTreeLength = 0;
  for (const auto& child : Children)
    SubTreeLength = std::max(SubTreeLength, child->getLengthOfSubTree());
  return ++SubTreeLength;
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CTreeNode<Type>::getNumberOfLeaves() const {
  if (isLeaf())
    return 1;
  size_t NumberOfLeaves = 0;
  for (const auto& child : Children)
    NumberOfLeaves += child->getNumberOfLeaves();
  return NumberOfLeaves;
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CTreeNode<Type>::getDistanceToRoot() const {
  size_t distance = 0;
  CConstNodePtr Current = this;
  while (!Current->isRoot()) {
    Current = Current->Parent;
    ++distance;
  }
  return distance;
}
// ---------------------------------------------------------------------------

template<class Type>
void CTreeNode<Type>::moveChildrenTo(CNodePtr pReceiver) {
  for (auto& child : Children)
    child->Parent = pReceiver;
  pReceiver->Children = std::move(Children);
}
// ---------------------------------------------------------------------------

template<class Type>
void CTreeNode<Type>::moveChildrenToBeginOf(CNodePtr pReceiver) {
  for (auto& child : Children)
    child->Parent = pReceiver;
  pReceiver->Children.splice(pReceiver->Children.begin(), Children);
}
// ---------------------------------------------------------------------------

template<class Type>
void CTreeNode<Type>::moveChildrenToEndOf(CNodePtr pReceiver) {
  for (auto& child : Children)
    child->Parent = pReceiver;
  pReceiver->Children.splice(pReceiver->Children.end(), Children);
}
// ---------------------------------------------------------------------------

template<class Type>
void CTreeNode<Type>::splitRight() {
  CNodeUPtr newLeftNode (new CTreeNode());
  newLeftNode->Parent = this;
  moveChildrenTo(newLeftNode.get());
  Children.push_back(std::move(newLeftNode));
  CNodeUPtr newRightNode (new CTreeNode());
  newRightNode->Parent = this;
  Children.push_back(std::move(newRightNode));
}
// ---------------------------------------------------------------------------

template<class Type>
void CTreeNode<Type>::addLastChild() {
  CNodeUPtr newNode (new CTreeNode());
  newNode->Parent = this;
  Children.push_back(std::move(newNode));
}
// ---------------------------------------------------------------------------

template<class Type>
void CTreeNode<Type>::addLastChild(const Type& NodeData) {
  CNodeUPtr newNode (new CTreeNode(NodeData));
  newNode->Parent = this;
  Children.push_back(std::move(newNode));
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodePtr
                    CTreeNode<Type>::getNextPreOrderNode() {
  if (isThereChild())
    return getFirstChild();
  CNodePtr ResultPtr = this;
  while ( ResultPtr->isThereParent() &&
          !ResultPtr->isThereNextSibling())
    ResultPtr = ResultPtr->Parent;
  if (!ResultPtr->isThereParent())
    return nullptr;
  return ResultPtr->getNextSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CConstNodePtr
                    CTreeNode<Type>::getNextPreOrderNode() const {
  if (isThereChild())
    return getFirstChild();
  CConstNodePtr ResultPtr = this;
  while ( ResultPtr->isThereParent() &&
          !ResultPtr->isThereNextSibling())
    ResultPtr = ResultPtr->Parent;
  if (!ResultPtr->isThereParent())
    return nullptr;
  return ResultPtr->getNextSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodePtr
                    CTreeNode<Type>::getPreviousPreOrderNode() {
  if (!isThereParent())
    return nullptr;
  if (!isTherePreviousSibling())
    return Parent;
  return getPreviousSibling()->getPreOrderLastNode();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CConstNodePtr
                    CTreeNode<Type>::getPreviousPreOrderNode() const {
  if (!isThereParent())
    return nullptr;
  if (!isTherePreviousSibling())
    return Parent;
  return getPreviousSibling()->getPreOrderLastNode();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CNodePtr
                    CTreeNode<Type>::getPreOrderLastNode() {
  CNodePtr ResultPtr = this;
  while (ResultPtr->isThereChild())
    ResultPtr = ResultPtr->getLastChild();
  return ResultPtr;
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTreeNode<Type>::CConstNodePtr
                    CTreeNode<Type>::getPreOrderLastNode() const {
  CConstNodePtr ResultPtr = this;
  while (ResultPtr->isThereChild())
    ResultPtr = ResultPtr->getLastChild();
  return ResultPtr;
}
// ---------------------------------------------------------------------------
// Definition of CTreeNode<Type> Friends
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderLess(const CTreeNode<Type>& first,
                    const CTreeNode<Type>& second) {
  const CTreeNode<Type>* pNode1 = &first;
  const CTreeNode<Type>* pNode2 = &second;
  size_t DistanceToRoot1 = pNode1->getDistanceToRoot();
  size_t DistanceToRoot2 = pNode2->getDistanceToRoot();
  if (DistanceToRoot1 == DistanceToRoot2) {
    if (pNode1 == pNode2)
      return false;
  }
  else {
    if (DistanceToRoot1 < DistanceToRoot2) {
      while (DistanceToRoot2 != DistanceToRoot1 + 1) {
        pNode2 = pNode2->Parent;
        --DistanceToRoot2;
      }
      if (pNode1 == pNode2->Parent)
        return true;
      pNode2 = pNode2->Parent;
      --DistanceToRoot2;
    }
    else
      return !isPreOrderLess(*pNode2, *pNode1);
  }
  assert(DistanceToRoot1 == DistanceToRoot2);
  assert(pNode1 != pNode2);
  while(pNode1->Parent != pNode2->Parent) {
    pNode1 = pNode1->Parent;
    pNode2 = pNode2->Parent;
  }
  const CTreeNode<Type>* Parent = pNode1->Parent;
  for ( auto iter = Parent->Children.cbegin();
        iter != Parent->Children.end();
        ++iter) {
    if (iter->get() == pNode1)
      return true;
    if (iter->get() == pNode2)
      return false;
  }
  assert(false);
  return false;
}
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderGreater( const CTreeNode<Type>& first,
                        const CTreeNode<Type>& second) {
  return isPreOrderLess(second, first);
}
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderLessOrEqual( const CTreeNode<Type>& first,
                            const CTreeNode<Type>& second) {
  return !isPreOrderGreater(first, second);
}
// ---------------------------------------------------------------------------

template<class Type>
bool isPreOrderGreaterOrEqual(const CTreeNode<Type>& first,
                              const CTreeNode<Type>& second) {
  return !isPreOrderLess(first, second);
}
// ---------------------------------------------------------------------------
// Definition of CTree<Type>
// ---------------------------------------------------------------------------

template<class Type>
CTree<Type>::CTree()
  : Root(nullptr) {
}
// ---------------------------------------------------------------------------


template<class Type>
CTree<Type>::~CTree() {
  if (Root == nullptr)
    return;
  destroyExceptRoot();
  Root = nullptr;
}
// ---------------------------------------------------------------------------

template<class Type>
CTree<Type>::CTree(const DataType& Data)
  : Root(new CMyNode(Data)) {
}
// ---------------------------------------------------------------------------

template<class Type>
CTree<Type>::CTree(const CTree& Tree)
  : Root(nullptr) {
  if (!Tree.empty())
    Root = std::move(Tree.Root->cloneWithoutParent());
}
// ---------------------------------------------------------------------------

template<class Type>
CTree<Type>& CTree<Type>::operator=(const CTree& Tree) {
  return *this = CTree(Tree);
}
// ---------------------------------------------------------------------------

template<class Type>
CTree<Type>& CTree<Type>::operator=(CTree&& Tree) {
  Root = std::move(Tree.Root);
  return *this;
}
// ---------------------------------------------------------------------------

template<class Type>
void CTree<Type>::destroyExceptRoot() {
  CDeletionList DeletionList;
  moveAllChildren(&Root->Children, &DeletionList);
  clearDeletionList(&DeletionList);
}
// ---------------------------------------------------------------------------

template<class Type>
bool CTree<Type>::empty() const {
  return Root.get() == nullptr;
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CTree<Type>::size() const {
  if (empty())
    return 0;
  return Root->getSizeOfSubTree();
}
// ---------------------------------------------------------------------------

template<class Type>
void CTree<Type>::clear() {
  Root = nullptr;
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstNodePtr CTree<Type>::getRootPtr() const {
  return Root.get();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CNodePtr CTree<Type>::getRootPtr() {
  return Root.get();
}
// ---------------------------------------------------------------------------

template<class Type>
void CTree<Type>::moveLastChildToFirst( CChildrenStr* pSource,
                                        CDeletionList* pTarget) {
  pTarget->push_front(pSource->back().release());
  pSource->pop_back();
}
// ---------------------------------------------------------------------------

template<class Type>
void CTree<Type>::moveAllChildren(CChildrenStr* pSource,
                                  CDeletionList* pTarget) {
  while(!pSource->empty())
    moveLastChildToFirst(pSource, pTarget);
}
// ---------------------------------------------------------------------------

template<class Type>
void CTree<Type>::clearDeletionList(CDeletionList* pDeletionList) {
  while(!pDeletionList->empty()) {
    CNodePtr pNode = pDeletionList->front();
    pDeletionList->pop_front();
    if (pNode->isThereChild())
      moveAllChildren(&pNode->Children, pDeletionList);
    pNode->~CTreeNode<Type>();
  }
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstPreOrderIterator
  CTree<Type>::beginPreOrder() const {
  return CConstPreOrderIterator(this, getRootPtr());
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstPreOrderIterator
  CTree<Type>::endPreOrder() const {
  return CConstPreOrderIterator(this, nullptr);
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstPreOrderIterator
  CTree<Type>::cbeginPreOrder() const {
  return beginPreOrder();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstPreOrderIterator
  CTree<Type>::cendPreOrder() const {
  return endPreOrder();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CPreOrderIterator
  CTree<Type>::beginPreOrder() {
  return CPreOrderIterator(this, getRootPtr());
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CPreOrderIterator
  CTree<Type>::endPreOrder() {
  return CPreOrderIterator(this, nullptr);
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstLastSonIterator
  CTree<Type>::beginLastSon() const {
  return CConstLastSonIterator(this, getRootPtr());
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstLastSonIterator
  CTree<Type>::endLastSon() const {
  return CConstLastSonIterator(this, nullptr);
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstLastSonIterator
  CTree<Type>::cbeginLastSon() const {
  return beginLastSon();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CConstLastSonIterator
  CTree<Type>::cendLastSon() const {
  return endLastSon();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CLastSonIterator
  CTree<Type>::beginLastSon() {
  return CLastSonIterator(this, getRootPtr());
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::CLastSonIterator
  CTree<Type>::endLastSon() {
  return CLastSonIterator(this, nullptr);
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::const_iterator
  CTree<Type>::begin() const {
  return beginPreOrder();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::const_iterator
  CTree<Type>::end() const {
  return endPreOrder();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::const_iterator
  CTree<Type>::cbegin() const {
  return begin();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::const_iterator
  CTree<Type>::cend() const {
  return end();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::iterator
  CTree<Type>::begin() {
  return beginPreOrder();
}
// ---------------------------------------------------------------------------

template<class Type>
typename CTree<Type>::iterator
  CTree<Type>::end() {
  return endPreOrder();
}
// ---------------------------------------------------------------------------
// Definition of CBaseIterator
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
CTree<Type>::CBaseIterator<TIteratorDefines>::CBaseIterator()
  : pHost(nullptr),
    pCurrent(nullptr) {
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    CBaseIterator(CHostTreePtr HostTree,
                  const CIteratorNodePtr& CurrentPtr)
  : pHost(HostTree),
    pCurrent(CurrentPtr) {
}

// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    CBaseIterator(const CBaseIterator& other)
  : pHost(other.pHost),
    pCurrent(other.pCurrent) {
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    CBaseIterator(CBaseIterator&& other)
  : pHost(other.pHost),
    pCurrent(other.pCurrent) {
  other.pHost = nullptr;
  other.pCurrent = nullptr;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
typename CTree<Type>::
  template CBaseIterator<TIteratorDefines>&
CTree<Type>::
  CBaseIterator<TIteratorDefines>::operator=(const CBaseIterator& other) {
  return *this = CBaseIterator(other);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
typename CTree<Type>::
  template CBaseIterator<TIteratorDefines>&
CTree<Type>::
  CBaseIterator<TIteratorDefines>::operator=(CBaseIterator&& other) {
  pHost = other.pHost;
  pCurrent = other.pCurrent;
  other.pCurrent = nullptr;
  other.pHost = nullptr;
  return *this;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
template<class TOtherIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    operator==(const CBaseIterator<TOtherIteratorDefines>& Iterator) const {
  return pCurrent == Iterator.pCurrent;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
template<class TOtherIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    operator!=(const CBaseIterator<TOtherIteratorDefines>& Iterator) const {
  return !(*this == Iterator);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    isDefined() const {
  return pCurrent != nullptr;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    isRoot() const {
  if (!isDefined())
    return false;
  return pCurrent->isRoot();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    isLeaf() const {
  if (!isDefined())
    return false;
  return pCurrent->isLeaf();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    isThereParent() const {
  // this means the end iterator does not have a parent
  if (!isDefined())
    return false;
  return pCurrent->isThereParent();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    isThereChild() const {
  if (!isDefined())
    return false;
  return pCurrent->isThereChild();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    isThereNextSibling() const {
  if (!isDefined())
    return false;
  return pCurrent->isThereNextSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
bool
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    isTherePreviousSibling() const {
  if (!isDefined())
    return false;
  return pCurrent->isTherePreviousSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
size_t
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    getNumberOfChildren() const {
  if (!isDefined())
    return 0;
  return pCurrent->getNumberOfChildren();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
size_t
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    getSizeOfSubTree() const {
  if (!isDefined())
    return 0;
  return pCurrent->getSizeOfSubTree();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
size_t
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    getNumberOfSiblings() const {
  if (!isDefined())
    return 0;
  return pCurrent->getNumberOfSiblings();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
size_t
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    getLengthOfSubTree() const {
  if (!isDefined())
    return 0;
  return pCurrent->getLengthOfSubTree();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
size_t
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    getNumberOfLeaves() const {
  if (!isDefined())
    return 0;
  return pCurrent->getNumberOfLeaves();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
size_t
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    getDistanceToRoot() const {
  if (isDefined())
    return pCurrent->getDistanceToRoot();
  size_t distance = 0;
  for ( auto index = pHost->cbeginLastSon();
        index != pHost->cendLastSon();
        ++index)
    ++distance;
  return distance;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    setToParent() {
  // TO DO
  // This must work for the end iterator!
  // this means the end iterator will assert if we set it to the parent
  assert(isDefined());
  pCurrent = pCurrent->Parent;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    setToFirstChild() {
  assert(isDefined());
  // this means
  // we assert if attempt to set to the end iterator via this operation
  assert(isThereChild());
  pCurrent = pCurrent->getFirstChild();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    setToLastChild() {
  assert(isDefined());
  // this means
  // we assert if attempt to set to the end iterator via this operation
  assert(isThereChild());
  pCurrent = pCurrent->getLastChild();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    setToNextSibling() {
  assert(isDefined());
  assert(isThereNextSibling());
  pCurrent = pCurrent->getNextSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    setToPreviousSibling() {
  assert(isDefined());
  assert(isTherePreviousSibling());
  pCurrent = pCurrent->getPreviousSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CBaseIterator<TIteratorDefines>::
    addLastChild(const Type& NodeData) {
  pCurrent->addLastChild(NodeData);
}
// ---------------------------------------------------------------------------
// Definition of CDataReference
// ---------------------------------------------------------------------------

template<class Type>
template<class TBaseIterator>
template<class TOtherBaseIterator>
CTree<Type>::
  template
        CDataReference<TBaseIterator>::
          CDataReference(const CDataReference<TOtherBaseIterator>& other)
            : CBase(other.pHost, other.pCurrent) {
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TBaseIterator>
typename
CTree<Type>::
  template
    CDataReference<TBaseIterator>::
      reference
CTree<Type>::
  CDataReference<TBaseIterator>::
    operator*() const {
  return CBase::pCurrent->Data;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TBaseIterator>
typename
CTree<Type>::
  template
    CDataReference<TBaseIterator>::
      pointer
CTree<Type>::
  CDataReference<TBaseIterator>::
    operator->() const {
  return &(CBase::pCurrent->Data);
}
// ---------------------------------------------------------------------------
// Definition of CNodeReference
// ---------------------------------------------------------------------------

template<class Type>
template<class TBaseIterator>
CTree<Type>::
  CNodeReference<TBaseIterator>::
    CNodeReference(const CDataReference<TBaseIterator>& other)
  : CBase(other.pHost, other.pCurrent) {
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TBaseIterator>
typename
CTree<Type>::
  template
    CNodeReference<TBaseIterator>::
      CMyNodeRef
CTree<Type>::
  CNodeReference<TBaseIterator>::
    operator*() const {
  return *(CBase::pCurrent);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TBaseIterator>
typename
CTree<Type>::
  template
    CNodeReference<TBaseIterator>::
      CIteratorNodePtr
CTree<Type>::
  CNodeReference<TBaseIterator>::
    operator->() const {
  return CBase::pCurrent;
}
// ---------------------------------------------------------------------------
// Definition of CPreOrderLogic
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
void
CTree<Type>::
  CPreOrderLogic<TIteratorWithDereferencing>::
    setToNext() {
  assert(CBase::isDefined());
  CBase::pCurrent = CBase::pCurrent->getNextPreOrderNode();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
void
CTree<Type>::
  CPreOrderLogic<TIteratorWithDereferencing>::
    setToPrevious() {
  assert(CBase::pHost != nullptr);
  if (CBase::isDefined())
    CBase::pCurrent = CBase::pCurrent->getPreviousPreOrderNode();
  else
    CBase::pCurrent = CBase::pHost->getRootPtr()->getPreOrderLastNode();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CPreOrderLogic<TIteratorWithDereferencing>::
    operator<(const CPreOrderLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  //if (!CBase::isDefined() && !other.isDefined())
  //  return false;
  if (!CBase::isDefined())
    return false;
  if (!other.isDefined())
    return true;
  return isPreOrderLess(*CBase::pCurrent, *other.pCurrent);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CPreOrderLogic<TIteratorWithDereferencing>::
    operator<=(const CPreOrderLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  return !(other < *this);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CPreOrderLogic<TIteratorWithDereferencing>::
    operator>(const CPreOrderLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  return other < *this;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CPreOrderLogic<TIteratorWithDereferencing>::
    operator>=(const CPreOrderLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  return !(*this < other);
}
// ---------------------------------------------------------------------------
// Definition of CLastSonLogic
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CLastSonLogic<TIteratorDefines>::
    setToNext() {
  assert(CBase::isDefined());
  if (CBase::isThereChild())
    CBase::pCurrent = CBase::pCurrent->getLastChild();
  else
    CBase::pCurrent = nullptr;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CLastSonLogic<TIteratorDefines>::
    setToPrevious() {
  assert(CBase::pHost != nullptr);
  if (CBase::isDefined())
    CBase::pCurrent = CBase::pCurrent->Parent;
  else
    CBase::pCurrent = CBase::pHost->getRootPtr()->getPreOrderLastNode();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CLastSonLogic<TIteratorDefines>::
    operator<(const CLastSonLogic<
                          TOtherIteratorWithDereferencing>& other) const {
  // This if statements are redundant but speed up the comparison
  //if (!CBase::isDefined() && !other.isDefined())
  //  return false;
  if (!CBase::isDefined())
    return false;
  if (!other.isDefined())
    return true;
  return CBase::getDistanceToRoot() < other.getDistanceToRoot();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CLastSonLogic<TIteratorDefines>::
    operator<=(const CLastSonLogic<
                          TOtherIteratorWithDereferencing>& other) const {
  return !(other < *this);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CLastSonLogic<TIteratorDefines>::
    operator>(const CLastSonLogic<
                          TOtherIteratorWithDereferencing>& other) const {
  return other < *this;
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CLastSonLogic<TIteratorDefines>::
    operator>=(const CLastSonLogic<
                          TOtherIteratorWithDereferencing>& other) const {
  return !(*this < other);
}
// ---------------------------------------------------------------------------
// Definition of CSiblingLogic
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CSiblingLogic<TIteratorDefines>::
    setToNext() {
  assert(CBase::isDefined());
  CBase::pCurrent = CBase::pCurrent->getNextSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorDefines>
void
CTree<Type>::
  CSiblingLogic<TIteratorDefines>::
    setToPrevious() {
  assert(CBase::isDefined());
  CBase::pCurrent = CBase::pCurrent->getPreviousSibling();
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CSiblingLogic<TIteratorWithDereferencing>::
    operator<(const CSiblingLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  return isPreOrderLess(*CBase::pCurrent, *other.pCurrent);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CSiblingLogic<TIteratorWithDereferencing>::
    operator<=(const CSiblingLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  return !(other < *this);//isPreOrderLessOrEqual(*CBase::pCurrent, *other.pCurrent);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CSiblingLogic<TIteratorWithDereferencing>::
    operator>(const CSiblingLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  return other < *this; //isPreOrderGreater(*CBase::pCurrent, *other.pCurrent);
}
// ---------------------------------------------------------------------------

template<class Type>
template<class TIteratorWithDereferencing>
template<class TOtherIteratorWithDereferencing>
bool
CTree<Type>::
  CSiblingLogic<TIteratorWithDereferencing>::
    operator>=(const CSiblingLogic<
                        TOtherIteratorWithDereferencing>& other) const {
  return !(*this < other);//isPreOrderGreaterOrEqual(*CBase::pCurrent, *other.pCurrent);
}
// ---------------------------------------------------------------------------
// Definition of CIteratorTemplate
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
template <template<class> class TOtherReferenceLogic,
          template<class> class TOtherTravellingLogic,
          class TOtherIteratorDefines>
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
        CIteratorTemplate(
              const CIteratorTemplate<TOtherReferenceLogic,
                                      TOtherTravellingLogic,
                                      TOtherIteratorDefines>& other)
          : CBase(other.pHost, other.pCurrent) {
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
        CIteratorTemplate(CHostTreePtr HostTree,
                          const CIteratorNodePtr& CurrentPtr)
          : CBase(HostTree, CurrentPtr) {
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>&
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        operator++() {
  CBase::setToNext();
  return *this;
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        operator++(int) {
  CIteratorTemplate temp = *this;
  ++*this;
  return temp;
}
template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>&
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
      operator+=(difference_type Difference) {
  if (Difference < 0)
    return *this -= -Difference;
  while (Difference > 0) {
    ++*this;
    --Difference;
  }
  return *this;
}

// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>&
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        operator--() {
  CBase::setToPrevious();
  return *this;
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        operator--(int) {
  CIteratorTemplate temp = *this;
  --*this;
  return temp;
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>&
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
      operator-=(difference_type Difference) {
  if (Difference < 0)
    return *this += -Difference;
  while (Difference > 0) {
    --*this;
    --Difference;
  }
  return *this;
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
template <template<class> class TOtherReferenceLogic,
          class TOtherIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        difference_type
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
            operator-(const CIteratorTemplate<
                                  TOtherReferenceLogic,
                                  TTravellingLogic,
                                  TOtherIteratorDefines>& other) const {
  if (*this > other)
    return  subtractSmaller(other);
  return -other.subtractSmaller(*this);
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
template <template<class> class TOtherReferenceLogic,
          class TOtherIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        difference_type
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
            subtractSmaller(const CIteratorTemplate<
                                  TOtherReferenceLogic,
                                  TTravellingLogic,
                                  TOtherIteratorDefines>& smaller) const {
  difference_type difference = 0;
  for (auto Current = smaller; Current != *this; ++Current)
    ++difference;
  return difference;
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        CChildIterator
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        FirstChild() const{
  return CChildIterator(CBase::pHost, CBase::pCurrent->getFirstChild());
}
// ---------------------------------------------------------------------------

template<class Type>
template <template<class> class TReferenceLogic,
          template<class> class TTravellingLogic,
          class TIteratorDefines>
typename
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        CChildIterator
CTree<Type>::
  template
    CIteratorTemplate<TReferenceLogic,
                      TTravellingLogic,
                      TIteratorDefines>::
                        LastChild() const{
  return CChildIterator(CBase::pHost, CBase::pCurrent->getLastChild());
}
// ---------------------------------------------------------------------------
} // NSLibrary
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
