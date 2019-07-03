//---------------------------------------------------------------------------

#ifndef UnitRootFinderH
#define UnitRootFinderH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <boost/math/tools/roots.hpp>
#include "UnitFunctionGrid.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

//class CRootFinderTester;
//---------------------------------------------------------------------------
// Declaration of CUpToFirstDerivativeFunctor1
//---------------------------------------------------------------------------

template<class TApproximation>
class CUpToFirstDerivativeFunctor1 {
public:
  CUpToFirstDerivativeFunctor1(const TApproximation* pNewApproximation);
  std::pair<double, double> operator()(double argument) const;
private:
  const TApproximation* pApproximation;
};
//---------------------------------------------------------------------------
// Declaration of CUpToFirstDerivativeFunctor2
//---------------------------------------------------------------------------

template<class TApproximation>
class CUpToFirstDerivativeFunctor2 {
public:
  CUpToFirstDerivativeFunctor2(const TApproximation* pNewApproximation);
  std::pair<double, double> operator()(double argument) const;
private:
  const TApproximation* pApproximation;
};
//---------------------------------------------------------------------------
// Declaration of CUpToSecondDerivativeFunctor1
//---------------------------------------------------------------------------

// TO DO
//---------------------------------------------------------------------------
// Declaration of CUpToSecondDerivativeFunctor2
//---------------------------------------------------------------------------

// TO DO
//---------------------------------------------------------------------------
// Declaration of CUpToFirstDerivativeFunctor
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
class CUpToFirstDerivativeFunctor {
public:
  CUpToFirstDerivativeFunctor(const TApproximation* pNewApproximation);
  std::pair<double, double> operator()(double argument) const;
private:
  const TApproximation* pApproximation;
};
//---------------------------------------------------------------------------
// Declaration of CUpToSecondDerivativeFunctor
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
class CUpToSecondDerivativeFunctor{
  public:
  CUpToSecondDerivativeFunctor(
            const TApproximation* pNewApproximation);
  boost::math::tuple<double, double, double>
                          operator()(double argument) const;
  private:
  const TApproximation* pApproximation;
};
//---------------------------------------------------------------------------
// Declaration of CRootFinderBase
//---------------------------------------------------------------------------

class CRootFinderBase {
protected:
  static constexpr int kNumberDigitsForExtremumPrecision = 16;
};
//---------------------------------------------------------------------------
// Declaration of CNewtonRootFinderDirectEvaluation
//---------------------------------------------------------------------------

class CNewtonRootFinderDirectEvaluation : protected CRootFinderBase {
  //friend class CRootFinderTester;
protected:
  template<class TApproximation>
  inline static double findRootOnSmallInterval1(
                          const TApproximation& Approximation,
                          const CInterval& Interval);
  template<class TApproximation>
  inline static double findRootOnSmallInterval2(
                          const TApproximation& Approximation,
                          const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CNewtonRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

class CNewtonRootFinderTemplateEvaluation : protected CRootFinderBase {
  //friend class CRootFinderTester;
protected:
  template <unsigned int derivative,
            class TApproximation>
  inline static double findRootOnSmallInterval(
                          const TApproximation& Approximation,
                          const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CHalleyRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

class CHalleyRootFinderTemplateEvaluation : protected CRootFinderBase {
  //friend class CRootFinderTester;
protected:
  template <unsigned int derivative,
            class TApproximation>
  inline static double findRootOnSmallInterval(
                          const TApproximation& Approximation,
                          const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CSchroederRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

class CSchroederRootFinderTemplateEvaluation : protected CRootFinderBase {
  //friend class CRootFinderTester;
protected:
  template <unsigned int derivative,
            class TApproximation>
  inline static double findRootOnSmallInterval(
                          const TApproximation& Approximation,
                          const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CRootFinderDirectEvaluation
//---------------------------------------------------------------------------

template<class TConcreteRootFinder>
class CRootFinderDirectEvaluation : protected TConcreteRootFinder {
  using CBase = TConcreteRootFinder;
  //friend class CRootFinderTester;
public:
  template<class TApproximation>
  static double findRoot1(const TApproximation& Approximation,
                          const CInterval& Interval);
  template<class TApproximation>
  static double findRoot2(const TApproximation& Approximation,
                          const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

template<class TConcreteRootFinder>
class CRootFinderTemplateEvaluation : protected TConcreteRootFinder {
  using CBase = TConcreteRootFinder;
  //friend class CRootFinderTester;
public:
  template <unsigned int derivative,
            class TApproximation>
  static double findRoot( const TApproximation& Approximation,
                          const CInterval& Interval);
};
//---------------------------------------------------------------------------
// Declaration of CRootFinder
//---------------------------------------------------------------------------

using CRootFinder =
          CRootFinderDirectEvaluation<CNewtonRootFinderDirectEvaluation>;
//---------------------------------------------------------------------------
// Declaration of CNewtonRootFinderT
//---------------------------------------------------------------------------

using CNewtonRootFinderT =
        CRootFinderTemplateEvaluation<CNewtonRootFinderTemplateEvaluation>;
//---------------------------------------------------------------------------
// Declaration of CHalleyRootFinderT
//---------------------------------------------------------------------------

using CHalleyRootFinderT =
        CRootFinderTemplateEvaluation<CHalleyRootFinderTemplateEvaluation>;
//---------------------------------------------------------------------------
// Declaration of CSchroederRootFinderT
//---------------------------------------------------------------------------

using CSchroederRootFinderT =
        CRootFinderTemplateEvaluation<CSchroederRootFinderTemplateEvaluation>;
//---------------------------------------------------------------------------
// Declaration of CRootFinderT
//---------------------------------------------------------------------------

using CRootFinderT =  CNewtonRootFinderT;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Definitions of CUpToFirstDerivativeFunctor1
// ---------------------------------------------------------------------------

template<class TApproximation>
CUpToFirstDerivativeFunctor1<TApproximation>::
        CUpToFirstDerivativeFunctor1(const TApproximation* pNewApproximation)
  : pApproximation(pNewApproximation){
}
// ---------------------------------------------------------------------------

template<class TApproximation>
std::pair<double, double>
          CUpToFirstDerivativeFunctor1<TApproximation>::
                                        operator()(double argument) const {
  return
    std::make_pair(
        pApproximation->evaluate1(argument),
        pApproximation->evaluate2(argument));
}
// ---------------------------------------------------------------------------
// Definitions of CUpToFirstDerivativeFunctor2
// ---------------------------------------------------------------------------

template<class TApproximation>
CUpToFirstDerivativeFunctor2<TApproximation>::
      CUpToFirstDerivativeFunctor2(const TApproximation* pNewApproximation)
  : pApproximation(pNewApproximation){
}
// ---------------------------------------------------------------------------

template<class TApproximation>
std::pair<double, double>
          CUpToFirstDerivativeFunctor2<TApproximation>::
                                        operator()(double argument) const{
  return
    std::make_pair(
        pApproximation->evaluate2(argument),
        pApproximation->evaluate3(argument));
}
//---------------------------------------------------------------------------
// Definition of CUpToFirstDerivativeFunctor
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
CUpToFirstDerivativeFunctor<derivative, TApproximation>::
  CUpToFirstDerivativeFunctor(const TApproximation* pNewApproximation)
  : pApproximation(pNewApproximation) {
}
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
std::pair<double, double>
  CUpToFirstDerivativeFunctor<derivative, TApproximation>::
    operator()(double argument) const {
  return
    std::make_pair(
        pApproximation->template evaluate<derivative>(argument),
        pApproximation->template evaluate<derivative + 1>(argument));
}
//---------------------------------------------------------------------------
// Definition of CUpToSecondDerivativeFunctor
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
CUpToSecondDerivativeFunctor<derivative, TApproximation>::
  CUpToSecondDerivativeFunctor(
    const TApproximation* pNewApproximation)
  : pApproximation(pNewApproximation){
}
// ---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
boost::math::tuple<double, double, double>
CUpToSecondDerivativeFunctor<derivative, TApproximation>::
                              operator()(double argument) const {
  return boost::math::make_tuple(
            pApproximation->template evaluate<derivative>(argument),
            pApproximation->template evaluate<derivative + 1>(argument),
            pApproximation->template evaluate<derivative + 2>(argument));
}
//---------------------------------------------------------------------------
// Definition of CNewtonRootFinderDirectEvaluation
//---------------------------------------------------------------------------

template<class TApproximation>
double
CNewtonRootFinderDirectEvaluation::
                        findRootOnSmallInterval1(
                          const TApproximation& Approximation,
                          const CInterval& Interval) {
  return
    boost::math::tools::
      newton_raphson_iterate( CUpToFirstDerivativeFunctor1<
                                        TApproximation>(&Approximation),
                              Interval.getCenter(),
                              Interval.first,
                              Interval.second,
                              kNumberDigitsForExtremumPrecision);
}
//---------------------------------------------------------------------------

template<class TApproximation>
double
CNewtonRootFinderDirectEvaluation::
                        findRootOnSmallInterval2(
                          const TApproximation& Approximation,
                          const CInterval& Interval) {
  return
    boost::math::tools::
      newton_raphson_iterate( CUpToFirstDerivativeFunctor2<
                                        TApproximation>(&Approximation),
                              Interval.getCenter(),
                              Interval.first,
                              Interval.second,
                              kNumberDigitsForExtremumPrecision);
}
//---------------------------------------------------------------------------
// Definition of CNewtonRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
double
CNewtonRootFinderTemplateEvaluation::
                                findRootOnSmallInterval(
                                  const TApproximation& Approximation,
                                  const CInterval& Interval) {
  return
    boost::math::tools::
      newton_raphson_iterate(
                CUpToFirstDerivativeFunctor<
                          derivative, TApproximation>(&Approximation),
                Interval.getCenter(),
                Interval.first,
                Interval.second,
                kNumberDigitsForExtremumPrecision);
}
//---------------------------------------------------------------------------
// Definition of CHalleyRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
double
CHalleyRootFinderTemplateEvaluation::
                            findRootOnSmallInterval(
                              const TApproximation& Approximation,
                              const CInterval& Interval) {
  return  boost::math::tools::
            halley_iterate(
                CUpToSecondDerivativeFunctor<
                            derivative, TApproximation>(&Approximation),
                Interval.getCenter(),
                Interval.first,
                Interval.second,
                kNumberDigitsForExtremumPrecision);
}
//---------------------------------------------------------------------------
// Definition of CSchroederRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

template <unsigned int derivative,
          class TApproximation>
double
  CSchroederRootFinderTemplateEvaluation::
                              findRootOnSmallInterval(
                                const TApproximation& Approximation,
                                const CInterval& Interval) {
  return  boost::math::tools::
            schroeder_iterate(
                CUpToSecondDerivativeFunctor<
                            derivative, TApproximation>(&Approximation),
                Interval.getCenter(),
                Interval.first,
                Interval.second,
                kNumberDigitsForExtremumPrecision);
}
//---------------------------------------------------------------------------
// Definition of CRootFinderDirectEvaluation
//---------------------------------------------------------------------------

template <class TConcreteRootFinder>
template<class TApproximation>
double
CRootFinderDirectEvaluation<TConcreteRootFinder>::
                              findRoot1(
                                  const TApproximation& Approximation,
                                  const CInterval& Interval) {

  CFunctionGrid Grid;
  Grid.setApproximationGrid1(Approximation, Interval);
  CInterval SmallInterval = Grid.findRoughRoot();
  return CBase::findRootOnSmallInterval1(Approximation, SmallInterval);
}
// ---------------------------------------------------------------------------

template <class TConcreteRootFinder>
template<class TApproximation>
double
CRootFinderDirectEvaluation<TConcreteRootFinder>::
                              findRoot2(
                                  const TApproximation& Approximation,
                                  const CInterval& Interval) {
  CFunctionGrid Grid;
  Grid.setApproximationGrid2(Approximation, Interval);
  CInterval SmallInterval = Grid.findRoughRoot();
  return CBase::findRootOnSmallInterval2(Approximation, SmallInterval);
}
//---------------------------------------------------------------------------
// Definition of CRootFinderTemplateEvaluation
//---------------------------------------------------------------------------

template<class TConcreteRootFinder>
template <unsigned int derivative,
          class TApproximation>
double CRootFinderTemplateEvaluation<TConcreteRootFinder>::
                                findRoot(
                                  const TApproximation& Approximation,
                                  const CInterval& Interval) {
  CFunctionGrid Grid;
  Grid.setApproximationGrid<derivative>(Approximation, Interval);
  CInterval SmallInterval = Grid.findRoughRoot();
  return CBase::template
              findRootOnSmallInterval<derivative>(Approximation,
                                                  SmallInterval);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
