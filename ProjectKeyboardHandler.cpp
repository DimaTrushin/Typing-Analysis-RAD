//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <tchar.h>
#include "UnitApplicationStarter.h"
//---------------------------------------------------------------------------

USEFORM("UnitMainForm.cpp", MainForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
  try {
     Application->Initialize();
     Application->MainFormOnTaskBar = true;
     Application->CreateForm(__classid(TMainForm), &MainForm);
     NSApplication::CApplicationStarter ApplicationStarter(Application->Handle);
     Application->Run();
  }
  catch (Exception &exception) {
     Application->ShowException(&exception);
  }
  catch (...) {
     try {
       throw Exception("");
     }
     catch (Exception &exception) {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------

