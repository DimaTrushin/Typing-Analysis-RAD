//---------------------------------------------------------------------------

#ifndef UnitStableZonesFillerH
#define UnitStableZonesFillerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitExtremumFinder.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CThreadPool ThreadPool;
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CStableZonesFillerBase
//---------------------------------------------------------------------------

template<class TExtremumFinder>
class CStableZonesFillerBase {
public:
  template<class TApproximation>
  void computeMarkedIntervals(const TApproximation& Approximation,
                              CMarkedIntervalContainer* pMarkedIntervals);
private:
  void registerData(CMarkedIntervalContainer* MarkedIntervals);
  template<class TApproximation>
  void fillMaxMinPairs(const TApproximation& Approximation);
  template<class TApproximation>
  void fillMarkedPoints(const TApproximation& Approximation);
  template<class TApproximation>
  void sortMarkedIntervals(const TApproximation& Approximation);

  template<class TApproximation>
  void findRoughMaxMinPairs(const TApproximation& Approximation,
                            CRoughMaxMinPairContainer *pMaxMinPairs) const;
  // need this serial version for speed comparison
  template<class TApproximation>
  void findMaxMinPairs( const TApproximation& Approximation,
                        const CRoughMaxMinPairContainer& MaxMinPairs,
                        CIntervalContainer *pIntervals) const;
  template<class TApproximation>
  void findMaxMinPairsParallel( const TApproximation& Approximation,
                                const CRoughMaxMinPairContainer& MaxMinPairs,
                                CIntervalContainer *pIntervals) const;
  template<class TApproximation>
  void convertMaxMinPairToInterval( const TApproximation& Approximation,
                                    const CRoughMaxMinPair& RMaxMinPair,
                                    CInterval* pInterval) const;
  void excludeIncorrectIntervals(CIntervalContainer* pIntervals) const;
  // ---------------------------------------------------------------------------
  // Declaration of CFindMaxMinPairsLoopEvent
  // ---------------------------------------------------------------------------
  template<class TApproximation>
  friend class CFindMaxMinPairsLoopEvent;

  template<class TApproximation>
  class CFindMaxMinPairsLoopEvent : public ILoopWorker {
  public:
    CFindMaxMinPairsLoopEvent(const CStableZonesFillerBase* Filler,
                              const TApproximation& Approximation,
                              const CRoughMaxMinPairContainer& MaxMinPairs,
                              CIntervalContainer* MaxMinIntervals);
    void execute(size_t index) override;
  private:
    const CStableZonesFillerBase* pFiller;
    const TApproximation* pApproximation;
    const CRoughMaxMinPairContainer* pMaxMinPairs;
    CIntervalContainer* pMaxMinIntervals;
  };
  // ---------------------------------------------------------------------------
  // Declaration of CFillMarkedPointsLoopEvent
  // ---------------------------------------------------------------------------
  template<class TApproximation>
  friend class CFillMarkedPointsLoopEvent;

  template<class TApproximation>
  class CFillMarkedPointsLoopEvent : public ILoopWorker {
  public:
    CFillMarkedPointsLoopEvent(
                      CStableZonesFillerBase* Filler,
                      const TApproximation& Approximation);
    void execute(size_t index) override;
  private:
    CStableZonesFillerBase* pFiller;
    const TApproximation* pApproximation;
  };
  // ---------------------------------------------------------------------------
  // Declaration of CParallelFor
  // ---------------------------------------------------------------------------

  class CParallelFor : ParallelFor {
  public:
    void operator()(size_t begin,
                    size_t end,
                    ILoopWorker* pLoopWorker,
                    CThreadPool* pPool);
  private:
    // need to be tuned
    // maybe chunkSize = 10 by default
    size_t getChunk(size_t begin,
                    size_t end,
                    CThreadPool* pPool) const;
    static constexpr size_t kNumberOfChunks = 250;
  };
  // ---------------------------------------------------------------------------
  CMarkedIntervalContainer* pMarkedIntervals;
};
//---------------------------------------------------------------------------
// Declaration of CStableZonesFiller
//---------------------------------------------------------------------------

using CStableZonesFiller = CStableZonesFillerBase<CExtremumFinder>;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definitions of CStableZonesFillerBase
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::computeMarkedIntervals(
                                  const TApproximation& Approximation,
                                  CMarkedIntervalContainer* pMarkedIntervals) {
  registerData(pMarkedIntervals);
  fillMaxMinPairs(Approximation);
  fillMarkedPoints(Approximation);
  sortMarkedIntervals(Approximation);
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
void CStableZonesFillerBase<TExtremumFinder>::registerData(
                                  CMarkedIntervalContainer* MarkedIntervals) {
  pMarkedIntervals = MarkedIntervals;
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::
                        fillMaxMinPairs(const TApproximation& Approximation) {
  CRoughMaxMinPairContainer RoughMaxMinPairs;
  findRoughMaxMinPairs(Approximation, &RoughMaxMinPairs); // LogTime
  CIntervalContainer MaxMinIntervals;
  findMaxMinPairsParallel(Approximation, RoughMaxMinPairs, &MaxMinIntervals); // LogTime
  pMarkedIntervals->setWithIntervalContainer(MaxMinIntervals);
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::
                        fillMarkedPoints(const TApproximation& Approximation){
  size_t size = pMarkedIntervals->size();
  CFillMarkedPointsLoopEvent<TApproximation> LoopEvent(this, Approximation);
  CParallelFor Computer;
  Computer(0, size, &LoopEvent, &ThreadPool); // LogTime
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::sortMarkedIntervals(
                                        const TApproximation& Approximation) {
  CMarkedInterval::Comparator<TApproximation> Compare(Approximation);
  std::sort(pMarkedIntervals->begin(), pMarkedIntervals->end(), Compare); // LogTime
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::findRoughMaxMinPairs(
                          const TApproximation& Approximation,
                          CRoughMaxMinPairContainer *pMaxMinPairs) const{

  CFunctionGrid DerivativeGrid;
  // This is the heaviest computation in the program
  DerivativeGrid.setApproximationGridParallel1(Approximation); // LogTime
  DerivativeGrid.fillRoughMaxMinPairContainer(pMaxMinPairs);
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::findMaxMinPairs(
                          const TApproximation& Approximation,
                          const CRoughMaxMinPairContainer& MaxMinPairs,
                          CIntervalContainer *pIntervals) const {
  size_t size = MaxMinPairs.size();
  pIntervals->resize(size);
  for (size_t index = 0; index < size; ++index)
    convertMaxMinPairToInterval(Approximation,
                                MaxMinPairs[index],
                                &((*pIntervals)[index]));
  excludeIncorrectIntervals(pIntervals);
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::findMaxMinPairsParallel(
                            const TApproximation& Approximation,
                            const CRoughMaxMinPairContainer& MaxMinPairs,
                            CIntervalContainer *pIntervals) const {
  size_t size = MaxMinPairs.size();
  pIntervals->resize(size);
  CFindMaxMinPairsLoopEvent<TApproximation> LoopEvent(this,
                                                      Approximation,
                                                      MaxMinPairs,
                                                      pIntervals);
  CParallelFor Computer;
  Computer(0, size, &LoopEvent, &ThreadPool);
  excludeIncorrectIntervals(pIntervals);
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::convertMaxMinPairToInterval(
                                      const TApproximation& Approximation,
                                      const CRoughMaxMinPair& RMaxMinPair,
                                      CInterval* pInterval) const{
  pInterval->first =
              TExtremumFinder::computeMaximumOnInterval1( Approximation,
                                                          RMaxMinPair.first);
  pInterval->second =
              TExtremumFinder::computeMinimumOnInterval1( Approximation,
                                                          RMaxMinPair.second);
}
// ---------------------------------------------------------------------------
template<class TExtremumFinder>
void CStableZonesFillerBase<TExtremumFinder>::excludeIncorrectIntervals(
                                      CIntervalContainer* pIntervals) const {
  assert(pIntervals != nullptr);
  size_t amountOfCorrectIntervals = pIntervals->size();
  size_t currentInterval = 0;
  while (currentInterval < amountOfCorrectIntervals) {
    if ((*pIntervals)[currentInterval].getLength() > 0)
      ++currentInterval;
    else {
      --amountOfCorrectIntervals;
      if(currentInterval == amountOfCorrectIntervals)
        break;
      std::swap((*pIntervals)[currentInterval],
                (*pIntervals)[amountOfCorrectIntervals]);
    }
  }
  pIntervals->resize(amountOfCorrectIntervals);
}
// ---------------------------------------------------------------------------
// Definition of CStableZonesFillerBase::CFindMaxMinPairsLoopEvent
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
CStableZonesFillerBase<TExtremumFinder>::
  CFindMaxMinPairsLoopEvent<TApproximation>::
    CFindMaxMinPairsLoopEvent(const CStableZonesFillerBase* Filler,
                              const TApproximation& Approximation,
                              const CRoughMaxMinPairContainer& MaxMinPairs,
                              CIntervalContainer* MaxMinIntervals)
    : pFiller(Filler),
      pApproximation(&Approximation),
      pMaxMinPairs(&MaxMinPairs),
      pMaxMinIntervals(MaxMinIntervals) {
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::
      CFindMaxMinPairsLoopEvent<TApproximation>::execute(size_t index) {
  pFiller->convertMaxMinPairToInterval( *pApproximation,
                                        (*pMaxMinPairs)[index],
                                        &((*pMaxMinIntervals)[index]));
}
// ---------------------------------------------------------------------------
// Definition of CStableZonesFillerBase::CFillMarkedPointsLoopEvent
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
CStableZonesFillerBase<TExtremumFinder>::
  CFillMarkedPointsLoopEvent<TApproximation>::
    CFillMarkedPointsLoopEvent( CStableZonesFillerBase* Filler,
                                const TApproximation& Approximation)
  : pFiller(Filler),
    pApproximation(&Approximation) {
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
template<class TApproximation>
void CStableZonesFillerBase<TExtremumFinder>::
      CFillMarkedPointsLoopEvent<TApproximation>::execute(size_t index) {
  auto pMarkedIntervals = pFiller->pMarkedIntervals;
  (*pMarkedIntervals)[index].point =
    TExtremumFinder::
      computeMaximumOnInterval0(*pApproximation, (*pMarkedIntervals)[index]);
}
// ---------------------------------------------------------------------------
// Definition of CStableZonesFillerBase::CParallelFor
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
void CStableZonesFillerBase<TExtremumFinder>::
                        CParallelFor::operator()( size_t begin,
                                                  size_t end,
                                                  ILoopWorker* pLoopWorker,
                                                  CThreadPool* pPool) {
  size_t chunk = getChunk(begin, end, pPool);
  ParallelFor::operator()(begin, end, chunk, pLoopWorker, pPool);
}
// ---------------------------------------------------------------------------

template<class TExtremumFinder>
size_t CStableZonesFillerBase<TExtremumFinder>::
                          CParallelFor::getChunk( size_t begin,
                                                  size_t end,
                                                  CThreadPool* pPool) const {
  using std::max;
  using std::min;
  size_t threadBoundary = (end - begin) / pPool->getThreadMaximum();
  size_t empiricalBoundary = (end - begin) / kNumberOfChunks;
  return max<size_t>(min<size_t>(empiricalBoundary, threadBoundary), 1);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
