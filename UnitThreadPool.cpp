//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitThreadPool.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------------

CThreadPool ThreadPool;
//---------------------------------------------------------------------------------
// Definition of CallBack Functions
//---------------------------------------------------------------------------------

VOID CALLBACK WorkerCallback( PTP_CALLBACK_INSTANCE Instance,
                              PVOID Parameter,
                              PTP_WORK Work) {
  //UNREFERENCED_PARAMETER(Instance);
  IWorker* pWorker = static_cast<IWorker*>(Parameter);
  pWorker->execute();
  // not sure about using this function here
  CloseThreadpoolWork(Work);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolBase
//---------------------------------------------------------------------------------

CThreadPoolBase::CThreadPoolBase()
  : Pool(CreateThreadpool(nullptr)) {
  if (Pool == nullptr)
    throw std::exception ("CreateThreadpool fails\n");
}
//---------------------------------------------------------------------------------

CThreadPoolBase::~CThreadPoolBase() {
  assert(Pool != nullptr);
  CloseThreadpool(Pool);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithEnvironmentBase
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironmentBase::CThreadPoolwithEnvironmentBase() {
  InitializeThreadpoolEnvironment(&Environment);
}
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironmentBase::~CThreadPoolwithEnvironmentBase() {
  DestroyThreadpoolEnvironment(&Environment);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithEnvironment
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironment::CThreadPoolwithEnvironment() {
  SetThreadpoolCallbackPool(&Environment, Pool);
}
//---------------------------------------------------------------------------------

CThreadPoolwithEnvironment::~CThreadPoolwithEnvironment() {
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithCleanupGroupBase
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroupBase::CThreadPoolwithCleanupGroupBase()
  : CleanupGroup(CreateThreadpoolCleanupGroup()) {
  if (CleanupGroup == nullptr)
    throw std::exception("CreateThreadpoolCleanupGroup fails\n");
}
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroupBase::~CThreadPoolwithCleanupGroupBase() {
  assert(CleanupGroup != nullptr);
  CloseThreadpoolCleanupGroup(CleanupGroup);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPoolwithCleanupGroup
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroup::CThreadPoolwithCleanupGroup() {
  SetThreadpoolCallbackCleanupGroup(&Environment, CleanupGroup, nullptr);
}
//---------------------------------------------------------------------------------

CThreadPoolwithCleanupGroup::~CThreadPoolwithCleanupGroup() {
  assert(CleanupGroup != nullptr);
  // If this part of CThreadPool is destroyed, there must be no
  // tasks running. Hence, we do not wait any running tasks.
  CloseThreadpoolCleanupGroupMembers(CleanupGroup, true, nullptr);
}
//---------------------------------------------------------------------------------
// Definition of CThreadPool
//---------------------------------------------------------------------------------

CThreadPool::CThreadPool(size_t MaximalNumberOfThreads,
                         size_t MinimalNumberOfThreads)
  : ThreadMaximum(MaximalNumberOfThreads),
    ThreadMinimum(MinimalNumberOfThreads) {
  assert(MaximalNumberOfThreads >= MinimalNumberOfThreads);
  assert(MaximalNumberOfThreads > 0);
  SetThreadpoolThreadMaximum(Pool, MaximalNumberOfThreads);
  BOOL result = SetThreadpoolThreadMinimum(Pool, MinimalNumberOfThreads);
  if (result == FALSE)
    throw std::exception("SetThreadpoolThreadMinimum failed\n");
}
//---------------------------------------------------------------------------------

CThreadPool::~CThreadPool() {
  assert(CleanupGroup != nullptr);
  // If we destroy CThreadPool, we wait until all running tasks
  // are over.
  CloseThreadpoolCleanupGroupMembers(CleanupGroup, false, nullptr);
}
//---------------------------------------------------------------------------------

void CThreadPool::submit(IWorker* pWorker) {
  PTP_WORK work = CreateThreadpoolWork( WorkerCallback,
                                        pWorker,
                                        &Environment);
  if (work == nullptr)
    throw std::exception("CreateThreadpoolWork fails\n");
  SubmitThreadpoolWork(work);
}
//---------------------------------------------------------------------------------

void CThreadPool::wait() {
  CloseThreadpoolCleanupGroupMembers(CleanupGroup, false, nullptr);
}
//---------------------------------------------------------------------------------

void CThreadPool::setNumberOfThreads( size_t maximum, size_t minimum) {
  assert(maximum >= minimum);
  assert(maximum > 0);
  SetThreadpoolThreadMaximum(Pool, maximum);
  ThreadMaximum = maximum;
  BOOL result = SetThreadpoolThreadMinimum(Pool, minimum);
  if (result == FALSE)
    throw std::exception("SetThreadpoolThreadMinimum failed\n");
  ThreadMinimum = minimum;
}
//---------------------------------------------------------------------------------

void CThreadPool::smartInitialization() {
  size_t numberOfThreads = std::thread::hardware_concurrency();
  if (numberOfThreads == 0)
    numberOfThreads = kDefaultNumberOfThreads;
  setNumberOfThreads(numberOfThreads, numberOfThreads);
}
//---------------------------------------------------------------------------

size_t CThreadPool::getThreadMaximum() const {
  return ThreadMaximum;
}
//---------------------------------------------------------------------------

size_t CThreadPool::getThreadMinimum() const {
  return ThreadMinimum;
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)

