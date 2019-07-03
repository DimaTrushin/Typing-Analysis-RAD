//---------------------------------------------------------------------------

#ifndef UnitKeyPoliciesH
#define UnitKeyPoliciesH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKeyboardRelatedDefinitions.h"
#include "../UnitTimer.h"
//---------------------------------------------------------------------------

#define __STORE_LAYOUT_AS_HKL__

namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Forward Declaration of CPoliciesTester
//---------------------------------------------------------------------------

class CPoliciesTester;
//---------------------------------------------------------------------------
// Declaration of CScanCodeMaker
//---------------------------------------------------------------------------

class CScanCodeMaker {
public:
  inline static unsigned short makeScanCode(unsigned short VKCode,
                                            HKL Layout);
};
//---------------------------------------------------------------------------
// Declaration of CKeyFlagsBase
//---------------------------------------------------------------------------

class CKeyFlagsBase {
  friend class CPoliciesTester;
public:
  inline CKeyFlagsBase(unsigned char newFlags = kDefaultFlags);

  inline unsigned char getFlags() const;
  inline bool isPressed() const;
  inline bool isReleased() const;

protected:
  ~CKeyFlagsBase() = default;
  unsigned char Flags;

  constexpr static unsigned char kDefaultFlags = 0;

  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CKeyFlagsBase& KeyFlagBase);
  template<class TStreamer>
  friend TStreamer& operator>>( TStreamer& Streamer,
                                CKeyFlagsBase& KeyFlagBase);
};
//---------------------------------------------------------------------------
// Declaration of CKeyFlagsBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyFlagsBase& KeyFlagBase);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyFlagsBase& KeyFlagBase);
//---------------------------------------------------------------------------
// Declaration of CKeyVKCodeBase
//---------------------------------------------------------------------------

class CKeyVKCodeBase {
  friend class CPoliciesTester;
public:
  inline CKeyVKCodeBase(unsigned short newVKCode = kDefaultVKCode);

  inline bool isLShift() const;
  inline bool isRShift() const;
  inline bool isShift() const;
  inline bool isAnyShift() const;
  inline bool isLCtrl() const;
  inline bool isRCtrl() const;
  inline bool isCtrl() const;
  inline bool isAnyCtrl() const;
  inline bool isLAlt() const;
  inline bool isRAlt() const;
  inline bool isAlt() const;
  inline bool isAnyAlt() const;
  inline bool isEnter() const;
  inline bool isBackspace() const;
  inline bool isCapslock() const;
  inline bool isSpacebar() const;
  inline bool isEscape() const;
  inline bool isSystemKey() const;
  bool isSymbolKey() const;
  inline bool isSymbolOrSpace() const;
  inline bool isNumber() const;
  inline bool isEnglishSymbol() const;
  wchar_t getSystemKeySymbol() const;
  inline unsigned short getVKCode() const;
protected:
  ~CKeyVKCodeBase() = default;
  unsigned short VKCode;

  constexpr static unsigned short kDefaultVKCode = 0;
  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CKeyVKCodeBase& KeyVKCodeBase);
  template<class TStreamer>
  friend TStreamer& operator>>( TStreamer& Streamer,
                                CKeyVKCodeBase& KeyVKCodeBase);

};
//---------------------------------------------------------------------------
// Declaration of CKeyVKCodeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyVKCodeBase& KeyVKCodeBase);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyVKCodeBase& KeyVKCodeBase);
//---------------------------------------------------------------------------
// Declaration of CKeyVKCodeLangLayoutBase
//---------------------------------------------------------------------------

class CKeyVKCodeLangLayoutBase : public CKeyVKCodeBase{
  friend class CPoliciesTester;
public:
  inline CKeyVKCodeLangLayoutBase(unsigned short newVKCode = kDefaultVKCode,
                                  HKL newLayout = kDefaultLayout);
  inline bool isDeadKey() const;
  inline unsigned short getScanCode() const;
  //wchar_t getKeySymbol() const;
  inline HKL getLayout() const;
protected:
  ~CKeyVKCodeLangLayoutBase() = default;
  #ifdef __STORE_LAYOUT_AS_HKL__
  HKL Layout;
  #else
  long Layout;
  #endif
  constexpr static HKL kDefaultLayout = 0;
  using CKeyVKCodeBase::kDefaultVKCode;

  template<class TStreamer>
  friend TStreamer& operator<<(
                      TStreamer& Streamer,
                      const CKeyVKCodeLangLayoutBase& KeyVKCodeLangLayoutBase);
  template<class TStreamer>
  friend TStreamer& operator>>(
                      TStreamer& Streamer,
                      CKeyVKCodeLangLayoutBase& KeyVKCodeLangLayoutBase);
};
//---------------------------------------------------------------------------
// Declaration of CKeyVKCodeLangLayoutBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyVKCodeLangLayoutBase& KeyVKCodeLangLayoutBase);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyVKCodeLangLayoutBase& KeyVKCodeLangLayoutBase);
//---------------------------------------------------------------------------
// Declaration of CKeyTimeBase
//---------------------------------------------------------------------------

class CKeyTimeBase {
  friend class CPoliciesTester;
public:
  inline CKeyTimeBase(microseconds newTime = kDefaultTime);
  inline microseconds getTime() const;
protected:
  ~CKeyTimeBase() = default;
  microseconds Time;
  constexpr static microseconds kDefaultTime = 0;

  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CKeyTimeBase& KeyTimeBase);
  template<class TStreamer>
  friend TStreamer& operator>>( TStreamer& Streamer,
                                CKeyTimeBase& KeyTimeBase);
};
//---------------------------------------------------------------------------
// Declaration of CKeyTimeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyTimeBase& KeyTimeBase);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyTimeBase& KeyTimeBase);
//---------------------------------------------------------------------------
// Declaration of CKeyPressingTimeBase
//---------------------------------------------------------------------------

class CKeyPressingTimeBase : protected CKeyTimeBase {
  friend class CPoliciesTester;
public:
  inline CKeyPressingTimeBase(microseconds PressingTime = kDefaultTime);
  inline microseconds getPressingTime() const;
  inline bool isPressedBefore(microseconds Time) const;
  inline bool isPressedAfter(microseconds Time) const;
protected:
  ~CKeyPressingTimeBase() = default;
  using CKeyTimeBase::kDefaultTime;

  template<class TStreamer>
  friend TStreamer& operator<<(
                        TStreamer& Streamer,
                        const CKeyPressingTimeBase& KeyPressingTimeBase);
  template<class TStreamer>
  friend TStreamer& operator>>(
                        TStreamer& Streamer,
                        CKeyPressingTimeBase& KeyPressingTimeBase);
};
//---------------------------------------------------------------------------
// Declaration of CKeyPressingTimeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyPressingTimeBase& KeyPressingTimeBase);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyPressingTimeBase& KeyPressingTimeBase);
//---------------------------------------------------------------------------
// Declaration of CKeyReleasingTimeBase
//---------------------------------------------------------------------------

class CKeyReleasingTimeBase : protected CKeyTimeBase {
  friend class CPoliciesTester;
public:
  inline CKeyReleasingTimeBase(microseconds ReleasingTime = kDefaultTime);
  inline microseconds getReleasingTime() const;
  inline void setReleasingTime(microseconds ReleasingTime);
  inline bool isReleasedBefore(microseconds Time) const;
  inline bool isReleasedAfter(microseconds Time) const;
protected:
  ~CKeyReleasingTimeBase() = default;
  using CKeyTimeBase::kDefaultTime;

  template<class TStreamer>
  friend TStreamer& operator<<(
                      TStreamer& Streamer,
                      const CKeyReleasingTimeBase& KeyReleasingTimeBase);

  template<class TStreamer>
  friend TStreamer& operator>>(
                      TStreamer& Streamer,
                      CKeyReleasingTimeBase& KeyReleasingTimeBase);
};
//---------------------------------------------------------------------------
// Declaration of CKeyReleasingTimeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyReleasingTimeBase& KeyReleasingTimeBase);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyReleasingTimeBase& KeyReleasingTimeBase);
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------


namespace NSApplication {
namespace NSKeyboard {
//---------------------------------------------------------------------------
// Definition of CScanCodeMaker
//---------------------------------------------------------------------------

unsigned short CScanCodeMaker::makeScanCode(unsigned short VKCode,
                                            HKL Layout) {
  return MapVirtualKeyEx(VKCode, MAPVK_VK_TO_VSC, Layout);
}
//---------------------------------------------------------------------------
// Definition of CKeyFlagsBase
//---------------------------------------------------------------------------

CKeyFlagsBase::CKeyFlagsBase(unsigned char newFlags)
  : Flags(newFlags) {
}
//---------------------------------------------------------------------------

unsigned char CKeyFlagsBase::getFlags() const {
  return Flags;
}
//---------------------------------------------------------------------------

bool CKeyFlagsBase::isPressed() const {
  return (Flags & 1) == RI_KEY_MAKE;
}
//---------------------------------------------------------------------------

bool CKeyFlagsBase::isReleased() const {
  return (Flags & 1) == RI_KEY_BREAK;
}
//---------------------------------------------------------------------------
// Definition of CKeyFlagsBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyFlagsBase& KeyFlagBase) {
  Streamer << KeyFlagBase.Flags;
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyFlagsBase& KeyFlagBase) {
  Streamer >> KeyFlagBase.Flags;
  return Streamer;
}
//---------------------------------------------------------------------------
// Definition of CKeyVKCodeBase
//---------------------------------------------------------------------------

CKeyVKCodeBase::CKeyVKCodeBase(unsigned short newVKCode)
  : VKCode(newVKCode) {
}
//---------------------------------------------------------------------------

bool CKeyVKCodeBase::isLShift() const {
  return VKCode == VK_LSHIFT;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isRShift() const {
  return VKCode == VK_RSHIFT;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isShift() const {
  return VKCode == VK_SHIFT;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAnyShift() const {
  return isLShift() || isRShift() || isShift();
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isLCtrl() const {
  return VKCode == VK_LCONTROL;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isRCtrl() const {
  return VKCode == VK_RCONTROL;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isCtrl() const {
  return VKCode == VK_CONTROL;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAnyCtrl() const {
  return isLCtrl() || isRCtrl() || isCtrl();
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isLAlt() const {
  return VKCode == VK_LMENU;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isRAlt() const {
  return VKCode == VK_RMENU;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAlt() const {
  return VKCode == VK_MENU;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isAnyAlt() const {
  return isLAlt() || isRAlt() || isAlt();
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isEnter() const {
  return VKCode == VK_RETURN;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isBackspace() const {
  return VKCode == VK_BACK;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isCapslock() const {
  return VKCode == VK_CAPITAL;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSpacebar() const {
  return VKCode == VK_SPACE;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isEscape() const {
  return VKCode == VK_ESCAPE;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSystemKey() const {
  return  isAnyShift() || isAnyCtrl() || isAnyAlt() ||
          isCapslock() || isEnter()   || isBackspace();
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isSymbolOrSpace() const {
  return isSpacebar() || isSymbolKey();
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isNumber() const {
  return VK_0 <= VKCode && VKCode <= VK_9;
}
// ---------------------------------------------------------------------------

bool CKeyVKCodeBase::isEnglishSymbol() const {
  return VK_A <= VKCode && VKCode <= VK_Z;
}
//---------------------------------------------------------------------------

unsigned short CKeyVKCodeBase::getVKCode() const {
  return VKCode;
}
//---------------------------------------------------------------------------
// Definition of CKeyVKCodeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyVKCodeBase& KeyVKCodeBase) {
  Streamer << KeyVKCodeBase.VKCode;
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyVKCodeBase& KeyVKCodeBase) {
  Streamer >> KeyVKCodeBase.VKCode;
  return Streamer;
}
//---------------------------------------------------------------------------
// Definition of CKeyVKCodeLangLayoutBase
//---------------------------------------------------------------------------

CKeyVKCodeLangLayoutBase::CKeyVKCodeLangLayoutBase(
                                        unsigned short newVKCode,
                                        HKL newLayout)
  : CKeyVKCodeBase(newVKCode),
    #ifdef __STORE_LAYOUT_AS_HKL__
    Layout(newLayout) {
    #else
    Layout(HandleToLong(newLayout)) {
    #endif
}
//---------------------------------------------------------------------------

bool CKeyVKCodeLangLayoutBase::isDeadKey() const {
  unsigned int Flag = MapVirtualKeyEx(VKCode,
                                      MAPVK_VK_TO_CHAR,
                                      getLayout());
  if (((Flag << 1) >> 1) ^ Flag)
    return true;
  return false;
}

// ---------------------------------------------------------------------------

unsigned short CKeyVKCodeLangLayoutBase::getScanCode() const {
  return CScanCodeMaker::makeScanCode(VKCode, getLayout());
}
// ---------------------------------------------------------------------------

//wchar_t CKeyVKCodeLangLayoutBase::getKeySymbol() const {
//  wchar_t keyName;
//  unsigned char emptyKeyboardState[256] = {0};
//  ToUnicodeEx(VKCode,
//              getScanCode(),
//              emptyKeyboardState,
//              &keyName,
//              1,
//              0,
//              getLayout());
//  return keyName;
//}
//---------------------------------------------------------------------------

HKL CKeyVKCodeLangLayoutBase::getLayout() const {
  #ifdef __STORE_LAYOUT_AS_HKL__
  return Layout;
  #else
  return reinterpret_cast<HKL>(LongToHandle(Layout));
  #endif
}
//---------------------------------------------------------------------------
// Definition of CKeyVKCodeLangLayoutBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyVKCodeLangLayoutBase& KeyVKCodeLangLayoutBase) {
  Streamer << static_cast<const CKeyVKCodeBase&>(KeyVKCodeLangLayoutBase);
  #ifdef __STORE_LAYOUT_AS_HKL__
  static_assert(sizeof(int) == sizeof(HKL), "Incompatible types");
  Streamer << reinterpret_cast<int>(KeyVKCodeLangLayoutBase.Layout);
  #else
  Streamer << KeyVKCodeLangLayoutBase.Layout;
  #endif
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyVKCodeLangLayoutBase& KeyVKCodeLangLayoutBase) {
  Streamer >> static_cast<CKeyVKCodeBase&>(KeyVKCodeLangLayoutBase);
  #ifdef __STORE_LAYOUT_AS_HKL__
  int tmpLayout;
  Streamer >> tmpLayout;
  static_assert(sizeof(int) == sizeof(HKL), "Incompatible types");
  KeyVKCodeLangLayoutBase.Layout = reinterpret_cast<HKL>(tmpLayout);
  #else
  Streamer >> KeyVKCodeLangLayoutBase.Layout;
  #endif
  return Streamer;
}
//---------------------------------------------------------------------------
// Definition of CKeyTimeBase
//---------------------------------------------------------------------------

CKeyTimeBase::CKeyTimeBase(microseconds newTime)
  : Time(newTime) {
}
//---------------------------------------------------------------------------

microseconds CKeyTimeBase::getTime() const {
  return Time;
}
//---------------------------------------------------------------------------
// Declaration of CKeyTimeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyTimeBase& KeyTimeBase) {
  Streamer << KeyTimeBase.Time;
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyTimeBase& KeyTimeBase) {
  Streamer >> KeyTimeBase.Time;
  return Streamer;
}
//---------------------------------------------------------------------------
// Definition of CKeyPressingTimeBase
//---------------------------------------------------------------------------

CKeyPressingTimeBase::CKeyPressingTimeBase(microseconds PressingTime)
  : CKeyTimeBase(PressingTime) {
}
//---------------------------------------------------------------------------

microseconds CKeyPressingTimeBase::getPressingTime() const {
  return CKeyTimeBase::getTime();
}
//---------------------------------------------------------------------------

bool CKeyPressingTimeBase::isPressedBefore(microseconds Time) const {
  return CKeyTimeBase::Time < Time;
}
//---------------------------------------------------------------------------

bool CKeyPressingTimeBase::isPressedAfter(microseconds Time) const {
  return CKeyTimeBase::Time > Time;
}
//---------------------------------------------------------------------------
// Definition of CKeyPressingTimeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyPressingTimeBase& KeyPressingTimeBase) {
  Streamer << static_cast<const CKeyTimeBase&>(KeyPressingTimeBase);
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyPressingTimeBase& KeyPressingTimeBase) {
  Streamer >> static_cast<CKeyTimeBase&>(KeyPressingTimeBase);
  return Streamer;
}
//---------------------------------------------------------------------------
// Definition of CKeyReleasingTimeBase
//---------------------------------------------------------------------------

CKeyReleasingTimeBase::CKeyReleasingTimeBase(microseconds ReleasingTime)
  : CKeyTimeBase(ReleasingTime) {
}
//---------------------------------------------------------------------------

microseconds CKeyReleasingTimeBase::getReleasingTime() const {
  return CKeyTimeBase::getTime();
}
//---------------------------------------------------------------------------

void CKeyReleasingTimeBase::setReleasingTime(microseconds ReleasingTime) {
  CKeyTimeBase::Time = ReleasingTime;
}
//---------------------------------------------------------------------------

bool CKeyReleasingTimeBase::isReleasedBefore(microseconds Time) const {
  return CKeyTimeBase::Time < Time;
}
//---------------------------------------------------------------------------

bool CKeyReleasingTimeBase::isReleasedAfter(microseconds Time) const {
  return CKeyTimeBase::Time > Time;
}
//---------------------------------------------------------------------------
// Definition of CKeyReleasingTimeBase Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyReleasingTimeBase& KeyReleasingTimeBase) {
  Streamer << static_cast<const CKeyTimeBase&>(KeyReleasingTimeBase);
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyReleasingTimeBase& KeyReleasingTimeBase) {
  Streamer >> static_cast<CKeyTimeBase&>(KeyReleasingTimeBase);
  return Streamer;
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
