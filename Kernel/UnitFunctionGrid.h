//---------------------------------------------------------------------------

#ifndef UnitFunctionGridH
#define UnitFunctionGridH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitMarkedInterval.h"
#include "UnitParallelFor.h"
//---------------------------------------------------------------------------

namespace NSApplication {
// ---------------------------------------------------------------------------
// Global Variable
// ---------------------------------------------------------------------------
extern CThreadPool ThreadPool;
namespace NSKernel {

// ---------------------------------------------------------------------------
// Declaration of CFunctionGrid
// ---------------------------------------------------------------------------

enum class EExtremalPointType {
  Minimum, Maximum, Inflection
};
//---------------------------------------------------------------------------
// Declaration of isFirstExtremum
//---------------------------------------------------------------------------

template<EExtremalPointType PointType>
bool isFirstExtremum(double extremum, double other);
// ---------------------------------------------------------------------------
// Declaration of CFunctionGridBase
// ---------------------------------------------------------------------------

class CFunctionGridBase : public std::vector<double> {
public:
  CFunctionGridBase() = default;
  CFunctionGridBase(double start, double step);

  double getPoint(size_t position) const;
  double getPoint(const const_iterator& position) const;
  double getStart() const;
  double getStep() const;
  double getArea() const;
  // Need functions for integration
  void fillRoughMaxMinPairContainer(
                          CRoughMaxMinPairContainer *target) const;
  CInterval findRoughRoot() const;
protected:
  inline void findNextMax(const const_iterator& itCurrent,
                          const_iterator* pItMax) const;
  inline void findNextMin(const const_iterator& itCurrent,
                          const_iterator* pItMin) const;
  template<EExtremalPointType PointType>
  inline void findNextExtremum( const const_iterator& itCurrent,
                                const_iterator* pItExtremum) const;
  template<EExtremalPointType PointType>
  inline bool isExtremum( const const_iterator& extremum,
                          const const_iterator& previous,
                          const const_iterator& next) const;
  // ---------------------------------------------------------------------------
  // Declaration of CParallelFor
  // ---------------------------------------------------------------------------

  class CParallelFor : ParallelFor {
  public:
    void operator()(size_t begin,
                    size_t end,
                    size_t samples,
                    ILoopWorker* pLoopWorker,
                    CThreadPool* pPool);
  private:
    size_t getChunk(size_t begin,
                    size_t end,
                    size_t samples,
                    CThreadPool* pPool) const;
    static constexpr size_t threadCoefficient = 10;
  };
  // ---------------------------------------------------------------------------
  double Start;
  double Step;
};
// ---------------------------------------------------------------------------
// Declaration of CFunctionGridDirectEvaluation
// ---------------------------------------------------------------------------

class CFunctionGridDirectEvaluation : public CFunctionGridBase {
public:
  using CFunctionGridBase::CFunctionGridBase;
  template<class TApproximation>
  void setApproximationGrid0(
                  const TApproximation& Approximation);
  template<class TApproximation>
  void setApproximationGrid1(
                  const TApproximation& Approximation);
  template<class TApproximation>
  void setApproximationGridParallel0(
                  const TApproximation& Approximation);
  template<class TApproximation>
  void setApproximationGridParallel1(
                  const TApproximation& Approximation);

  template<class TApproximation>
  void setApproximationGrid0(
                  const TApproximation& Approximation,
                  const CInterval& Interval);
  template<class TApproximation>
  void setApproximationGrid1(
                  const TApproximation& Approximation,
                  const CInterval& Interval);
  template<class TApproximation>
  void setApproximationGrid2(
                  const TApproximation& Approximation,
                  const CInterval& Interval);

  template<class TApproximation>
  void setApproximationGridParallel0(
                  const TApproximation& Approximation,
                  const CInterval& Interval);
  template<class TApproximation>
  void setApproximationGridParallel1(
                  const TApproximation& Approximation,
                  const CInterval& Interval);
  template<class TApproximation>
  void setApproximationGridParallel2(
                  const TApproximation& Approximation,
                  const CInterval& Interval);
private:
  // define for [kMinimumValue, kMaximumValue) with step = kStep
  // the kConst are taken from TApproximation
  template <class TMethod,
            class TApproximation>
  inline void setApproximationGridWithMethod(
                  const TMethod& Method,
                  const TApproximation& Approximation);
  template <class TGridFiller,
            class TApproximation>
  inline void setApproximationGridWithMethodParallel(
                  const TApproximation& Approximation);
  template <class TMethod,
            class TApproximation>
  inline void setApproximationGridWithMethod(
                  const TMethod& Method,
                  const TApproximation& Approximation,
                  const CInterval& Interval);
  template <class TGridFiller,
            class TApproximation>
  inline void setApproximationGridWithMethodParallel(
                  const TApproximation& Approximation,
                  const CInterval& Interval);
  // ---------------------------------------------------------------------------
  // Declaration of CGridFiller0
  // ---------------------------------------------------------------------------

  template<class TApproximation>
  class CGridFiller0 : public ILoopWorker {
  public:
    CGridFiller0( CFunctionGridDirectEvaluation& Grid,
                  const TApproximation& Approximation);
    void execute(size_t index) override;
  private:
    CFunctionGridDirectEvaluation* pGrid;
    const TApproximation* pApproximation;
  };
  // ---------------------------------------------------------------------------
  // Declaration of CGridFiller1
  // ---------------------------------------------------------------------------

  template<class TApproximation>
  class CGridFiller1 : public ILoopWorker {
  public:
    CGridFiller1( CFunctionGridDirectEvaluation& Grid,
                  const TApproximation& Approximation);
    void execute(size_t index) override;
  private:
    CFunctionGridDirectEvaluation* pGrid;
    const TApproximation* pApproximation;
  };
  // ---------------------------------------------------------------------------
  // Declaration of CGridFiller2
  // ---------------------------------------------------------------------------

  template<class TApproximation>
  class CGridFiller2 : public ILoopWorker {
  public:
    CGridFiller2( CFunctionGridDirectEvaluation& Grid,
                  const TApproximation& Approximation);
    void execute(size_t index) override;
  private:
    CFunctionGridDirectEvaluation* pGrid;
    const TApproximation* pApproximation;
  };
};
// ---------------------------------------------------------------------------
// Declaration of CFunctionGridTemplateEvaluation
// ---------------------------------------------------------------------------

class CFunctionGridTemplateEvaluation : public CFunctionGridDirectEvaluation {
public:
  using CFunctionGridDirectEvaluation::CFunctionGridDirectEvaluation;
  template <unsigned int derivative,
            class TApproximation>
  void setApproximationGrid(const TApproximation& Approximation);
  template <unsigned int derivative,
            class TApproximation>
  void setApproximationGridParallel(
                            const TApproximation& Approximation);
  template <unsigned int derivative,
            class TApproximation>
  void setApproximationGrid(const TApproximation& Approximation,
                            const CInterval& Interval);
  template <unsigned int derivative,
            class TApproximation>
  void setApproximationGridParallel(
                            const TApproximation& Approximation,
                            const CInterval& Interval);
private:
  // ---------------------------------------------------------------------------
  // Declaration of CGridFiller
  // ---------------------------------------------------------------------------

  template <unsigned int derivative,
            class TApproximation>
  class CGridFiller : public ILoopWorker {
  public:
    CGridFiller(CFunctionGridTemplateEvaluation& Grid,
                const TApproximation& Approximation);
    void execute(size_t index) override;
  private:
    CFunctionGridTemplateEvaluation* pGrid;
    const TApproximation* pApproximation;
  };
};
// ---------------------------------------------------------------------------
// Declaration of CFunctionGrid
// ---------------------------------------------------------------------------

using CFunctionGrid = CFunctionGridTemplateEvaluation;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of isFirstExtremum
// ---------------------------------------------------------------------------

template<>
bool isFirstExtremum<EExtremalPointType::Maximum>(double extremum,
                                                  double other) {
  return extremum > other;
}
// ---------------------------------------------------------------------------

template<>
bool isFirstExtremum<EExtremalPointType::Minimum>(double extremum,
                                                  double other) {
  return extremum < other;
}
// ---------------------------------------------------------------------------
// Definition of CFunctionGridDirectEvaluation
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
            ::setApproximationGrid0(
                  const TApproximation& Approximation) {
  setApproximationGridWithMethod(&TApproximation::evaluate0, Approximation);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
            ::setApproximationGrid1(
                  const TApproximation& Approximation) {
  setApproximationGridWithMethod(&TApproximation::evaluate1, Approximation);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
            ::setApproximationGridParallel0(
                                const TApproximation& Approximation) {
  setApproximationGridWithMethodParallel<
                          CGridFiller0<TApproximation>>(Approximation);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
          ::setApproximationGridParallel1(
                                const TApproximation& Approximation) {
  setApproximationGridWithMethodParallel<
                          CGridFiller1<TApproximation>>(Approximation);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
            ::setApproximationGrid0(
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  setApproximationGridWithMethod(&TApproximation::evaluate0,
                                  Approximation,
                                  Interval);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
          ::setApproximationGrid1(
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  setApproximationGridWithMethod(&TApproximation::evaluate1,
                                  Approximation,
                                  Interval);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
          ::setApproximationGrid2(
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  setApproximationGridWithMethod(&TApproximation::evaluate2,
                                  Approximation,
                                  Interval);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
          ::setApproximationGridParallel0(
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  setApproximationGridWithMethodParallel<
                      CGridFiller0<TApproximation>>(Approximation, Interval);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
    ::setApproximationGridParallel1(
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  setApproximationGridWithMethodParallel<
                      CGridFiller1<TApproximation>>(Approximation, Interval);
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void CFunctionGridDirectEvaluation
    ::setApproximationGridParallel2(
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  setApproximationGridWithMethodParallel<
                      CGridFiller2<TApproximation>>(Approximation, Interval);
}
// ---------------------------------------------------------------------------

template <class TMethod,
          class TApproximation>
void CFunctionGridDirectEvaluation::
                setApproximationGridWithMethod(
                                    const TMethod& Method,
                                    const TApproximation& Approximation) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = CGridDefault::kMinimumValue;
  Step = CGridDefault::kStep;
  resize(CGridDefault::kNumberOfSteps);
  for (size_t index = 0; index < CGridDefault::kNumberOfSteps; ++index)
    (*this)[index] = (Approximation.*Method)(getPoint(index));
}
// ---------------------------------------------------------------------------

template <class TGridFiller,
          class TApproximation>
void CFunctionGridDirectEvaluation::
              setApproximationGridWithMethodParallel(
                  const TApproximation& Approximation) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = CGridDefault::kMinimumValue;
  Step = CGridDefault::kStep;
  resize(CGridDefault::kNumberOfSteps);
  TGridFiller LoopEvent(*this, Approximation);
  CParallelFor Computer;
  Computer( 0,
            CGridDefault::kNumberOfSteps,
            Approximation.getNumberOfSamples(),
            &LoopEvent,
            &ThreadPool);
}
// ---------------------------------------------------------------------------

template <class TMethod,
          class TApproximation>
void CFunctionGridDirectEvaluation::
              setApproximationGridWithMethod(
                  const TMethod& Method,
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = Interval.first;
  assert(Interval.getLength() > 0);
  size_t numberOfSteps =
            static_cast<size_t>(
                    std::ceil(Interval.getLength() / CGridDefault::kStep));
  assert(numberOfSteps != 0);
  resize(numberOfSteps);
  Step = Interval.getLength() / static_cast<double>(numberOfSteps);
  for (size_t index = 0; index < numberOfSteps; ++index)
    (*this)[index] = (Approximation.*Method)(getPoint(index));
}
// ---------------------------------------------------------------------------

template <class TGridFiller,
          class TApproximation>
void CFunctionGridDirectEvaluation::
              setApproximationGridWithMethodParallel(
                  const TApproximation& Approximation,
                  const CInterval& Interval) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = Interval.first;
  assert(Interval.getLength() > 0);
  size_t numberOfSteps =
            static_cast<size_t>(
                    std::ceil(Interval.getLength() / CGridDefault::kStep));
  assert(numberOfSteps != 0);
  resize(numberOfSteps);
  Step = Interval.getLength() / static_cast<double>(numberOfSteps);
  TGridFiller LoopEvent(*this, Approximation);
  CParallelFor Computer;
  Computer( 0,
            numberOfSteps,
            Approximation.getNumberOfSamples(),
            &LoopEvent,
            &ThreadPool);
}
// ---------------------------------------------------------------------------
// Definition of CFunctionGridDirectEvaluation::CGridFiller0
// ---------------------------------------------------------------------------

template<class TApproximation>
CFunctionGridDirectEvaluation::
  CGridFiller0<TApproximation>::
                CGridFiller0( CFunctionGridDirectEvaluation& Grid,
                              const TApproximation& Approximation)
    : pGrid(&Grid),
      pApproximation(&Approximation) {
  }
// ---------------------------------------------------------------------------

template<class TApproximation>
void
  CFunctionGridDirectEvaluation::
    CGridFiller0<TApproximation>::execute(size_t index) {
  (*pGrid)[index] = pApproximation->evaluate0(pGrid->getPoint(index));
}
// ---------------------------------------------------------------------------
// Definition of CFunctionGridDirectEvaluation::CGridFiller1
// ---------------------------------------------------------------------------

template<class TApproximation>
CFunctionGridDirectEvaluation::
  CGridFiller1<TApproximation>::
                CGridFiller1( CFunctionGridDirectEvaluation& Grid,
                              const TApproximation& Approximation)
    : pGrid(&Grid),
      pApproximation(&Approximation) {
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void
  CFunctionGridDirectEvaluation::
    CGridFiller1<TApproximation>::execute(size_t index) {
    (*pGrid)[index] = pApproximation->evaluate1(pGrid->getPoint(index));
}
// ---------------------------------------------------------------------------
// Definition of CFunctionGridDirectEvaluation::CGridFiller2
// ---------------------------------------------------------------------------

template<class TApproximation>
CFunctionGridDirectEvaluation::
  CGridFiller2<TApproximation>::
                CGridFiller2( CFunctionGridDirectEvaluation& Grid,
                              const TApproximation& Approximation)
    : pGrid(&Grid),
      pApproximation(&Approximation) {
}
// ---------------------------------------------------------------------------

template<class TApproximation>
void
  CFunctionGridDirectEvaluation::
    CGridFiller2<TApproximation>::execute(size_t index) {
    (*pGrid)[index] = pApproximation->evaluate2(pGrid->getPoint(index));
}
// ---------------------------------------------------------------------------
// Definition of CFunctionGridTemplateEvaluation
// ---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
void CFunctionGridTemplateEvaluation::
  setApproximationGrid( const TApproximation& Approximation) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = CGridDefault::kMinimumValue;
  Step = CGridDefault::kStep;
  resize(CGridDefault::kNumberOfSteps);
  for (unsigned int index = 0; index < CGridDefault::kNumberOfSteps; ++index)
    (*this)[index] = Approximation.template evaluate<derivative>(getPoint(index));
}
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
void CFunctionGridTemplateEvaluation::
                setApproximationGridParallel(
                            const TApproximation& Approximation) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = CGridDefault::kMinimumValue;
  Step = CGridDefault::kStep;
  resize(CGridDefault::kNumberOfSteps);
  CGridFiller<derivative, TApproximation> LoopEvent(*this, Approximation);
  CParallelFor Computer;
  Computer( 0,
            CGridDefault::kNumberOfSteps,
            Approximation.getNumberOfSamples(),
            &LoopEvent,
            &ThreadPool);
}
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
void CFunctionGridTemplateEvaluation::
        setApproximationGrid( const TApproximation& Approximation,
                              const CInterval& Interval) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = Interval.first;
  assert(Interval.getLength() > 0);
  size_t numberOfSteps =
            static_cast<size_t>(
                    std::ceil(Interval.getLength() / CGridDefault::kStep));
  assert(numberOfSteps != 0);
  resize(numberOfSteps);
  Step = Interval.getLength() / static_cast<double>(numberOfSteps);
  for (size_t index = 0; index < numberOfSteps; ++index)
    (*this)[index] = Approximation.template evaluate<derivative>(getPoint(index));
}
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
void CFunctionGridTemplateEvaluation::
                      setApproximationGridParallel(
                            const TApproximation& Approximation,
                            const CInterval& Interval) {
  using CGridDefault = typename TApproximation::CGridDefault;
  clear();
  Start = Interval.first;
  assert(Interval.getLength() > 0);
  size_t numberOfSteps =
            static_cast<size_t>(
                    std::ceil(Interval.getLength() / CGridDefault::kStep));
  assert(numberOfSteps != 0);
  resize(numberOfSteps);
  Step = Interval.getLength() / static_cast<double>(numberOfSteps);
  CGridFiller<derivative, TApproximation> LoopEvent(*this, Approximation);
  CParallelFor Computer;
  Computer( 0,
            numberOfSteps,
            Approximation.getNumberOfSamples(),
            &LoopEvent,
            &ThreadPool);
}
// ---------------------------------------------------------------------------
// Definition of CGridFiller
// ---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
CFunctionGridTemplateEvaluation::
  CGridFiller<derivative, TApproximation>::
    CGridFiller(CFunctionGridTemplateEvaluation& Grid,
                const TApproximation& Approximation)
  : pGrid(&Grid),
    pApproximation(&Approximation){
}
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
void CFunctionGridTemplateEvaluation::
  CGridFiller<derivative, TApproximation>::execute(size_t index) {
  (*pGrid)[index] =
      pApproximation->template evaluate<derivative>(pGrid->getPoint(index));
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
