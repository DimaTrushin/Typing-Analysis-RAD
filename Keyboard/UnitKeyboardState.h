// ---------------------------------------------------------------------------

#ifndef UnitKeyboardStateH
#define UnitKeyboardStateH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <windows.h>
#include <array>

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Using
// ---------------------------------------------------------------------------

using CLowLevelKeyboardState = std::array<unsigned char, 256>;

// ---------------------------------------------------------------------------
// Declaration of CKeyboardState
// ---------------------------------------------------------------------------

class CKeyboardState {
public:
  CKeyboardState();
  void setToSystemKeyboardState();
  void setKeyboardState(const CKeyboardState& currentKeyboardState);
  void setKeyState(unsigned short VK_Code, unsigned char KeyFlag);

  // For the next two functions:
  // The application kernel uses left and right versions
  // of Ctrl, Alt, Shift. Windows API uses twosided versions
  // of those in almost all cases (e.g. ToUnicodeEx).
  // Thus, the functions additionally deal with twosided
  // versions of Ctrl, Alt, Shift, even if a onesided key
  // is passed.
  void PressKey(unsigned short VK_Code);
  void ReleaseKey(unsigned short VK_Code);

  const unsigned char* getLowLevelKeyboardState() const;
  unsigned char getKeyState(unsigned short VK_Code) const;
  bool isPressed(unsigned short VK_Code) const;
  bool isReleased(unsigned short VK_Code) const;
  bool isToggled(unsigned short VK_Code) const;

  static constexpr unsigned short getBeginVKCode();
  static constexpr unsigned short getEndVKCode();

private:
  inline void pressTwoSidedKey( unsigned short VK_Code,
                                unsigned short VK_Left,
                                unsigned short VK_Right,
                                unsigned short VK_TwoSided);
  inline void releaseTwoSidedKey( unsigned short VK_Code,
                                  unsigned short VK_Left,
                                  unsigned short VK_Right,
                                  unsigned short VK_TwoSided);
  CLowLevelKeyboardState LowLevelKeyboardState;

  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CKeyboardState& KeyboardState);
  template<class TStreamer>
  friend TStreamer& operator>>( TStreamer& Streamer,
                                CKeyboardState& KeyboardState);
};
// ---------------------------------------------------------------------------
// Declaration of CKeyboardState Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKeyboardState& KeyboardState);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyboardState& KeyboardState);
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

namespace NSApplication{
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Definition of CKeyboardState
// ---------------------------------------------------------------------------

constexpr unsigned short CKeyboardState::getBeginVKCode() {
  return 0;
}
// ---------------------------------------------------------------------------

constexpr unsigned short CKeyboardState::getEndVKCode() {
  return 256;
}
// ---------------------------------------------------------------------------
// Definition of CKeyboardState Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyboardState& KeyboardState) {
  Streamer << KeyboardState.LowLevelKeyboardState;
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKeyboardState& KeyboardState) {
  Streamer >> KeyboardState.LowLevelKeyboardState;
  return Streamer;
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
