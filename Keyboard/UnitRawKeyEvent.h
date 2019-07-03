// ---------------------------------------------------------------------------

#ifndef UnitRawKeyEventH
#define UnitRawKeyEventH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <deque>
#include "UnitKeyPolicies.h"
#include "UnitKeyboardState.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Declarations of CRawKey
// ---------------------------------------------------------------------------

class CRawKey : public CKeyVKCodeLangLayoutBase,
                public CKeyFlagsBase,
                public CKeyTimeBase {
public:
  CRawKey() = default;
  CRawKey(unsigned short newVKCode,
          HKL newLayout,
          unsigned char newFlags,
          microseconds newTime);

  template<class TStreamer>
  friend TStreamer& operator<<(TStreamer& Streamer, const CRawKey& RawKey);
  template<class TStreamer>
  friend TStreamer& operator>>(TStreamer& Streamer, CRawKey& RawKey);
};
// ---------------------------------------------------------------------------
// Declarations of CRawKey Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CRawKey& RawKey);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CRawKey& RawKey);
// ---------------------------------------------------------------------------
// Declaration of CRawEventContainer
// ---------------------------------------------------------------------------

class CRawEventContainer : protected std::deque<CRawKey> {
public:
  using CBase = std::deque<CRawKey>;

  using CBase::push_back;
  using CBase::empty;
  using CBase::front;
  using CBase::back;
  using CBase::size;
  using CBase::begin;
  using CBase::end;


  inline void clearKeys();
  inline void popFirstKey();

  inline void setToSystemKeyboardState();
  inline void setKeyboardState(const CKeyboardState& newKeyboardState);
  inline const CKeyboardState& getInitialKeyboardState() const;
  inline CKeyboardState& getInitialKeyboardState();
  void setNewKeyboardState(const CRawKey& RawKey);
private:
  CKeyboardState InitialKeyboardState;

  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CRawEventContainer& RawEventContainer);
  template<class TStreamer>
  friend TStreamer& operator>>( TStreamer& Streamer,
                                CRawEventContainer& RawEventContainer);
};
// ---------------------------------------------------------------------------
// Declaration of CRawEventContainer Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CRawEventContainer& RawEventContainer);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CRawEventContainer& RawEventContainer);
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------



namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Definition of CRawKey
// ---------------------------------------------------------------------------

CRawKey::CRawKey( unsigned short newVKCode,
                  HKL newLayout,
                  unsigned char newFlags,
                  microseconds newTime)
  : CKeyVKCodeLangLayoutBase(newVKCode, newLayout),
    CKeyFlagsBase(newFlags),
    CKeyTimeBase(newTime) {
}
// ---------------------------------------------------------------------------
// Definition of CRawKey Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CRawKey& RawKey) {
  Streamer << static_cast<const CKeyVKCodeLangLayoutBase&>(RawKey);
  Streamer << static_cast<const CKeyFlagsBase&>(RawKey);
  Streamer << static_cast<const CKeyTimeBase&>(RawKey);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CRawKey& RawKey) {
  Streamer >> static_cast<CKeyVKCodeLangLayoutBase&>(RawKey);
  Streamer >> static_cast<CKeyFlagsBase&>(RawKey);
  Streamer >> static_cast<CKeyTimeBase&>(RawKey);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definitions of CRawEventContainer
// ---------------------------------------------------------------------------

void CRawEventContainer::clearKeys() {
  while (!empty())
    popFirstKey();
}
// ---------------------------------------------------------------------------

void CRawEventContainer::popFirstKey() {
  setNewKeyboardState(front());
  CBase::pop_front();
}
// ---------------------------------------------------------------------------

void CRawEventContainer::setToSystemKeyboardState() {
  InitialKeyboardState.setToSystemKeyboardState();
}
// ---------------------------------------------------------------------------

void CRawEventContainer::setKeyboardState(
                              const CKeyboardState& newKeyboardState) {
  InitialKeyboardState.setKeyboardState(newKeyboardState);
}
// ---------------------------------------------------------------------------

const CKeyboardState& CRawEventContainer::getInitialKeyboardState() const {
  return InitialKeyboardState;
}
// ---------------------------------------------------------------------------

CKeyboardState& CRawEventContainer::getInitialKeyboardState() {
  return InitialKeyboardState;
}
// ---------------------------------------------------------------------------
// Definition of CRawEventContainer Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CRawEventContainer& RawEventContainer) {
  Streamer << static_cast<const CRawEventContainer::CBase&>(RawEventContainer);
  Streamer << RawEventContainer.InitialKeyboardState;
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CRawEventContainer& RawEventContainer) {
  Streamer >> static_cast<CRawEventContainer::CBase&>(RawEventContainer);
  Streamer >> RawEventContainer.InitialKeyboardState;
  return Streamer;
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
