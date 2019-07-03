//---------------------------------------------------------------------------

#ifndef UnitIntervalH
#define UnitIntervalH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------
#include <algorithm>
#include <list>
#include <cassert>
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
// ---------------------------------------------------------------------------
// Declaration of CSemiIntervalBase
// ---------------------------------------------------------------------------

// Base for semi-interval of the form [begin, end)
template<class Type>
class CSemiIntervalBase {
public:
  CSemiIntervalBase();
  CSemiIntervalBase(const Type& Begin, const Type& End);
  Type begin;
  Type end;
};
// ---------------------------------------------------------------------------
// Declaration of CSemiIntervalBase Streaming
// ---------------------------------------------------------------------------

template< class TStreamer,
          class TType>
TStreamer& operator<<(TStreamer& Streamer,
                      const CSemiIntervalBase<TType>& SemiIntervalBase);
// ---------------------------------------------------------------------------

template< class TStreamer,
          class TType>
TStreamer& operator>>(TStreamer& Streamer,
                      CSemiIntervalBase<TType>& SemiIntervalBase);
// ---------------------------------------------------------------------------
// Forward Declarations
// ---------------------------------------------------------------------------

template<class Type>
class CSemiInterval;
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyLess(const CSemiInterval<Type>& first,
                    const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyLessOrEquivalent(const CSemiInterval<Type>& first,
                                const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isLess(const CSemiInterval<Type>& first,
            const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isLessOrEquivalent(const CSemiInterval<Type>& first,
                        const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyGreater( const CSemiInterval<Type>& first,
                        const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyGreaterOrEquivalent( const CSemiInterval<Type>& first,
                                    const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isGreater( const CSemiInterval<Type>& first,
                const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
bool isGreaterOrEquivalent( const CSemiInterval<Type>& first,
                            const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type> intersect(const CSemiInterval<Type>& first,
                              const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type> uniteConvexly(const CSemiInterval<Type>& first,
                                  const CSemiInterval<Type>& second);
// ---------------------------------------------------------------------------
// Declaration of CSemiInterval
// ---------------------------------------------------------------------------

template<class Type>
class CSemiInterval : public CSemiIntervalBase<Type> {
public:
  using MyBase = CSemiIntervalBase<Type>;
  using MyBase::begin;
  using MyBase::end;
  CSemiInterval();
  CSemiInterval(const Type& Begin, const Type& End);

  bool isInInterval(const Type& Element) const;
  void setToIntersection(const CSemiInterval& Interval);
  void setToConvexUnion(const CSemiInterval& Interval);
  void setToEmpty();

  bool isIntersecting(const CSemiInterval& Interval) const;
  bool isCoveredBy(const CSemiInterval& Interval) const;
  bool isCovering(const CSemiInterval& Interval) const;
  bool isEmpty() const;

  std::list<CSemiInterval>getDifference(
                                const CSemiInterval& Interval) const;
  size_t getNumberOfComponentsInDifference(
                                const CSemiInterval& Interval) const;

  // ---------------------------------------------------------------------------

  static const CSemiInterval EmptyInterval;
  // ---------------------------------------------------------------------------

  friend bool isStrictlyLess<Type>( const CSemiInterval& first,
                                    const CSemiInterval& second);
  friend bool isStrictlyLessOrEquivalent<Type>( const CSemiInterval& first,
                                                const CSemiInterval& second);
  friend bool isLess<Type>( const CSemiInterval& first,
                            const CSemiInterval& second);
  friend bool isLessOrEquivalent<Type>( const CSemiInterval& first,
                                        const CSemiInterval& second);
  friend bool isStrictlyGreater<Type>(const CSemiInterval& first,
                                      const CSemiInterval& second);
  friend bool isStrictlyGreaterOrEquivalent<Type>(const CSemiInterval& first,
                                                  const CSemiInterval& second);
  friend bool isGreater<Type>(const CSemiInterval& first,
                              const CSemiInterval& second);
  friend bool isGreaterOrEquivalent<Type>(const CSemiInterval& first,
                                          const CSemiInterval& second);
  // TO DO
  // make these two functions to be members
  friend CSemiInterval intersect<Type>( const CSemiInterval& first,
                                    const CSemiInterval& second);
  friend CSemiInterval uniteConvexly<Type>( const CSemiInterval& first,
                                        const CSemiInterval& second);
  // ---------------------------------------------------------------------------
private:
  void setEndToMax(const CSemiInterval& Interval);
  void setEndToMin(const CSemiInterval& Interval);
  void setBeginToMax(const CSemiInterval& Interval);
  void setBeginToMin(const CSemiInterval& Interval);

  CSemiInterval getLeftComponentOfDifference(
                                const CSemiInterval& Interval) const;
  CSemiInterval getRightComponentOfDifference(
                                const CSemiInterval& Interval) const;
};
// ---------------------------------------------------------------------------
// Declaration of CSemiInterval Streaming
// ---------------------------------------------------------------------------

template<class TStreamer, class TType>
TStreamer& operator<<(TStreamer& Streamer,
                      const CSemiInterval<TType>& SemiInterval);
//---------------------------------------------------------------------------

template<class TStreamer, class TType>
TStreamer& operator>>(TStreamer& Streamer,
                      CSemiInterval<TType>& SemiInterval);
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
// ---------------------------------------------------------------------------
// Definition of CSemiIntervalBase
// ---------------------------------------------------------------------------

template<class Type>
CSemiIntervalBase<Type>::CSemiIntervalBase()
  : begin(Type()),
    end(Type()) {
}
// ---------------------------------------------------------------------------

template<class Type>
CSemiIntervalBase<Type>::CSemiIntervalBase(const Type& Begin, const Type& End)
  : begin(Begin),
    end(End) {
  assert(Begin <= End);
}
// ---------------------------------------------------------------------------
// Definition of CSemiIntervalBase Streaming
// ---------------------------------------------------------------------------

template< class TStreamer,
          class TType>
TStreamer& operator<<(TStreamer& Streamer,
                      const CSemiIntervalBase<TType>& SemiIntervalBase) {
  Streamer << SemiIntervalBase.begin;
  Streamer << SemiIntervalBase.end;
  return Streamer;
}
// ---------------------------------------------------------------------------

template< class TStreamer,
          class TType>
TStreamer& operator>>(TStreamer& Streamer,
                      CSemiIntervalBase<TType>& SemiIntervalBase) {
  Streamer >> SemiIntervalBase.begin;
  Streamer >> SemiIntervalBase.end;
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CSemiInterval
// ---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type>::CSemiInterval()
  : CSemiIntervalBase<Type>() {
}
// ---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type>::CSemiInterval(const Type& Begin, const Type& End)
  : CSemiIntervalBase<Type>(Begin, End) {
}
// ---------------------------------------------------------------------------

template<class Type>
bool CSemiInterval<Type>::isInInterval(const Type& Element) const {
  return (begin <= Element) && (Element < end);
}
// ---------------------------------------------------------------------------

template<class Type>
void CSemiInterval<Type>::setToIntersection(const CSemiInterval& Interval) {
  Type Begin = std::max(begin, Interval.begin);
  Type End = std::min(end, Interval.end);
  if (Begin <= End) {
    begin = Begin;
    end = End;
  }
  else
    setToEmpty();
}
// ---------------------------------------------------------------------------

template<class Type>
void CSemiInterval<Type>::setToConvexUnion(const CSemiInterval& Interval) {
  setBeginToMin(Interval);
  setEndToMax(Interval);
}
// ---------------------------------------------------------------------------

template<class Type>
void CSemiInterval<Type>::setToEmpty() {
  *this = EmptyInterval;
}
// ---------------------------------------------------------------------------

template<class Type>
bool CSemiInterval<Type>::isIntersecting(const CSemiInterval& Interval) const {
  return !intersect(*this, Interval).isEmpty();
}
// ---------------------------------------------------------------------------

template<class Type>
bool CSemiInterval<Type>::isCoveredBy(const CSemiInterval& Interval) const {
  return (Interval.begin <= begin) && (end <= Interval.end);
}
// ---------------------------------------------------------------------------

template<class Type>
bool CSemiInterval<Type>::isCovering(const CSemiInterval& Interval) const {
  return Interval.isCoveredBy(*this);
}
// ---------------------------------------------------------------------------

template<class Type>
std::list<CSemiInterval<Type>> CSemiInterval<Type>::getDifference(
                                      const CSemiInterval& Interval) const {
  // TO DO
  // This block is redundant
  if (isEmpty())
    return std::list<CSemiInterval>();
  if (Interval.isEmpty()){
    std::list<CSemiInterval> Difference;
    Difference.push_back(*this);
    return Difference;
  }
  // block

  std::list<CSemiInterval> Difference;
  CSemiInterval Left = getLeftComponentOfDifference(Interval);
  if(!Left.isEmpty())
    Difference.push_back(Left);

  CSemiInterval Right = getRightComponentOfDifference(Interval);
  if(!Right.isEmpty())
    Difference.push_back(Right);
  return Difference;
}
// ---------------------------------------------------------------------------

template<class Type>
size_t CSemiInterval<Type>::getNumberOfComponentsInDifference(
                                      const CSemiInterval& Interval) const {
  if (isEmpty())
    return 0;
  if (Interval.isEmpty())
    return 1;

  size_t result = 0;
  if (begin < Interval.begin)
    ++result;
  if (end > Interval.end)
    ++result;
  return result;
}
// ---------------------------------------------------------------------------

template<class Type>
bool CSemiInterval<Type>::isEmpty() const {
  return end <= begin;
}
// ---------------------------------------------------------------------------

template<class Type>
const CSemiInterval<Type> CSemiInterval<Type>::EmptyInterval = CSemiInterval<Type>();
// ---------------------------------------------------------------------------

template<class Type>
void CSemiInterval<Type>::setEndToMax(const CSemiInterval& Interval) {
  end = std::max(end, Interval.end);
  assert(begin <= end);
}
// ---------------------------------------------------------------------------

template<class Type>
void CSemiInterval<Type>::setEndToMin(const CSemiInterval& Interval) {
  end = std::min(end, Interval.end);
  assert(begin <= end);
}
// ---------------------------------------------------------------------------

template<class Type>
void CSemiInterval<Type>::setBeginToMax(const CSemiInterval& Interval) {
  begin = std::max(begin, Interval.begin);
  assert(begin <= end);
}
// ---------------------------------------------------------------------------

template<class Type>
void CSemiInterval<Type>::setBeginToMin(const CSemiInterval& Interval) {
  begin = std::min(begin, Interval.begin);
  assert(begin <= end);
}
// ---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type> CSemiInterval<Type>::getLeftComponentOfDifference(
                                        const CSemiInterval& Interval) const {
  if (Interval.begin <= begin)
    return EmptyInterval;
  if(!isIntersecting(Interval))
    return *this;
  return CSemiInterval(begin, Interval.begin);
}
// ---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type> CSemiInterval<Type>::getRightComponentOfDifference(
                                        const CSemiInterval& Interval) const {
  if (end <= Interval.end || Interval.isEmpty())
    return EmptyInterval;
  if(!isIntersecting(Interval))
    return *this;
  return CSemiInterval(Interval.end, end);
}
// ---------------------------------------------------------------------------
// Definition of CSemiInterval Streaming
// ---------------------------------------------------------------------------

template<class TStreamer, class TType>
TStreamer& operator<<(TStreamer& Streamer, const CSemiInterval<TType>& SemiInterval) {
  Streamer <<
    static_cast<const typename CSemiInterval<TType>::MyBase&>(SemiInterval);
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer, class TType>
TStreamer& operator>>(TStreamer& Streamer, CSemiInterval<TType>& SemiInterval) {
  Streamer >>
    static_cast<typename CSemiInterval<TType>::MyBase&>(SemiInterval);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definitions of Global Functions
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyLess(const CSemiInterval<Type>& first,
                    const CSemiInterval<Type>& second) {
  return first.end < second.begin;
}
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyLessOrEquivalent(const CSemiInterval<Type>& first,
                                const CSemiInterval<Type>& second) {
  return !isStrictlyGreater(first, second);
}
// ---------------------------------------------------------------------------

template<class Type>
bool isLess(const CSemiInterval<Type>& first,
            const CSemiInterval<Type>& second) {
  return first.end <= second.begin;
}
// ---------------------------------------------------------------------------

template<class Type>
bool isLessOrEquivalent(const CSemiInterval<Type>& first,
                        const CSemiInterval<Type>& second) {
  return !isGreater(first, second);
}
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyGreater( const CSemiInterval<Type>& first,
                        const CSemiInterval<Type>& second) {
  return isStrictlyLess(second, first);
}
// ---------------------------------------------------------------------------

template<class Type>
bool isStrictlyGreaterOrEquivalent( const CSemiInterval<Type>& first,
                                    const CSemiInterval<Type>& second) {
  return !isStrictlyLess(first, second);
}
// ---------------------------------------------------------------------------

template<class Type>
bool isGreater( const CSemiInterval<Type>& first,
                const CSemiInterval<Type>& second) {
  return isLess(second, first);
}
// ---------------------------------------------------------------------------

template<class Type>
bool isGreaterOrEquivalent( const CSemiInterval<Type>& first,
                            const CSemiInterval<Type>& second) {
  return !isLess(first, second);
}
//---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type> intersect(const CSemiInterval<Type>& first,
                          const CSemiInterval<Type>& second) {
  CSemiInterval<Type> Intersection = first;
  Intersection.setToIntersection(second);
  return Intersection;
}
// ---------------------------------------------------------------------------

template<class Type>
CSemiInterval<Type> uniteConvexly(const CSemiInterval<Type>& first,
                              const CSemiInterval<Type>& second) {
  CSemiInterval<Type> ConvexUnion = first;
  ConvexUnion.setToConvexUnion(second);
  return ConvexUnion;
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
