//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKeyboardCallback.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {

//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

WNDPROC StandardApplicationWindowProc;
extern CKeyboardHandler KeyboardHandler;
//---------------------------------------------------------------------------
// Global Functions
//---------------------------------------------------------------------------

LRESULT CALLBACK ApplicationCallback( HWND hWnd,
                                      UINT message,
                                      WPARAM wParam,
                                      LPARAM lParam) {
  if (message == WM_INPUT)
      KeyboardHandler.HandleInput(hWnd, message, wParam, lParam);

 return CallWindowProc( StandardApplicationWindowProc,
                        hWnd,
                        message,
                        wParam,
                        lParam);
}
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
