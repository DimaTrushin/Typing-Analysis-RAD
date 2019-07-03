//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitFileWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CFileWriterBase
//---------------------------------------------------------------------------

CFileWriterBase::CFileWriterBase(const std::wstring& FileName)
  : File_(FileName, std::fstream::binary | std::fstream::trunc) {
  if (!File_.is_open())
    throw std::exception ("Cannot open ofstream\n");
}
//---------------------------------------------------------------------------

void CFileWriterBase::open(const std::wstring& FileName) {
  File_.open(FileName, std::fstream::binary | std::fstream::trunc);
  if (!File_.is_open())
    throw std::exception ("Cannot open ofstream\n");
}
//---------------------------------------------------------------------------

void CFileWriterBase::close() {
  File_.close();
}
//---------------------------------------------------------------------------

bool CFileWriterBase::isOpen() const {
  return File_.is_open();
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
