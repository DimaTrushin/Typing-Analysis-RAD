//---------------------------------------------------------------------------

#ifndef UnitTimeLoggerH
#define UnitTimeLoggerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <string>
#include <cassert>
#include "UnitTimer.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Declaration of CCallProxy
//---------------------------------------------------------------------------

template<class TObject>
class CCallProxy {
public:
  inline CCallProxy(TObject* pNewObject,
                    microseconds* pNewElapsedTime);
  inline ~CCallProxy();
  inline TObject* operator->();
private:
  TObject* pObject;
  microseconds* pElapsedTime;
  const microseconds StartTime;
};
//---------------------------------------------------------------------------
// Declaration of CLogBase
//---------------------------------------------------------------------------

class CLogBase {
public:
  inline void addToLog(const std::wstring& LogInfo);
  inline const std::wstring& getLog() const;
protected:
  std::wstring Log;
};
//---------------------------------------------------------------------------
// Declaration of CLogCaller
//---------------------------------------------------------------------------

template <class TObject,
          class TLogWrapper>
class CLogCaller {
public:
  inline CLogCaller(TLogWrapper* pNewLogWrapper);
  inline ~CLogCaller();
  inline CCallProxy<TObject> operator->();
private:
  TLogWrapper* pLogWrapper;
  microseconds ElapsedTime;
};
//---------------------------------------------------------------------------
// Declaration of CTimeLogger
//---------------------------------------------------------------------------

template<class TObject>
class CTimeLogger : protected TObject, protected CLogBase {
friend class CLogCaller<TObject, CTimeLogger>;
public:
  using TObject::TObject;
  inline CLogCaller<TObject, CTimeLogger> Log(const std::wstring& LogInfo);
  using CLogBase::getLog;
private:
  inline TObject* getObject();
};
//---------------------------------------------------------------------------
// Declaration of CObjectTimeLogger
//---------------------------------------------------------------------------

template<class TObject>
class CObjectTimeLogger : protected CLogBase {
friend class CLogCaller<TObject, CObjectTimeLogger>;
public:
  inline CObjectTimeLogger(TObject* pNewObject);
  inline CLogCaller<TObject, CObjectTimeLogger>
                                      Log(const std::wstring& LogInfo);
  using CLogBase::getLog;
private:
  inline TObject* getObject();
  TObject* pObject;
};
//---------------------------------------------------------------------------
// Declaration of getTimeLogger
//---------------------------------------------------------------------------

template<class TObject>
inline CObjectTimeLogger<TObject> getTimeLogger(TObject& Object);
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
extern CTimer GlobalTimer;
//---------------------------------------------------------------------------
// Definition of CCallProxy
//---------------------------------------------------------------------------

template<class TObject>
CCallProxy<TObject>::CCallProxy(TObject* pNewObject,
                                microseconds* pNewElapsedTime)
    : pObject(pNewObject),
      pElapsedTime(pNewElapsedTime),
      StartTime(GlobalTimer.getTime()) {

}
//---------------------------------------------------------------------------

template<class TObject>
CCallProxy<TObject>::~CCallProxy() {
    microseconds EndTime = GlobalTimer.getTime();
    *pElapsedTime = EndTime - StartTime;
}
//---------------------------------------------------------------------------

template<class TObject>
TObject* CCallProxy<TObject>::operator->() {
    return pObject;
}
//---------------------------------------------------------------------------
// Definition of CLogBase
//---------------------------------------------------------------------------

void CLogBase::addToLog(const std::wstring& LogInfo) {
  Log += LogInfo;
}
//---------------------------------------------------------------------------

const std::wstring& CLogBase::getLog() const {
  return Log;
}
//---------------------------------------------------------------------------
// Definition of CLogCaller
//---------------------------------------------------------------------------

template <class TObject,
          class TLogWrapper>
CLogCaller<TObject, TLogWrapper>::CLogCaller(TLogWrapper* pNewLogWrapper)
  : pLogWrapper(pNewLogWrapper),
    ElapsedTime(0) {
}
//---------------------------------------------------------------------------

template <class TObject,
          class TLogWrapper>
CLogCaller<TObject, TLogWrapper>::~CLogCaller() {
  pLogWrapper->addToLog(L" = ");
  // this is just a wierd way to make 3 digits precision
  // to_wstring makes 6 digits, then I cut 3 of them
  std::wstring TimeText = std::to_wstring(
                          CTimer::MicroSecondsToMilliSeconds(ElapsedTime));
  TimeText.pop_back();
  TimeText.pop_back();
  TimeText.pop_back();
  pLogWrapper->addToLog(TimeText);
  pLogWrapper->addToLog(L" ms\n");
}
//---------------------------------------------------------------------------

template <class TObject,
          class TLogWrapper>
CCallProxy<TObject> CLogCaller<TObject, TLogWrapper>::operator->() {
  return CCallProxy<TObject>( pLogWrapper->getObject(),
                              &ElapsedTime);
}
//---------------------------------------------------------------------------
// Definition of CTimeLogger
//---------------------------------------------------------------------------

template<class TObject>
CLogCaller<TObject, CTimeLogger<TObject>>
                  CTimeLogger<TObject>::Log(const std::wstring& LogInfo) {
  CLogBase::Log += LogInfo;
  return CLogCaller<TObject, CTimeLogger>(this);
}
//---------------------------------------------------------------------------

template<class TObject>
TObject* CTimeLogger<TObject>::getObject() {
  return static_cast<TObject*>(this);
}
//---------------------------------------------------------------------------
// Definition of CObjectTimeLogger
//---------------------------------------------------------------------------

template<class TObject>
CObjectTimeLogger<TObject>::CObjectTimeLogger(TObject* pNewObject)
  : pObject(pNewObject) {
  assert(pObject != nullptr);
}
//---------------------------------------------------------------------------

template<class TObject>
CLogCaller<TObject, CObjectTimeLogger<TObject>>
  CObjectTimeLogger<TObject>::Log(const std::wstring& LogInfo) {
  CLogBase::Log += LogInfo;
  return CLogCaller<TObject, CObjectTimeLogger>(this);
}
//---------------------------------------------------------------------------

template<class TObject>
TObject* CObjectTimeLogger<TObject>::getObject() {
  return pObject;
}
//---------------------------------------------------------------------------
// Definition of getTimeLogger
//---------------------------------------------------------------------------

template<class TObject>
CObjectTimeLogger<TObject> getTimeLogger(TObject& Object) {
  return CObjectTimeLogger<TObject>(&Object);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
