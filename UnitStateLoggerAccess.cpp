//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitStateLoggerAccess.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of static member of CStateLoggerAccess
//---------------------------------------------------------------------------

template<>
CStateLoggerAccess::CStaticObjectType CStateLoggerAccess::gObject_ = nullptr;
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
