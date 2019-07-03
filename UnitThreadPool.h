//---------------------------------------------------------------------------

#ifndef UnitThreadPoolH
#define UnitThreadPoolH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <windows.h>
#include <thread>
#include <cassert>
#include <exception>
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------------
// Declaration of IWorker
//---------------------------------------------------------------------------------

class IWorker {
public:
  virtual ~IWorker() = default;
  virtual void execute() = 0;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolBase
//---------------------------------------------------------------------------------

class CThreadPoolBase {
public:
  CThreadPoolBase();
  CThreadPoolBase(const CThreadPoolBase&) = delete;
  CThreadPoolBase& operator=(const CThreadPoolBase&) = delete;
protected:
  ~CThreadPoolBase();
  PTP_POOL Pool;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithEnvironmentBase
//---------------------------------------------------------------------------------

class CThreadPoolwithEnvironmentBase {
public:
  CThreadPoolwithEnvironmentBase();
  CThreadPoolwithEnvironmentBase(
      const CThreadPoolwithEnvironmentBase&) = delete;
  CThreadPoolwithEnvironmentBase& operator=(
      const CThreadPoolwithEnvironmentBase&) = delete;
protected:
  ~CThreadPoolwithEnvironmentBase();
  TP_CALLBACK_ENVIRON Environment;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithEnvironment
//---------------------------------------------------------------------------------

class CThreadPoolwithEnvironment :  protected CThreadPoolBase,
                                    protected CThreadPoolwithEnvironmentBase {
public:
  CThreadPoolwithEnvironment();
protected:
  ~CThreadPoolwithEnvironment();
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithCleanupGroupBase
//---------------------------------------------------------------------------------

class CThreadPoolwithCleanupGroupBase {
public:
  CThreadPoolwithCleanupGroupBase();
  CThreadPoolwithCleanupGroupBase(
      const CThreadPoolwithCleanupGroupBase&) = delete;
  CThreadPoolwithCleanupGroupBase& operator=(
      const CThreadPoolwithCleanupGroupBase&) = delete;
protected:
  ~CThreadPoolwithCleanupGroupBase();
  PTP_CLEANUP_GROUP CleanupGroup;
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPoolwithCleanupGroup
//---------------------------------------------------------------------------------

class CThreadPoolwithCleanupGroup : protected CThreadPoolwithCleanupGroupBase,
                                    protected CThreadPoolwithEnvironment {
public:
  CThreadPoolwithCleanupGroup();
protected:
  ~CThreadPoolwithCleanupGroup();
};
//---------------------------------------------------------------------------------
// Declaration of CThreadPool
//---------------------------------------------------------------------------------

class CThreadPool : protected CThreadPoolwithCleanupGroup {
public:
  CThreadPool(size_t MaximalNumberOfThreads = kDefaultMaximalNumberOfThreads,
              size_t MinimalNumberOfThreads = kDefaultMinimalNumberOfThreads);
  ~CThreadPool();
  void submit(IWorker* pWorker);
  void wait();

  void setNumberOfThreads(size_t maximum, size_t minimum);
  void smartInitialization();
  size_t getThreadMaximum() const;
  size_t getThreadMinimum() const;
protected:
  static constexpr size_t kDefaultMaximalNumberOfThreads = 4;
  static constexpr size_t kDefaultMinimalNumberOfThreads = 1;
  static constexpr size_t kDefaultNumberOfThreads =
                              kDefaultMaximalNumberOfThreads;
private:
  size_t ThreadMaximum;
  size_t ThreadMinimum;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif

