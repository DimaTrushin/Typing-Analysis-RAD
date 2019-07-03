//---------------------------------------------------------------------------

#ifndef UnitParallelForH
#define UnitParallelForH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vector>
#include "UnitThreadPool.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------------
// Declaration ILoopWorker
//---------------------------------------------------------------------------------

class ILoopWorker {
public:
  virtual ~ILoopWorker() = default;
  virtual void execute(size_t index) = 0;
};
//---------------------------------------------------------------------------------
// Declaration LoopWorker
//---------------------------------------------------------------------------------

class LoopWorker : public IWorker {
public:
  LoopWorker(size_t Begin, size_t End, ILoopWorker* pLoopWorker);
  void execute();
private:
  size_t begin;
  size_t end;
  ILoopWorker* ptrLoopWorker;
};

//---------------------------------------------------------------------------------
// Declaration ParallelFor
//---------------------------------------------------------------------------------

class ParallelFor {
public:
  void operator() ( size_t begin,
                    size_t end,
                    size_t chunk,
                    ILoopWorker* pLoopWorker,
                    CThreadPool* pPool);
private:
  void makeLoopWorkers (size_t begin,
                        size_t end,
                        size_t chunk,
                        ILoopWorker* pLoopWorker);
  void submitLoopWorkers(CThreadPool* pPool);
  std::vector<LoopWorker> LoopWorkers;
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
