//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitLexSum.h"
#if !defined(NDEBUG)
//#define __LEX_SUM_TEST__
#if defined(__LEX_SUM_TEST__)
#include <vector>
#include <deque>
#include <vcl.h>
#endif
#endif
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Tester
//---------------------------------------------------------------------------

#if !defined(NDUBUG)
#if defined(__LEX_SUM_TEST__)
class CLexSumTester {
public:
  CLexSumTester() {
    runTest();
  }
  void runTest() {
    UnicodeString Result = L"LexSumTest:";

    using CIntVector = std::vector<int>;
    using CIntVectorVector = std::vector<CIntVector>;
    using COuterContainer = CIntVectorVector;
    using COuterIterator = COuterContainer::iterator;
    using CInnerIterator = CIntVector::iterator;
    using CConstOuterIterator = COuterContainer::const_iterator;
    using CConstInnerIterator = CIntVector::const_iterator;
    using CLexSumIterator = CLexSum<COuterContainer,
                                    COuterIterator,
                                    CInnerIterator>;
    using CConstLexSumIterator = CLexSum< const COuterContainer,
                                          CConstOuterIterator,
                                          CConstInnerIterator>;
    CLexSumIterator Iterator1;
    COuterContainer Vector;
    Vector.emplace_back(1);
    Vector.emplace_back(2);
    Vector.emplace_back(3);
    Vector[0][0] = 1;
    Vector[1][0] = 2;
    Vector[1][1] = 3;
    Vector[2][0] = 4;
    Vector[2][1] = 5;
    Vector[2][2] = 6;
    CLexSumIterator Iterator2 = CLexSumIterator::begin(Vector);
    CConstLexSumIterator Iterator3 = CLexSumIterator::end(Vector);
    Result += L"\n";
    for (auto Iterator = Iterator2; Iterator != Iterator3; ++Iterator) {
      Result += *Iterator;
      Result += L" ";
    }
    Result += L"\n";
    auto Iterator = Iterator3;
    --Iterator;
    while (Iterator != Iterator2) {
      Result += *Iterator;
      Result += L" ";
      --Iterator;
    }
    Result += *Iterator;
    Result += L" ";
    ShowMessage(Result.c_str());
  }
protected:
private:
} LexSumTester;
#endif
#endif
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
