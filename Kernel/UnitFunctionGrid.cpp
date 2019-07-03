//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitFunctionGrid.h"
//---------------------------------------------------------------------------
//#include <vcl.h>
namespace NSApplication {
namespace NSKernel {
/*
class CFunctionGridTester {
public:
  CFunctionGridTester()
    : Text(L"FunctionGridTester:\n") {
    CFunctionGrid Grid;
    CFunctionGrid GridT;
    CSpeedApproximation Approximation;
    std::vector<double> Data(1);
    Data[0] = 400.0;
    Approximation.setApproximation(Data);
    Grid.setApproximationGridParallel1(Approximation);
    GridT.setApproximationGridParallel<1>(Approximation);
    double difference = 0.0;
    for (size_t index = 0; index < Grid.size(); ++index) {
      difference = std::max(difference, std::fabs(Grid[index] - GridT[index]));
    }
    Text += L"Grid size = ";
    Text += Grid.size();
    Text += L"\nGridT size = ";
    Text += GridT.size();
    Text += L"\nDifference = ";
    Text += difference;

    ShowMessage(Text.c_str());
  }
private:
  UnicodeString Text;
};
CFunctionGridTester FunctionGridTester;*/
// ---------------------------------------------------------------------------
// Definition of CFunctionGridBase
// ---------------------------------------------------------------------------

CFunctionGridBase::CFunctionGridBase(double start, double step)
    : Start(start), Step(step) {
  assert(Step > 0);
}
// ---------------------------------------------------------------------------

double CFunctionGridBase::getPoint(const const_iterator& position) const {
  return Start + static_cast<double>(position - begin()) * Step;
}
// ---------------------------------------------------------------------------

double CFunctionGridBase::getPoint(size_t position) const {
  return getStart() + getStep() * static_cast<double>(position);
}
// ---------------------------------------------------------------------------

double CFunctionGridBase::getStart() const {
  return Start;
}
// ---------------------------------------------------------------------------

double CFunctionGridBase::getStep() const {
  return Step;
}
// ---------------------------------------------------------------------------

double CFunctionGridBase::getArea() const{
  if (size() < 2)
    return 0.0;
  double Area = 0.0;
  const_iterator itCurrent = begin();
  const_iterator itNext = itCurrent;
  ++itNext;
  while(itNext != end()){
    Area += (*itCurrent + *itNext) * Step / 2.0;
    ++itCurrent;
    ++itNext;
  }
  return Area;
}
// ---------------------------------------------------------------------------

// есть push_back
// Это нельзя параллелить без concurrent vector
// так как у меня используется push_back
void CFunctionGridBase::fillRoughMaxMinPairContainer(
                        CRoughMaxMinPairContainer *target) const {
  target->clear();
  if (size() < 2)
    return;
  // исключительный случай, если максимум приходится на первый элемент
  const_iterator itCurrent = begin();
  const_iterator itNext = itCurrent;
  ++itNext;
  if (isFirstExtremum<EExtremalPointType::Maximum>(*itCurrent, *itNext)) {
    const_iterator itMax = itCurrent;
    const_iterator itMin;
    findNextMin(itCurrent, &itMin);
    if (itMin == end())
      return;
    itCurrent = itMin;
    // Здесь getPoint(itMax) должен быть = 0
    // Потому я не вычитаю из него Step, чтобы не получить
    // отрицательные значения
    target->
      push_back(CRoughMaxMinPair(
        CInterval(getPoint(itMax), getPoint(itMax) + Step),
        CInterval(getPoint(itMin) - Step, getPoint(itMin) + Step)));
  }
  // общий случай, если максимум находится за первым элементом
  while (itCurrent != end()) {
    const_iterator itMax;
    findNextMax(itCurrent, &itMax);
    if (itMax == end())
      return;
    itCurrent = itMax;
    const_iterator itMin;
    findNextMin(itCurrent, &itMin);
    if (itMin == end())
      return;
    itCurrent = itMin;
    target->
      push_back(CRoughMaxMinPair(
        CInterval(getPoint(itMax) - Step, getPoint(itMax) + Step),
        CInterval(getPoint(itMin) - Step, getPoint(itMin) + Step)));
  }
}
// ---------------------------------------------------------------------------

CInterval CFunctionGridBase::findRoughRoot() const{
  if (empty())
    return CInterval(0.0, 0.0);
  const_iterator currentRoot = begin();
  for (auto index = begin(); index != end(); ++index)
    if (std::fabs(*currentRoot) > std::fabs(*index))
      currentRoot = index;
  return CInterval( getPoint(currentRoot) - Step,
                    getPoint(currentRoot) + Step);
}
// ---------------------------------------------------------------------------

void CFunctionGridBase::findNextMax( const const_iterator& itCurrent,
                                        const_iterator* pItMax) const {
  findNextExtremum<EExtremalPointType::Maximum>(itCurrent, pItMax);
}
// ---------------------------------------------------------------------------

void CFunctionGridBase::findNextMin( const const_iterator& itCurrent,
                                        const_iterator* pItMin) const {
  findNextExtremum<EExtremalPointType::Minimum>(itCurrent, pItMin);
}
// ---------------------------------------------------------------------------

template<EExtremalPointType PointType>
void CFunctionGridBase::findNextExtremum(
                              const const_iterator& itCurrent,
                              const_iterator* pItExtremum) const {
  const_iterator itPrevious = itCurrent;
  const_iterator& itExtremum = *pItExtremum = itPrevious;
  ++itExtremum;
  if (itExtremum == end())
    return;
  const_iterator itNext = itExtremum;
  ++itNext;
  while (itNext != end()) {
    if (isExtremum<PointType>(itExtremum, itPrevious, itNext))
      return;
    ++itPrevious;
    ++itExtremum;
    ++itNext;
  }
  if (!isFirstExtremum<PointType>(*itExtremum, *itPrevious))
    itExtremum = end();
}
// ---------------------------------------------------------------------------

template<EExtremalPointType PointType>
bool CFunctionGridBase::isExtremum( const const_iterator& extremum,
                                    const const_iterator& previous,
                                    const const_iterator& next) const {
  return  isFirstExtremum<PointType>(*extremum, *previous) &&
          isFirstExtremum<PointType>(*extremum, *next);
}
// ---------------------------------------------------------------------------
// Definition of CFunctionGridBase::CParallelFor
// ---------------------------------------------------------------------------

void CFunctionGridBase::CParallelFor::operator()(
                                        size_t begin,
                                        size_t end,
                                        size_t samples,
                                        ILoopWorker* pLoopWorker,
                                        CThreadPool* pPool) {
  size_t chunk = getChunk(begin, end, samples, pPool);
  ParallelFor::operator()(begin, end, chunk, pLoopWorker, pPool);
}
// ---------------------------------------------------------------------------

size_t CFunctionGridBase::CParallelFor::getChunk(
                                          size_t begin,
                                          size_t end,
                                          size_t samples,
                                          CThreadPool* pPool) const {
  size_t threadBoundary = (end - begin) / pPool->getThreadMaximum();
  if (samples == 0)
    ++samples;
  size_t empiricalBoundary = (threadCoefficient * (end - begin)) / samples;
  return std::max<size_t>(std::min<size_t>(threadBoundary, empiricalBoundary),
                          1);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
