// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitKeyboardState.h"

#if !defined(NDEBUG)
//#define __KEYBOARD__STATE__TEST__
#if defined(__KEYBOARD__STATE__TEST__)
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
#if defined(__KEYBOARD__STATE__TEST__)
class CKeyboardStateTester {
public:
  CKeyboardStateTester() {
    runTest();
  }
private:
  void runTest() {
    std::wstring FileName(L"KeyboardStateTests.bin");
    UnicodeString Result(L"KeyboardStateTests:");
    writeToFile(FileName, &Result);
    readFromFile(FileName, &Result);
    ShowMessage(Result.c_str());
  }
  void writeToFile(const std::wstring& FileName, UnicodeString* pResult) {
    NSLibrary::CFileWriter FileWriter(FileName);
    CKeyboardState KeyboardState;
    KeyboardState.setToSystemKeyboardState();
    FileWriter << KeyboardState;
    //printKeyboardState(KeyboardState, pResult);
    *pResult += L"\nKeys\n";
    *pResult += KeyboardState.getKeyState(VK_CAPITAL);
  }
  void readFromFile(const std::wstring& FileName, UnicodeString* pResult) {
   NSLibrary::CFileReader FileReader(FileName);
    CKeyboardState KeyboardState;
    FileReader >> KeyboardState;
    //printKeyboardState(KeyboardState, pResult);
    *pResult += L"\nKeys\n";
    *pResult += KeyboardState.getKeyState(VK_CAPITAL);
  }
  void printKeyboardState( const CKeyboardState& KeyboardState,
                           UnicodeString* pResult) {
    *pResult += L"\nKeyboardState\n";
    for (auto index = 0; index < 256; ++index) {
      *pResult += KeyboardState.getKeyState(index);
      *pResult += L" ";
    }
  }

} KeyboardStateTester;
#endif
#endif
// ---------------------------------------------------------------------------
// Definitions of CKeyboardState
// ---------------------------------------------------------------------------

CKeyboardState::CKeyboardState() {
  for (auto index = getBeginVKCode(); index < getEndVKCode(); ++index)
    LowLevelKeyboardState[index] = 0;
}
// ---------------------------------------------------------------------------

void CKeyboardState::setToSystemKeyboardState() {
  GetKeyboardState(&(LowLevelKeyboardState[0]));
}

// ---------------------------------------------------------------------------

void CKeyboardState::setKeyboardState(
                        const CKeyboardState& CurrentKeyboardState) {
  for (auto index = getBeginVKCode(); index < getEndVKCode(); ++index)
    LowLevelKeyboardState[index] =
        CurrentKeyboardState.LowLevelKeyboardState[index];
}
// ---------------------------------------------------------------------------

void CKeyboardState::setKeyState( unsigned short VK_Code,
                                  unsigned char KeyFlag) {
  LowLevelKeyboardState[VK_Code] = KeyFlag;
}
// ---------------------------------------------------------------------------

const unsigned char* CKeyboardState::getLowLevelKeyboardState() const {
  return &(LowLevelKeyboardState[0]);
}
// ---------------------------------------------------------------------------

unsigned char CKeyboardState::getKeyState(unsigned short VK_Code) const {
  return LowLevelKeyboardState[VK_Code];
}
// ---------------------------------------------------------------------------

void CKeyboardState::PressKey(unsigned short VK_Code) {
  // First press the key itself
  LowLevelKeyboardState[VK_Code] =
                  (LowLevelKeyboardState[VK_Code] | 128) ^ 1;
  // The application kernel uses left and right versions
  // of Ctrl, Alt, Shift. Windows API uses twosided versions
  // of those in almost all cases. Hence, we need to press
  // twosided key also.
  pressTwoSidedKey(VK_Code, VK_LCONTROL, VK_RCONTROL, VK_CONTROL);
  pressTwoSidedKey(VK_Code, VK_LSHIFT, VK_RSHIFT, VK_SHIFT);
  pressTwoSidedKey(VK_Code, VK_LMENU, VK_RMENU, VK_MENU);
}
// ---------------------------------------------------------------------------

void CKeyboardState::ReleaseKey(unsigned short VK_Code) {
  // First press the key itself
  LowLevelKeyboardState[VK_Code] =
                      LowLevelKeyboardState[VK_Code] & 127;
  // The application kernel uses left and right versions
  // of Ctrl, Alt, Shift. Windows API uses twosided versions
  // of those in almost all cases. Hence, we need to release
  // twosided key also.
  releaseTwoSidedKey(VK_Code, VK_LCONTROL, VK_RCONTROL, VK_CONTROL);
  releaseTwoSidedKey(VK_Code, VK_LSHIFT, VK_RSHIFT, VK_SHIFT);
  releaseTwoSidedKey(VK_Code, VK_LMENU, VK_RMENU, VK_MENU);
}
// ---------------------------------------------------------------------------

bool CKeyboardState::isPressed(unsigned short VK_Code) const {
  if (getKeyState(VK_Code) & 128)
    return true;
  return false;
}
// ---------------------------------------------------------------------------

bool CKeyboardState::isReleased(unsigned short VK_Code) const {
  return !isPressed(VK_Code);
}
// ---------------------------------------------------------------------------

bool CKeyboardState::isToggled(unsigned short VK_Code) const {
  if (getKeyState(VK_Code) & 1)
    return true;
  return false;
}
// ---------------------------------------------------------------------------

void CKeyboardState::pressTwoSidedKey(unsigned short VK_Code,
                                      unsigned short VK_Left,
                                      unsigned short VK_Right,
                                      unsigned short VK_TwoSided) {
  if (VK_Code == VK_Left || VK_Code == VK_Right)
    LowLevelKeyboardState[VK_TwoSided] =
        (LowLevelKeyboardState[VK_TwoSided] | 128) ^ 1;
}
// ---------------------------------------------------------------------------

void CKeyboardState::releaseTwoSidedKey(unsigned short VK_Code,
                                        unsigned short VK_Left,
                                        unsigned short VK_Right,
                                        unsigned short VK_TwoSided) {
  if ((VK_Code == VK_Left && isReleased(VK_Right)) ||
      (VK_Code == VK_Right && isReleased(VK_Left)))
    LowLevelKeyboardState[VK_TwoSided] =
        LowLevelKeyboardState[VK_TwoSided] & 127;
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

