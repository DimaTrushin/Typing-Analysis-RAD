//---------------------------------------------------------------------------

#ifndef UnitApplicationStarterH
#define UnitApplicationStarterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitThreadPool.h"
#include "Keyboard/UnitKeyboardCallback.h"
//---------------------------------------------------------------------------

namespace NSApplication{
//---------------------------------------------------------------------------
// Declaration CApplicationStarter
//---------------------------------------------------------------------------

// TO DO
// Make a separate callback substitutor as a base class
// for CApplicationStarter

class CApplicationStarter {
public:
  CApplicationStarter(HWND ApplicationHandle);
  ~CApplicationStarter();

  CApplicationStarter(const CApplicationStarter&) = delete;
  CApplicationStarter(CApplicationStarter&&) = delete;
  CApplicationStarter& operator=(const CApplicationStarter&) = delete;
  CApplicationStarter& operator=(CApplicationStarter&&) = delete;
private:
  void substituteApplicationCallback();
  void restoreApplicationCallback();
  void initializeGlobalObjects();
  HWND pApplicationHandle;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
