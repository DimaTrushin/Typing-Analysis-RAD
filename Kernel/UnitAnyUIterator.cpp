//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAnyUIterator.h"
#if !defined(NDEBUG)
//#define __ANY_U_ITERATOR_TEST__
#if defined(__ANY_U_ITERATOR_TEST__)
#include <algorithm>
#include <vector>
#include <vcl.h>
#endif
#endif
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Tester
//---------------------------------------------------------------------------
#if !defined(NDEBUG)
#if defined(__ANY_U_ITERATOR_TEST__)

class CEmptyIterator {
public:
    ETextFormat getTextFormat() const {
      return ETextFormat::MainText;
    }
    CFormatStructure getTextFormatStructure() const {
      return CFormatStructure(ETextFormat::MainText, 0);
    }
    wchar_t getSymbol() const {
      return L'?';
    }
    unsigned short getVKCode() const {
      return 0;
    }
    bool isValid() const {
      return false;
    }
    microseconds getPressingTime() const {
      return 0;
    }
    microseconds getReleasingTime() const {
      return 0;
    }
    void setNext(){
    }
    microseconds getPhysicalResponseTime() const {
      return 0;
    }
};

class CAnyIteratorTester {
public:
  CAnyIteratorTester()  {
    runTest();
  }
  void runTest() {
    UnicodeString Result = L"AnyUIterator:";
    testAnyIterator(&Result);
    ShowMessage(Result.c_str());
  }
  void testAnyIterator(UnicodeString* pResult) {
    CEmptyIterator EIter1;
    CEmptyIterator EIter2;
    CAnyUIterator Iterator1;
    CAnyUIterator Iterator2(EIter2);
    CAnyUIterator Iterator3 = EIter1;
    CAnyUIterator Iterator4(Iterator3);
    CAnyUIterator Iterator5 = Iterator4;
    CAnyUIterator Iterator6(std::move(Iterator5));
    CAnyUIterator Iterator7 = Iterator6;
    CAnyUIterator Iterator8 = std::move(Iterator7);

    *pResult += L"\nIterator1.isDefined() = ";
    *pResult += Iterator1.isDefined();
    *pResult += L"\nIterator2.isDefined() = ";
    *pResult += Iterator2.isDefined();
    *pResult += L"\nIterator3.isDefined() = ";
    *pResult += Iterator3.isDefined();
    *pResult += L"\nIterator4.isDefined() = ";
    *pResult += Iterator4.isDefined();
    *pResult += L"\nIterator5.isDefined() = ";
    *pResult += Iterator5.isDefined();
    *pResult += L"\nIterator6.isDefined() = ";
    *pResult += Iterator6.isDefined();
    *pResult += L"\nIterator7.isDefined() = ";
    *pResult += Iterator7.isDefined();
    *pResult += L"\nIterator8.isDefined() = ";
    *pResult += Iterator8.isDefined();
  }
protected:
private:
} AnyIteratorTester;
#endif
#endif
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
