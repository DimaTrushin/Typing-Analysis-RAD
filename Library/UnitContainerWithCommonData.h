//---------------------------------------------------------------------------

#ifndef UnitContainerWithCommonDataH
#define UnitContainerWithCommonDataH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <deque>
#include <list>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Declaration of TDequeBase
//---------------------------------------------------------------------------

template<class ElementType>
class TDequeBase : public std::deque<ElementType> {
public:
protected:
  ~TDequeBase() = default;
};
//---------------------------------------------------------------------------
// Declaration of TListBase
//---------------------------------------------------------------------------

template<class ElementType>
class TListBase : public std::list<ElementType> {
public:
protected:
  ~TListBase() = default;
};
//---------------------------------------------------------------------------
// Declaration of CContainerWithCommonDataBase
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TBaseContainer = TDequeBase>
class CContainerWithCommonDataBase : protected TBaseContainer<ElementType> {
public:
  using BaseContainer = TBaseContainer<ElementType>;
  using typename BaseContainer::const_iterator;
  using typename BaseContainer::iterator;

  CContainerWithCommonDataBase(const CommonDataType& newCommonData);

  using BaseContainer::push_back;
  using BaseContainer::pop_back;
  using BaseContainer::back;
  using BaseContainer::push_front;
  using BaseContainer::front;
  using BaseContainer::pop_front;
  using BaseContainer::empty;
  using BaseContainer::size;
  using BaseContainer::begin;
  using BaseContainer::end;
  using BaseContainer::cbegin;
  using BaseContainer::cend;

  CommonDataType& common_data();
  const CommonDataType& common_data() const;

  void clear_elements();
  bool isCommonDataTheSame(const CommonDataType& newCommonData) const;
  protected:
  CommonDataType CommonData;

};
//---------------------------------------------------------------------------
// Declaration of CElementWithCommonData
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType>
struct CElementWithCommonData {
  CElementWithCommonData( const ElementType& newElement,
                          const CommonDataType& newCommonData);
  ElementType Element;
  CommonDataType CommonData;
};
//---------------------------------------------------------------------------
// Declaration of CEmptyInterface
//---------------------------------------------------------------------------

template<class TIteratorBase>
class CEmptyInterface : public TIteratorBase {
  using CBase = TIteratorBase;
public:
  using CBase::CBase;
};
//---------------------------------------------------------------------------
// Declaration of CContainerWithCommonData
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface = CEmptyInterface,
          template<class, class> class TElementWithCommonData =
                                                      CElementWithCommonData,
          template<class> class TInnerBase = TDequeBase,
          template<class> class TOuterBase = TDequeBase>
class CContainerWithCommonData :
        protected TOuterBase<
                      CContainerWithCommonDataBase< ElementType,
                                                    CommonDataType,
                                                    TInnerBase>> {
public:
  using InnerBaseContainer = CContainerWithCommonDataBase<ElementType,
                                                          CommonDataType,
                                                          TInnerBase>;
  using OuterBaseContainer =
          TOuterBase<
            CContainerWithCommonDataBase<
                                    ElementType,
                                    CommonDataType,
                                    TInnerBase>>;
  using BaseContainer = OuterBaseContainer;

  using BaseContainer::clear;
  using BaseContainer::empty;

  void push_back( const ElementType& Element,
                  const CommonDataType& CommonData);
  void pop_back();
  TElementWithCommonData< const ElementType&,
                          const CommonDataType& > back() const;
  TElementWithCommonData< ElementType&,
                          const CommonDataType& > back();

  void push_front(const ElementType& Element,
                  const CommonDataType& CommonData);
  void pop_front();
  TElementWithCommonData< const ElementType&,
                          const CommonDataType&> front() const;
  TElementWithCommonData< ElementType&,
                          const CommonDataType&> front();

  size_t size() const;
  size_t segments() const;
private:
  bool needNewInnerContainerForPushBack(
                                  const CommonDataType& CommonData) const;
  bool needNewInnerContainerForPushFront(
                                  const CommonDataType& CommonData) const;
protected:
  //---------------------------------------------------------------------------
  // Declaration of CConstIteratorTypeDefinitions
  //---------------------------------------------------------------------------

  class CConstIteratorTypeDefinitions {
  public:
    using CElementType = const ElementType;
    using CCommonDataType = const CommonDataType;
    using CDifferenceType = int;
    using CElementReference = CElementType&;
    using CElementPointer = CElementType*;
    using CCommonDataReference = CCommonDataType&;
    using CCommonDataPointer = CCommonDataType*;
    using CInnerIterator = typename InnerBaseContainer::const_iterator;
    using COuterIterator = typename OuterBaseContainer::const_iterator;
    using CDataReferencePair = TElementWithCommonData<CElementReference,
                                                      CCommonDataReference>;
  };
  //---------------------------------------------------------------------------
  // Declaration of CIteratorTypeDefinitions
  //---------------------------------------------------------------------------

  class CIteratorTypeDefinitions {
  public:
    using CElementType = ElementType;
    using CCommonDataType = const CommonDataType;
    using CDifferenceType = int;
    using CElementReference = CElementType&;
    using CElementPointer = CElementType*;
    using CCommonDataReference = CCommonDataType&;
    using CCommonDataPointer = CCommonDataType*;
    using CInnerIterator = typename InnerBaseContainer::iterator;
    using COuterIterator = typename OuterBaseContainer::iterator;
    using CDataReferencePair = TElementWithCommonData<CElementReference,
                                                      CCommonDataReference>;
  };
  //---------------------------------------------------------------------------
  // Declaration of CIteratorBase
  //---------------------------------------------------------------------------
  template<class TIteratorTypeDefinitions>
  class CIteratorBase : public TIteratorTypeDefinitions {
    using CBase = TIteratorTypeDefinitions;
  public:
    using CElementType = typename CBase::CElementType;
    using CCommonDataType = typename CBase::CCommonDataType;
    using CDifferenceType = typename CBase::CDifferenceType;
    using CElementReference = typename CBase::CElementReference;
    using CElementPointer = typename CBase::CElementPointer;
    using CCommonDataReference = typename CBase::CCommonDataReference;
    using CCommonDataPointer = typename CBase::CCommonDataPointer;
    using CInnerIterator = typename CBase::CInnerIterator;
    using COuterIterator = typename CBase::COuterIterator;
    using CDataReferencePair = typename CBase::CDataReferencePair;
  private:
    template<class TOtherIteratorTypeDefinitions>
    friend class CIteratorBase;
  public:
    CIteratorBase();
    CIteratorBase(const OuterBaseContainer* newHost,
                  COuterIterator newOuterIterator,
                  CInnerIterator newInnerIterator);
    CIteratorBase(const CIteratorBase<CIteratorTypeDefinitions>& other);

    CElementReference operator*() const;
    CElementPointer operator->() const;
  protected:
    void setToNext();
    void setToPrevious();
    void addOffset(CDifferenceType Offset);
    void subtractOffset(CDifferenceType Offset);
    template<class TOtherIteratorTypeDefinitions>
    CDifferenceType subtractIterator(
            const  CIteratorBase<TOtherIteratorTypeDefinitions>& other) const;
    CElementReference getElementAtOffset(const CDifferenceType& Offset) const;
  public:
    template<class TOtherIteratorTypeDefinitions>
    bool operator==(const CIteratorBase<
                                TOtherIteratorTypeDefinitions>& other) const;
    template<class TOtherIteratorTypeDefinitions>
    bool operator!=(const CIteratorBase<
                                TOtherIteratorTypeDefinitions>& other) const;
    template<class TOtherIteratorTypeDefinitions>
    bool operator<(const CIteratorBase<
                                TOtherIteratorTypeDefinitions>& other) const;
    template<class TOtherIteratorTypeDefinitions>
    bool operator>(const CIteratorBase<
                                TOtherIteratorTypeDefinitions>& other) const;
    template<class TOtherIteratorTypeDefinitions>
    bool operator<=(const CIteratorBase<
                                TOtherIteratorTypeDefinitions>& other) const;
    template<class TOtherIteratorTypeDefinitions>
    bool operator>=(const CIteratorBase<
                                TOtherIteratorTypeDefinitions>& other) const;

    CCommonDataReference getCommonData() const;
  private:
    template<class TOtherIteratorTypeDefinitions>
    CDifferenceType subtractSmaller(
          const CIteratorBase<
                  TOtherIteratorTypeDefinitions>& smallerIterator) const;

  private:
    const OuterBaseContainer* pHost;
    COuterIterator outerIterator;
    CInnerIterator innerIterator;
  };
  //---------------------------------------------------------------------------
  // Declaration of CIteratorTemplate
  //---------------------------------------------------------------------------

  template< class TIteratorTypeDefinitions>
  class CIteratorTemplate :
    public TIteratorInterface<CIteratorBase<TIteratorTypeDefinitions>> {
    using CBase = TIteratorInterface<CIteratorBase<TIteratorTypeDefinitions>>;
  public:
    using CBase::CBase;
    using CElementType = typename CBase::CElementType;
    using CCommonDataType = typename CBase::CCommonDataType;
    using CDifferenceType = typename CBase::CDifferenceType;
    using CElementReference = typename CBase::CElementReference;
    using CElementPointer = typename CBase::CElementPointer;
    using CCommonDataReference = typename CBase::CCommonDataReference;
    using CCommonDataPointer = typename CBase::CCommonDataPointer;
    using CInnerIterator = typename CBase::CInnerIterator;
    using COuterIterator = typename CBase::COuterIterator;
    using CDataReferencePair = typename CBase::CDataReferencePair;

    CIteratorTemplate& operator++();
    CIteratorTemplate operator++(int);
    CIteratorTemplate& operator--();
    CIteratorTemplate operator--(int);
    CIteratorTemplate& operator+=(CDifferenceType Offset);
    CIteratorTemplate operator+(CDifferenceType Offset) const;
    CIteratorTemplate& operator-=(CDifferenceType Offset);
    CIteratorTemplate operator-(CDifferenceType Offset) const;
    template< class TOtherIteratorTypeDefinitions>
    CDifferenceType
      operator-(const CIteratorTemplate<
                        TOtherIteratorTypeDefinitions>& other) const;
    CElementReference operator[](CDifferenceType Offset) const;
  };
public:
  //---------------------------------------------------------------------------
  // Declaration of const_iterator
  //---------------------------------------------------------------------------

  using const_iterator = CIteratorTemplate<CConstIteratorTypeDefinitions>;
  //---------------------------------------------------------------------------
  // Declaration of iterator
  //---------------------------------------------------------------------------

  using iterator = CIteratorTemplate<CIteratorTypeDefinitions>;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CContainerWithCommonDataBase
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class BaseContainer>
CContainerWithCommonDataBase<ElementType, CommonDataType, BaseContainer>::
    CContainerWithCommonDataBase(const CommonDataType& newCommonData)
  : CommonData(newCommonData) {
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class BaseContainer>
CommonDataType&
  CContainerWithCommonDataBase<ElementType, CommonDataType, BaseContainer>::
    common_data() {
  return CommonData;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class BaseContainer>
const CommonDataType&
  CContainerWithCommonDataBase<ElementType, CommonDataType, BaseContainer>::
    common_data() const {
  return CommonData;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class BaseContainer>
void
  CContainerWithCommonDataBase<ElementType, CommonDataType, BaseContainer>::
    clear_elements() {
  BaseContainer::clear();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class BaseContainer>
bool
  CContainerWithCommonDataBase<ElementType, CommonDataType, BaseContainer>::
    isCommonDataTheSame(const CommonDataType& newCommonData) const {
  return CommonData == newCommonData;
}
//---------------------------------------------------------------------------
// Definition of CElementWithCommonData
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType>
CElementWithCommonData<ElementType, CommonDataType>::
  CElementWithCommonData( const ElementType& newElement,
                          const CommonDataType& newCommonData)
  : Element(newElement),
    CommonData(newCommonData) {
}
//---------------------------------------------------------------------------
// Definition of CContainerWithCommonData
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
void
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    push_back(const ElementType& Element,
              const CommonDataType& CommonData) {
  if (needNewInnerContainerForPushBack(CommonData))
    BaseContainer::push_back(CommonData);
  BaseContainer::back().push_back(Element);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
void
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    pop_back() {
  BaseContainer::back().pop_back();
  if (BaseContainer::back().empty())
    BaseContainer::pop_back();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
TElementWithCommonData< const ElementType&,
                        const CommonDataType&>
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    back() const {
  const ElementType& Element = BaseContainer::back().back();
  const CommonDataType& CommonData = BaseContainer::back().common_data();
  return TElementWithCommonData<const ElementType&,
                                const CommonDataType&>(Element, CommonData);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
TElementWithCommonData< ElementType&,
                        const CommonDataType&>
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    back() {
  ElementType& Element = BaseContainer::back().back();
  const CommonDataType& CommonData = BaseContainer::back().common_data();
  return TElementWithCommonData<ElementType&,
                                const CommonDataType&>(Element, CommonData);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
void
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    push_front( const ElementType& Element,
                const CommonDataType& CommonData) {
  if (needNewInnerContainerForPushFront(CommonData))
    BaseContainer::push_front(CommonData);
  BaseContainer::front().push_front(Element);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
void
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    pop_front() {
  BaseContainer::front().pop_front();
  if (BaseContainer::front().empty())
    BaseContainer::pop_front();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
TElementWithCommonData< const ElementType&,
                        const CommonDataType&>
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    front() const {
  const ElementType& Element = BaseContainer::front().front();
  const CommonDataType& CommonData = BaseContainer::front().common_data();
  return TElementWithCommonData<const ElementType&,
                                const CommonDataType&>(Element, CommonData);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
TElementWithCommonData< ElementType&,
                        const CommonDataType&>
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    front() {
  ElementType& Element = BaseContainer::front().front();
  const CommonDataType& CommonData = BaseContainer::front().common_data();
  return TElementWithCommonData<ElementType&,
                                const CommonDataType&>(Element, CommonData);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
size_t
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    size() const {
  size_t result = 0;
  for(const auto& innerContainer : *(BaseContainer*)this)
    result += innerContainer.size();
  return result;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
size_t
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    segments() const {
  return BaseContainer::size();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
bool
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    needNewInnerContainerForPushBack(
                                  const CommonDataType& CommonData) const {
  if (BaseContainer::empty())
    return true;
  if(BaseContainer::back().isCommonDataTheSame(CommonData))
    return false;
  return true;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
bool
  CContainerWithCommonData< ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
    needNewInnerContainerForPushFront(
                                  const CommonDataType& CommonData) const {
  if(BaseContainer::empty())
    return true;
  if(BaseContainer::front().isCommonDataTheSame(CommonData))
    return false;
  return true;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
typename CContainerWithCommonData<
                            ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
                              iterator
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            begin() {
  if (!empty())
    return iterator(this,
                    BaseContainer::begin(),
                    BaseContainer::front().begin());
  return end();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
typename CContainerWithCommonData<
                            ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
                              iterator
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            end() {
  return iterator(this,
                  BaseContainer::end(),
                  typename iterator::CInnerIterator());
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
typename CContainerWithCommonData<
                            ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
                              const_iterator
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            begin() const {
  if (!empty())
    return const_iterator(this,
                          BaseContainer::cbegin(),
                          BaseContainer::front().cbegin());
  return cend();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
typename CContainerWithCommonData<
                            ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
                              const_iterator
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            end() const {
  return const_iterator(this,
                        BaseContainer::cend(),
                        typename const_iterator::CInnerIterator());
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
typename CContainerWithCommonData<
                            ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
                              const_iterator
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            cbegin() const {
  return begin();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
typename CContainerWithCommonData<
                            ElementType,
                            CommonDataType,
                            TIteratorInterface,
                            TElementWithCommonData,
                            TInnerBase,
                            TOuterBase>::
                              const_iterator
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            cend() const {
  return end();
}
//---------------------------------------------------------------------------
// Definition of CIteratorBase
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              CIteratorBase()
  : pHost(nullptr) {
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              CIteratorBase (
                                const OuterBaseContainer* newHost,
                                COuterIterator newOuterIterator,
                                CInnerIterator newInnerIterator)
    : pHost(newHost),
      outerIterator(std::move(newOuterIterator)),
      innerIterator(std::move(newInnerIterator)) {
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
  CIteratorBase(const CContainerWithCommonData<
                          ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<CIteratorTypeDefinitions>& other)
  : pHost(other.pHost),
    outerIterator(other.outerIterator),
    innerIterator(other.innerIterator) {
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorBase<TIteratorTypeDefinitions>::
                CElementReference
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              operator*() const {
  return (*innerIterator);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorBase<TIteratorTypeDefinitions>::
                CElementPointer
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              operator->() const {
  return (&(*innerIterator));
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
void
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              setToNext() {
  ++innerIterator;
  if (innerIterator == outerIterator->end()) {
    ++outerIterator;
    if (outerIterator != pHost->end())
      innerIterator = outerIterator->begin();
  }
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
void
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              setToPrevious() {
  if (outerIterator == pHost->end() ||
      innerIterator == outerIterator->begin()) {
    --outerIterator;
    innerIterator = outerIterator->end();
  }
  --innerIterator;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
void
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              addOffset(CDifferenceType Offset) {
  if (Offset < 0) {
    subtractOffset(-Offset);
    return;
  }

  CDifferenceType untilInnerEnd = outerIterator->end() - innerIterator;
  if (untilInnerEnd > Offset) {
    innerIterator += Offset;
    return;
  }

  while(untilInnerEnd <= Offset) {
    ++outerIterator;
    Offset -= untilInnerEnd;
    if (outerIterator == pHost->end() && Offset == 0)
      return;
    untilInnerEnd = outerIterator->size();
  }

  innerIterator = outerIterator->begin();
  innerIterator += Offset;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
void
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              subtractOffset(CDifferenceType Offset) {
  if (Offset < 0) {
    addOffset(-Offset);
    return;
  }

  if (outerIterator == pHost->end()) {
    setToPrevious();
    --Offset;
  }

  CDifferenceType untilInnerBegin = innerIterator - outerIterator->begin();
  if (untilInnerBegin >= Offset)  {
    innerIterator -= Offset;
    return;
  }

  while (untilInnerBegin < Offset) {
    --outerIterator;
    Offset -= untilInnerBegin;
    untilInnerBegin = outerIterator->size();
  }

  innerIterator = outerIterator->end();
  innerIterator -= Offset;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorBase<TIteratorTypeDefinitions>::
                CDifferenceType
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                subtractIterator(
                    const  CIteratorBase<
                              TOtherIteratorTypeDefinitions>& other) const {
  if (*this > other)
    return subtractSmaller(other);
  return -other.subtractSmaller(*this);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorBase<TIteratorTypeDefinitions>::
                CElementReference
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                    getElementAtOffset(const CDifferenceType& Offset) const {
  CIteratorBase temp(*this);
  temp.addOffset(Offset);
  return (*temp);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
bool
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
      operator==(const CIteratorBase<
                            TOtherIteratorTypeDefinitions>& other) const {
  if (outerIterator != other.outerIterator)
    return false;
  if (outerIterator == pHost->end())
    return true;
  if (innerIterator == other.innerIterator)
    return true;
  return false;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
bool
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
      operator!=(const CIteratorBase<
                            TOtherIteratorTypeDefinitions>& other) const {
  return !(*this == other);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
bool
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
      operator<(const CIteratorBase<
                            TOtherIteratorTypeDefinitions>& other) const {
  if (outerIterator < other.outerIterator)
    return true;
  if (outerIterator > other.outerIterator)
    return false;
  if (outerIterator == pHost->end())
    return false;
  return innerIterator < other.innerIterator;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
bool
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
      operator>(const CIteratorBase<
                            TOtherIteratorTypeDefinitions>& other) const {
  return other < *this;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
bool
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
      operator<=(const CIteratorBase<
                            TOtherIteratorTypeDefinitions>& other) const {
  return !(*this > other);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
bool
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
      operator>=(const CIteratorBase<
                            TOtherIteratorTypeDefinitions>& other) const {
  return !(*this < other);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorBase<TIteratorTypeDefinitions>::
                CCommonDataReference
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
                              getCommonData() const {
  return outerIterator->common_data();
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template<class TIteratorTypeDefinitions>
template<class TOtherIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorBase<TIteratorTypeDefinitions>::
                CDifferenceType
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorBase<TIteratorTypeDefinitions>::
  subtractSmaller(
        const CIteratorBase<
                    TOtherIteratorTypeDefinitions>& smallerIterator) const {
  if (smallerIterator.outerIterator == outerIterator) {
    if (smallerIterator.outerIterator == smallerIterator.pHost->end())
      return 0;
    return innerIterator - smallerIterator.innerIterator;
  }
  auto currentPosition = smallerIterator;
  CDifferenceType Offset =  currentPosition.outerIterator->end() -
                            currentPosition.innerIterator;
  ++(currentPosition.outerIterator);
  while (currentPosition.outerIterator != outerIterator) {
    Offset += currentPosition.outerIterator->size();
    ++(currentPosition.outerIterator);
  }
  if (currentPosition.outerIterator != currentPosition.pHost->end())
    Offset += innerIterator - currentPosition.outerIterator->begin();
  return Offset;
}
//---------------------------------------------------------------------------
// Definition of CIteratorTemplate
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate< TIteratorTypeDefinitions>::
                CIteratorTemplate&
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                                operator++() {
  CBase::setToNext();
  return *this;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate< TIteratorTypeDefinitions>::
                CIteratorTemplate
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                                operator++(int) {
  CIteratorTemplate temp(*this);
  ++(*this);
  return temp;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate<TIteratorTypeDefinitions>::
                CIteratorTemplate&
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                                operator--() {
  CBase::setToPrevious();
  return *this;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate< TIteratorTypeDefinitions>::
                CIteratorTemplate
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                                operator--(int) {
  CIteratorTemplate temp(*this);
  --(*this);
  return temp;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate<TIteratorTypeDefinitions>::
                CIteratorTemplate&
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                        operator+=(CDifferenceType Offset) {
  addOffset(Offset);
  return *this;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate<TIteratorTypeDefinitions>::
                CIteratorTemplate
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                    operator+(CDifferenceType Offset) const {
  CIteratorTemplate temp(*this);
  return temp += Offset;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate<TIteratorTypeDefinitions>::
                CIteratorTemplate&
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                      operator-=(CDifferenceType Offset) {
  subtractOffset(Offset);
  return *this;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate<TIteratorTypeDefinitions>::
                CIteratorTemplate
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                  operator-(CDifferenceType Offset) const {
  CIteratorTemplate temp(*this);
  return temp -= Offset;
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
template< class TOtherIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate<TIteratorTypeDefinitions>::
                CDifferenceType
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
  operator-(const CIteratorTemplate<
                          TOtherIteratorTypeDefinitions>& other) const {
  return CBase::subtractIterator(other);
}
//---------------------------------------------------------------------------

template< class ElementType,
          class CommonDataType,
          template<class> class TIteratorInterface,
          template<class, class> class TElementWithCommonData,
          template<class> class TInnerBase,
          template<class> class TOuterBase>
template< class TIteratorTypeDefinitions>
typename CContainerWithCommonData<
              ElementType,
              CommonDataType,
              TIteratorInterface,
              TElementWithCommonData,
              TInnerBase,
              TOuterBase>::
              template CIteratorTemplate<TIteratorTypeDefinitions>::
                CElementReference
CContainerWithCommonData< ElementType,
                          CommonDataType,
                          TIteratorInterface,
                          TElementWithCommonData,
                          TInnerBase,
                          TOuterBase>::
                            CIteratorTemplate<TIteratorTypeDefinitions>::
                                operator[](CDifferenceType Offset) const {
  return CBase::getElementAtOffset(Offset);
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
