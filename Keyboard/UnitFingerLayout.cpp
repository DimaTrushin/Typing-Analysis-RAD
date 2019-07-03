// ---------------------------------------------------------------------------

#pragma hdrstop
// ---------------------------------------------------------------------------
// Include
// ---------------------------------------------------------------------------

#include "UnitFingerLayout.h"

#if !defined(NDEBUG)
//#define __FILNGER__LAYOUT__TEST__
#if defined(__FILNGER__LAYOUT__TEST__)
#include "UnitFileWriter.h"
#include "UnitFileReader.h"
#include <vcl.h>
#endif
#endif
// ---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKeyboard {
// ---------------------------------------------------------------------------
// Tester
// ---------------------------------------------------------------------------

#if !defined(NDEBUG)
#if defined(__FILNGER__LAYOUT__TEST__)
class CFingerLayoutTester {
public:
  CFingerLayoutTester() {
    runTest();
  }
private:
  void runTest() {
    std::wstring FileName(L"FingerLayoutTests.bin");
    UnicodeString Result(L"FingerLayoutTests:");
    writeToFile(FileName, &Result);
    readFromFile(FileName, &Result);
    ShowMessage(Result.c_str());
  }
  void writeToFile(const std::wstring& FileName, UnicodeString* pResult) {
    NSLibrary::CFileWriter FileWriter(FileName);
    CFinger Finger;
    CFingerWithKeys FingerWithKeys;
    CFingerLayout FingerLayout;

    FingerWithKeys.setToDefault();
    CFingerLayout::generateDefaultLayout(&FingerLayout);

    FileWriter << Finger;
    FileWriter << FingerWithKeys;
    FileWriter << FingerLayout;
  }
  void readFromFile(const std::wstring& FileName, UnicodeString* pResult) {
   NSLibrary::CFileReader FileReader(FileName);
    CFinger Finger;
    CFingerWithKeys FingerWithKeys;
    CFingerLayout FingerLayout;
    FileReader >> Finger;
    FileReader >> FingerWithKeys;
    FileReader >> FingerLayout;
  }

} FingerLayoutTester;
#endif
#endif
// ---------------------------------------------------------------------------
// Definition of Enum Functions
// ---------------------------------------------------------------------------

EHandSide getHand(EHandFinger HandFingerData) {
  if (HandFingerData < EHandFinger::RhThumb)
    return EHandSide::Left;
  return EHandSide::Right;
}
// ---------------------------------------------------------------------------

EFinger getFinger(EHandFinger HandFingerData) {
  // TO DO
  // this is very unsafe!
  return static_cast<EFinger>(static_cast<unsigned int>(HandFingerData) & 127);
}
// ---------------------------------------------------------------------------

EHandFinger makeHandFinger(EHandSide Hand, EFinger Finger) {
  // TO DO
  // this is very unsafe!
  return static_cast<EHandFinger>(static_cast<unsigned int>(Hand) +
                                  static_cast<unsigned int>(Finger));
}
// ---------------------------------------------------------------------------

EHandFinger getNext(EHandFinger HandFingerData) {
  // TO DO
  // this is very unsafe!
  return static_cast<EHandFinger>(
            static_cast<unsigned int>(HandFingerData) + 1);
}
// ---------------------------------------------------------------------------

void setHand(EHandSide Hand, EHandFinger* pHandFingerData) {
  *pHandFingerData = makeHandFinger(Hand, getFinger(*pHandFingerData));
}
// ---------------------------------------------------------------------------

void setFinger(EFinger Finger, EHandFinger* pHandFingerData) {
  *pHandFingerData = makeHandFinger(getHand(*pHandFingerData), Finger);
}
// ---------------------------------------------------------------------------

void setToNext(EHandFinger* pHandFingerData) {
  *pHandFingerData = getNext(*pHandFingerData);
}
// ---------------------------------------------------------------------------
// Definition of CKey
// ---------------------------------------------------------------------------

CKey::CKey() : CKeyVKCodeBase(0) {
}
// ---------------------------------------------------------------------------

CKey& CKey::operator=(unsigned short VKCode) {
  CKeyVKCodeBase::VKCode = VKCode;
  return *this;
}
// ---------------------------------------------------------------------------

bool CKey::operator==(const CKey& Key) const {
  return VKCode == Key.VKCode;
}
// ---------------------------------------------------------------------------

bool CKey::operator!=(const CKey& Key) const {
  return !(*this == Key);
}
// ---------------------------------------------------------------------------
// Definitions of CFinger
// ---------------------------------------------------------------------------

CFinger::CFinger(EHandFinger newFingerData) : FingerData(newFingerData) {
}
// ---------------------------------------------------------------------------

CFinger::CFinger(EHandSide Hand, EFinger Finger)
  : FingerData(makeHandFinger(Hand, Finger)) {
}
// ---------------------------------------------------------------------------

bool CFinger::isLeftHand() const {
  return getHand() == EHandSide::Left;
}
// ---------------------------------------------------------------------------

bool CFinger::isRightHand() const {
  return !isLeftHand();
}
// ---------------------------------------------------------------------------

bool CFinger::isThumb() const {
  return getFinger() == EFinger::Thumb;
}
// ---------------------------------------------------------------------------

bool CFinger::isIndex() const {
  return getFinger() == EFinger::Index;
}
// ---------------------------------------------------------------------------

bool CFinger::isMiddle() const {
  return getFinger() == EFinger::Middle;
}
// ---------------------------------------------------------------------------

bool CFinger::isRing() const {
  return getFinger() == EFinger::Ring;
}
// ---------------------------------------------------------------------------

bool CFinger::isPinky() const {
  return getFinger() == EFinger::Pinky;
}
// ---------------------------------------------------------------------------

EHandSide CFinger::getHand() const {
  return NSApplication::NSKeyboard::getHand(FingerData);
}
// ---------------------------------------------------------------------------

EFinger CFinger::getFinger() const {
  return NSApplication::NSKeyboard::getFinger(FingerData);
}
// ---------------------------------------------------------------------------

EHandFinger CFinger::getHandFinger() const {
  return FingerData;
}
// ---------------------------------------------------------------------------

void CFinger::setHand(EHandSide Hand) {
  NSApplication::NSKeyboard::setHand(Hand, &FingerData);
}
// ---------------------------------------------------------------------------

void CFinger::setFinger(EFinger Finger) {
  NSApplication::NSKeyboard::setFinger(Finger, &FingerData);
}
// ---------------------------------------------------------------------------

void CFinger::setHandFinger(EHandFinger HandFinger) {
  FingerData = HandFinger;
}
// ---------------------------------------------------------------------------

void CFinger::getFingerName(std::wstring* FingerName) const {
  if (isThumb()) {
    *FingerName = L"Thumb";
    return;
  }
  if (isIndex()) {
    *FingerName = L"Index Finger";
    return;
  }
  if (isMiddle()) {
    *FingerName = L"Middle Finger";
    return;
  }
  if (isRing()) {
    *FingerName = L"Ring Finger";
    return;
  }
  if (isPinky()) {
    *FingerName = L"Pinky";
    return;
  }
  *FingerName =L"Unknown Finger";
  return;
}
// ---------------------------------------------------------------------------

void CFinger::getHandName(std::wstring* HandName) const {
  if (isLeftHand())
    *HandName = L"Left Hand";
  else
    *HandName = L"Right Hand";
}
// ---------------------------------------------------------------------------

bool CFinger::operator<(const CFinger& other) const {
  CDirectOrder DirectOrder;
  return DirectOrder(*this, other);
}
// ---------------------------------------------------------------------------
// Definition CFinger::CThumbFirst
// ---------------------------------------------------------------------------

bool CFinger::CThumbFirst::operator()(const CFinger& first,
                                      const CFinger& second) const {
  return first.isThumb() && !second.isThumb();
}
// ---------------------------------------------------------------------------
// Definition CFinger::CLeftHandFirst
// ---------------------------------------------------------------------------

bool CFinger::CLeftHandFirst::operator()( const CFinger& first,
                                          const CFinger& second) const {
  return first.isLeftHand() && !second.isLeftHand();
}
// ---------------------------------------------------------------------------
// Definition CFinger::CDirectOrder
// ---------------------------------------------------------------------------

bool CFinger::CDirectOrder::operator()( const CFinger& first,
                                        const CFinger& second) const {
  return first.FingerData < second.FingerData;
}
// ---------------------------------------------------------------------------
// Definition CFinger::CReverseOrder
// ---------------------------------------------------------------------------

bool CFinger::CReverseOrder::operator()(const CFinger& first,
                                        const CFinger& second) const {
  return first.FingerData > second.FingerData;
}
// ---------------------------------------------------------------------------
// Definition CFinger::CLeftReverseRightDirect
// ---------------------------------------------------------------------------

bool CFinger::CLeftReverseRightDirect::operator()(
                                              const CFinger& first,
                                              const CFinger& second) const {
  if (first.isLeftHand()) {
    if (second.isLeftHand())
      // first - left, second - left
      return CReverseOrder()(first, second);
    else
      // first - left, second - right
      return true;
  } else {
    if (second.isLeftHand())
      // first - right, second - left
      return false;
    else
      // first - right, second - right
      return CDirectOrder()(first, second);
  }
}
// ---------------------------------------------------------------------------
// Definitions of CFingerWithKeys
// ---------------------------------------------------------------------------

bool CFingerWithKeys::isThereKey(const CKey& Key) const {
  for (const auto& KeyInContainer : *this)
    if (KeyInContainer == Key)
      return true;
  return false;
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefault() {
  clear();
  switch (getHandFinger()) {
  case EHandFinger::LhThumb:
    setToDefaultLhThumb();
    break;
  case EHandFinger::LhIndex:
    setToDefaultLhIndex();
    break;
  case EHandFinger::LhMiddle:
    setToDefaultLhMiddle();
    break;
  case EHandFinger::LhRing:
    setToDefaultLhRing();
    break;
  case EHandFinger::LhPinky:
    setToDefaultLhPinky();
    break;
  case EHandFinger::RhThumb:
    setToDefaultRhThumb();
    break;
  case EHandFinger::RhIndex:
    setToDefaultRhIndex();
    break;
  case EHandFinger::RhMiddle:
    setToDefaultRhMiddle();
    break;
  case EHandFinger::RhRing:
    setToDefaultRhRing();
    break;
  case EHandFinger::RhPinky:
    setToDefaultRhPinky();
    break;
    // unknown finger, do nothing
  default:
    break;
  }
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhThumb() {
  //push_back(VK_SPACE);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhIndex() {
  push_back(VK_5);
  push_back(VK_R);
  push_back(VK_F);
  push_back(VK_V);
  push_back(VK_6);
  push_back(VK_T);
  push_back(VK_G);
  push_back(VK_B);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhMiddle() {
  push_back(VK_4);
  push_back(VK_E);
  push_back(VK_D);
  push_back(VK_C);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhRing() {
  push_back(VK_3);
  push_back(VK_W);
  push_back(VK_S);
  push_back(VK_X);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultLhPinky() {
  push_back(VK_1);
  push_back(VK_2);
  push_back(VK_Q);
  push_back(VK_A);
  push_back(VK_Z);
  push_back(VK_LSHIFT);
  push_back(VK_LCONTROL);
  push_back(VK_LMENU);
  push_back(VK_CAPITAL);
  push_back(VK_ENG_TILDE);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhThumb() {
  push_back(VK_SPACE);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhIndex() {
  push_back(VK_7);
  push_back(VK_8);
  push_back(VK_Y);
  push_back(VK_H);
  push_back(VK_N);
  push_back(VK_U);
  push_back(VK_J);
  push_back(VK_M);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhMiddle() {
  push_back(VK_9);
  push_back(VK_I);
  push_back(VK_K);
  push_back(VK_ENG_COMMA);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhRing() {
  push_back(VK_0);
  push_back(VK_O);
  push_back(VK_L);
  push_back(VK_ENG_PERIOD);
}
// ---------------------------------------------------------------------------

void CFingerWithKeys::setToDefaultRhPinky() {
  push_back(VK_P);
  push_back(VK_ENG_SEMICOLON);
  push_back(VK_ENG_SLASH_QUESTION);
  push_back(VK_ENG_MINUS);
  push_back(VK_ENG_PLUS);
  push_back(VK_ENG_LEFT_BRACE);
  push_back(VK_ENG_RIGHT_BRACE);
  push_back(VK_ENG_QUOTE);
  push_back(VK_BACK);
  push_back(VK_ENG_BACKSLASH);
  push_back(VK_RETURN);
  push_back(VK_RSHIFT);
  push_back(VK_RMENU);
  push_back(VK_RCONTROL);
}
// ---------------------------------------------------------------------------
// Definition of CFingerLayout
// ---------------------------------------------------------------------------

void CFingerLayout::addFinger(EHandFinger HandFinger) {
  if (isThereFinger(HandFinger))
    return;
  push_back(CFingerWithKeys(HandFinger));
}
// ---------------------------------------------------------------------------

void CFingerLayout::removeFinger(EHandFinger HandFinger) {
  CFingerIterator index;
  if (findFingerIterator(HandFinger, &index))
    erase(index);
}
// ---------------------------------------------------------------------------

void CFingerLayout::assignKeyToFinger(const CKey& Key,
                                      const CFingerIterator& index) {
  unAssignKey(Key);
  index->push_back(Key);
}
// ---------------------------------------------------------------------------

void CFingerLayout::assignKeyToFinger(const CKey& Key,
                                      EHandFinger HandFinger) {
  unAssignKey(Key);
  addFinger(HandFinger);
  CFingerIterator index;
  findFingerIterator(HandFinger, &index);
  assignKeyToFinger(Key, index);
}
// ---------------------------------------------------------------------------

void CFingerLayout::unAssignKey(const CKey& Key) {
  CFingerIterator index;
  if (findFingerIteratorOfKey(Key, &index))
    index->remove(Key);
}
// ---------------------------------------------------------------------------

bool CFingerLayout::findFingerIterator(
                                EHandFinger HandFinger,
                                CFingerConstIterator* pIndex) const {
  CFingerConstIterator& index = *pIndex;
  index = std::find_if( begin(),
                        end(),
                        [&HandFinger](const CFingerWithKeys& Finger){
    return Finger.getHandFinger() == HandFinger;
  });
  if (index == end())
    return false;
  return true;
}
// ---------------------------------------------------------------------------

bool CFingerLayout::findFingerIteratorOfKey(
                                const CKey& Key,
                                CFingerConstIterator* pIndex) const {
  CFingerConstIterator& index = *pIndex;
  for (index = begin(); index != end(); ++index)
    if (index->isThereKey(Key))
      return true;
  return false;

}
// ---------------------------------------------------------------------------

bool CFingerLayout::isThereFinger(EHandFinger HandFinger) const {
  CFingerConstIterator index;
  return findFingerIterator(HandFinger, &index);
}
// ---------------------------------------------------------------------------

bool CFingerLayout::isKeyAssigned(const CKey& Key) const {
  CFingerConstIterator index;
  return findFingerIteratorOfKey(Key, &index);
}
// ---------------------------------------------------------------------------

bool CFingerLayout::isKeyAssignedToFinger(const CKey& Key,
                                          EHandFinger HandFinger) const {
  CFingerConstIterator index;
  if (!findFingerIteratorOfKey(Key, &index))
    return false;
  if (index->getHandFinger() != HandFinger)
    return false;
  return true;
}
// ---------------------------------------------------------------------------

void CFingerLayout::generateDefaultLayout(CFingerLayout* FingerLayout) {
  FingerLayout->clear();
  // Since there is no way to distinguish left and right thumbs
  // we assume that the space is pressed by the right one.
  // Thus we delete the left thumb from the layout
  addLeftHand(FingerLayout);
  FingerLayout->removeFinger(EHandFinger::LhThumb);
  addRightHand(FingerLayout);
  for (auto& Finger : *FingerLayout)
    Finger.setToDefault();
}
// ---------------------------------------------------------------------------

void CFingerLayout::addLeftHand(CFingerLayout* FingerLayout) {
  for ( EHandFinger finger = EHandFinger::LhThumb;
        finger <= EHandFinger::LhPinky;
        setToNext(&finger))
    FingerLayout->push_back(finger);
}
// ---------------------------------------------------------------------------

void CFingerLayout::addRightHand(CFingerLayout* FingerLayout) {
  for ( EHandFinger finger = EHandFinger::RhThumb;
        finger <= EHandFinger::RhPinky;
        setToNext(&finger))
    FingerLayout->push_back(finger);
}
// ---------------------------------------------------------------------------
} // NSKeyboard
// ---------------------------------------------------------------------------
} // NSApplication
// ---------------------------------------------------------------------------
#pragma package(smart_init)
