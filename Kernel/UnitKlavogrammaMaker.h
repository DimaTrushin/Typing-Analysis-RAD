//---------------------------------------------------------------------------

#ifndef UnitKlavogrammaMakerH
#define UnitKlavogrammaMakerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKlavogramma.h"
#include "UnitAnalysisRover.h"
#include "../Library/UnitVectorHeapWithAccess.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CKeyUnderConstruction
//---------------------------------------------------------------------------

class CKeyUnderConstruction {
public:
  CKeyUnderConstruction(const CAnyUIterator& AnyUIterator);

  CKlavogrammaKey Key;
  unsigned short VKCode;
  milliseconds ReleasingTime;
  //---------------------------------------------------------------------------
  // Declaration of CFirstReleasedOnTop
  //---------------------------------------------------------------------------

  class CFirstReleasedOnTop {
  public:
    bool operator() ( const CKeyUnderConstruction& first,
                      const CKeyUnderConstruction& second);
  };
  //---------------------------------------------------------------------------
};
//---------------------------------------------------------------------------
// Declaration of CHeapOfKeysUnderConstruction
//---------------------------------------------------------------------------

class CHeapOfKeysUnderConstruction
      : private NSLibrary::
                  CVectorHeapWithAccess<
                      CKeyUnderConstruction,
                      CKeyUnderConstruction::CFirstReleasedOnTop> {
  using CBase = CVectorHeapWithAccess<
                                CKeyUnderConstruction,
                                CKeyUnderConstruction::CFirstReleasedOnTop>;
public:
  milliseconds getFirstReleasingTime() const;
  bool empty() const;
  CKeyUnderConstruction getAndReleaseKey();
  void insertNewKey(const CAnyUIterator& AnyUIterator);
private:
  inline void updateMultiplicities(milliseconds NewKeyTime);
};
//---------------------------------------------------------------------------
// Declaration of CKlavogrammaMaker
//---------------------------------------------------------------------------

class CKlavogrammaMaker {
  using CFingerLayout = NSKeyboard::CFingerLayout;
public:
  CKlavogrammaMaker() = default;
  void constructKlavogramma(const CAnalysisData& AnalysisData,
                            EOutputMode outputMode,
                            const CTextMode& textMode,
                            const CFingerLayout& Layout,
                            CKlavogramma* target);
private:
  inline void prepareInitialState(const CAnalysisData& AnalysisData,
                                  EOutputMode outputMode,
                                  const CTextMode& textMode,
                                  milliseconds* pStartingTime,
                                  CAnalysisRover* pNextKeyRover) const;
  inline void constructKlavogramma( const CFingerLayout& Layout,
                                    milliseconds StartingTime,
                                    CAnalysisRover* pNextKeyRover,
                                    CKlavogramma* target);
  inline bool isWorkDone(const CAnalysisRover& NextKeyRover) const;
  inline bool isNextPressing(const CAnalysisRover& NextKeyRover) const;
  inline void handlePressing( const CFingerLayout& Layout,
                              CAnalysisRover* pNextKeyRover);
  inline void handleReleasing(const CFingerLayout& Layout,
                              CKlavogramma* target);
  inline void shiftKlavogrammaTime( milliseconds StartingTime,
                                    CKlavogramma* target) const;
  inline void shiftFingerKlavogrammaTime( milliseconds StartingTime,
                                          CFingerKlavogramma* target) const;
  inline void shiftKeyTime( milliseconds StartingTime,
                            CKlavogrammaKey* target) const;
  inline void shiftSegmentTime( milliseconds StartingTime,
                                CMultiplicitySegment* target) const;
  inline void insertKeys( const CFingerLayout& Layout,
                          CKlavogramma* target);
  CHeapOfKeysUnderConstruction KeysUnderConstruction;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
