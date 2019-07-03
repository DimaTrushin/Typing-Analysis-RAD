// ---------------------------------------------------------------------------
#ifndef UnitKeyboardHandlerH
#define UnitKeyboardHandlerH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <exception>
#include "UnitRawKeyGenerator.h"
#include "UnitKeyFilter.h"
#include "../Kernel/UnitMaster.h"
#include "../UnitThreadIDLogger.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Declaration of CSafeRawBuffer
// ---------------------------------------------------------------------------

class CSafeRawBuffer {
public:
  CSafeRawBuffer();
  CSafeRawBuffer(size_t Size);
  ~CSafeRawBuffer();
  CSafeRawBuffer(const CSafeRawBuffer&) = delete;
  CSafeRawBuffer(CSafeRawBuffer&& other);
  CSafeRawBuffer& operator=(const CSafeRawBuffer&) = delete;
  CSafeRawBuffer& operator=(CSafeRawBuffer&& other);

  inline RAWINPUT* getPRAWINPUT();
  inline RAWINPUT& getRAWINPUT();
  inline const RAWINPUT& getRAWINPUT() const;
  inline LPBYTE getBuffer() const;
  inline bool isDefined() const;
  inline size_t getSize() const;
  // resize does not make the buffer smaller!!!
  inline void resizeIfSmaller(size_t newSize);
  inline void clear();

private:
  LPBYTE pBuffer;
  size_t size;
};
// ---------------------------------------------------------------------------
// Declaration of CSafeRawBuffer Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CSafeRawBuffer& SafeRawBuffer);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CSafeRawBuffer& SafeRawBuffer);
// ---------------------------------------------------------------------------
// Declaration of RAWINPUTDEVICE Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const RAWINPUTDEVICE& Device);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, RAWINPUTDEVICE& Device);
// ---------------------------------------------------------------------------
// Declaration of CLowLevelKeyboard
// ---------------------------------------------------------------------------
// Class interacts with Raw Input using Windows API

class CLowLevelKeyboard {
public:
  CLowLevelKeyboard();
  ~CLowLevelKeyboard();
  void Initialize(HWND ReceiverHandle);
  const RAWKEYBOARD& getRawInputData(LPARAM lParam) const;

  CLowLevelKeyboard(const CLowLevelKeyboard&) = delete;
  CLowLevelKeyboard(CLowLevelKeyboard&&) = delete;
  CLowLevelKeyboard& operator=(const CLowLevelKeyboard&) = delete;
  CLowLevelKeyboard& operator=(CLowLevelKeyboard&&) = delete;

private:
  inline size_t getRawDataSize(LPARAM lParam) const;
  inline void readRawInputData(LPARAM lParam) const;
  inline void setDeviceClassToKeyboardClass();
  inline void setDeviceToKeyboard();
  inline void setToCollectEverything();
  inline void setToRemove();
  inline void setReceiver(HWND ReceiverHandle);
  inline void registerDevice();
  inline void shutdownDevice();
  inline void removeDevice();

  RAWINPUTDEVICE lowLevelDevice;
  mutable CSafeRawBuffer RawInputBuffer;

  template<class TStreamer>
  friend TStreamer& operator<<(
                      TStreamer& Streamer,
                      const CLowLevelKeyboard& LowLevelKeyboard);
  template<class TStreamer>
  friend TStreamer& operator>>(
                      TStreamer& Streamer,
                      CLowLevelKeyboard& LowLevelKeyboard);
};
// ---------------------------------------------------------------------------
// Declaration of CLowLevelKeyboard Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CLowLevelKeyboard& LowLevelKeyboard);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CLowLevelKeyboard& LowLevelKeyboard);
// ---------------------------------------------------------------------------
// Declaration of CKeyboardHandler
// ---------------------------------------------------------------------------

class CKeyboardHandler {
public:
  CKeyboardHandler();
  void Initialize(HWND ReceiverHandle);
  void HandleInput( HWND hWnd,
                    UINT message,
                    WPARAM wParam,
                    LPARAM lParam);
  void Activate();
  void DeActivate();

  bool isActive() const;
  void transferDataToUser();

  CKeyboardHandler(const CKeyboardHandler&) = delete;
  CKeyboardHandler(CKeyboardHandler&&) = delete;
  CKeyboardHandler& operator=(const CKeyboardHandler&) = delete;
  CKeyboardHandler& operator=(CKeyboardHandler&&) = delete;

private:
  inline microseconds getMessageTime() const;
  inline RAWKEYBOARD getRawKeyboardData(LPARAM lParam) const;
  inline HKL getKeyboardLayout() const;
  inline void HandleDataInput(microseconds MessageTime,
                              const RAWKEYBOARD& KeyboardData,
                              HKL KeyboardLayout);
  inline void HandleCommandInput(const RAWKEYBOARD& KeyboardData);
  //inline void AddRawEventToBuffer(const CRawKey& RawKey,
  //                                HKL KeyboardLayout);
  inline bool isProcessable(const RAWKEYBOARD& KeyboardData) const;
  inline bool needToTransferData(const RAWKEYBOARD& KeyboardData) const;
  inline bool isEscapePressed(const RAWKEYBOARD& KeyboardData) const;
  inline void resetRawBuffer();

  bool ActiveState;
  CRawEventContainer RawBuffer;
  CLowLevelKeyboard LowLevelKeyboard;
  CKeyFilter KeyFilter;

  template<class TStreamer>
  friend TStreamer& operator<<(
                      TStreamer& Streamer,
                      const CKeyboardHandler& KeyboardHandler);
  template<class TStreamer>
  friend TStreamer& operator>>(
                      TStreamer& Streamer,
                      CKeyboardHandler& KeyboardHandler);
};
// ---------------------------------------------------------------------------
// Declaration of CKeyboardHandler Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyboardHandler& KeyboardHandler);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyboardHandler& KeyboardHandler);
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
}// NSApplication
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {

// ---------------------------------------------------------------------------
// Definition of CSafeRawBuffer Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CSafeRawBuffer& SafeRawBuffer) {
  Streamer << SafeRawBuffer.getSize();
  if (SafeRawBuffer.getSize() != 0)
    Streamer.writePOD(SafeRawBuffer.getRAWINPUT());
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CSafeRawBuffer& SafeRawBuffer) {
  size_t size;
  Streamer >> size;
  CSafeRawBuffer tmpBuffer(size);
  if (size != 0)
    Streamer.readPOD(tmpBuffer.getPRAWINPUT());
  SafeRawBuffer = std::move(tmpBuffer);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of RAWINPUTDEVICE Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const RAWINPUTDEVICE& Device) {
  Streamer.writePOD(Device);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, RAWINPUTDEVICE& Device) {
  Streamer.readPOD(&Device);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definnition of CLowLevelKeyboard Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CLowLevelKeyboard& LowLevelKeyboard) {
  Streamer << LowLevelKeyboard.lowLevelDevice;
  Streamer << LowLevelKeyboard.RawInputBuffer;
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CLowLevelKeyboard& LowLevelKeyboard) {
  Streamer >> LowLevelKeyboard.lowLevelDevice;
  Streamer >> LowLevelKeyboard.RawInputBuffer;
  return Streamer;
}
// ---------------------------------------------------------------------------
// Declaration of CKeyboardHandler Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CKeyboardHandler& KeyboardHandler) {
  Streamer << KeyboardHandler.ActiveState;
  Streamer << KeyboardHandler.RawBuffer;
  Streamer << KeyboardHandler.LowLevelKeyboard;
  Streamer << KeyboardHandler.KeyFilter;
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CKeyboardHandler& KeyboardHandler) {
  Streamer >> KeyboardHandler.ActiveState;
  Streamer >> KeyboardHandler.RawBuffer;
  Streamer >> KeyboardHandler.LowLevelKeyboard;
  Streamer >> KeyboardHandler.KeyFilter;
  return Streamer;
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
}// NSApplication
// ---------------------------------------------------------------------------

#endif
