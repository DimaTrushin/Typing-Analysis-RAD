//---------------------------------------------------------------------------

#ifndef UnitGlobalLoggerH
#define UnitGlobalLoggerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitBasicLoggers.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Forward Declaration of CGlobalLogger
//---------------------------------------------------------------------------

class CGlobalLogger;
//---------------------------------------------------------------------------
// Declaration of CObjectLoggerProxy
//---------------------------------------------------------------------------

template<class TType>
class CObjectLoggerProxy {
public:
  inline CObjectLoggerProxy(CGlobalLogger* pLogger,
                            TType* pObject,
                            const std::wstring& Text);
  inline ~CObjectLoggerProxy();
  inline TType* operator->();
private:
  void makeLogText(std::wstring* pLogText);
  std::wstring microsecondsToString(microseconds Time);

  CGlobalLogger* pLogger_;
  TType* pObject_;
  std::wstring Text_;
  microseconds startingTime_;
  microseconds endingTime_;
};
//---------------------------------------------------------------------------
// Declaration of CBlockLogger
//---------------------------------------------------------------------------

class CBlockLogger {
public:
  inline CBlockLogger(CGlobalLogger* pLogger,
                            const std::wstring& Text);
  inline ~CBlockLogger();
  inline void stopLog();
private:
  inline void finishLogging();
  void makeLogText(std::wstring* pLogText);
  std::wstring microsecondsToString(microseconds Time);

  CGlobalLogger* pLogger_;
  std::wstring Text_;
  bool isLogging_;
  microseconds startingTime_;
  microseconds endingTime_;
};
//---------------------------------------------------------------------------
// Declaration of CGlobalLogger
//---------------------------------------------------------------------------

class CGlobalLogger : protected NSLibrary::CScreenLogger,
                      protected NSLibrary::CFileLogger {
template<class TType>
friend class CObjectLoggerProxy;
friend class CBlockLogger;
  using CTextWriter = NSInterface::CTextWriter;
public:
  inline CGlobalLogger() = default;
  inline CGlobalLogger( CTextWriter& TextWriter,
                        const std::wstring& fileName = kDefaultFileName);
  inline void initialize( CTextWriter& TextWriter,
                          const std::wstring& fileName = kDefaultFileName);
  template<class TType>
  inline CObjectLoggerProxy<TType> Log( TType* pObject,
                                        const std::wstring& Text);
  inline CBlockLogger LogBlock(const std::wstring& Text);
  static constexpr const wchar_t* const kDefaultFileName = L"Log.txt";
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CTimer GlobalTimer;
//---------------------------------------------------------------------------
// Definition of CObjectLoggerProxy
//---------------------------------------------------------------------------

template<class TType>
CObjectLoggerProxy<TType>::CObjectLoggerProxy(CGlobalLogger* pLogger,
                                              TType* pObject,
                                              const std::wstring& Text)
  : pLogger_(pLogger),
    pObject_(pObject),
    Text_(Text),
    startingTime_(GlobalTimer.getTime()),
    endingTime_(startingTime_) {
}
//---------------------------------------------------------------------------

template<class TType>
CObjectLoggerProxy<TType>::~CObjectLoggerProxy() {
  endingTime_ = GlobalTimer.getTime();
  std::wstring LogText;
  makeLogText(&LogText);
  static_cast<NSLibrary::CScreenLogger*>(pLogger_)->Log(LogText);
  static_cast<NSLibrary::CFileLogger*>(pLogger_)->Log(LogText);
}
//---------------------------------------------------------------------------

template<class TType>
TType* CObjectLoggerProxy<TType>::operator->() {
  return pObject_;
}
//---------------------------------------------------------------------------

template<class TType>
void CObjectLoggerProxy<TType>::makeLogText(std::wstring* pLogText) {
  std::wstring& LogText = *pLogText;
  LogText = L"";
  LogText += L"[";
  LogText += microsecondsToString(startingTime_);
  LogText += L" : ";
  LogText += microsecondsToString(endingTime_);
  LogText += L"] duration = ";
  LogText += microsecondsToString(endingTime_ - startingTime_);
  LogText += L" ";
  LogText += Text_;
  LogText += L"\n";
}
//---------------------------------------------------------------------------

template<class TType>
std::wstring
  CObjectLoggerProxy<TType>::microsecondsToString(microseconds Time) {
  // this is just a wierd way to make 3 digits precision
  // to_string makes 6 digits, then I cut 3 of them
  std::wstring TimeText = std::to_wstring(
                          CTimer::MicroSecondsToMilliSeconds(Time));
  TimeText.pop_back();
  TimeText.pop_back();
  TimeText.pop_back();
  return TimeText;
}
//---------------------------------------------------------------------------
// Definition of CBlockLogger
//---------------------------------------------------------------------------

CBlockLogger::CBlockLogger( CGlobalLogger* pLogger,
                            const std::wstring& Text)
  : pLogger_(pLogger),
    Text_(Text),
    isLogging_(true),
    startingTime_(GlobalTimer.getTime()),
    endingTime_(startingTime_) {
}
//---------------------------------------------------------------------------

CBlockLogger::~CBlockLogger() {
  if(isLogging_)
    finishLogging();
}
//---------------------------------------------------------------------------

void CBlockLogger::stopLog() {
  if(isLogging_)
    finishLogging();
}
//---------------------------------------------------------------------------

void CBlockLogger::finishLogging() {
  isLogging_ = false;
  endingTime_ = GlobalTimer.getTime();
  std::wstring LogText;
  makeLogText(&LogText);
  static_cast<NSLibrary::CScreenLogger*>(pLogger_)->Log(LogText);
  static_cast<NSLibrary::CFileLogger*>(pLogger_)->Log(LogText);
}
//---------------------------------------------------------------------------

void CBlockLogger::makeLogText(std::wstring* pLogText) {
  std::wstring& LogText = *pLogText;
  LogText = L"";
  LogText += L"[";
  LogText += microsecondsToString(startingTime_);
  LogText += L" : ";
  LogText += microsecondsToString(endingTime_);
  LogText += L"] duration = ";
  LogText += microsecondsToString(endingTime_ - startingTime_);
  LogText += L" ";
  LogText += Text_;
  LogText += L"\n";
}
//---------------------------------------------------------------------------

std::wstring CBlockLogger::microsecondsToString(microseconds Time) {
  // this is just a wierd way to make 3 digits precision
  // to_string makes 6 digits, then I cut 3 of them
  std::wstring TimeText = std::to_wstring(
                          CTimer::MicroSecondsToMilliSeconds(Time));
  TimeText.pop_back();
  TimeText.pop_back();
  TimeText.pop_back();
  return TimeText;
}
//---------------------------------------------------------------------------
// Definition of CGlobalLogger
//---------------------------------------------------------------------------

CGlobalLogger::CGlobalLogger( CTextWriter& TextWriter,
                              const std::wstring& fileName)
  : CScreenLogger(TextWriter),
    CFileLogger(fileName) {
}
//---------------------------------------------------------------------------

void CGlobalLogger::initialize( CTextWriter& TextWriter,
                                const std::wstring& fileName) {
  CScreenLogger::initialize(TextWriter);
  CFileLogger::initialize(fileName);
}
//---------------------------------------------------------------------------

template<class TType>
CObjectLoggerProxy<TType> CGlobalLogger::Log( TType* pObject,
                                              const std::wstring& Text) {
  assert(pObject != nullptr);
  assert(CScreenLogger::isDefined());
  assert(CFileLogger::isDefined());
  return CObjectLoggerProxy<TType>(this, pObject, Text);
}
//---------------------------------------------------------------------------

CBlockLogger CGlobalLogger::LogBlock(const std::wstring& Text) {
  assert(CScreenLogger::isDefined());
  assert(CFileLogger::isDefined());
  return CBlockLogger(this, Text);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
