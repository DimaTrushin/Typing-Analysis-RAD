//---------------------------------------------------------------------------

#ifndef UnitBasicLoggersH
#define UnitBasicLoggersH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <cassert>
#include <string>
#include <mutex>
//#include <fstream>
#include <boost/filesystem/fstream.hpp>
#include "../UnitTimer.h"
#include "../Interface/UnitTextWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Declaration of CFileLogger
//---------------------------------------------------------------------------

class CFileLogger {
public:
  CFileLogger() = default;
  CFileLogger(const std::wstring& fileName);
  void initialize(const std::wstring& fileName);
  void Log(const std::wstring& Text);
protected:
  bool isDefined() const;
private:
  inline void makeFirstEntry();
  inline void makeLogHeader(std::wstring* pLogHeader) const;
  std::mutex guardian_;
  boost::filesystem::wofstream oFileStream_;
  //std::wofstream oFileStream_;
};
//---------------------------------------------------------------------------
// Declaration of CScreenLogger
//---------------------------------------------------------------------------

class CScreenLogger {
  using CTextWriter = NSInterface::CTextWriter;
public:
  CScreenLogger() = default;
  CScreenLogger(CTextWriter& LogScreen);
  void initialize(CTextWriter& LogScreen);
  void Log(const std::wstring& Text);
protected:
  bool isDefined() const;
private:
  inline void makeFirstEntry();
  inline void makeLogHeader(std::wstring* pLogHeader) const;
  std::mutex guardian_;
  CTextWriter* pLogScreen_;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
