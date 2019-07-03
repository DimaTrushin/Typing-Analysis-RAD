// ---------------------------------------------------------------------------

#ifndef UnitFingerLayoutH
#define UnitFingerLayoutH
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include <list>
#include <algorithm>
#include "../Library/UnitComparator.h"
#include "UnitKeyPolicies.h"
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Declaration of EHandSide
// ---------------------------------------------------------------------------

enum class EHandSide {
  Left = 0, Right = 128
};
// ---------------------------------------------------------------------------
// Declaration of EHandSide Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const EHandSide& HandSide);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, EHandSide& HandSide);
// ---------------------------------------------------------------------------
// Declaration of EFinger
// ---------------------------------------------------------------------------

enum class EFinger {
  Thumb, Index, Middle, Ring, Pinky
};
// ---------------------------------------------------------------------------
// Declaration of EFinger Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const EFinger& Finger);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, EFinger& Finger);
// ---------------------------------------------------------------------------
// Declaration of EHandFinger
// ---------------------------------------------------------------------------

enum class EHandFinger {
  LhThumb,        LhIndex, LhMiddle, LhRing, LhPinky,
  RhThumb = 128,  RhIndex, RhMiddle, RhRing, RhPinky
};
// ---------------------------------------------------------------------------
// Declaration of EHandFinger Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const EHandFinger& HandFinger);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, EHandFinger& HandFinger);
// ---------------------------------------------------------------------------
// Declaration of Enum Functions
// ---------------------------------------------------------------------------

EHandSide getHand(EHandFinger HandFingerData);
EFinger getFinger(EHandFinger HandFingerData);
EHandFinger makeHandFinger(EHandSide Hand, EFinger Finger);
EHandFinger getNext(EHandFinger HandFingerData);
void setHand(EHandSide Hand, EHandFinger* pHandFingerData);
void setFinger(EFinger Finger, EHandFinger* pHandFingerData);
void setToNext(EHandFinger* pHandFingerData);
// ---------------------------------------------------------------------------
// Declaration of CKey
// ---------------------------------------------------------------------------

class CKey : public CKeyVKCodeBase {
public:
  CKey();
  using CKeyVKCodeBase::CKeyVKCodeBase;

  CKey& operator=(unsigned short VKCode);
  bool operator==(const CKey& Key) const;
  bool operator!=(const CKey& Key) const;
};
// ---------------------------------------------------------------------------
// Declaration of CKey Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKey& Key);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKey& Key);
// ---------------------------------------------------------------------------
// Declaration CFinger
// ---------------------------------------------------------------------------

class CFinger {
public:
  CFinger(EHandFinger newFingerData = kDefaultFingerData);
  CFinger(EHandSide Hand, EFinger Finger);

  bool isLeftHand() const;
  bool isRightHand() const;
  bool isThumb() const;
  bool isIndex() const;
  bool isMiddle() const;
  bool isRing() const;
  bool isPinky() const;

  EHandSide getHand() const;
  EFinger getFinger() const;
  EHandFinger getHandFinger() const;

  void setHand(EHandSide Hand);
  void setFinger(EFinger Finger);
  void setHandFinger(EHandFinger HandFinger);

  void getFingerName(std::wstring* FingerName) const;
  void getHandName(std::wstring* HandName) const;

  // coincides ñ CDirectOrder
  bool operator<(const CFinger& other) const;
  // ---------------------------------------------------------------------------
  // Declaration CFinger::CThumbFirst
  // ---------------------------------------------------------------------------

  class CThumbFirst{
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  // ---------------------------------------------------------------------------
  // Declaration CFinger::CLeftHandFirst
  // ---------------------------------------------------------------------------

  class CLeftHandFirst{
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  // ---------------------------------------------------------------------------
  // Declaration CFinger::CDirectOrder
  // ---------------------------------------------------------------------------

  class CDirectOrder{
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  // ---------------------------------------------------------------------------
  // Declaration CFinger::CReverseOrder
  // ---------------------------------------------------------------------------

  class CReverseOrder{
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  // ---------------------------------------------------------------------------
  // Declaration CFinger::CLeftReverseRightDirect
  // ---------------------------------------------------------------------------

  class CLeftReverseRightDirect{
  public:
    using ArgumentType = CFinger;
    bool operator()(const CFinger& first,
                    const CFinger& second) const;
  };
  using CThumbOrder = NSLibrary::CLexSum<CThumbFirst, CLeftHandFirst>;
  using CStandardFingerOrder = NSLibrary::CLexSum<CThumbOrder,
                                                  CLeftReverseRightDirect>;
  // ---------------------------------------------------------------------------
private:
  // Higher bit: left hand - 0, right hand - 1
  // Fingers:
  // thumb - 0, index - 1, middle - 2, ring - 3, pinky - 4
  EHandFinger FingerData;
  constexpr static EHandFinger kDefaultFingerData = EHandFinger::LhThumb;

  template<class TStreamer>
  friend TStreamer& operator<<(TStreamer& Streamer, const CFinger& Finger);
  template<class TStreamer>
  friend TStreamer& operator>>(TStreamer& Streamer, CFinger& Finger);
};
// ---------------------------------------------------------------------------
// Declaration CFinger Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CFinger& Finger);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CFinger& Finger);
// ---------------------------------------------------------------------------
// Declaration of CFingerWithKeys
// ---------------------------------------------------------------------------

class CFingerWithKeys : public CFinger, public std::list<CKey> {
public:
  using CKeyContainer = std::list<CKey>;
  using CKeyIterator = CKeyContainer::iterator;
  using CKeyConstIterator = CKeyContainer::const_iterator;

  using CFinger::CFinger;

  bool isThereKey(const CKey& Key) const;
  void setToDefault();
private:
  // this functions do not check if a key is already in the key list
  void setToDefaultLhThumb();
  void setToDefaultLhIndex();
  void setToDefaultLhMiddle();
  void setToDefaultLhRing();
  void setToDefaultLhPinky();
  void setToDefaultRhThumb();
  void setToDefaultRhIndex();
  void setToDefaultRhMiddle();
  void setToDefaultRhRing();
  void setToDefaultRhPinky();
};
// ---------------------------------------------------------------------------
// Declaration of CFingerWithKeys Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CFingerWithKeys& FingerWithKeys);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CFingerWithKeys& FingerWithKeys);
// ---------------------------------------------------------------------------
// Declaration of CFingerLayout
// ---------------------------------------------------------------------------

class CFingerLayout : public std::list<CFingerWithKeys> {
public:
  using CFingerContainer = std::list<CFingerWithKeys>;
  using CFingerIterator = typename CFingerContainer::iterator;
  using CFingerConstIterator = typename CFingerContainer::const_iterator;
  using CKeyContainer = typename CFingerWithKeys::CKeyContainer;

  void addFinger(EHandFinger HandFinger);
  void removeFinger(EHandFinger HandFinger);
  void assignKeyToFinger( const CKey& Key,
                          const CFingerIterator& index);
  void assignKeyToFinger(const CKey& Key, EHandFinger HandFinger);
  void unAssignKey(const CKey& Key);
  bool findFingerIterator(EHandFinger HandFinger,
                          CFingerConstIterator* pIndex) const;
  bool findFingerIteratorOfKey( const CKey& Key,
                                CFingerConstIterator* pIndex) const;
  bool isThereFinger(EHandFinger HandFinger) const;
  bool isKeyAssigned(const CKey& Key) const;
  bool isKeyAssignedToFinger(const CKey& Key, EHandFinger HandFinger) const;

  static void generateDefaultLayout(CFingerLayout* FingerLayout);
private:
  // this functions do not check if a finger is already in the finger list
  static void addLeftHand(CFingerLayout* FingerLayout);
  static void addRightHand(CFingerLayout* FingerLayout);
};
// ---------------------------------------------------------------------------
// Declaration of CFingerLayout Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CFingerLayout& FingerLayout);
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CFingerLayout& FingerLayout);
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Definition of EHandSide Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const EHandSide& HandSide) {
  Streamer.writePOD(HandSide);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, EHandSide& HandSide) {
  Streamer.readPOD(&HandSide);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of EFinger Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const EFinger& Finger) {
  Streamer.writePOD(Finger);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, EFinger& Finger) {
  Streamer.readPOD(&Finger);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of EHandFinger Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const EHandFinger& HandFinger) {
  Streamer.writePOD(HandFinger);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, EHandFinger& HandFinger) {
  Streamer.readPOD(&HandFinger);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CKey Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CKey& Key) {
  Streamer << static_cast<const CKeyVKCodeBase&>(Key);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CKey& Key) {
  Streamer >> static_cast<CKeyVKCodeBase&>(Key);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition CFinger Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CFinger& Finger) {
  Streamer << Finger.FingerData;
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CFinger& Finger) {
  Streamer >> Finger.FingerData;
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CFingerWithKeys Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CFingerWithKeys& FingerWithKeys) {
  Streamer << static_cast<const CFinger&>(FingerWithKeys);
  Streamer <<
        static_cast<const CFingerWithKeys::CKeyContainer&>(FingerWithKeys);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer,
                      CFingerWithKeys& FingerWithKeys) {
  Streamer >> static_cast<CFinger&>(FingerWithKeys);
  Streamer >> static_cast<CFingerWithKeys::CKeyContainer&>(FingerWithKeys);
  return Streamer;
}
// ---------------------------------------------------------------------------
// Definition of CFingerLayout Streaming
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CFingerLayout& FingerLayout) {
  Streamer <<
        static_cast<const CFingerLayout::CFingerContainer&>(FingerLayout);
  return Streamer;
}
// ---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CFingerLayout& FingerLayout) {
  Streamer >> static_cast<CFingerLayout::CFingerContainer&>(FingerLayout);
  return Streamer;
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#endif
