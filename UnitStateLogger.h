//---------------------------------------------------------------------------

#ifndef UnitStateLoggerH
#define UnitStateLoggerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "Library/UnitBasicLoggers.h"
//---------------------------------------------------------------------------

namespace NSApplication {

//---------------------------------------------------------------------------
// Declaration of CStateLogger
//---------------------------------------------------------------------------

class CStateLogger : protected NSLibrary::CScreenLogger {
  using CTextWriter = NSInterface::CTextWriter;
public:
  CStateLogger() = default;
  CStateLogger(CTextWriter& LogScreen);
  void initialize(CTextWriter& LogScreen);
  void Log(const std::wstring& Description);
  template<class TAction>
  void Log( const std::wstring& Description,
            TAction&& LogAction);
protected:
private:
};
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of CStateLogger
//---------------------------------------------------------------------------

template<class TAction>
void CStateLogger::Log( const std::wstring& Description,
                        TAction&& LogAction) {
  TAction Action(std::forward<TAction>(LogAction));
  std::wstring LogText(Description);
  LogText += L" ";
  Action(&LogText);
  LogText += L"\n";
  CScreenLogger::Log(LogText);
}
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
