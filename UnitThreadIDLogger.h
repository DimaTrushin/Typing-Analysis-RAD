//---------------------------------------------------------------------------

#ifndef UnitThreadIDLoggerH
#define UnitThreadIDLoggerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Library/UnitBasicLoggers.h"
//---------------------------------------------------------------------------

namespace NSApplication {

//---------------------------------------------------------------------------
// Declaration of CThreadIDLogger
//---------------------------------------------------------------------------

class CThreadIDLogger : protected NSLibrary::CScreenLogger {
  using CTextWriter = NSInterface::CTextWriter;
public:
  CThreadIDLogger() = default;
  void initialize(CTextWriter& LogScreen);
  void Log(const std::wstring& Description);
protected:
  inline void makeLogText(const std::wstring& Description,
                          std::wstring* pLogText);
private:
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
