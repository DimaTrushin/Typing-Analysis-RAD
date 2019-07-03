//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitBasicLoggers.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CTimer GlobalTimer;
//---------------------------------------------------------------------------

namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CFileLogger
//---------------------------------------------------------------------------

CFileLogger::CFileLogger(const std::wstring& fileName)
  : oFileStream_( fileName,
                  std::wofstream::out | std::wofstream::app) {
  assert(isDefined());
  makeFirstEntry();
}
//---------------------------------------------------------------------------

void CFileLogger::initialize(const std::wstring& fileName) {
  assert(!isDefined());
  oFileStream_.open(fileName,
                    std::wofstream::out | std::wofstream::app);
  assert(isDefined());
  makeFirstEntry();
}
//---------------------------------------------------------------------------

void CFileLogger::Log(const std::wstring& Text) {
  assert(isDefined());
  std::lock_guard<std::mutex> blocker(guardian_);
  oFileStream_ << Text;
}
//---------------------------------------------------------------------------

bool CFileLogger::isDefined() const {
  return oFileStream_.is_open();
}
//---------------------------------------------------------------------------

void CFileLogger::makeFirstEntry() {
  std::wstring LogHeader;
  makeLogHeader(&LogHeader);
  Log(LogHeader);
}
//---------------------------------------------------------------------------

void CFileLogger::makeLogHeader(std::wstring* pLogHeader) const {
  std::wstring& LogHeader = *pLogHeader;
  LogHeader = L"gLog (" +
              std::to_wstring(
                    CTimer::MicroSecondsToMilliSeconds(
                                        GlobalTimer.getTime())) +
              L"):\n";
}
//---------------------------------------------------------------------------
// Definition of CScreenLogger
//---------------------------------------------------------------------------

CScreenLogger::CScreenLogger(CTextWriter& LogScreen)
  : pLogScreen_(&LogScreen) {
  assert(isDefined());
  makeFirstEntry();
}
//---------------------------------------------------------------------------

void CScreenLogger::initialize(CTextWriter& LogScreen) {
  assert(!isDefined());
  pLogScreen_ = &LogScreen;
  assert(isDefined());
  makeFirstEntry();
}
//---------------------------------------------------------------------------

void CScreenLogger::Log(const std::wstring& Text) {
  assert(isDefined());
  std::lock_guard<std::mutex> blocker(guardian_);
  pLogScreen_->printPlaneText(Text.c_str());
}
//---------------------------------------------------------------------------

bool CScreenLogger::isDefined() const {
  return pLogScreen_ != nullptr;
}
//---------------------------------------------------------------------------

void CScreenLogger::makeFirstEntry() {
  std::wstring LogHeader;
  makeLogHeader(&LogHeader);
  Log(LogHeader);
}
//---------------------------------------------------------------------------

void CScreenLogger::makeLogHeader(std::wstring* pLogHeader) const{
  std::wstring& LogHeader = *pLogHeader;
  LogHeader = L"gLog (" +
              std::to_wstring(
                    CTimer::MicroSecondsToMilliSeconds(
                                        GlobalTimer.getTime())) +
              L"):\n";
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
