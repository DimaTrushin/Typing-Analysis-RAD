//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitStateLogger.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CStateLogger
//---------------------------------------------------------------------------

CStateLogger::CStateLogger(CTextWriter& LogScreen)
  : CScreenLogger(LogScreen) {
}
//---------------------------------------------------------------------------

void CStateLogger::initialize(CTextWriter& LogScreen) {
  CScreenLogger::initialize(LogScreen);
}
//---------------------------------------------------------------------------

void CStateLogger::Log(const std::wstring& Description) {
  std::wstring LogText(Description);
  LogText += L"\n";
  CScreenLogger::Log(LogText);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
