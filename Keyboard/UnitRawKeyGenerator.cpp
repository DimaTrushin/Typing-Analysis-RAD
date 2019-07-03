//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitRawKeyGenerator.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definition of CRawKeyGenerator
//---------------------------------------------------------------------------

// Windows API distinguishs left and right versions of
// Shift, Ctrl, Alt as follows:
// Shift is signed by MakeCode. Left is 0x2a, Right is 0x36
// Alt and Ctrl are signed by second bit of Flags:
// Left has 0 bit, Right has 1 bit.

// Since Application Kernel does not store MakeCode
// we change VKCode and Flags appropriately.
CRawKey CRawKeyGenerator::GenerateRawKey(
                          microseconds Time,
                          HKL Layout,
                          const RAWKEYBOARD& KeyboardData) {
  if (isTwoSidedShift(KeyboardData))
    return GenerateRawKeyShift(Time, Layout, KeyboardData);

  if (isTwoSidedCtrl(KeyboardData))
    return GenerateRawKeyCtrl(Time, Layout, KeyboardData);

  if (isTwoSidedAlt(KeyboardData))
    return GenerateRawKeyAlt(Time, Layout, KeyboardData);

  return GenerateRawKeyRegular(Time, Layout, KeyboardData);
}
// ---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyShift(
                          microseconds Time,
                          HKL Layout,
                          const RAWKEYBOARD& KeyboardData) {
  if (isLeftShift(KeyboardData))
    return GenerateRawKeyLShift(Time, Layout, KeyboardData);
  else
    return GenerateRawKeyRShift(Time, Layout, KeyboardData);
}
// ---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyLShift(
                                      microseconds Time,
                                      HKL Layout,
                                      const RAWKEYBOARD& KeyboardData) {
  return CRawKey( VK_LSHIFT,
                  Layout,
                  KeyboardData.Flags,
                  Time);
}
// ---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyRShift(
                                      microseconds Time,
                                      HKL Layout,
                                      const RAWKEYBOARD& KeyboardData) {
  return CRawKey( VK_RSHIFT,
                  Layout,
                  KeyboardData.Flags,
                  Time);
}
// ---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyAlt(
                                      microseconds Time,
                                      HKL Layout,
                                      const RAWKEYBOARD& KeyboardData) {
  unsigned char newFlags;
  unsigned short newVKCode;
  if (isLeftAlt(KeyboardData)) {
    newFlags = KeyboardData.Flags;
    newVKCode = VK_LMENU;
  }
  else {
    newFlags = KeyboardData.Flags & 1;
    newVKCode = VK_RMENU;
  }
  return CRawKey( newVKCode,
                  Layout,
                  newFlags,
                  Time);
}
// ---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyCtrl(
                                      microseconds Time,
                                      HKL Layout,
                                      const RAWKEYBOARD& KeyboardData) {
  unsigned char newFlags;
  unsigned short newVKCode;
  if (isLeftCtrl(KeyboardData)) {
    newFlags = KeyboardData.Flags;
    newVKCode = VK_LCONTROL;
  }
  else {
    newFlags = KeyboardData.Flags & 1;
    newVKCode = VK_RCONTROL;
  }
  return CRawKey( newVKCode,
                  Layout,
                  newFlags,
                  Time);
}
// ---------------------------------------------------------------------------

CRawKey CRawKeyGenerator::GenerateRawKeyRegular(
                                      microseconds Time,
                                      HKL Layout,
                                      const RAWKEYBOARD& KeyboardData) {
  return CRawKey( KeyboardData.VKey,
                  Layout,
                  KeyboardData.Flags,
                  Time);
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isTwoSidedShift(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.VKey == VK_SHIFT;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isTwoSidedCtrl(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.VKey == VK_CONTROL;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isTwoSidedAlt(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.VKey == VK_MENU;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isLeftShift(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.MakeCode == 0x2a;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isRightShift(const RAWKEYBOARD& KeyboardData) {
  return KeyboardData.MakeCode == 0x36;
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isLeftCtrl(const RAWKEYBOARD& KeyboardData) {
  return secondBitIsZero(KeyboardData.Flags);
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::isLeftAlt(const RAWKEYBOARD& KeyboardData) {
  return secondBitIsZero(KeyboardData.Flags);
}
//---------------------------------------------------------------------------

bool CRawKeyGenerator::secondBitIsZero(unsigned char Flags) {
  return ((Flags >> 1) & 1) == 0;
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
