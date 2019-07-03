//---------------------------------------------------------------------------

#ifndef UnitAnalysisDataH
#define UnitAnalysisDataH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitCapitalWithDependenciesFillers.h"
#include <queue>
#include <functional>
//#include "../Debug/UnitDisabler.h"
//---------------------------------------------------------------------------

#if !defined(__ANALYSIS_DATA__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CAnalysisData
// ---------------------------------------------------------------------------

class CAnalysisData {
public:
  CAnalysisData();
  CAnalysisData(const CSession& source);
  void clear();

  size_t getRawLength() const;
  size_t getTextLength(const CTextMode& TextMode) const;
  size_t getAmountOfShifts(const CTextMode& TextMode) const;
  size_t getAmountOfCapslocks(const CTextMode& TextMode) const;

  bool isDefined() const;
  bool isSessionEmpty() const;
  bool isTextEmpty(const CTextMode& TextMode) const;

  microseconds getRawDurationTime() const;
  microseconds getTextDurationTime(const CTextMode& TextMode) const;
  microseconds getFirstPressingTime(const CTextMode& TextMode) const;
  microseconds getLastPressingTime(const CTextMode& TextMode) const;

  symbolsPerMinute getRawSpeed() const;
  symbolsPerMinute getTextSpeed(const CTextMode& TextMode) const;

  // TO DO
  // move these two functions to SessionToAnalysisDataConverter
  void fillShiftsWithDependencies();
  void fillCapslocksWithDependencies();

  // Контейнеры для shift-ов и capslock-ов с количеством клавиш,
  // на которые они повлияли
  CCapitalWithDependenciesContainer ShiftsWithDependencies;
  CCapitalWithDependenciesContainer CapslocksWithDependencies;

  CTextDataTree TextTree;
  const CSession* pSession;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
