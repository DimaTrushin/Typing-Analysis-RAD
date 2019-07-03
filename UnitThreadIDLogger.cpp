//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitThreadIDLogger.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CTimer GlobalTimer;

// use this to log the thread id
extern CThreadIDLogger ThreadIDLogger;
CThreadIDLogger ThreadIDLogger;
//---------------------------------------------------------------------------
// Definition of CThreadIDLogger
//---------------------------------------------------------------------------

void CThreadIDLogger::initialize(CTextWriter& LogScreen) {
  CScreenLogger::initialize(LogScreen);
}
//---------------------------------------------------------------------------

void CThreadIDLogger::Log(const std::wstring& Description) {
  std::wstring LogText;
  makeLogText(Description, &LogText);
  CScreenLogger::Log(LogText);
}
//---------------------------------------------------------------------------

void CThreadIDLogger::makeLogText(const std::wstring& Description,
                                  std::wstring* pLogText) {
  std::wstring& LogText = *pLogText;
  LogText = std::to_wstring(CTimer::MicroSecondsToMilliSeconds(
                                              GlobalTimer.getTime()));
  LogText += L" Thread ID = ";
  LogText += std::to_wstring(GetCurrentThreadId());
  LogText += L" ";
  LogText += Description;
  LogText += L"\n";
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
