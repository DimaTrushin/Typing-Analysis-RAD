// ---------------------------------------------------------------------------

#ifndef UnitKeyEventH
#define UnitKeyEventH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <vector>
#include "../Keyboard/UnitRawKeyEvent.h"
#include <cassert>
#include "../Debug/UnitDisabler.h"
// ---------------------------------------------------------------------------

#if !defined(__KEY_EVENT__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declarations of CKeyEvent
// ---------------------------------------------------------------------------

class CKeyEvent : public NSKeyboard::CKeyVKCodeLangLayoutBase,
                  public NSKeyboard::CKeyPressingTimeBase,
                  public NSKeyboard::CKeyReleasingTimeBase {
public:
  CKeyEvent() = default;
  inline CKeyEvent( unsigned short VKCode,
                    HKL newLayout,
                    microseconds PressingTime);
  inline CKeyEvent( unsigned short VKCode,
                    HKL newLayout,
                    microseconds PressingTime,
                    microseconds ReleasingTime);
  inline explicit CKeyEvent(const NSKeyboard::CRawKey& RawKey);

  inline void setReleasingTimeByDelay(microseconds HoldingTime);

  inline bool isReleasedBeforePressed(const CKeyEvent& KeyEvent) const;
  inline bool isReleasedBeforeReleased(const CKeyEvent& KeyEvent) const;
  inline bool isPressedBeforePressed(const CKeyEvent& KeyEvent) const;
  inline bool isPressedBeforeReleased(const CKeyEvent& KeyEvent) const;

  inline bool isReleasedAfterPressed(const CKeyEvent& KeyEvent) const;
  inline bool isReleasedAfterReleased(const CKeyEvent& KeyEvent) const;
  inline bool isPressedAfterPressed(const CKeyEvent& KeyEvent) const;
  inline bool isPressedAfterReleased(const CKeyEvent& KeyEvent) const;

  inline microseconds getDurationTime() const;

  inline wchar_t getKeySymbol(const NSKeyboard::CKeyboardState& KeyboardState) const;
protected:
private:
  constexpr static const microseconds kStandardDuration = 1;
};
// ---------------------------------------------------------------------------
// Declarations of CKeyEvent Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyEvent& KeyEvent);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyEvent& KeyEvent);
// ---------------------------------------------------------------------------
// Declaration of CSession
// ---------------------------------------------------------------------------

// Should make it vector but then I need to correct all
// algorithms using iterators and changing CSession
class CSession : protected std::deque<CKeyEvent> {
public:
  using CBase = std::deque<CKeyEvent>;

  using CBase::iterator;
  using CBase::const_iterator;

  inline CSession();
  inline CSession(const NSKeyboard::CKeyboardState& newKeyboardState);

  using CBase::push_back;
  using CBase::emplace_back;
  using CBase::back;
  using CBase::front;
  using CBase::empty;
  using CBase::size;
  using CBase::begin;
  using CBase::end;
  using CBase::cbegin;
  using CBase::cend;
  using CBase::operator[];

  inline void setKeyboardState(const NSKeyboard::CKeyboardState& newKeyboardState);
  inline const NSKeyboard::CKeyboardState& getKeyboardState() const;
  inline NSKeyboard::CKeyboardState& getKeyboardState();
  inline microseconds getDurationTime() const;
  inline microseconds getFirstPressingTime() const;
  inline microseconds getLastPressingTime() const;
  microseconds getResponseTime(const const_iterator& index) const;

  // ---------------------------------------------------------------------------
  // Declaration of CSession::CFirstReleasedOnTop
  // ---------------------------------------------------------------------------
  class CFirstReleasedOnTop {
  public:
    template<class TIterator>
    bool operator()(TIterator first,
                    TIterator second) const;
  };
private:
  NSKeyboard::CKeyboardState InitialKeyboardState;

  template<class TStreamer>
  friend TStreamer& operator<<(TStreamer& Streamer, const CSession& Session);
  template<class TStreamer>
  friend TStreamer& operator>>(TStreamer& Streamer, CSession& Session);
};
// ---------------------------------------------------------------------------
// Declaration of CSession Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CSession& Session);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CSession& Session);
// ---------------------------------------------------------------------------
// Declaration of CSeance
// ---------------------------------------------------------------------------

class CSeance : protected std::deque<CSession> {
public:
  using CBase = std::deque<CSession>;
  using CBase::iterator;
  using CBase::const_iterator;

  using CBase::begin;
  using CBase::end;
  using CBase::cbegin;
  using CBase::cend;
  using CBase::back;
  using CBase::pop_back;
  using CBase::front;
  using CBase::size;
  using CBase::empty;
  using CBase::operator[];
  microseconds getResponseTime(const const_iterator& index) const;
  void openNewSession(const NSKeyboard::CKeyboardState& KeyboardState);

  template<class TStreamer>
  friend TStreamer& operator<<(TStreamer& Streamer, const CSeance& Seance);
  template<class TStreamer>
  friend TStreamer& operator>>(TStreamer& Streamer, CSeance& Seance);
};
// ---------------------------------------------------------------------------
// Declaration of CSeance Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CSeance& Seance);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CSeance& Seance);
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definition of CKeyEvent
// ---------------------------------------------------------------------------

CKeyEvent::CKeyEvent( unsigned short VKCode,
                      HKL Layout,
                      microseconds PressingTime)
  : CKeyVKCodeLangLayoutBase(VKCode, Layout),
    CKeyPressingTimeBase(PressingTime),
    CKeyReleasingTimeBase(PressingTime + kStandardDuration) {
}
// ---------------------------------------------------------------------------

CKeyEvent::CKeyEvent( unsigned short VKCode,
                      HKL Layout,
                      microseconds PressingTime,
                      microseconds ReleasingTime)
  : CKeyVKCodeLangLayoutBase(VKCode, Layout),
    CKeyPressingTimeBase(PressingTime),
    CKeyReleasingTimeBase(ReleasingTime) {
  assert(PressingTime < ReleasingTime);
}
// ---------------------------------------------------------------------------

CKeyEvent::CKeyEvent(const NSKeyboard::CRawKey& RawKey)
  : CKeyEvent(RawKey.getVKCode(), RawKey.getLayout(), RawKey.getTime()) {
}
// ---------------------------------------------------------------------------

void CKeyEvent::setReleasingTimeByDelay(microseconds HoldingTime) {
  setReleasingTime(CKeyPressingTimeBase::Time + HoldingTime);
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isReleasedBeforePressed(const CKeyEvent& KeyEvent) const {
  return isReleasedBefore(KeyEvent.getPressingTime());
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isReleasedBeforeReleased(const CKeyEvent& KeyEvent) const {
  return isReleasedBefore(KeyEvent.getReleasingTime());
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isPressedBeforePressed(const CKeyEvent& KeyEvent) const {
  return isPressedBefore(KeyEvent.getPressingTime());
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isPressedBeforeReleased(const CKeyEvent& KeyEvent) const {
  return isPressedBefore(KeyEvent.getReleasingTime());
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isReleasedAfterPressed(const CKeyEvent& KeyEvent) const {
  return isReleasedAfter(KeyEvent.getPressingTime());
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isReleasedAfterReleased(const CKeyEvent& KeyEvent) const {
  return isReleasedAfter(KeyEvent.getReleasingTime());
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isPressedAfterPressed(const CKeyEvent& KeyEvent) const {
  return isPressedAfter(KeyEvent.getPressingTime());
}
// ---------------------------------------------------------------------------

bool CKeyEvent::isPressedAfterReleased(const CKeyEvent& KeyEvent) const {
  return isPressedAfter(KeyEvent.getReleasingTime());
}
// ---------------------------------------------------------------------------

microseconds CKeyEvent::getDurationTime() const {
  return CKeyReleasingTimeBase::Time - CKeyPressingTimeBase::Time;
}
//---------------------------------------------------------------------------

wchar_t CKeyEvent::getKeySymbol(
                      const NSKeyboard::CKeyboardState& KeyboardState) const {
  wchar_t keyName;
  if(ToUnicodeEx( getVKCode(),
                  getScanCode(),
                  KeyboardState.getLowLevelKeyboardState(),
                  &keyName,
                  1,
                  0,
                  getLayout()) == 1)
    return keyName;
  return L'?';
}
// ---------------------------------------------------------------------------
// Definition of CKeyEvent Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyEvent& KeyEvent) {
  Streamer <<
        static_cast<const NSKeyboard::CKeyVKCodeLangLayoutBase&>(KeyEvent);
  Streamer << static_cast<const NSKeyboard::CKeyPressingTimeBase&>(KeyEvent);
  Streamer << static_cast<const NSKeyboard::CKeyReleasingTimeBase&>(KeyEvent);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyEvent& KeyEvent) {
  Streamer >> static_cast<NSKeyboard::CKeyVKCodeLangLayoutBase&>(KeyEvent);
  Streamer >> static_cast<NSKeyboard::CKeyPressingTimeBase&>(KeyEvent);
  Streamer >> static_cast<NSKeyboard::CKeyReleasingTimeBase&>(KeyEvent);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CSession
// ---------------------------------------------------------------------------

CSession::CSession() {
}
// ---------------------------------------------------------------------------

CSession::CSession(const NSKeyboard::CKeyboardState& newKeyboardState)
  : InitialKeyboardState(newKeyboardState) {
}
// ---------------------------------------------------------------------------

void CSession::setKeyboardState(
                    const NSKeyboard::CKeyboardState& newKeyboardState) {
  InitialKeyboardState = newKeyboardState;
}
// ---------------------------------------------------------------------------

const NSKeyboard::CKeyboardState& CSession::getKeyboardState() const {
  return InitialKeyboardState;
}
// ---------------------------------------------------------------------------

NSKeyboard::CKeyboardState& CSession::getKeyboardState() {
  return InitialKeyboardState;
}
// ---------------------------------------------------------------------------

microseconds CSession::getDurationTime() const {
  if (empty())
    return 0;
  return getLastPressingTime() - getFirstPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CSession::getFirstPressingTime() const {
  return front().getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CSession::getLastPressingTime() const {
  return back().getPressingTime();
}
// ---------------------------------------------------------------------------

microseconds CSession::getResponseTime(const const_iterator& index) const {
  if (index == begin())
    return 0;
  auto previous = index;
  --previous;
  return  index->getPressingTime() -
          previous->getPressingTime();
}
// ---------------------------------------------------------------------------
// Definition of CSession Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CSession& Session) {
  Streamer << static_cast<const CSession::CBase&>(Session);
  Streamer << Session.InitialKeyboardState;
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CSession& Session) {
  Streamer >> static_cast<CSession::CBase&>(Session);
  Streamer >> Session.InitialKeyboardState;
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CSession::CFirstReleasedOnTop
// ---------------------------------------------------------------------------

template<class TIterator>
bool CSession::CFirstReleasedOnTop::operator()(
                                TIterator first,
                                TIterator second) const {
  // TO DO
  // Add verification that TIterator is either iterator or const_iterator

  // The inequality must be strict here
  return first->getReleasingTime() > second->getReleasingTime();
}
// ---------------------------------------------------------------------------
// Definition of CSeance Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CSeance& Seance) {
  Streamer << static_cast<const CSeance::CBase&>(Seance);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CSeance& Seance) {
  Streamer >> static_cast<CSeance::CBase&>(Seance);
  return Streamer;
}
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
#endif
