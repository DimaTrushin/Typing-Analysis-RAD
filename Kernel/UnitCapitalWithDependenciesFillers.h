//---------------------------------------------------------------------------

#ifndef UnitCapitalWithDependenciesFillersH
#define UnitCapitalWithDependenciesFillersH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitCapitalWithDependencies.h"
//---------------------------------------------------------------------------

#if !defined(__CAPITAL_WITH_DEPENDENCIES_FILLERS__DISABLE__)
namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration CCapitalWithDependenciesBeingPressed
// ---------------------------------------------------------------------------

class CCapitalWithDependenciesBeingPressed
    : public std::list<CCapitalWithDependenciesContainer::iterator> {
  public:
  void increasePrintedDependencies();
  void increaseDeletedDependencies();
  private:
};

// ---------------------------------------------------------------------------
// Declaration CShiftsWithDependenciesFiller
// ---------------------------------------------------------------------------

class CShiftsWithDependenciesFiller {
  public:
  void fill(const CSession& Session,
            const CTextDataTree& TextTree,
            CCapitalWithDependenciesContainer* pShifts);
  private:
  void fillWithoutDependencies(
                          const CSession& Session,
                          CCapitalWithDependenciesContainer* pShifts);
  bool isThereSymbolAndShift(
                    const CTextDataTree& TextTree,
                    CCapitalWithDependenciesContainer* pShifts) const;
  void setPressedShifts(CCapitalWithDependenciesContainer* pShifts);
  void updateDependencies();
  void pressCurrentShifts(
                    CCapitalWithDependenciesContainer* pShifts);
  void removeReleasedShifts();
  bool initialize(const CSession& Session,
                  const CTextDataTree& TextTree,
                  CCapitalWithDependenciesContainer* pShifts);


  CCapitalWithDependenciesBeingPressed PressedShifts;
  CCapitalWithDependenciesContainer::iterator itNextShift;
  CTextDataTree::CConstFullTextIterator itCurrentSymbol;
};
// ---------------------------------------------------------------------------
// Declaration CCapslocksWithDependenciesFiller
// ---------------------------------------------------------------------------

class CCapslocksWithDependenciesFiller {
  public:
  void fill(const CSession& Session,
            const CTextDataTree& TextTree,
            CCapitalWithDependenciesContainer* pCapslocks);
  private:

  class CCorrector{
    public:
    CCorrector(
      const CCapitalWithDependenciesContainer::iterator& itInitialPosition);
    void setToCorrectionPlace(ETextMode TextMode,
                              CCapitalWithDependenciesContainer* pCapitals);
    CCapitalWithDependenciesContainer::iterator& getPosition();
    bool needCorrection() const;
    private:
    bool needToMove(ETextMode TextMode) const;
    void moveLeft();
    void makeExceptionalMoveLeft(CCapitalWithDependenciesContainer* pCapitals);

    CCapitalWithDependenciesContainer::iterator itCorrectionPosition;
    unsigned int NumberOfSkippedCapslocks;
  };
  bool initialize(const CSession& Session,
                  const CTextDataTree& TextTree,
                  CCapitalWithDependenciesContainer* pCapslocks);

  void correctDependencies(CCapitalWithDependenciesContainer* pCapslocks);

  void correctDependencies( ETextMode TextMode,
                            CCapitalWithDependenciesContainer* pCapslocks);
  void correctDependenciesOfOneCapslock(
                  ETextMode TextMode,
                  CCapitalWithDependenciesContainer::iterator itCapslock,
                  CCapitalWithDependenciesContainer* pCapslocks);
  bool needToUseCorrector(
                      ETextMode TextMode,
                      CCapitalWithDependenciesContainer::iterator itCapslock,
                      CCapitalWithDependenciesContainer* pCapslocks) const;

  void fillWithoutDependencies(
                          const CSession& Session,
                          CCapitalWithDependenciesContainer* pCapslocks);
  void moveCurrentSymbolAfterCurrentCapslock(const CTextDataTree& TextTree);
  void setNearestCapslock(CCapitalWithDependenciesContainer* pCapslocks);
  void updateDependencies();

  CCapitalWithDependenciesContainer::iterator itCurrentCapslock;
  CTextDataTree::CConstFullTextIterator itCurrentSymbol;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
