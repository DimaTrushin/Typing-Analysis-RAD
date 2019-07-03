//---------------------------------------------------------------------------

#ifndef UnitKlavogrammaH
#define UnitKlavogrammaH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vector>
#include <map>
#include "../Keyboard/UnitFingerLayout.h"
#include "../UnitTimer.h"
//---------------------------------------------------------------------------
namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CMultiplicityTime
//---------------------------------------------------------------------------

class CMultiplicitySegment {
  public:
  CMultiplicitySegment( unsigned int multiplicity,
                        milliseconds segmentEndingTime);
  unsigned int Multiplicity;
  milliseconds SegmentEndingTime;
};
//---------------------------------------------------------------------------
// Declaration of CKlavogrammaKey
//---------------------------------------------------------------------------

class CKlavogrammaKey {
  public:
  using MultiplicitySegmentContainer = std::vector<CMultiplicitySegment>;
  CKlavogrammaKey(wchar_t symbol,
                  milliseconds pressingTime);
  void AddMultiplicitySegment(unsigned int Multiplicity,
                              milliseconds SegmentEndingTime);
  unsigned int getNumberOfSegments() const;
  milliseconds getPressingTime() const;
  milliseconds getReleasingTime() const;

  wchar_t Symbol;
  milliseconds PressingTime;
  MultiplicitySegmentContainer MultiplicitySegments;
};
//---------------------------------------------------------------------------
// Declaration of CFingerKlavogramma
//---------------------------------------------------------------------------

class CFingerKlavogramma : public std::vector<CKlavogrammaKey> {
};
//---------------------------------------------------------------------------
// Declaration of CKlavogramma
//---------------------------------------------------------------------------

class CKlavogramma : public std::map< NSKeyboard::CFinger,
                                      CFingerKlavogramma,
                                      NSKeyboard::
                                        CFinger::
                                          CStandardFingerOrder> {
  public:
  size_t getNumberOfFingers() const;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif


