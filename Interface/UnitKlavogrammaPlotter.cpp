//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKlavogrammaPlotter.h"
#include "UnitColorManipulator.h"
//---------------------------------------------------------------------------
namespace NSApplication {
//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CThreadPool ThreadPool;
//---------------------------------------------------------------------------

namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CKlavogrammaPlotter
//---------------------------------------------------------------------------

CKlavogrammaPlotter::CKlavogrammaPlotter()
  : pChart(nullptr) {
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::setChart(TChart* Chart) {
  assert(Chart != nullptr);
  pChart = Chart;
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawKlavogramma(const CKlavogramma& Klavogramma) {
  ClearKeys();
  setAxis(Klavogramma);
  size_t FingerLinePosition = 0;
  for (const auto& FingerData : Klavogramma) {
    createAreaSeries(FingerLinePosition);
    drawFingerKlavogramma(FingerLinePosition, FingerData.second);
    ++FingerLinePosition;
  }
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawKlavogrammaParallel(
                                          const CKlavogramma& Klavogramma) {
  ClearKeys();
  setAxis(Klavogramma);
  createAllAreaSeries(Klavogramma);
  drawFingerAreasParallel(Klavogramma);
  drawFingerKeys(Klavogramma);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::createAllAreaSeries(
                                            const CKlavogramma& Klavogramma) {
  for ( size_t FingerLinePosition = 0;
        FingerLinePosition < Klavogramma.getNumberOfFingers();
        ++FingerLinePosition)
    createAreaSeries(FingerLinePosition);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawFingerAreasParallel(
                                            const CKlavogramma& Klavogramma) {
  CAreaLoopFiller AreaLoopFiller(Klavogramma, this);
  CParallelFor Computer;
  Computer(0, Klavogramma.getNumberOfFingers(), &AreaLoopFiller, &ThreadPool);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawFingerKeys(const CKlavogramma& Klavogramma) {
  size_t FingerLinePosition = 0;
  for (const auto& FingerData : Klavogramma) {
    drawFingerKeys(FingerLinePosition, FingerData.second);
    ++FingerLinePosition;
  }
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawFingerKeys(
                              size_t FingerLinePosition,
                              const CFingerKlavogramma& FingerKlavogramma) {
  for (const auto& Key : FingerKlavogramma)
    drawKey(FingerLinePosition, Key);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::ClearKeys() {
  assert(pChart != nullptr);
  FingerAreas.clear();
  while (pChart->SeriesList->Count > 0)
    pChart->SeriesList->Last()->Free();
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawFingerKlavogramma(
                        size_t FingerLinePosition,
                        const CFingerKlavogramma& FingerKlavogramma) {
  for (const auto& Key : FingerKlavogramma)
    drawKlavogrammaKey(FingerLinePosition, Key);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawKlavogrammaKey(size_t FingerLinePosition,
                                            const CKlavogrammaKey& Key) {
  drawKeyAreas(FingerLinePosition, Key);
  drawKey(FingerLinePosition, Key);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawKeyAreas(size_t FingerLinePosition,
                                      const CKlavogrammaKey& Key) {
  milliseconds beginTime = Key.PressingTime;
  milliseconds endTime;
  for (const auto& Zone : Key.MultiplicitySegments) {
    endTime = Zone.SegmentEndingTime;
    drawArea( FingerLinePosition,
              beginTime,
              endTime,
              Zone.Multiplicity);
    beginTime = endTime;
  }
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawKey( size_t FingerLinePosition,
                                  const CKlavogrammaKey& Key) {
  auto KeyBorder = createRectangleSeries();
  drawKeyBoundary(FingerLinePosition, Key, KeyBorder);
  drawKeyName(Key, KeyBorder);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawKeyBoundary( size_t FingerLinePosition,
                                          const CKlavogrammaKey& Key,
                                          TChartShape* KeyBorder) {
  assert(KeyBorder != nullptr);
  KeyBorder->X0 = Key.getPressingTime();
  KeyBorder->X1 = Key.getReleasingTime();
  KeyBorder->Y0 = static_cast<double>(FingerLinePosition);
  KeyBorder->Y1 = static_cast<double>(FingerLinePosition) + 1.0;
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawKeyName( const CKlavogrammaKey& Key,
                                      TChartShape* KeyBorder) {
  assert(KeyBorder != nullptr);
  KeyBorder->Text->Add(Key.Symbol);
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::drawArea(size_t FingerLinePosition,
                                  milliseconds beginTime,
                                  milliseconds endTime,
                                  size_t multiplicity) {
  double KeyTop = static_cast<double>(FingerLinePosition) + 1.0;
  FingerAreas[FingerLinePosition]->AddXY(beginTime, KeyTop);
  FingerAreas[FingerLinePosition]->AddXY( endTime,
                                          KeyTop,
                                          L"",
                                          getColor(multiplicity));
  FingerAreas[FingerLinePosition]->AddNullXY(endTime, KeyTop);
}
//---------------------------------------------------------------------------

TChartShape* CKlavogrammaPlotter::createRectangleSeries() {
  TChartShape* NewSeries;
  NewSeries = new TChartShape(pChart);
  NewSeries->ParentChart = pChart;
  NewSeries->Selected->Hover->Visible = false;
  NewSeries->Legend->Visible = false;
  NewSeries->Transparent = true;
  NewSeries->Pen->Width = kKeyBorderWidth;
  NewSeries->Style = chasRectangle;
  NewSeries->Font->Name = "Tahoma";
  return NewSeries;
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::createAreaSeries(size_t FingerLinePosition) {
  TAreaSeries* NewSeries;
  NewSeries = new TAreaSeries(pChart);
  NewSeries->ParentChart = pChart;
  NewSeries->UseYOrigin = true;
  NewSeries->YOrigin = static_cast<double>(FingerLinePosition);
  NewSeries->AreaLinesPen->Visible = false;
  NewSeries->Selected->Hover->Visible = false;
  NewSeries->ColorEachLine = true;
  NewSeries->Legend->Visible = false;
  FingerAreas[FingerLinePosition] = NewSeries;
}
//---------------------------------------------------------------------------

TColor CKlavogrammaPlotter::getColor(size_t multiplicity) const {
  return TColor(NSKernel::
                  CColorManipulator::makeColorDarker( kBaseKeyAreaColor,
                                                      multiplicity - 1));
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::setAxis(const CKlavogramma& Klavogramma) {
  assert(pChart != nullptr);
  pChart->LeftAxis->Minimum = 0;
  pChart->LeftAxis->Maximum = Klavogramma.getNumberOfFingers();
  setFingerNamesOnAxis(Klavogramma);
  pChart->BottomAxis->Minimum = 0;
  pChart->BottomAxis->Maximum = kKlavogrammaWindowWidth;
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::setFingerNamesOnAxis(
                                            const CKlavogramma& Klavogramma) {
  assert(pChart != nullptr);
  pChart->LeftAxis->Items->Clear();
  size_t FingerLinePosition = 0;
  for (const auto& FingerData : Klavogramma) {
    double MarkPosition = static_cast<double>(FingerLinePosition) + 0.5;
    std::wstring FingerName;
    getFingerName(FingerData.first, &FingerName);
    pChart->LeftAxis->Items->Add(MarkPosition, FingerName.c_str());
    ++FingerLinePosition;
  }
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::getFingerName(const CFinger& Finger,
                                        std::wstring* pText) {
  Finger.getFingerName(pText);
}
//---------------------------------------------------------------------------
// Definition of CAreaLoopFiller
//---------------------------------------------------------------------------

CKlavogrammaPlotter::
  CAreaLoopFiller::CAreaLoopFiller( const CKlavogramma& Klavogramma,
                                    CKlavogrammaPlotter* KlavogrammaPlotter)
  : pKlavogramma(&Klavogramma),
    pKlavogrammaPlotter(KlavogrammaPlotter) {
}
//---------------------------------------------------------------------------

void CKlavogrammaPlotter::CAreaLoopFiller::execute(size_t index) {
  size_t FingerLinePosition = index;
  auto& FingerKlavogramma = getFingerKlavogramma(FingerLinePosition);
  for (const auto& Key : FingerKlavogramma)
    pKlavogrammaPlotter->drawKeyAreas(FingerLinePosition, Key);
}
//---------------------------------------------------------------------------

const NSKernel::CFingerKlavogramma&
  CKlavogrammaPlotter::CAreaLoopFiller::getFingerKlavogramma(
                                            size_t FingerLinePosition) const {
  auto itFingerData = pKlavogramma->begin();
  while (FingerLinePosition > 0) {
    ++itFingerData;
    --FingerLinePosition;
  }
  return itFingerData->second;
}
// ---------------------------------------------------------------------------
// Definition of CParallelFor
// ---------------------------------------------------------------------------

void CKlavogrammaPlotter::CParallelFor::operator()( size_t begin,
                                                    size_t end,
                                                    ILoopWorker* pLoopWorker,
                                                    CThreadPool* pPool) {
  size_t chunk = getChunk(begin, end, pPool);
  ParallelFor::operator()(begin, end, chunk, pLoopWorker, pPool);
}
// ---------------------------------------------------------------------------

size_t CKlavogrammaPlotter::CParallelFor::getChunk( size_t begin,
                                                    size_t end,
                                                    CThreadPool* pPool) const {
  return kDefaultChunkSize;
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
