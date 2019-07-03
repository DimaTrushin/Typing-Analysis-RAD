//---------------------------------------------------------------------------

#ifndef UnitSessionIteratorH
#define UnitSessionIteratorH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitStringFormat.h"
#include "UnitSessionToTreeConverter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
// ---------------------------------------------------------------------------
// Declaration of CSessionIterator
// ---------------------------------------------------------------------------

class CSessionIterator {
public:
  CSessionIterator(const CSession& Session);
  ~CSessionIterator() = default;

  ETextFormat getTextFormat() const;
  CFormatStructure getTextFormatStructure() const;
  wchar_t getSymbol() const;
  unsigned short getVKCode() const;
  bool isValid() const;
  microseconds getPressingTime() const;
  microseconds getReleasingTime() const;
  void setNext();
  microseconds getPhysicalResponseTime() const;
private:
  void releaseBefore(microseconds Time);
  void pressCurrentKeyOnKeyboardState(
                            const CSession::const_iterator& KeyIterator);

  const CSession* pSession;
  CSession::const_iterator CurrentPosition;
  CPressedKeys PressedKeys;
  NSKeyboard::CKeyboardState CurrentKeyboardState;
};
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
