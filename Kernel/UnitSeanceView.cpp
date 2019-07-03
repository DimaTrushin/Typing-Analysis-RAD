//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitSeanceView.h"
#if !defined(NDEBUG)
//#define __SEANCE_VIEW_TEST__
#if defined(__SEANCE_VIEW_TEST__)
#include <vcl.h>
#endif
#endif
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Tester
//---------------------------------------------------------------------------

#if !defined(NDUBUG)
#if defined(__SEANCE_VIEW_TEST__)
class CSeanceViewTester {
public:
  CSeanceViewTester() {
    runTest();
  }
  void runTest() {
    UnicodeString Result = L"SeanceViewTest:";
    makeTest(&Result);
    ShowMessage(Result.c_str());
  }
  void makeTest(UnicodeString* pResult) {
    CSeance Seance;
    populateSeance(&Seance);
    printSeance(Seance, pResult);
    testSeanceView(Seance, pResult);
  }
  void testSeanceView(const CSeance& Seance, UnicodeString* pResult) {
    CSeanceView SeanceView(Seance);
    printSeanceView(SeanceView, pResult);
  }
  void printSeanceView(const CSeanceView& SeanceView, UnicodeString* pResult) {
    *pResult += L"\nSeanceView:";
    *pResult += L"\nouter size = ";
    *pResult += SeanceView.size();
    for (const auto& SessionView : SeanceView)
      printSessionView(SessionView, pResult);
  }
  void printSessionView(const CSessionView& SessionView, UnicodeString* pResult) {
    *pResult += L"\nSessionView:";
    *pResult += L" size = ";
    *pResult += SessionView.size();
    for (const auto& Key : SessionView)
      printKey(Key, pResult);
  }
  void populateSeance(CSeance* pSeance) {
    pSeance->openNewSession(NSKeyboard::CKeyboardState());
    pSeance->back().push_back(CKeyEvent(VK_A, 0, 0, 40000));
    pSeance->back().push_back(CKeyEvent(VK_B, 0, 20000, 60000));
    pSeance->back().push_back(CKeyEvent(VK_C, 0, 80000, 100000));
    pSeance->openNewSession(NSKeyboard::CKeyboardState());
    pSeance->back().push_back(CKeyEvent(VK_A, 0, 150000, 190000));
    pSeance->back().push_back(CKeyEvent(VK_B, 0, 180000, 220000));
    pSeance->back().push_back(CKeyEvent(VK_C, 0, 230000, 250000));
  }
  void printSeance(const CSeance& Seance, UnicodeString* pResult) {
    *pResult += L"\nSeance:";
    for (const auto& Session : Seance)
      printSession(Session, pResult);
  }
  void printSession(const CSession& Session, UnicodeString* pResult) {
    *pResult += L"\nSession:";
    for (const auto& Key : Session)
      printKey(Key, pResult);
  }
  void printKey(const CKeyEvent& Key, UnicodeString* pResult) {
    *pResult += L"\nKey:";
    *pResult += L" VK = ";
    *pResult += Key.getVKCode();
    *pResult += L" Layout = ";
    *pResult += reinterpret_cast<int>(Key.getLayout());
    *pResult += L" Pressing = ";
    *pResult += Key.getPressingTime();
    *pResult += L" Releasing = ";
    *pResult += Key.getReleasingTime();
  }
protected:
private:
} SeanceViewTester;
#endif
#endif
//---------------------------------------------------------------------------
// Declaration of CSeanceKeyInterval
//---------------------------------------------------------------------------

CSeanceKeyInterval::CSeanceKeyInterval( CSeanceKeyIterator begin,
                                        CSeanceKeyIterator end)
  : begin_(begin),
    end_(end),
    size_(end - begin) {
  assert(begin_ < end_);
}
//---------------------------------------------------------------------------

CSeanceKeyInterval::CSeanceKeyInterval( const CSeance& Seance,
                                        CSeance::const_iterator itSession)
  : begin_(CSeanceKeyIterator(&Seance, itSession, itSession->begin())),
    end_(getNext(Seance, itSession)),
    size_(end_ - begin_) {
  assert(begin_ < end_);
}
//---------------------------------------------------------------------------

CSeanceKeyIterator CSeanceKeyInterval::begin() const {
  return begin_;
}
//---------------------------------------------------------------------------

CSeanceKeyIterator CSeanceKeyInterval::end() const {
  return end_;
}
//---------------------------------------------------------------------------

std::size_t CSeanceKeyInterval::size() const {
  return size_;
}
//---------------------------------------------------------------------------

bool CSeanceKeyInterval::empty() const {
  return size_ == 0;
}
//---------------------------------------------------------------------------

bool CSeanceKeyInterval::isHostDefined() const {
  return  begin_.isHostDefined() && begin_.areHostsTheSame(end_);
}
//---------------------------------------------------------------------------

CSeanceKeyIterator CSeanceKeyInterval::getNext(
                              const CSeance& Seance,
                              CSeance::const_iterator itSession) const {
  ++itSession;
  if (itSession != Seance.end())
    return CSeanceKeyIterator(&Seance, itSession, itSession->begin());
  return CSeanceKeyIterator::end(Seance);
}
//---------------------------------------------------------------------------
// Declaration of CSessionView
//---------------------------------------------------------------------------

CSessionView::CSessionView( const CSeance& Seance,
                            CSeance::const_iterator itSession)
  : CBase({CSeanceKeyInterval(Seance, itSession)}) {
}
//---------------------------------------------------------------------------

CSessionView::iterator CSessionView::begin() {
  return iterator::begin(*this);
}
//---------------------------------------------------------------------------

CSessionView::const_iterator CSessionView::begin() const {
  return const_iterator::begin(*this);
}
//---------------------------------------------------------------------------

CSessionView::iterator CSessionView::end() {
  return iterator::end(*this);
}
//---------------------------------------------------------------------------

CSessionView::const_iterator CSessionView::end() const {
  return const_iterator::end(*this);
}
//---------------------------------------------------------------------------

size_t CSessionView::size() const {
  size_t size = 0;
  for (const auto& SeanceKeyInterval : *static_cast<const CBase*>(this))
    size += SeanceKeyInterval.size();
  return size;
}
//---------------------------------------------------------------------------

bool CSessionView::empty() const {
  return size() == 0;
}
//---------------------------------------------------------------------------
// Declaration of CSeanceView
//---------------------------------------------------------------------------

CSeanceView::CSeanceView(const CSeance& Seance)
  : CBase(Seance.size()) {
  auto itSessionView = begin();
  for ( auto itSession = Seance.begin();
        itSession != Seance.end();
        ++itSession, ++itSessionView) {
    *itSessionView = CSessionView(Seance, itSession);
  }
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
