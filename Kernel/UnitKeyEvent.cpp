// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitKeyEvent.h"

#if !defined(NDEBUG)
//#define __KEY__EVENT__TEST__
#if defined(__KEY__EVENT__TEST__)
#include "UnitFileWriter.h"
#include "UnitFileReader.h"
#include <vcl.h>
#endif
#endif
// ---------------------------------------------------------------------------

#if !defined(__KEY_EVENT__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Tester
// ---------------------------------------------------------------------------

#if !defined(NDEBUG)
#if defined(__KEY__EVENT__TEST__)
class CKeyEventTester {
public:
  CKeyEventTester() {
    runTest();
  }
private:
  void runTest() {
    std::wstring FileName(L"KeyEventTests.bin");
    UnicodeString Result(L"KeyEventTests:");
    writeToFile(FileName, &Result);
    readFromFile(FileName, &Result);
    ShowMessage(Result.c_str());
  }
  void writeToFile(const std::wstring& FileName, UnicodeString* pResult) {
    NSLibrary::CFileWriter FileWriter(FileName);
    CKeyEvent Key1;
    CKeyEvent Key2(1,0,5,10);
    CSession Session;
    Session.push_back(CKeyEvent(1,0,1,10));
    Session.push_back(CKeyEvent(2,0,2,20));
    Session.push_back(CKeyEvent(3,0,3,30));

    CSeance Seance;
    Seance.openNewSession(Session.getKeyboardState());
    Seance.back().push_back(CKeyEvent(1,0,1,10));
    Seance.back().push_back(CKeyEvent(2,0,2,20));
    Seance.openNewSession(Session.getKeyboardState());
    Seance.back().push_back(CKeyEvent(11,0,11,110));
    Seance.back().push_back(CKeyEvent(12,0,12,120));

    FileWriter.writeHeader();
    FileWriter << Key1;
    FileWriter << Key2;
    FileWriter << Session;
    FileWriter << Seance;
    *pResult += L"\nInput:";
    printKey(Key1, pResult);
    printKey(Key2, pResult);
    *pResult += L"\nSession:";
    for(const auto& Key : Session)
      printKey(Key, pResult);
    *pResult += L"\nSeance:";
    for(const auto& Session : Seance) {
      *pResult += L"\nSession:";
      for(const auto& Key : Session)
        printKey(Key, pResult);
    }
  }
  void readFromFile(const std::wstring& FileName, UnicodeString* pResult) {
   NSLibrary::CFileReader FileReader(FileName);
    CKeyEvent Key1;
    CKeyEvent Key2;
    CSession Session;
    CSeance Seance;

    try {
      FileReader.readHeader();
    } catch(...)
    {
      *pResult += L"\n    Exception";
    }
    FileReader >> Key1;
    FileReader >> Key2;
    FileReader >> Session;
    FileReader >> Seance;
    *pResult += L"\nOutput:";
    printKey(Key1, pResult);
    printKey(Key2, pResult);
    for(const auto& Key : Session)
      printKey(Key, pResult);
    *pResult += L"\nSeance:";
    for(const auto& Session : Seance) {
      *pResult += L"\nSession:";
      for(const auto& Key : Session)
        printKey(Key, pResult);
    }
  }
  void printKey(const CKeyEvent& Key, UnicodeString* pResult){
    *pResult += L"\nVK = ";
    *pResult += Key.getVKCode();
    *pResult += L" HKL = ";
    *pResult += reinterpret_cast<int>(Key.getLayout());
    *pResult += L" Pressing =";
    *pResult += Key.getPressingTime();
    *pResult += L" Releasing = ";
    *pResult += Key.getReleasingTime();
  }
} KeyEventTester;
#endif
#endif
// ---------------------------------------------------------------------------
// Definitions of CSeance
// ---------------------------------------------------------------------------

void CSeance::openNewSession(const NSKeyboard::CKeyboardState& KeyboardState) {
  push_back(CSession(KeyboardState));
}
// ---------------------------------------------------------------------------

microseconds CSeance::getResponseTime(const const_iterator& index) const {
  if (index == begin())
    return 0;
  auto previous = index;
  --previous;
  return  index->getFirstPressingTime() -
          previous->getLastPressingTime();

}
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
#pragma package(smart_init)

