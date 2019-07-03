//---------------------------------------------------------------------------

#ifndef UnitAnalysisRoverH
#define UnitAnalysisRoverH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitAnalysisMode.h"
#include "UnitTextRover.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Declaration of CAnalysisRover
// ---------------------------------------------------------------------------

class CAnalysisRover : protected CTextRover {
public:
  CAnalysisRover() = default;
  CAnalysisRover( const CAnalysisData& AnalysisData,
                  const CTextMode& textMode);
  CAnalysisRover(const CSession& Session);
  CAnalysisRover(CAnalysisRover&&) = default;
  CAnalysisRover& operator=(CAnalysisRover&&) = default;

  void initialize(const CAnalysisData& AnalysisData,
                  const CTextMode& textMode);
  void initialize(const CSession& Session);

  void setNext();
  using CTextRover::top;
  using CTextRover::empty;
  microseconds getResponseTime(EAnalysisType AnalysisType) const;
protected:
  inline microseconds getPhysicalResponseTime() const;
  // For the first symbol ResponseTime = PhysicalResponseTime
  inline microseconds getResponseTime() const;

  microseconds PreviousKeyTime;
};

//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
