//---------------------------------------------------------------------------

#ifndef UnitRawBufferToSeanceConverterH
#define UnitRawBufferToSeanceConverterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKeyEvent.h"
#include <list>
#include <algorithm>

//#include "UnitRawToEventConverter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CKeysBeingPressed
// ---------------------------------------------------------------------------

// TO DO
// CSession::iterator here is Rad Studio dependent
// iterators on deque must become invalidated after a push_back
// or after emplace_back
// Apparently this does not happen in Rad Studio!
class CKeysBeingPressed : public std::list<CSession::iterator> {
public:
  using BaseContainer = std::list<CSession::iterator>;
  // there should be two versions of the function:
  // 1) for const_iterator
  // 2) for iterator
  bool findIteratorOfEvent(
                    unsigned short VKey,
                    const_iterator* pIndex) const;
};
// ---------------------------------------------------------------------------
// Declaration of CRawBufferToSeanceConverter
// ---------------------------------------------------------------------------

class CRawBufferToSeanceConverter {
  using CRawBuffer = NSKeyboard::CRawEventContainer;
  using CRawKey = NSKeyboard::CRawKey;
public:
  CRawBufferToSeanceConverter() = default;
  CRawBufferToSeanceConverter(microseconds SessionTimeLimit);
  void convert(CRawBuffer* pBuffer, CSeance* pSeance);
protected:
private:
  void setInternalResources(CRawBuffer* pBuffer, CSeance* pSeance);
  void prepareFirstSession();
  void handleRawEvent(const CRawKey& RawEvent);
  bool needNewSession(const CRawKey& RawEvent) const;
  void prepareNewSession();
  void releaseAllKeysInCurrentKeyboard();
  void handlePressing(const CRawKey& RawEvent);
  void handleKeyHolding(const CRawKey& RawEvent,
                        const CKeysBeingPressed::iterator& index);
  void handleKeyPressing(const CRawKey& RawEvent);

  void handleReleasing(const CRawKey& RawEvent);
  void handleKeyReleasing(microseconds ReleasingTime,
                          const CKeysBeingPressed::iterator& index);
  void releaseAllRemainingKeys();
  void releaseAtGivenTime(microseconds ReleasingTime,
                          CKeysBeingPressed* pKeysBeingPressed);
  const CSession& CurrentSession() const;
  CSession& CurrentSession();
  void removeEmptyOutput();
  void flushBuffer();


  CRawBuffer* pBuffer_ = nullptr;
  CSeance* pSeance_ = nullptr;
  NSKeyboard::CKeyboardState CurrentKeyboardState_;

  CKeysBeingPressed PressedKeys_;
  microseconds SessionTimeLimit_ = kSessionTimeLimit;
  // Time between sessions is 5 seconds
  static constexpr const microseconds kSessionTimeLimit = 5000000;
  // If, by any reason, we have unreleased keys in a session,
  // and we cannot determine when to release them
  // we release the keys after 40 milliseconds
  static constexpr const microseconds kStandardHoldingTime = 40000;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
