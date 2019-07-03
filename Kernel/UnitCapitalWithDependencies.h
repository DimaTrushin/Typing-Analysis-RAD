//---------------------------------------------------------------------------

#ifndef UnitCapitalWithDependenciesH
#define UnitCapitalWithDependenciesH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTextDataTree.h"
#include "UnitKeyEvent.h"
//#include "../Debug/UnitDisabler.h"
//---------------------------------------------------------------------------

#if !defined(__CAPITAL_WITH_DEPENDENCIES__DISABLE__)
namespace NSApplication {
namespace NSKernel {

// ---------------------------------------------------------------------------
// Using
// ---------------------------------------------------------------------------

using CapitalEvents = std::list<CSession::const_iterator>;
using ShiftEvents = CapitalEvents;
using CapslockEvents = CapitalEvents;
// ---------------------------------------------------------------------------
// Declaration CCapitalWithDependencies
// ---------------------------------------------------------------------------

class CCapitalWithDependencies {
  public:
  CCapitalWithDependencies( const CSession::const_iterator& Iterator,
                            unsigned int numberOfDependentPrintedKeys = 0,
                            unsigned int numberOfDependentDeletedKeys = 0);

  unsigned int getNumberOfDependentPrintedKeys() const;
  unsigned int getNumberOfDependentDeletedKeys() const;
  unsigned int getNumberOfDependentFullKeys() const;

  unsigned int getNumberOfDependentKeys(ETextMode TextMode) const;
  const CSession::const_iterator& getIterator() const;
  void setNumberOfDependentKeys(ETextMode TextMode, unsigned int newValue);

  bool isPrintedEssential() const;
  bool isFullEssential() const;
  bool isEssential(ETextMode TextMode) const;

  void increasePrintedDependencies();
  void increaseDeletedDependencies();

  void increaseNumberOfDependentKeysBy( ETextMode TextMode,
                                        unsigned int amount);

  CSession::const_iterator& getIterator();

  private:
  CSession::const_iterator KeyIterator;
  unsigned int NumberOfDependentKeysInPrintedMode;
  unsigned int NumberOfDependentKeysInFullMode;
};
// ---------------------------------------------------------------------------
// Forward Declarations
// ---------------------------------------------------------------------------

class CPressedCapitalWithDependencies;
// ---------------------------------------------------------------------------
// Declaration CCapitalWithDependenciesContainer
// ---------------------------------------------------------------------------

class CCapitalWithDependenciesContainer
    : public std::deque<CCapitalWithDependencies>{
  public:
  int getSize(ETextMode TextMode, ECapitalMode CapitalMode) const;
  bool isEmpty(ETextMode TextMode, ECapitalMode CapitalMode) const;

  const_iterator getFirstCapital( ETextMode TextMode,
                                  ECapitalMode CapitalMode) const;
  const_iterator getLastCapital(  ETextMode TextMode,
                                  ECapitalMode CapitalMode) const;
  // функции ниже возвращают -1 если в указанном режиме не было нажатий или отпусканий
  microseconds getFirstPressingTime( ETextMode TextMode,
                                    ECapitalMode CapitalMode) const;
  microseconds getFirstReleasingTime(ETextMode TextMode,
                                    ECapitalMode CapitalMode) const;
  microseconds getLastPressingTime(ETextMode TextMode,
                                  ECapitalMode CapitalMode) const;
  microseconds getLastReleasingTime( ETextMode TextMode,
                                    ECapitalMode CapitalMode) const;
  private:
  int getNumberOfEssential(ETextMode TextMode) const;

  const_iterator getFirstEssentialCapital(ETextMode TextMode) const;

  const_iterator getLastEssentialCapital(ETextMode TextMode) const;

  microseconds getFirstReleasingTime() const;
  microseconds getFirstEssentialReleasingTime(ETextMode TextMode) const;

  microseconds getLastReleasingTime() const;
  microseconds getLastEssentialReleasingTime(ETextMode TextMode) const;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
