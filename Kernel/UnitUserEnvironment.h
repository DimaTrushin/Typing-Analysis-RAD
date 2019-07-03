//---------------------------------------------------------------------------

#ifndef UnitUserEnvironmentH
#define UnitUserEnvironmentH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitKeyEvent.h"
#include "../Keyboard/UnitFingerLayout.h"
//#include "../Debug/UnitDisabler.h"
//---------------------------------------------------------------------------

#if !defined(__USER_ENVIRONMENT__DISABLE__)
namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Declaration of CUserEnvironment
//---------------------------------------------------------------------------

class CUserEnvironment {
  using CFingerLayout = NSKeyboard::CFingerLayout;
public:
  CUserEnvironment();
  CSeance Seance;
  CFingerLayout FingerLayout;

protected:
  CUserEnvironment(const CUserEnvironment&) = default;
  CUserEnvironment(CUserEnvironment&&) = default;
  CUserEnvironment& operator=(const CUserEnvironment&) = default;
  CUserEnvironment& operator=(CUserEnvironment&&) = default;

  friend class CMaster;

  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CUserEnvironment& UserEnvironment);
  template<class TStreamer>
  friend TStreamer& operator>>( TStreamer& Streamer,
                                CUserEnvironment& UserEnvironment);
};
//---------------------------------------------------------------------------
// Declaration of CUserEnvironment Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CUserEnvironment& UserEnvironment);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CUserEnvironment& UserEnvironment);
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSKernel {
//---------------------------------------------------------------------------
// Definition of CUserEnvironment Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer,
                      const CUserEnvironment& UserEnvironment) {
  Streamer << UserEnvironment.Seance;
  Streamer << UserEnvironment.FingerLayout;
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CUserEnvironment& UserEnvironment) {
  Streamer >> UserEnvironment.Seance;
  Streamer >> UserEnvironment.FingerLayout;
  return Streamer;
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#endif
