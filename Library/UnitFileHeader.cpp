//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitFileHeader.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CFileHeader
//---------------------------------------------------------------------------

CFileHeader::CFileHeader() {
  static_assert(sizeof(CFileBasicType) == kBasicBlockSize,
                "CFileBasicType has inappropriate size");
  static_assert(sizeof(CBase::size_type) == kBasicBlockSize,
                "size_type of CFileHeader has inappropriate size");
}
//---------------------------------------------------------------------------

void CFileHeader::setToDefault() {
  clear();
  push_back(sizeof(bool));
  push_back(sizeof(short));
  push_back(sizeof(unsigned short));
  push_back(sizeof(int));
  push_back(sizeof(unsigned int));
  push_back(sizeof(long));
  push_back(sizeof(unsigned long));
  push_back(sizeof(long long));
  push_back(sizeof(unsigned long long));
  push_back(sizeof(float));
  push_back(sizeof(double));
  push_back(sizeof(long double));
  push_back(sizeof(char));
  push_back(sizeof(unsigned char));
  push_back(sizeof(wchar_t));
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
