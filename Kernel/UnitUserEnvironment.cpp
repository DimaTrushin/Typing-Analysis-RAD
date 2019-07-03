//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitUserEnvironment.h"
#include "../Debug/UnitDisabler.h"
//---------------------------------------------------------------------------

#if !defined(__USER_ENVIRONMENT__DISABLE__)
namespace NSApplication {
namespace NSKernel {

//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

// The object containing global data
extern CUserEnvironment UserEnvironment;
CUserEnvironment UserEnvironment;
//---------------------------------------------------------------------------
// Definition of CUserEnvironment
//---------------------------------------------------------------------------

CUserEnvironment::CUserEnvironment() {
  CFingerLayout::generateDefaultLayout(&FingerLayout);
}
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
#pragma package(smart_init)
