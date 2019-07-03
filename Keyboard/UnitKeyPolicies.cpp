//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKeyPolicies.h"

#if !defined(NDEBUG)
//#define __POLICIES__TEST__
#if defined(__POLICIES__TEST__)
#include "UnitFileWriter.h"
#include "UnitFileReader.h"
#include <vcl.h>
#endif
#endif
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Tester
//---------------------------------------------------------------------------

#if !defined(NDEBUG)
#if defined(__POLICIES__TEST__)
class CPoliciesTester {
public:
  CPoliciesTester() {
    runTest();
  }
protected:
  void runTest() {
    std::wstring FileName(L"PoliciesTests.bin");
    UnicodeString Result(L"PoliciesTests:");
    writeToFile(FileName, &Result);
    readFromFile(FileName, &Result);
    ShowMessage(Result.c_str());
  }

  template<class TType>
  class TD;
  void writeToFile(const std::wstring& FileName, UnicodeString* pResult) {
    NSLibrary::CFileWriter FileWriter(FileName);
    CKeyFlagsBase KeyFlagsBase(1);
    CKeyVKCodeBase KeyVKCodeBase(2);
    CKeyVKCodeLangLayoutBase KeyVKCodeLangLayoutBase(3, reinterpret_cast<HKL>(4));
    CKeyTimeBase KeyTimeBase(5);
    CKeyPressingTimeBase KeyPressingTimeBase(6);
    CKeyReleasingTimeBase KeyReleasingTimeBase(7);

    FileWriter << KeyFlagsBase;
    FileWriter << KeyVKCodeBase;
    FileWriter << KeyVKCodeLangLayoutBase;
    FileWriter << KeyTimeBase;
    FileWriter << KeyPressingTimeBase;
    FileWriter << KeyReleasingTimeBase;

    *pResult += L"\nKeyFlagsBase = ";
    *pResult += KeyFlagsBase.Flags;
    *pResult += L"\nKeyVKCodeBase = ";
    *pResult += KeyVKCodeBase.VKCode;
    *pResult += L"\nKeyVKCodeLangLayoutBase = ";
    *pResult += KeyVKCodeLangLayoutBase.VKCode;
    *pResult += L" ";
    *pResult += reinterpret_cast<int>(KeyVKCodeLangLayoutBase.Layout);
    *pResult += L"\nKeyTimeBase = ";
    *pResult += KeyTimeBase.Time;
    *pResult += L"\nKeyPressingTimeBase = ";
    *pResult += KeyPressingTimeBase.Time;
    *pResult += L"\nKeyReleasingTimeBase = ";
    *pResult += KeyReleasingTimeBase.Time;
 }
  void readFromFile(const std::wstring& FileName, UnicodeString* pResult) {
    NSLibrary::CFileReader FileReader(FileName);
    CKeyFlagsBase KeyFlagsBase(11);
    CKeyVKCodeBase KeyVKCodeBase(12);
    CKeyVKCodeLangLayoutBase KeyVKCodeLangLayoutBase(13, reinterpret_cast<HKL>(14));
    CKeyTimeBase KeyTimeBase(15);
    CKeyPressingTimeBase KeyPressingTimeBase(16);
    CKeyReleasingTimeBase KeyReleasingTimeBase(17);

    FileReader >> KeyFlagsBase;
    FileReader >> KeyVKCodeBase;
    FileReader >> KeyVKCodeLangLayoutBase;
    FileReader >> KeyTimeBase;
    FileReader >> KeyPressingTimeBase;
    FileReader >> KeyReleasingTimeBase;

    *pResult += L"\nKeyFlagsBase = ";
    *pResult += KeyFlagsBase.Flags;
    *pResult += L"\nKeyVKCodeBase = ";
    *pResult += KeyVKCodeBase.VKCode;
    *pResult += L"\nKeyVKCodeLangLayoutBase = ";
    *pResult += KeyVKCodeLangLayoutBase.VKCode;
    *pResult += L" ";
    *pResult += reinterpret_cast<int>(KeyVKCodeLangLayoutBase.Layout);
    *pResult += L"\nKeyTimeBase = ";
    *pResult += KeyTimeBase.Time;
    *pResult += L"\nKeyPressingTimeBase = ";
    *pResult += KeyPressingTimeBase.Time;
    *pResult += L"\nKeyReleasingTimeBase = ";
    *pResult += KeyReleasingTimeBase.Time;
  }
} PoliciesTester;
#endif
#endif
//---------------------------------------------------------------------------
// Definition of CKeyVKCodeBase
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSymbolKey() const {
  if (isNumber())
    return true;
  if (isEnglishSymbol())
    return true;
  if (0xba <= VKCode && VKCode <= 0xbf)
    return true;
  if (0xdb <= VKCode && VKCode <= 0xde)
    return true;
  if (VKCode == VK_ENG_TILDE)
    return true;
  return false;
}
// ---------------------------------------------------------------------------

wchar_t CKeyVKCodeBase::getSystemKeySymbol() const {
  if (isEnter())
    return SMB_ENTER;

  if (isLShift())
    return SMB_LSHIFT;
  if (isRShift())
    return SMB_RSHIFT;
  if (isShift())
    return SMB_SHIFT;

  if (isLCtrl())
    return SMB_LCTRL;
  if (isRCtrl())
    return SMB_RCTRL;
  if (isCtrl())
    return SMB_CTRL;

  if (isLAlt())
    return SMB_LALT;
  if (isRAlt())
    return SMB_RALT;
  if (isAlt())
    return SMB_ALT;

  if (isBackspace())
    return SMB_BACKSPACE;
  if (isCapslock())
    return SMB_CAPSLOCK;
  return L'?';
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
