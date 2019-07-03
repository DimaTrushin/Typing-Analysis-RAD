//---------------------------------------------------------------------------

#ifndef UnitLexSumH
#define UnitLexSumH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <type_traits>
#include <iterator>
#include <cassert>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CIsInt
//---------------------------------------------------------------------------

template<class Type>
class CIsInt;
//---------------------------------------------------------------------------

template<>
class CIsInt<int> {};
//---------------------------------------------------------------------------
// Declaration of CIsDifferenceTypeInt
//---------------------------------------------------------------------------

template<class TIterator>
using CIsDifferenceTypeInt =
        CIsInt<typename std::iterator_traits<TIterator>::difference_type>;
//---------------------------------------------------------------------------
// Declaration of CIsRandomAccessTag
//---------------------------------------------------------------------------

template<class TTag>
class CIsRandomAccessTag;
//---------------------------------------------------------------------------

template<>
class CIsRandomAccessTag<std::random_access_iterator_tag> {};
//---------------------------------------------------------------------------
// Declaration of CAnd
//---------------------------------------------------------------------------

template< class TFirst,
          class TSecond>
class CAnd {};
//---------------------------------------------------------------------------
// Declaration of CIsRandomAccessIterator
//---------------------------------------------------------------------------

template<class TIterator>
using CIsRandomAccessIterator =
        CIsRandomAccessTag<
            typename std::iterator_traits<TIterator>::iterator_category>;
//---------------------------------------------------------------------------
// Declaration of CLexSum
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
class CLexSum : CAnd<
                  CAnd< CIsDifferenceTypeInt<TOuterIterator>,
                        CIsDifferenceTypeInt<TInnerIterator>>,
                  CAnd< CIsRandomAccessIterator<TOuterIterator>,
                        CIsRandomAccessIterator<TInnerIterator>>> {
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
friend class CLexSum;
public:
  using difference_type = int;
  using value_type = typename std::iterator_traits<TInnerIterator>::value_type;
  using pointer = typename std::iterator_traits<TInnerIterator>::pointer;
  using reference = typename std::iterator_traits<TInnerIterator>::reference;
  using iterator_category = std::random_access_iterator_tag;

  CLexSum() = default;
  CLexSum(TOuterContainer* Host,
          TOuterIterator OuterIterator,
          TInnerIterator InnerIterator);
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  CLexSum(const CLexSum<TOtherOuterContainer,
                        TOtherOuterIterator,
                        TOtherInnerIterator>& OtherLexSum);
  CLexSum(const CLexSum&) = default;
  CLexSum(CLexSum&&) = default;
  CLexSum& operator=(const CLexSum&) = default;
  CLexSum& operator=(CLexSum&&) = default;

  reference operator*() const;
  pointer operator->() const;

  bool isHostDefined() const;
  bool isHostEmpty() const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool areHostsTheSame(const CLexSum<
                                TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool areOuterIteratorsTheSame(
                  const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool areInnerIteratorsTheSame(
                  const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;

  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool operator==(const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool operator!=(const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool operator<(const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool operator>(const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool operator<=(const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  bool operator>=(const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;

  CLexSum& operator++();
  CLexSum operator++(int);
  CLexSum& operator--();
  CLexSum operator--(int);
  CLexSum& operator+=(difference_type Offset);
  CLexSum operator+(difference_type Offset) const;
  CLexSum& operator-=(difference_type Offset);
  CLexSum operator-(difference_type Offset) const;
  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  difference_type operator-(const CLexSum<
                                TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;
  reference operator[](difference_type Offset) const;

  static CLexSum begin(TOuterContainer& Host);
  static CLexSum end(TOuterContainer& Host);
private:
  // Here I use random_access_iterator_tag
  // in the functions with Range checking
  bool isInValidState() const;
  // unsafe functions
  bool isOuterIteratorInFullRange() const;
  bool isOuterIteratorInDefinedRange() const;
  bool isInnerIteratorInFullRange() const;
  bool isInnerIteratorInDefinedRange() const;
  bool isOuterIteratorTheEnd() const;
  bool isOuterIteratorTheBegin() const;
  bool isInnerIteratorTheEnd() const;
  bool isInnerIteratorTheBegin() const;
  void invalidateOuterIterator();
  void invalidateInnerIterator();

  template< class TOtherOuterContainer,
            class TOtherOuterIterator,
            class TOtherInnerIterator>
  difference_type subtractSmaller(const CLexSum<
                                TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const;

  TOuterContainer* Host_ = nullptr;
  TOuterIterator OuterIterator_;
  TInnerIterator InnerIterator_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CLexSum
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer, TOuterIterator, TInnerIterator>::
  CLexSum(TOuterContainer* Host,
          TOuterIterator OuterIterator,
          TInnerIterator InnerIterator)
  : Host_(Host),
    OuterIterator_(std::move(OuterIterator)),
    InnerIterator_(std::move(InnerIterator)) {
  assert(isInValidState());
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
CLexSum<TOuterContainer, TOuterIterator, TInnerIterator>::
  CLexSum(const CLexSum<TOtherOuterContainer,
                        TOtherOuterIterator,
                        TOtherInnerIterator>& OtherLexSum)
  : Host_(OtherLexSum.Host_),
    OuterIterator_(OtherLexSum.OuterIterator_),
    InnerIterator_(OtherLexSum.InnerIterator_) {
  assert(isInValidState());
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
typename CLexSum< TOuterContainer,
                  TOuterIterator,
                  TInnerIterator>::reference
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator*() const {
  assert(isHostDefined() && isOuterIteratorInDefinedRange());
  return *InnerIterator_;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
typename CLexSum< TOuterContainer,
                  TOuterIterator,
                  TInnerIterator>::pointer
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator->() const {
  assert(isHostDefined() && isOuterIteratorInDefinedRange());
  return InnerIterator_.operator->();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isHostDefined() const {
  return Host_ != nullptr;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isHostEmpty() const {
  return Host_->empty();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  areHostsTheSame(const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const {
  return Host_ == Iterator.Host_;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  areOuterIteratorsTheSame(
                  const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const {
  return OuterIterator_ == Iterator.OuterIterator_;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  areInnerIteratorsTheSame(
                  const CLexSum<TOtherOuterContainer,
                                TOtherOuterIterator,
                                TOtherInnerIterator>& Iterator) const {
  return InnerIterator_ == Iterator.InnerIterator_;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  operator==(const CLexSum< TOtherOuterContainer,
                            TOtherOuterIterator,
                            TOtherInnerIterator>& Iterator) const {
  if (!areHostsTheSame(Iterator))
    return false;
  if (!isHostDefined())
    return true;
  // The Hosts are defined and the same
  // In particular, OuterIterator_ is in FullRange
  if (!areOuterIteratorsTheSame(Iterator))
    return false;
  if (isOuterIteratorTheEnd())
    return true;
  // The OuterIterators are defined and the same
  return areInnerIteratorsTheSame(Iterator);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  operator!=(const CLexSum< TOtherOuterContainer,
                            TOtherOuterIterator,
                            TOtherInnerIterator>& Iterator) const {
  return !(*this == Iterator);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  operator<(const CLexSum<TOtherOuterContainer,
                          TOtherOuterIterator,
                          TOtherInnerIterator>& Iterator) const {
  assert(areHostsTheSame(Iterator));
  // Hosts are the same
  if(!isHostDefined())
    return false;
  // Hosts are defined and the same
  // In particular OuterIterators are in the Full Range
  if (OuterIterator_ < Iterator.OuterIterator_)
    return true;
  if (OuterIterator_ > Iterator.OuterIterator_)
    return false;
  // OuterIterators are the same
  if (isOuterIteratorTheEnd())
    return false;
  return InnerIterator_ < Iterator.InnerIterator_;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  operator>(const CLexSum<TOtherOuterContainer,
                          TOtherOuterIterator,
                          TOtherInnerIterator>& Iterator) const {
  return Iterator < *this;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  operator<=(const CLexSum< TOtherOuterContainer,
                            TOtherOuterIterator,
                            TOtherInnerIterator>& Iterator) const {
  return !(*this > Iterator);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  operator>=(const CLexSum< TOtherOuterContainer,
                            TOtherOuterIterator,
                            TOtherInnerIterator>& Iterator) const {
  return !(*this < Iterator);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>&
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator++() {
  assert(isHostDefined() && !isOuterIteratorTheEnd());
  // Host is defined
  // OuterIterator_ is in Defined Range
  // InnerIterator_ is in Defined Range (by class invariant)
  ++InnerIterator_;
  if (!isInnerIteratorTheEnd())
    return (*this);
  ++OuterIterator_;
  // This avoids the problem with empty subcontainers
  while (!isOuterIteratorTheEnd() && OuterIterator_->empty())
    ++OuterIterator_;
  if (isOuterIteratorTheEnd()) {
    invalidateInnerIterator();
    return (*this);
  }
  assert(!OuterIterator_->empty());
  InnerIterator_ = OuterIterator_->begin();
  return (*this);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator++(int) {
  CLexSum Result = *this;
  ++(*this);
  return Result;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>&
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator--() {
  assert(isHostDefined() && isOuterIteratorInFullRange());
  assert(!isHostEmpty());
  // Host_ is defined and not empty
  // OuterIterator is in Full Range
  if (isOuterIteratorTheEnd() || isInnerIteratorTheBegin()) {
    --OuterIterator_;
  // This avoids the problem with empty subcontainers
    while (OuterIterator_->empty() && !isOuterIteratorTheBegin())
      --OuterIterator_;
    assert(!OuterIterator_->empty());
    // Assume that OuterIterator_ points to a non-empty subcontainer
    // this must be an invariant of the LexContainer
    InnerIterator_ = OuterIterator_->end();
  }
  // OterIterator_ is in Defined Range
  // InnerIterator_ is not the begin
  --InnerIterator_;
  return (*this);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator--(int) {
  CLexSum Result = *this;
  --(*this);
  return Result;
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>&
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator+=(difference_type Offset) {
  if (Offset < 0)
    return (*this -= -Offset);
  assert(isHostDefined() && !isOuterIteratorTheEnd());
  difference_type untilInnerEnd = OuterIterator_->end() - InnerIterator_;
  if (untilInnerEnd > Offset) {
    InnerIterator_ += Offset;
    return (*this);
  }
  while(untilInnerEnd <= Offset) {
    ++OuterIterator_;
    Offset -= untilInnerEnd;
    if (isOuterIteratorTheEnd()) {
      assert(Offset == 0);
      invalidateInnerIterator();
      return (*this);
    }
    untilInnerEnd = OuterIterator_->size();
  }
  InnerIterator_ = OuterIterator_->begin();
  InnerIterator_ += Offset;
  return (*this);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator+(difference_type Offset) const {
  CLexSum Result = *this;
  return (Result += Offset);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>&
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator-=(difference_type Offset) {
  if (Offset < 0)
    return (*this += -Offset);
  assert(isHostDefined());
  if (isOuterIteratorTheEnd()) {
    --(*this);
    --Offset;
  }
  difference_type untilInnerBegin = InnerIterator_ - OuterIterator_->begin();
  if (untilInnerBegin >= Offset)  {
    InnerIterator_ -= Offset;
    return (*this);
  }
  while (untilInnerBegin < Offset) {
    --OuterIterator_;
    Offset -= untilInnerBegin;
    untilInnerBegin = OuterIterator_->size();
  }
  InnerIterator_ = OuterIterator_->end();
  InnerIterator_ -= Offset;
  return (*this);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::operator-(difference_type Offset) const {
  CLexSum Result = *this;
  return (Result -= Offset);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
typename CLexSum< TOuterContainer,
                  TOuterIterator,
                  TInnerIterator>::difference_type
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::
    operator-(const CLexSum<TOtherOuterContainer,
                            TOtherOuterIterator,
                            TOtherInnerIterator>& Iterator) const {
  assert(isHostDefined() && areHostsTheSame(Iterator));
  if (*this > Iterator)
    return subtractSmaller(Iterator);
  return -Iterator.subtractSmaller(*this);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
typename CLexSum< TOuterContainer,
                  TOuterIterator,
                  TInnerIterator>::reference
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::
    operator[](difference_type Offset) const {
  CLexSum temp(*this);
  temp += Offset;
  return (*temp);
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::
    begin(TOuterContainer& Host) {
  auto OuterIterator = Host.begin();
  for(; OuterIterator != Host.end(); ++OuterIterator)
    if (!OuterIterator->empty())
      break;
  if(OuterIterator == Host.end())
    return end(Host);
  return CLexSum(&Host, OuterIterator, OuterIterator->begin());
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::
    end(TOuterContainer& Host) {
  return CLexSum(&Host, Host.end(), TInnerIterator());
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::isInValidState() const {
  return !isHostDefined() ||
          (isOuterIteratorTheEnd() ||
            (isOuterIteratorInDefinedRange() &&
             isInnerIteratorInDefinedRange()));
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isOuterIteratorInFullRange() const {
  return  OuterIterator_ >= Host_->begin() &&
          OuterIterator_ <= Host_->end();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isOuterIteratorInDefinedRange() const {
  return  OuterIterator_ >= Host_->begin() &&
          OuterIterator_ < Host_->end();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isInnerIteratorInFullRange() const {
  return  InnerIterator_ >= OuterIterator_->begin() &&
          InnerIterator_ <= OuterIterator_->end();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isInnerIteratorInDefinedRange() const {
  return  InnerIterator_ >= OuterIterator_->begin() &&
          InnerIterator_ < OuterIterator_->end();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isOuterIteratorTheEnd() const {
  return OuterIterator_ == Host_->end();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isOuterIteratorTheBegin() const {
  return OuterIterator_ == Host_->begin();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isInnerIteratorTheEnd() const {
  return InnerIterator_ == OuterIterator_->end();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
bool
CLexSum<TOuterContainer,
        TOuterIterator,
        TInnerIterator>::
  isInnerIteratorTheBegin() const {
  return InnerIterator_ == OuterIterator_->begin();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
void
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::
    invalidateOuterIterator() {
  OuterIterator_ = TOuterIterator();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
void
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::
    invalidateInnerIterator() {
  InnerIterator_ = TInnerIterator();
}
//---------------------------------------------------------------------------

template< class TOuterContainer,
          class TOuterIterator,
          class TInnerIterator>
template< class TOtherOuterContainer,
          class TOtherOuterIterator,
          class TOtherInnerIterator>
typename CLexSum< TOuterContainer,
                  TOuterIterator,
                  TInnerIterator>::difference_type
  CLexSum<TOuterContainer,
          TOuterIterator,
          TInnerIterator>::
    subtractSmaller(const CLexSum<TOtherOuterContainer,
                                  TOtherOuterIterator,
                                  TOtherInnerIterator>& Iterator) const {
  assert(*this >= Iterator);
  if (areOuterIteratorsTheSame(Iterator)) {
    if (Iterator.isOuterIteratorTheEnd())
      return 0;
    return InnerIterator_ - Iterator.InnerIterator_;
  }
  auto currentPosition = Iterator;
  difference_type Offset =  currentPosition.OuterIterator_->end() -
                            currentPosition.InnerIterator_;
  ++(currentPosition.OuterIterator_);
  while (!areOuterIteratorsTheSame(currentPosition)) {
    Offset += currentPosition.OuterIterator_->size();
    ++(currentPosition.OuterIterator_);
  }
  if (!currentPosition.isOuterIteratorTheEnd())
    Offset += InnerIterator_ - currentPosition.OuterIterator_->begin();
  return Offset;
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
