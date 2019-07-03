// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitRawKeyEvent.h"

#if !defined(NDEBUG)
//#define __RAW__KEY__EVENT__TEST__
#if defined(__RAW__KEY__EVENT__TEST__)
#include "UnitFileWriter.h"
#include "UnitFileReader.h"
#include <vcl.h>
#endif
#endif
// ---------------------------------------------------------------------------

#pragma package(smart_init)
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Tester
// ---------------------------------------------------------------------------

#if !defined(NDEBUG)
#if defined(__RAW__KEY__EVENT__TEST__)
class CRawKeyEventTester {
public:
  CRawKeyEventTester() {
    runTest();
  }
private:
  void runTest() {
    std::wstring FileName(L"RawKeyEventTests.bin");
    UnicodeString Result(L"RawKeyEventTests:");
    writeToFile(FileName, &Result);
    readFromFile(FileName, &Result);
    ShowMessage(Result.c_str());
  }
  void writeToFile(const std::wstring& FileName, UnicodeString* pResult) {
    NSLibrary::CFileWriter FileWriter(FileName);
    CRawKey Key1;
    CRawKey Key2(0,0,0,0);
    CRawEventContainer RContainer;
    RContainer.push_back(CRawKey(1,0,1,10));
    RContainer.push_back(CRawKey(2,0,2,20));
    RContainer.push_back(CRawKey(3,0,3,30));

    FileWriter << Key1;
    FileWriter << Key2;
    FileWriter << RContainer;
    printKey(Key1, pResult);
    printKey(Key2, pResult);
    for(const auto& Key : RContainer)
      printKey(Key, pResult);
  }
  void readFromFile(const std::wstring& FileName, UnicodeString* pResult) {
   NSLibrary::CFileReader FileReader(FileName);
    CRawKey Key1;
    CRawKey Key2;
    CRawEventContainer RContainer;

    FileReader >> Key1;
    FileReader >> Key2;
    FileReader >> RContainer;
    printKey(Key1, pResult);
    printKey(Key2, pResult);
    for(const auto& Key : RContainer)
      printKey(Key, pResult);
  }
  void printKey(const CRawKey& Key, UnicodeString* pResult){
    *pResult += L"\nVK = ";
    *pResult += Key.getVKCode();
    *pResult += L" HKL = ";
    *pResult += reinterpret_cast<int>(Key.getLayout());
    *pResult += L" Flags = ";
    *pResult += Key.getFlags();
    *pResult += L" Time = ";
    *pResult += Key.getTime();
  }
} RawKeyEventTester;
#endif
#endif
// ---------------------------------------------------------------------------
// Definitions of CRawEventContainer
// ---------------------------------------------------------------------------

void CRawEventContainer::setNewKeyboardState(const CRawKey& RawKey) {
  if (RawKey.isPressed())
    InitialKeyboardState.PressKey(RawKey.getVKCode());
  else
    InitialKeyboardState.ReleaseKey(RawKey.getVKCode());
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

