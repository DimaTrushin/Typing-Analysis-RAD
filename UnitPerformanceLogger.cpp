//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitPerformanceLogger.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Definition of static member of CPerformanceLogger
//---------------------------------------------------------------------------

template<>
CPerformanceLogger::CStaticObjectType CPerformanceLogger::gObject_ = nullptr;
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
