// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitKeyFilter.h"

#if !defined(NDEBUG)
//#define __KEY__FILTER__TEST__
#if defined(__KEY__FILTER__TEST__)
#include "UnitFileWriter.h"
#include "UnitFileReader.h"
#include <vcl.h>
#endif
#endif
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Tester
// ---------------------------------------------------------------------------

#if !defined(NDEBUG)
#if defined(__KEY__FILTER__TEST__)
class CKeyFilterTester {
public:
  CKeyFilterTester() {
    runTest();
  }
private:
  void runTest() {
    std::wstring FileName(L"KeyFilterTests.bin");
    UnicodeString Result(L"KeyFilterTests:");
    writeToFile(FileName, &Result);
    readFromFile(FileName, &Result);
    ShowMessage(Result.c_str());
  }
  void writeToFile(const std::wstring& FileName, UnicodeString* pResult) {
    NSLibrary::CFileWriter FileWriter(FileName);
    CKeyInterval Interval1(0,3);
    CKeyInterval Interval2(5);
    CKeyFilter EmptyKeyFilter;
    CKeyFilter DefaultKeyFilter;
    DefaultKeyFilter.setToDefaultFilter();

    FileWriter << Interval1;
    FileWriter << Interval2;
    FileWriter << EmptyKeyFilter;
    FileWriter << DefaultKeyFilter;
    *pResult += L"\nIntervals:\n";
    printInterval(Interval1, pResult);
    printInterval(Interval2, pResult);
  }
  void readFromFile(const std::wstring& FileName, UnicodeString* pResult) {
   NSLibrary::CFileReader FileReader(FileName);
    CKeyInterval Interval1(10,13);
    CKeyInterval Interval2(15);
    CKeyFilter EmptyKeyFilter;
    CKeyFilter DefaultKeyFilter;

    FileReader >> Interval1;
    FileReader >> Interval2;
    FileReader >> EmptyKeyFilter;
    FileReader >> DefaultKeyFilter;

    *pResult += L"\nIntervals:\n";
    printInterval(Interval1, pResult);
    printInterval(Interval2, pResult);
  }

  void printInterval(const CKeyInterval& Interval, UnicodeString* pResult) {
    *pResult += L"[";
    *pResult += Interval.begin;
    *pResult += L", ";
    *pResult += Interval.end;
    *pResult += L") ";
  }

} KeyFilterTester;
#endif
#endif
// ---------------------------------------------------------------------------
// Definition of CKeyInterval
// ---------------------------------------------------------------------------

CKeyInterval::CKeyInterval()
  : MyBase(0, 0) {
}
// ---------------------------------------------------------------------------

CKeyInterval::CKeyInterval(const MyBase& base)
  : MyBase(base) {
}
// ---------------------------------------------------------------------------

CKeyInterval::CKeyInterval(unsigned short begin, unsigned short end)
  : MyBase(begin, end) {
}
// ---------------------------------------------------------------------------

CKeyInterval::CKeyInterval(unsigned short VKCode)
  : MyBase(VKCode, VKCode + 1) {
}
// ---------------------------------------------------------------------------

const CKeyInterval CKeyInterval::NumberInterval =
                                          CKeyInterval(VK_0, VK_9 + 0x01);
// ---------------------------------------------------------------------------

const CKeyInterval CKeyInterval::EnglishSymbolInterval =
                                          CKeyInterval(VK_A, VK_Z + 0x01);
// ---------------------------------------------------------------------------
// Definitions of CKeyFilter
// ---------------------------------------------------------------------------

bool CKeyFilter::isProcessable(unsigned short VKCode) const {
   auto iterator = std::lower_bound(begin(),
                                    end(),
                                    CKeyInterval(VKCode),
                                    NSLibrary::isLess<unsigned short>);
  if (iterator == end())
    return false;
  return iterator->isInInterval(VKCode);
}
// ---------------------------------------------------------------------------

void CKeyFilter::AddInterval(const CKeyInterval& Interval) {
  assert(!Interval.isEmpty());
  iterator FirstAdjacent;
  if (!findFirstAtLeastAdjacent(Interval, &FirstAdjacent)) {
    insert(FirstAdjacent, Interval);
    return;
  }
  assert(FirstAdjacent->end >= Interval.begin);
  iterator LastAdjacent;
  findLastAtLeastAdjacent(Interval, &LastAdjacent);
  assert(LastAdjacent->begin <= Interval.end);
  CKeyInterval newInterval = NSLibrary::uniteConvexly(Interval, *FirstAdjacent);
  newInterval = NSLibrary::uniteConvexly(newInterval, *LastAdjacent);
  *LastAdjacent = newInterval;
  erase(FirstAdjacent, LastAdjacent);
}
// ---------------------------------------------------------------------------

void CKeyFilter::RemoveInterval(const CKeyInterval& Interval) {
  iterator FirstIntersection;
  if(!findFirstIntersecting(Interval, &FirstIntersection))
    return;
  assert(FirstIntersection->end > Interval.begin);
  iterator LastIntersection;
  findLastIntersecting(Interval, &LastIntersection);
  assert(LastIntersection->begin < Interval.end);
  if (FirstIntersection == LastIntersection)
    removeFromOneInterval(FirstIntersection, Interval);
  else
    removeFromRange(FirstIntersection, LastIntersection, Interval);
}
// ---------------------------------------------------------------------------

void CKeyFilter::setToDefaultFilter() {
  AddInterval(CKeyInterval(VK_0, VK_9 + 0x01));
  AddInterval(CKeyInterval(VK_A, VK_Z + 0x01));

  // See UnitKeyboardRelatedDefinitions.h
  // for details on the VKCodes below
  AddInterval(CKeyInterval(0xba, 0xbf + 0x01));
  AddInterval(CKeyInterval(0xdb, 0xde + 0x01));

  AddInterval(CKeyInterval(VK_ENG_TILDE, VK_ENG_TILDE + 0x01));
  AddInterval(CKeyInterval(VK_SHIFT, VK_MENU + 0x01));
  AddInterval(CKeyInterval(VK_LSHIFT, VK_RMENU + 0x01));
  AddInterval(CKeyInterval(VK_CAPITAL, VK_CAPITAL + 0x01));
  AddInterval(CKeyInterval(VK_RETURN, VK_RETURN + 0x01));
  AddInterval(CKeyInterval(VK_BACK, VK_BACK + 0x01));
  //AddInterval(CKeyInterval(VK_ESCAPE, VK_ESCAPE + 0x01));
  AddInterval(CKeyInterval(VK_SPACE, VK_SPACE + 0x01));
}
// ---------------------------------------------------------------------------

bool CKeyFilter::findFirstAtLeastAdjacent(const CKeyInterval& Interval,
                                          iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::lower_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isStrictlyLess<unsigned short>);
  if (Iterator == end())
    return false;
  if (NSLibrary::isStrictlyLess(Interval, *Iterator))
    return false;
  return true;
}
// ---------------------------------------------------------------------------

void CKeyFilter::findLastAtLeastAdjacent( const CKeyInterval& Interval,
                                          iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::upper_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isStrictlyLess<unsigned short>);
  --Iterator;
}
// ---------------------------------------------------------------------------

bool CKeyFilter::findFirstIntersecting( const CKeyInterval& Interval,
                                        iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::lower_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isLess<unsigned short>);
  if (Iterator == end())
    return false;
  if (NSLibrary::isLess(Interval, *Iterator))
    return false;
  return true;

}
// ---------------------------------------------------------------------------

void CKeyFilter::findLastIntersecting( const CKeyInterval& Interval,
                                        iterator* pIterator) {
  iterator& Iterator = *pIterator;
  Iterator = std::upper_bound(begin(),
                              end(),
                              Interval,
                              NSLibrary::isLess<unsigned short>);
  --Iterator;
}
// ---------------------------------------------------------------------------

void CKeyFilter::removeFromOneInterval( const iterator& Intersection,
                                        const CKeyInterval& Interval) {
  auto Difference = Intersection->getDifference(Interval);
  if (Difference.size() == 0) {
    erase(Intersection);
    return;
  }
  if (Difference.size() == 1) {
    *Intersection = Difference.back();
    return;
  }
  *Intersection = Difference.back();
  insert(Intersection, Difference.front());
}
// ---------------------------------------------------------------------------

void CKeyFilter::removeFromRange( iterator FirstIntersection,
                                  iterator LastIntersection,
                                  const CKeyInterval& Interval) {
  *FirstIntersection = CKeyInterval(FirstIntersection->begin, Interval.begin);
  if (!FirstIntersection->isEmpty())
    ++FirstIntersection;
  *LastIntersection = CKeyInterval(Interval.end, LastIntersection->end);
  if (LastIntersection->isEmpty())
    ++LastIntersection;
  erase(FirstIntersection, LastIntersection);
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#pragma package(smart_init)
