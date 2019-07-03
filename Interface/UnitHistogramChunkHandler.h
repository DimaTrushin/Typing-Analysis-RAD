//---------------------------------------------------------------------------

#ifndef UnitHistogramChunkHandlerH
#define UnitHistogramChunkHandlerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <Vcl.ComCtrls.hpp>
#include "../Kernel/UnitApproximation.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Declaration of CHistogramChunkHandler
//---------------------------------------------------------------------------

template<class TApproximation>
class CHistogramChunkHandler {
public:
  using CApproximation = TApproximation;
  static constexpr double kDefaultHistogramChunk =
                                      CApproximation::kHistogramChunk;
  CHistogramChunkHandler();
  void setHandler(TTrackBar* pNewTrackBar);
  void setChunk(double* pChunk) const;
  void setToDefaultPosition();
private:
  TTrackBar* pTrackBar;
  int DefaultPosition;
  double Scale;
};
//---------------------------------------------------------------------------
// Declaration of CSpeedHistogramChunkHandler
//---------------------------------------------------------------------------

using CSpeedHistogramChunkHandler =
        CHistogramChunkHandler<NSKernel::CSpeedApproximation>;
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CHistogramChunkHandler
//---------------------------------------------------------------------------

template<class TApproximation>
CHistogramChunkHandler<TApproximation>::CHistogramChunkHandler()
  : pTrackBar(nullptr),
    DefaultPosition(0),
    Scale(1.0) {
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CHistogramChunkHandler<TApproximation>::
                              setHandler(TTrackBar* pNewTrackBar) {
  assert(pNewTrackBar != nullptr);
  pTrackBar = pNewTrackBar;
  DefaultPosition = pTrackBar->Position;
  assert(DefaultPosition != 0);
  static_assert(kDefaultHistogramChunk != 0,
                "kDefaultHistogramChunk must not be zero!");
  Scale = static_cast<double>(DefaultPosition) / kDefaultHistogramChunk;
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CHistogramChunkHandler<TApproximation>::setChunk(double* pChunk) const {
  *pChunk = static_cast<double>(pTrackBar->Position) / Scale;
}
//---------------------------------------------------------------------------

template<class TApproximation>
void CHistogramChunkHandler<TApproximation>::setToDefaultPosition() {
  pTrackBar->Position = DefaultPosition;
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
