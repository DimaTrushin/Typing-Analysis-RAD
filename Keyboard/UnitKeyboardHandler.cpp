// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitKeyboardHandler.h"
#include "../UnitPerformanceLogger.h"

#if !defined(NDEBUG)
#include "../UnitStateLoggerAccess.h"
#endif
// ---------------------------------------------------------------------------

#pragma package(smart_init)
// ---------------------------------------------------------------------------

namespace NSApplication {
// ---------------------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------------------

extern CTimer GlobalTimer;
extern CThreadIDLogger ThreadIDLogger;

namespace NSKernel {
extern CMaster Master;
// ---------------------------------------------------------------------------
} // NSKernel
// ---------------------------------------------------------------------------
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------------------

// Global Keyboard Handler
extern CKeyboardHandler KeyboardHandler;
CKeyboardHandler KeyboardHandler;
// ---------------------------------------------------------------------------
// Definitions of CSafeRawBuffer
// ---------------------------------------------------------------------------

CSafeRawBuffer::CSafeRawBuffer()
  : pBuffer(nullptr),
    size(0) {
}
// ---------------------------------------------------------------------------

CSafeRawBuffer::CSafeRawBuffer(size_t Size)
  : pBuffer(new BYTE[Size]),
    size(Size) {
  if (!isDefined())
    throw std::exception("Cannot create space for Raw Input!\n");
}
// ---------------------------------------------------------------------------

CSafeRawBuffer::~CSafeRawBuffer() {
  clear();
}
// ---------------------------------------------------------------------------

CSafeRawBuffer::CSafeRawBuffer(CSafeRawBuffer&& other)
  : pBuffer(other.pBuffer),
    size(other.size) {
  other.pBuffer = nullptr;
  other.size = 0;
}
// ---------------------------------------------------------------------------

CSafeRawBuffer& CSafeRawBuffer::operator=(CSafeRawBuffer&& other) {
  delete[] pBuffer;
  pBuffer = other.pBuffer;
  size = other.size;
  other.pBuffer = nullptr;
  other.size = 0;
  return *this;
}
// ---------------------------------------------------------------------------

RAWINPUT* CSafeRawBuffer::getPRAWINPUT() {
  return (RAWINPUT*)pBuffer;
}
// ---------------------------------------------------------------------------

RAWINPUT& CSafeRawBuffer::getRAWINPUT() {
  return *((RAWINPUT*)pBuffer);
}
// ---------------------------------------------------------------------------

const RAWINPUT& CSafeRawBuffer::getRAWINPUT() const {
  return *((RAWINPUT*)pBuffer);
}
// ---------------------------------------------------------------------------

LPBYTE CSafeRawBuffer::getBuffer() const {
  return pBuffer;
}
// ---------------------------------------------------------------------------

bool CSafeRawBuffer::isDefined() const {
  if (pBuffer == nullptr)
    return false;
  return true;
}
// ---------------------------------------------------------------------------

size_t CSafeRawBuffer::getSize() const {
  return size;
}
// ---------------------------------------------------------------------------

void CSafeRawBuffer::resizeIfSmaller(size_t newSize) {
  if (isDefined())
    if (newSize <= size)
      return;
  *this = CSafeRawBuffer(newSize);
}
// ---------------------------------------------------------------------------

void CSafeRawBuffer::clear() {
  delete[] pBuffer;
}
// ---------------------------------------------------------------------------
// Definitions of CLowLevelKeyboard
// ---------------------------------------------------------------------------

CLowLevelKeyboard::CLowLevelKeyboard() {
}
// ---------------------------------------------------------------------------
CLowLevelKeyboard::~CLowLevelKeyboard() {
  shutdownDevice();
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::Initialize(HWND ReceiverHandle) {
  setDeviceClassToKeyboardClass();
  setDeviceToKeyboard();
  setToCollectEverything();
  setReceiver(ReceiverHandle);
  registerDevice();
}
// ---------------------------------------------------------------------------

const RAWKEYBOARD& CLowLevelKeyboard::getRawInputData(LPARAM lParam) const {
  RawInputBuffer.resizeIfSmaller(getRawDataSize(lParam));
  readRawInputData(lParam);
  return RawInputBuffer.getRAWINPUT().data.keyboard;
}
// ---------------------------------------------------------------------------

size_t CLowLevelKeyboard::getRawDataSize(LPARAM lParam) const {
  size_t dwSize;
  GetRawInputData((HRAWINPUT)lParam,
                  RID_INPUT,
                  nullptr,
                  &dwSize,
                  sizeof(RAWINPUTHEADER));
  return dwSize;
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::readRawInputData( LPARAM lParam) const {
  size_t bufferSize = RawInputBuffer.getSize();
  if (GetRawInputData((HRAWINPUT)lParam,
                      RID_INPUT,
                      RawInputBuffer.getBuffer(),
                      &bufferSize,
                      sizeof(RAWINPUTHEADER)) != bufferSize)
    throw std::exception("GetRawInputData does not return correct size !\n");
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::setDeviceClassToKeyboardClass() {
  lowLevelDevice.usUsagePage = 0x01;
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::setDeviceToKeyboard() {
  lowLevelDevice.usUsage = 0x06;
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::setToCollectEverything() {
  lowLevelDevice.dwFlags = RIDEV_INPUTSINK;
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::setToRemove() {
  lowLevelDevice.dwFlags = RIDEV_REMOVE;
  setReceiver(nullptr);
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::setReceiver(HWND ReceiverHandle) {
  lowLevelDevice.hwndTarget = ReceiverHandle;
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::registerDevice() {
  if (RegisterRawInputDevices(&lowLevelDevice,
                              1,
                              sizeof(lowLevelDevice))
      == FALSE)
    throw std::exception("Cannot initialize keyboard!\n");
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::shutdownDevice() {
  setDeviceClassToKeyboardClass();
  setDeviceToKeyboard();
  setToRemove();
  removeDevice();
}
// ---------------------------------------------------------------------------

void CLowLevelKeyboard::removeDevice() {
  if (RegisterRawInputDevices(&lowLevelDevice,
                              1,
                              sizeof(lowLevelDevice))
      == FALSE)
    throw std::exception("Cannot shutdown keyboard!\n");
}
// ---------------------------------------------------------------------------
// Definitions of CKeyboardHandler
// ---------------------------------------------------------------------------

CKeyboardHandler::CKeyboardHandler() {
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::Initialize(HWND ReceiverHandle) {
  LowLevelKeyboard.Initialize(ReceiverHandle);
  KeyFilter.setToDefaultFilter();
  Activate();
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::HandleInput( HWND hWnd,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam) {
  //#if !defined(NDEBUG)
  //CStateLoggerAccess StateLogger;
  //StateLogger->Log(L"KBState\n", [&](std::wstring* pTextLog){
  //  CKeyboardState KBState;
  //  KBState.setToSystemKeyboardState();
  //  *pTextLog += L"VK_LSHIFT VK_SHIFT VK_RSHIFT\n";
  //  *pTextLog += std::to_wstring(KBState.getKeyState(VK_LSHIFT));
  //  *pTextLog += L"\t\t\t";
  //  *pTextLog += std::to_wstring(KBState.getKeyState(VK_SHIFT));
  //  *pTextLog += L"\t\t\t";
  //  *pTextLog += std::to_wstring(KBState.getKeyState(VK_RSHIFT));
  //});
  //#endif

  microseconds MessageTime = getMessageTime();
  const RAWKEYBOARD& KeyboardData = getRawKeyboardData(lParam);
  HKL KeyboardLayout = getKeyboardLayout();
  if(isActive())
    HandleDataInput(MessageTime, KeyboardData, KeyboardLayout);
  HandleCommandInput(KeyboardData);
  //#if !defined(NDEBUG)
  //CStateLoggerAccess StateLogger;
  //StateLogger->Log(L"Buffer", [&](std::wstring* pTextLog){
  //  *pTextLog += L"size = ";
  //  *pTextLog += std::to_wstring(RawBuffer.size());
  //  *pTextLog += L"\n";
  //  for (const auto& element : RawBuffer) {
  //    *pTextLog += L"VK = ";
  //    *pTextLog += std::to_wstring(element.getVKCode());
  //    *pTextLog += L" FL = ";
  //    *pTextLog += std::to_wstring(element.getFlags());
  //    *pTextLog += L"; ";
  //  }
  //});
  //#endif
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::Activate() {
  resetRawBuffer();
  ActiveState = true;
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::DeActivate() {
  ActiveState = false;
}
// ---------------------------------------------------------------------------

bool CKeyboardHandler::isActive() const {
  return ActiveState;
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::transferDataToUser() {
  ThreadIDLogger.Log(L"CKeyboardHandler::transferDataToUser");
  #if !defined(__MASTER__DISABLE__)
  CPerformanceLogger Performance;
  Performance->Log( &NSKernel::Master,
                    L"transferDataToUser")->
                                  transferDataToUser(&RawBuffer);
  #endif
}
// ---------------------------------------------------------------------------

microseconds CKeyboardHandler::getMessageTime() const {
  return GlobalTimer.getTime();
}
// ---------------------------------------------------------------------------

RAWKEYBOARD CKeyboardHandler::getRawKeyboardData(LPARAM lParam) const {
  return LowLevelKeyboard.getRawInputData(lParam);
}
// ---------------------------------------------------------------------------

HKL CKeyboardHandler::getKeyboardLayout() const {
  return GetKeyboardLayout(
                  GetWindowThreadProcessId(
                        GetForegroundWindow(), nullptr));
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::HandleDataInput( microseconds MessageTime,
                                        const RAWKEYBOARD& KeyboardData,
                                        HKL KeyboardLayout) {
  if (isProcessable(KeyboardData))
    RawBuffer.push_back(CRawKeyGenerator::
                          GenerateRawKey( MessageTime,
                                          KeyboardLayout,
                                          KeyboardData));
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::HandleCommandInput(const RAWKEYBOARD& KeyboardData) {
  if (needToTransferData(KeyboardData))
    transferDataToUser();
}
// ---------------------------------------------------------------------------

//void CKeyboardHandler::AddRawEventToBuffer( const CRawKey& RawKey,
//                                            HKL KeyboardLayout) {
//    RawBuffer.push_back(RawKey, KeyboardLayout);
//}
// ---------------------------------------------------------------------------

bool CKeyboardHandler::isProcessable(const RAWKEYBOARD& KeyboardData) const {
 return KeyFilter.isProcessable(KeyboardData.VKey);
}
// ---------------------------------------------------------------------------

bool CKeyboardHandler::needToTransferData(const RAWKEYBOARD& KeyboardData) const {
  return isEscapePressed(KeyboardData);
}
// ---------------------------------------------------------------------------

bool CKeyboardHandler::isEscapePressed(const RAWKEYBOARD& KeyboardData) const {
  return  KeyboardData.VKey == VK_ESCAPE &&
          KeyboardData.Flags == RI_KEY_MAKE;
}
// ---------------------------------------------------------------------------

void CKeyboardHandler::resetRawBuffer() {
  RawBuffer.clearKeys();
  RawBuffer.setToSystemKeyboardState();
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

