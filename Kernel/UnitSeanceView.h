//---------------------------------------------------------------------------

#ifndef UnitSeanceViewH
#define UnitSeanceViewH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "../Library/UnitLexSum.h"
#include "UnitKeyEvent.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CSeanceKeyIterator
//---------------------------------------------------------------------------

using CSeanceKeyIterator = NSLibrary::CLexSum<const CSeance,
                                              CSeance::const_iterator,
                                              CSession::const_iterator>;
//---------------------------------------------------------------------------
// Declaration of CSeanceKeyInterval
//---------------------------------------------------------------------------

class CSeanceKeyInterval {
public:
  using const_iterator = CSeanceKeyIterator;
  CSeanceKeyInterval() = default;
  CSeanceKeyInterval(CSeanceKeyIterator begin, CSeanceKeyIterator end);
  CSeanceKeyInterval(const CSeance& Seance, CSeance::const_iterator itSession);
  CSeanceKeyIterator begin() const;
  CSeanceKeyIterator end() const;
  std::size_t size() const;
  bool empty() const;
  bool isHostDefined() const;
private:
  CSeanceKeyIterator getNext( const CSeance& Seance,
                              CSeance::const_iterator itSession) const;
  CSeanceKeyIterator begin_;
  CSeanceKeyIterator end_;
  std::size_t size_ = 0;
};
//---------------------------------------------------------------------------
// Declaration of CSessionView
//---------------------------------------------------------------------------

class CSessionView : protected std::deque<CSeanceKeyInterval> {
  using CBase = std::deque<CSeanceKeyInterval>;
public:
  using iterator = NSLibrary::CLexSum<CBase,
                                      CBase::iterator,
                                      CSeanceKeyInterval::const_iterator>;
  using const_iterator = NSLibrary::CLexSum<
                                      const CBase,
                                      CBase::const_iterator,
                                      CSeanceKeyInterval::const_iterator>;
  CSessionView() = default;
  CSessionView(const CSeance& Seance, CSeance::const_iterator itSession);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  size_t size() const;
  bool empty() const;
};
//---------------------------------------------------------------------------
// Declaration of CSeanceView
//---------------------------------------------------------------------------

class CSeanceView : protected std::deque<CSessionView> {
  using CBase = std::deque<CSessionView>;
public:
  CSeanceView() = default;
  CSeanceView(const CSeance& Seance);
  using CBase::begin;
  using CBase::end;
  using CBase::size;
  using CBase::empty;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
