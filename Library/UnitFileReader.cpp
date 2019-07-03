//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitFileReader.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CFileReaderBase
//---------------------------------------------------------------------------

CFileReaderBase::CFileReaderBase(const std::wstring& FileName)
  : File_(FileName, std::fstream::binary) {
  if (!File_.is_open())
    throw std::exception ("Cannot open ifstream\n");
}
//---------------------------------------------------------------------------

void CFileReaderBase::open(const std::wstring& FileName) {
  File_.open(FileName, std::fstream::binary);
  if (!File_.is_open())
    throw std::exception ("Cannot open ifstream\n");
}
//---------------------------------------------------------------------------

void CFileReaderBase::close() {
  File_.close();
}
//---------------------------------------------------------------------------

bool CFileReaderBase::isOpen() const {
  return File_.is_open();
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
