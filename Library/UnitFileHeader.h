//---------------------------------------------------------------------------

#ifndef UnitFileHeaderH
#define UnitFileHeaderH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vector>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CBasicType
//---------------------------------------------------------------------------

using CFileBasicType = int;
//---------------------------------------------------------------------------
// Declaration of CFileHeader
//---------------------------------------------------------------------------

class CFileHeader : public std::vector<CFileBasicType> {
  using CBase = std::vector<CFileBasicType>;
public:
  CFileHeader();

  void setToDefault();

  //each element of the file header must be of 4 bytes
  static constexpr int kBasicBlockSize = 4;
protected:
private:
  template<class TStreamer>
  friend TStreamer& operator<<( TStreamer& Streamer,
                                const CFileHeader& FileHeader);
  template<class TStreamer>
  friend TStreamer& operator>>( TStreamer& Streamer,
                                CFileHeader& FileHeader);
};
//---------------------------------------------------------------------------
// Declaration of CFileHeader Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CFileHeader& FileHeader);
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CFileHeader& FileHeader);
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {

//---------------------------------------------------------------------------
// Definition of CFileHeader Streaming
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator<<(TStreamer& Streamer, const CFileHeader& FileHeader) {
  Streamer << static_cast<const typename CFileHeader::CBase&>(FileHeader);
  return Streamer;
}
//---------------------------------------------------------------------------

template<class TStreamer>
TStreamer& operator>>(TStreamer& Streamer, CFileHeader& FileHeader) {
  Streamer >> static_cast<typename CFileHeader::CBase&>(FileHeader);
  return Streamer;
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
