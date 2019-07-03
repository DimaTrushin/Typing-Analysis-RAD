//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitApplicationStarter.h"
#include "UnitPerformanceLogger.h"
#include "UnitStateLoggerAccess.h"
//---------------------------------------------------------------------------

namespace NSApplication{

//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CThreadIDLogger ThreadIDLogger;
extern CThreadPool ThreadPool;
//---------------------------------------------------------------------------

namespace NSInterface {
  extern CGUIHandler GUIHandler;
}
//---------------------------------------------------------------------------

namespace NSKernel {
  extern CMaster Master;
}
//---------------------------------------------------------------------------

namespace NSKeyboard {
  extern WNDPROC StandardApplicationWindowProc;
  extern CKeyboardHandler KeyboardHandler;
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
// Definition CApplicationStarter
//---------------------------------------------------------------------------

CApplicationStarter::CApplicationStarter(HWND ApplicationHandle)
  : pApplicationHandle(ApplicationHandle) {
  // TO DO
  // this is a terrible hack to make russian filenames to work
  std::setlocale(LC_ALL,".UTF-8");
  substituteApplicationCallback();
  initializeGlobalObjects();
}
//---------------------------------------------------------------------------

CApplicationStarter::~CApplicationStarter() {
  restoreApplicationCallback();
}
//---------------------------------------------------------------------------

void CApplicationStarter::
                substituteApplicationCallback() {
  NSKeyboard::StandardApplicationWindowProc =
          (WNDPROC)SetWindowLong( pApplicationHandle,
                                  GWL_WNDPROC,
                                  (long)NSKeyboard::ApplicationCallback);
}
//---------------------------------------------------------------------------

void CApplicationStarter::restoreApplicationCallback() {
  SetWindowLong(pApplicationHandle,
                GWL_WNDPROC,
                (long)NSKeyboard::StandardApplicationWindowProc);
}
//---------------------------------------------------------------------------

void CApplicationStarter::initializeGlobalObjects() {
  CPerformanceLogger InitPerformanceLog(NSInterface::GUIHandler.LogWriter);
  ThreadIDLogger.initialize(NSInterface::GUIHandler.ThreadLogWriter);
  ThreadIDLogger.Log(L"main thread");
  CStateLoggerAccess InitStateLog(NSInterface::GUIHandler.StateLogWriter);
  NSKeyboard::KeyboardHandler.Initialize(pApplicationHandle);
  ThreadPool.smartInitialization();
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
