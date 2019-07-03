//---------------------------------------------------------------------------

#ifndef UnitPlotterH
#define UnitPlotterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vcl.h>
#include <VCLTee.Series.hpp>
#include "UnitParallelFor.h"
#include "../Kernel/UnitApproximation.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Extern Variables
//---------------------------------------------------------------------------

extern CThreadPool ThreadPool;
//---------------------------------------------------------------------------

namespace NSInterface {
//---------------------------------------------------------------------------
// Declaration of CPlotterBase
//---------------------------------------------------------------------------

template<class TApproximation>
class CPlotterBase {
public:
  using CApproximation = TApproximation;
  using CGridDefault = typename CApproximation::CGridDefault;
  CPlotterBase();
  void setPlotterBase(TFastLineSeries* pNewSeries);
protected:
  ~CPlotterBase() = default;
  void populateWithZeros();

  TFastLineSeries* pSeries;
};
//---------------------------------------------------------------------------
// Declaration of CSerialPlotFiller
//---------------------------------------------------------------------------

template<class TPlotterBase>
class CSerialPlotFiller : public TPlotterBase {
  using CBase = TPlotterBase;
public:
  using CApproximation = typename CBase::CApproximation;
  using CGridDefault = typename CBase::CGridDefault;
  using CBase::CBase;
protected:
  ~CSerialPlotFiller() = default;
  template<class TMethod>
  void fillPlotWithMethod(const CApproximation& Approximation,
                          const TMethod& Method,
                          double Scale = 1.0);
};
//---------------------------------------------------------------------------
// Declaration of CParallelPlotFiller
//---------------------------------------------------------------------------

template<class TPlotterBase>
class CParallelPlotFiller : public TPlotterBase {
  using CBase = TPlotterBase;
public:
  using CApproximation = typename CBase::CApproximation;
  using CGridDefault = typename CBase::CGridDefault;
  using CBase::CBase;
protected:
  ~CParallelPlotFiller() = default;
  //---------------------------------------------------------------------------
  // Declaration of CFillingWithMethodLoopEvent
  //---------------------------------------------------------------------------
  template<class TMethod>
  friend class CFillingWithMethodLoopEvent;

  template<class TMethod>
  class CFillingWithMethodLoopEvent : public ILoopWorker {
  public:
    CFillingWithMethodLoopEvent(double newScale,
                                const CApproximation& Approximation,
                                const TMethod& newMethod,
                                TFastLineSeries* Series);
    void execute(size_t index) override;
  private:
    double Scale;
    const CApproximation* pApproximation;
    const TMethod Method;
    TFastLineSeries* pSeries;
  };
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
    static constexpr size_t kThreadCoefficient = 10;
  };
  //---------------------------------------------------------------------------
  template<class TMethod>
  void fillPlotWithMethod(const CApproximation& Approximation,
                          const TMethod& Method,
                          double Scale = 1.0);
};
//---------------------------------------------------------------------------
// Declaration of CHistogramPlotter
//---------------------------------------------------------------------------

template<class TApproximation>
class CHistogramPlotter : public CPlotterBase<TApproximation> {
  using CBase = CPlotterBase<TApproximation>;
public:
  using CApproximation = typename CBase::CApproximation;
  using CBase::CBase;
  void draw(const CApproximation& Approximation, double Chunk);
private:
  using CGridDefault = typename CApproximation::CGridDefault;
};
//---------------------------------------------------------------------------
// Declaration of CSpeedHistogramPlotter
//---------------------------------------------------------------------------

using CSpeedHistogramPlotter =
        CHistogramPlotter<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CPlotterDirect0
//---------------------------------------------------------------------------

template<class TPlotFiller>
class CPlotterDirect0 : public TPlotFiller {
  using CBase = TPlotFiller;
public:
  using CApproximation = typename CBase::CApproximation;
  using CBase::CBase;
  void draw(const CApproximation& Approximation);
};
//---------------------------------------------------------------------------
// Declaration of CPlotterDirect1
//---------------------------------------------------------------------------

template<class TPlotFiller>
class CPlotterDirect1 : public TPlotFiller {
  using CBase = TPlotFiller;
public:
  using CApproximation = typename CBase::CApproximation;
  using CBase::CBase;
  void draw(const CApproximation& Approximation);
};
//---------------------------------------------------------------------------
// Declaration of CSerialPlotterDirect0
//---------------------------------------------------------------------------

template<class TApproximation>
using CSerialPlotterDirect0 =
        CPlotterDirect0<CSerialPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CSerialPlotterDirect1
//---------------------------------------------------------------------------

template<class TApproximation>
using CSerialPlotterDirect1 =
        CPlotterDirect1<CSerialPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CParallelPlotterDirect0
//---------------------------------------------------------------------------

template<class TApproximation>
using CParallelPlotterDirect0 =
        CPlotterDirect0<CParallelPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CParallelPlotterDirect1
//---------------------------------------------------------------------------

template<class TApproximation>
using CParallelPlotterDirect1 =
        CPlotterDirect1<CParallelPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CPlotterDirectUniform0
//---------------------------------------------------------------------------

template<class TPlotFiller>
class CPlotterDirectUniform0 : public TPlotFiller {
  using CBase = TPlotFiller;
public:
  using CApproximation = typename CBase::CApproximation;
  using CBase::CBase;
  void draw(const CApproximation& Approximation);
};
//---------------------------------------------------------------------------
// Declaration of CPlotterDirectUniform1
//---------------------------------------------------------------------------

template<class TPlotFiller>
class CPlotterDirectUniform1 : public TPlotFiller {
  using CBase = TPlotFiller;
public:
  using CApproximation = typename CBase::CApproximation;
  using CBase::CBase;
  void draw(const CApproximation& Approximation);
};
//---------------------------------------------------------------------------
// Declaration of CSerialPlotterDirectUniform0
//---------------------------------------------------------------------------

template<class TApproximation>
using CSerialPlotterDirectUniform0 =
        CPlotterDirectUniform0<
          CSerialPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CSerialPlotterDirectUniform1
//---------------------------------------------------------------------------

template<class TApproximation>
using CSerialPlotterDirectUniform1 =
        CPlotterDirectUniform1<
          CSerialPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CParallelPlotterDirectUniform0
//---------------------------------------------------------------------------

template<class TApproximation>
using CParallelPlotterDirectUniform0 =
        CPlotterDirectUniform0<
          CParallelPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CParallelPlotterDirectUniform1
//---------------------------------------------------------------------------

template<class TApproximation>
using CParallelPlotterDirectUniform1 =
        CPlotterDirectUniform1<
          CParallelPlotFiller<CPlotterBase<TApproximation>>>;
//---------------------------------------------------------------------------
// Declaration of CPlotterTemplate
//---------------------------------------------------------------------------

template <class TPlotFiller,
          unsigned int derivative>
class CPlotterTemplate : public TPlotFiller {
  using CBase = TPlotFiller;
public:
  using CApproximation = typename CBase::CApproximation;
  using CBase::CBase;
  void draw(const CApproximation& Approximation);
};
//---------------------------------------------------------------------------
// Declaration of CSerialPlotterTemplate
//---------------------------------------------------------------------------

template< class TApproximation,
          unsigned int derivative>
using CSerialPlotterTemplate =
        CPlotterTemplate<
          CSerialPlotFiller<CPlotterBase<TApproximation>>, derivative>;
//---------------------------------------------------------------------------
// Declaration of CParallelPlotterTemplate
//---------------------------------------------------------------------------

template< class TApproximation,
          unsigned int derivative>
using CParallelPlotterTemplate =
        CPlotterTemplate<
          CParallelPlotFiller<CPlotterBase<TApproximation>>, derivative>;
//---------------------------------------------------------------------------
// Declaration of CPlotterTemplateUniform
//---------------------------------------------------------------------------

template <class TPlotFiller,
          unsigned int derivative>
class CPlotterTemplateUniform : public TPlotFiller {
  using CBase = TPlotFiller;
public:
  using CApproximation = typename CBase::CApproximation;
  using CBase::CBase;
  void draw(const CApproximation& Approximation);
};
//---------------------------------------------------------------------------
// Declaration of CSerialPlotterTemplateUniform
//---------------------------------------------------------------------------

template< class TApproximation,
          unsigned int derivative>
using CSerialPlotterTemplateUniform =
        CPlotterTemplateUniform<
          CSerialPlotFiller<CPlotterBase<TApproximation>>, derivative>;
//---------------------------------------------------------------------------
// Declaration of CParallelPlotterTemplateUniform
//---------------------------------------------------------------------------

template< class TApproximation,
          unsigned int derivative>
using CParallelPlotterTemplateUniform =
        CPlotterTemplateUniform<
          CParallelPlotFiller<CPlotterBase<TApproximation>>, derivative>;
//---------------------------------------------------------------------------
// Declaration of CSerialSpeedPlotter
//---------------------------------------------------------------------------

using CSerialSpeedPlotter =
          CSerialPlotterDirect0<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CSerialSpeedDerivativePlotter
//---------------------------------------------------------------------------

using CSerialSpeedDerivativePlotter =
          CSerialPlotterDirect1<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CSerialSpeedPlotterUniform
//---------------------------------------------------------------------------

using CSerialSpeedPlotterUniform =
          CSerialPlotterDirectUniform0<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CSerialSpeedDerivativePlotterUniform
//---------------------------------------------------------------------------

using CSerialSpeedDerivativePlotterUniform =
          CSerialPlotterDirectUniform1<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CParallelSpeedPlotter
//---------------------------------------------------------------------------

using CParallelSpeedPlotter =
          CParallelPlotterDirect0<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CParallelSpeedDerivativePlotter
//---------------------------------------------------------------------------

using CParallelSpeedDerivativePlotter =
          CParallelPlotterDirect1<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CParallelSpeedPlotterUniform
//---------------------------------------------------------------------------

using CParallelSpeedPlotterUniform =
          CParallelPlotterDirectUniform0<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
// Declaration of CParallelSpeedDerivativePlotterUniform
//---------------------------------------------------------------------------

using CParallelSpeedDerivativePlotterUniform =
          CParallelPlotterDirectUniform1<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Definition of CPlotterBase
//---------------------------------------------------------------------------

template<class TApproximation>
CPlotterBase<TApproximation>::CPlotterBase()
  : pSeries(nullptr) {
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CPlotterBase<TApproximation>::
                                setPlotterBase(TFastLineSeries* pNewSeries) {
  pSeries = pNewSeries;
  populateWithZeros();
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CPlotterBase<TApproximation>::populateWithZeros() {
  assert(pSeries != nullptr);
  pSeries->Clear();
  for (size_t index = 0; index < CGridDefault::kNumberOfSteps; ++index) {
    double XValue = CGridDefault::kMinimumValue +
                    static_cast<double>(index) * CGridDefault::kStep;
    pSeries->AddXY(XValue, 0.0);
  }
}
//---------------------------------------------------------------------------
// Definition of CSerialPlotFiller
//---------------------------------------------------------------------------

template<class TPlotterBase>
template<class TMethod>
void
  CSerialPlotFiller<TPlotterBase>::
    fillPlotWithMethod( const CApproximation& Approximation,
                        const TMethod& Method,
                        double Scale) {
  assert(CBase::pSeries != nullptr);
  for (size_t index = 0; index < CGridDefault::kNumberOfSteps; ++index) {
    CBase::pSeries->XValue[index] =
                        CGridDefault::kMinimumValue +
                        static_cast<double>(index) * CGridDefault::kStep;
    CBase::pSeries->YValue[index] = Scale *
                        (Approximation.*Method)(CBase::pSeries->XValue[index]);
  }
}
//---------------------------------------------------------------------------
// Definition of CParallelPlotFiller
//---------------------------------------------------------------------------

template<class TPlotterBase>
template<class TMethod>
void
  CParallelPlotFiller<TPlotterBase>::
    fillPlotWithMethod( const CApproximation& Approximation,
                        const TMethod& Method,
                        double Scale) {
  CFillingWithMethodLoopEvent<TMethod> LoopEvent( Scale,
                                                  Approximation,
                                                  Method,
                                                  CBase::pSeries);
  CParallelFor Computer;
  Computer( 0,
            CGridDefault::kNumberOfSteps,
            Approximation.getNumberOfSamples(),
            &LoopEvent,
            &ThreadPool);

}
//---------------------------------------------------------------------------
// Definition of CParallelPlotFiller::CFillingWithMethodLoopEvent
//---------------------------------------------------------------------------

template<class TPlotterBase>
template<class TMethod>
CParallelPlotFiller<TPlotterBase>::
  CFillingWithMethodLoopEvent<TMethod>::
    CFillingWithMethodLoopEvent(double newScale,
                                const CApproximation& Approximation,
                                const TMethod& newMethod,
                                TFastLineSeries* Series)
  : Scale(newScale),
    pApproximation(&Approximation),
    Method(newMethod),
    pSeries(Series) {
}
// ---------------------------------------------------------------------------

template<class TPlotterBase>
template<class TMethod>
void
CParallelPlotFiller<TPlotterBase>::
  CFillingWithMethodLoopEvent<TMethod>::
    execute(size_t index) {
  pSeries->XValue[index] =  CGridDefault::kMinimumValue +
                            static_cast<double>(index) * CGridDefault::kStep;
  pSeries->YValue[index] =
                    Scale * (pApproximation->*Method)(pSeries->XValue[index]);

}
// ---------------------------------------------------------------------------
// Definition of CParallelPlotFiller::CParallelFor
// ---------------------------------------------------------------------------

template<class TPlotterBase>
void
CParallelPlotFiller<TPlotterBase>::
                    CParallelFor::operator()( size_t begin,
                                              size_t end,
                                              size_t samples,
                                              ILoopWorker* pLoopWorker,
                                              CThreadPool* pPool) {
  size_t chunk = getChunk(begin, end, samples, pPool);
  ParallelFor::operator()(begin, end, chunk, pLoopWorker, pPool);
}
// ---------------------------------------------------------------------------

template<class TPlotterBase>
size_t
CParallelPlotFiller<TPlotterBase>::
                    CParallelFor::getChunk( size_t begin,
                                            size_t end,
                                            size_t samples,
                                            CThreadPool* pPool) const {
  size_t threadBoundary = (end - begin) / pPool->getThreadMaximum();
  if (samples == 0)
    ++samples;
  size_t empiricalBoundary = (kThreadCoefficient * (end - begin)) / samples;
  return std::max<size_t>(std::min<size_t>(threadBoundary, empiricalBoundary),
                          1);
}
//---------------------------------------------------------------------------
// Definition of CHistogramPlotter
//---------------------------------------------------------------------------

template<class TApproximation>
void
CHistogramPlotter<TApproximation>::
  draw(const CApproximation& Approximation, double Chunk) {
  assert(CBase::pSeries != nullptr);
  for (size_t index = 0; index < CGridDefault::kNumberOfSteps; ++index) {
    CBase::pSeries->XValue[index] =
                        CGridDefault::kMinimumValue +
                        static_cast<double>(index) * CGridDefault::kStep;
    CBase::pSeries->YValue[index] = Approximation.
                                      evaluateHistogram(CBase::pSeries->
                                                          XValue[index],
                                                        Chunk);
  }
}
//---------------------------------------------------------------------------
// Definition of CPlotterDirect0
//---------------------------------------------------------------------------

template<class TPlotFiller>
void
CPlotterDirect0<TPlotFiller>::
  draw(const CApproximation& Approximation) {
  CBase::fillPlotWithMethod(Approximation, &CApproximation::evaluate0);
}
//---------------------------------------------------------------------------
// Definition of CPlotterDirect1
//---------------------------------------------------------------------------

template<class TPlotFiller>
void
CPlotterDirect1<TPlotFiller>::
  draw(const CApproximation& Approximation) {
  CBase::fillPlotWithMethod(Approximation,
                            &CApproximation::evaluate1,
                            CApproximation::kDerivativeScaleCoefficient);
}
//---------------------------------------------------------------------------
// Definition of CPlotterDirectUniform0
//---------------------------------------------------------------------------

template<class TPlotFiller>
void
CPlotterDirectUniform0<TPlotFiller>::
  draw(const CApproximation& Approximation) {
  CBase::fillPlotWithMethod(Approximation, &CApproximation::evaluateUniform0);
}
//---------------------------------------------------------------------------
// Definition of CPlotterDirectUniform1
//---------------------------------------------------------------------------

template<class TPlotFiller>
void
CPlotterDirectUniform1<TPlotFiller>::
  draw(const CApproximation& Approximation) {
  CBase::fillPlotWithMethod(Approximation,
                            &CApproximation::evaluateUniform1,
                            CApproximation::kDerivativeScaleCoefficient);
}
//---------------------------------------------------------------------------
// Definition of CPlotterTemplate
//---------------------------------------------------------------------------

template <class TPlotFiller,
          unsigned int derivative>
void
CPlotterTemplate<TPlotFiller, derivative>::
  draw(const CApproximation& Approximation) {
  double Scale(1.0);
  if (derivative == 1)
    Scale = CApproximation::kDerivativeScaleCoefficient;
  assert(derivative == 0 || derivative == 1);
  CBase::fillPlotWithMethod(Approximation,
                            &CApproximation::template evaluate<derivative>,
                            Scale);
}
//---------------------------------------------------------------------------
// Definition of CPlotterTemplateUniform
//---------------------------------------------------------------------------

template <class TPlotFiller,
          unsigned int derivative>
void
CPlotterTemplateUniform<TPlotFiller, derivative>::
  draw(const CApproximation& Approximation) {
  double Scale(1.0);
  if (derivative == 1)
    Scale = CApproximation::kDerivativeScaleCoefficient;
  assert(derivative == 0 || derivative == 1);
  CBase::fillPlotWithMethod(Approximation,
                            &CApproximation::
                                    template evaluateUniform<derivative>,
                            Scale);
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
