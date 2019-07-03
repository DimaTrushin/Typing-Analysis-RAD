//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitParallelFor.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------------
// Definition LoopWorker
//---------------------------------------------------------------------------------

LoopWorker::LoopWorker(size_t Begin, size_t End, ILoopWorker* pLoopWorker)
  : begin(Begin),
    end(End),
    ptrLoopWorker(pLoopWorker) {
}
//---------------------------------------------------------------------------------

void LoopWorker::execute() {
  for (size_t index = begin; index < end; ++index)
    ptrLoopWorker->execute(index);
}
//---------------------------------------------------------------------------------
// Definition ParallelFor
//---------------------------------------------------------------------------------

void ParallelFor::operator() (size_t begin,
                              size_t end,
                              size_t chunk,
                              ILoopWorker* pLoopWorker,
                              CThreadPool* pPool) {
  makeLoopWorkers(begin, end, chunk, pLoopWorker);
  submitLoopWorkers(pPool);
  pPool->wait();
}
//---------------------------------------------------------------------------------

void ParallelFor::makeLoopWorkers(size_t begin,
                                  size_t end,
                                  size_t chunk,
                                  ILoopWorker* pLoopWorker) {
  LoopWorkers.clear();
  size_t numberOfFullChunks = (end - begin) / chunk;
  size_t numberOfChunks = numberOfFullChunks;
  if ((end - begin) % chunk != 0)
    ++numberOfChunks;
  LoopWorkers.reserve(numberOfChunks);

  for (size_t index = 0; index < numberOfFullChunks; ++index) {
    size_t chunkStart = begin + index * chunk;
    size_t chunkEnd = chunkStart + chunk;
    LoopWorkers.emplace_back(LoopWorker(chunkStart,
                                        chunkEnd,
                                        pLoopWorker));
  }
  if (numberOfFullChunks != numberOfChunks)
    LoopWorkers.emplace_back(LoopWorker(begin + numberOfFullChunks * chunk,
                                        end,
                                        pLoopWorker));
}
//---------------------------------------------------------------------------------

void ParallelFor::submitLoopWorkers(CThreadPool* pPool) {
  for (auto& loopWorker : LoopWorkers)
    pPool->submit(&loopWorker);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
