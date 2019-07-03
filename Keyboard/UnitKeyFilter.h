// ---------------------------------------------------------------------------
#ifndef UnitKeyFilterH
#define UnitKeyFilterH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <windows.h>
#include <vector>
#include "UnitKeyboardRelatedDefinitions.h"
#include "../Library/UnitInterval.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Declaration of CKeyInterval
// ---------------------------------------------------------------------------

// Semi-intervals of the form [begin, end)
class CKeyInterval : public NSLibrary::CSemiInterval<unsigned short> {
  public:
  using MyBase = NSLibrary::CSemiInterval<unsigned short>;
  CKeyInterval();
  CKeyInterval(const MyBase& base);
  CKeyInterval(unsigned short begin, unsigned short end);
  CKeyInterval(unsigned short VKCode);

  static const CKeyInterval NumberInterval;
  static const CKeyInterval EnglishSymbolInterval;
};
// ---------------------------------------------------------------------------
// Declaration of CKeyInterval Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyInterval& KeyInterval);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyInterval& KeyInterval);
// ---------------------------------------------------------------------------
// Declaration of CKeyFilter
// ---------------------------------------------------------------------------
//class CTester;

// CKeyIntervals in the CKeyFilter are always:
// 1) non-empty
// 2) disjoint
// 3) sorted by NSLibrary::isLess
class CKeyFilter : protected std::vector<CKeyInterval> {
public:
  //friend class CTester;
  using MyBase = std::vector<CKeyInterval>;
  using MyBase::iterator;
  using MyBase::const_iterator;

  bool isProcessable(unsigned short VKCode) const;
  void AddInterval(const CKeyInterval& Interval);
  void RemoveInterval(const CKeyInterval& Interval);

  void setToDefaultFilter();

 private:
  bool findFirstAtLeastAdjacent(const CKeyInterval& Interval,
                                iterator* pIterator);
  // this function assumes that the previous one returns true
  void findLastAtLeastAdjacent( const CKeyInterval& Interval,
                                iterator* pIterator);
  bool findFirstIntersecting( const CKeyInterval& Interval,
                              iterator* pIterator);
  // this function assumes that the previous one returns true
  void findLastIntersecting(const CKeyInterval& Interval,
                            iterator* pIterator);
  void removeFromOneInterval( const iterator& Intersection,
                              const CKeyInterval& Interval);
  void removeFromRange( iterator FirstIntersection,
                        iterator LastIntersection,
                        const CKeyInterval& Interval);
  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CKeyFilter& KeyFilter);
  template<class TStreamer>
  friend TStreamer& operator>>(TStreamer& Streamer, CKeyFilter& KeyFilter);
};
// ---------------------------------------------------------------------------
// Declaration of CKeyFilter Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyFilter& KeyFilter);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyFilter& KeyFilter);
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Definition of CKeyInterval Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyInterval& KeyInterval) {
  Streamer << static_cast<const typename CKeyInterval::MyBase&>(KeyInterval);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyInterval& KeyInterval) {
  Streamer >> static_cast<typename CKeyInterval::MyBase&>(KeyInterval);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CKeyFilter Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyFilter& KeyFilter) {
  Streamer << static_cast<const typename CKeyFilter::MyBase&>(KeyFilter);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyFilter& KeyFilter) {
  Streamer >> static_cast<typename CKeyFilter::MyBase&>(KeyFilter);
  return Streamer;
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
