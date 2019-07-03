//---------------------------------------------------------------------------

#ifndef UnitKlavogrammaPlotterH
#define UnitKlavogrammaPlotterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeShape.hpp>
#include "UnitParallelFor.h"
#include "../Kernel/UnitKlavogramma.h"
//---------------------------------------------------------------------------
namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Declaration of CKlavogrammaPlotter
//---------------------------------------------------------------------------

class CKlavogrammaPlotter {
  using CKlavogramma = NSKernel::CKlavogramma;
  using CFingerKlavogramma = NSKernel::CFingerKlavogramma;
  using CKlavogrammaKey = NSKernel::CKlavogrammaKey;
  using CFinger = NSKeyboard::CFinger;
  using CAreasContainer = std::map<size_t, TAreaSeries*>;
public:
  CKlavogrammaPlotter();
  void setChart(TChart* Chart);
  void drawKlavogramma(const CKlavogramma& Klavogramma);
  void drawKlavogrammaParallel(const CKlavogramma& Klavogramma);
private:
  void createAllAreaSeries(const CKlavogramma& Klavogramma);
  void drawFingerAreasParallel(const CKlavogramma& Klavogramma);
  void drawFingerKeys(const CKlavogramma& Klavogramma);
  void drawFingerKeys(size_t FingerLinePosition,
                      const CFingerKlavogramma& FingerKlavogramma);
public:
  void ClearKeys();
private:
  void drawFingerKlavogramma( size_t FingerLinePosition,
                              const CFingerKlavogramma& FingerKlavogramma);
  void drawKlavogrammaKey(size_t FingerLinePosition,
                          const CKlavogrammaKey& Key);
  void drawKeyAreas(size_t FingerLinePosition,
                    const CKlavogrammaKey& Key);
  void drawKey( size_t FingerLinePosition,
                const CKlavogrammaKey& Key);
  void drawKeyBoundary( size_t FingerLinePosition,
                        const CKlavogrammaKey& Key,
                        TChartShape* KeyBorder);
  void drawKeyName( const CKlavogrammaKey& Key,
                    TChartShape* KeyBorder);
  void drawArea(size_t FingerLinePosition,
                milliseconds beginTime,
                milliseconds endTime,
                size_t multiplicity);
  TChartShape* createRectangleSeries();
  void createAreaSeries(size_t FingerLinePosition);
  TColor getColor(size_t multiplicity) const;
  void setAxis(const CKlavogramma& Klavogramma);
  void setFingerNamesOnAxis(const CKlavogramma& Klavogramma);
  void getFingerName( const CFinger& Finger,
                      std::wstring* pText);

  static constexpr COLORREF kBaseKeyAreaColor = RGB(255, 229, 204);
  static constexpr COLORREF kKeyBoundaryColor = RGB(0, 0, 0);
  static constexpr size_t kKeyBorderWidth = 2;
  static constexpr size_t kKlavogrammaWindowWidth = 2000;
  //---------------------------------------------------------------------------
  // Declaration of CAreaLoopFiller
  //---------------------------------------------------------------------------

  friend class CAreaLoopFiller;
  class CAreaLoopFiller : public ILoopWorker {
  public:
    CAreaLoopFiller(const CKlavogramma& Klavogramma,
                    CKlavogrammaPlotter* KlavogrammaPlotter);
    void execute(size_t index) override;
  private:
    const CFingerKlavogramma& getFingerKlavogramma(
                                            size_t FingerLinePosition) const;
    const CKlavogramma* pKlavogramma;
    CKlavogrammaPlotter* pKlavogrammaPlotter;
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
    size_t getChunk(size_t begin,
                    size_t end,
                    CThreadPool* pPool) const;
    static constexpr size_t kDefaultChunkSize = 1;
  };
  //---------------------------------------------------------------------------

  TChart* pChart;
  CAreasContainer FingerAreas;
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
