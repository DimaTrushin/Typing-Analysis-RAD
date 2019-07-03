//---------------------------------------------------------------------------

#ifndef UnitFileReaderH
#define UnitFileReaderH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

//#include <fstream>
#include <string>
//#include <vector>
#include <deque>
#include <list>
#include <array>
#include <map>
#include <queue>
#include <type_traits>
#include "UnitFileHeader.h"
#include <boost/filesystem/fstream.hpp>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CFileReaderBase
//---------------------------------------------------------------------------

class CFileReaderBase {
public:
  CFileReaderBase() = default;
  CFileReaderBase(const std::wstring& FileName);
  void open(const std::wstring& FileName);
  void close();
  bool isOpen() const;
protected:
  ~CFileReaderBase() = default;
  boost::filesystem::ifstream File_;
  //std::ifstream File_;
};
//---------------------------------------------------------------------------
// Declaration of CFileReaderPODTypes
//---------------------------------------------------------------------------

class CFileReaderPODTypes : public CFileReaderBase {
  using CBase = CFileReaderBase;
public:
  using CBase::CBase;

  // TO DO
  // MUST BE protected otherwise there is no guaranty that the header works
  template<class TPODType>
  inline void readPOD(TPODType* pData);

protected:
  ~CFileReaderPODTypes() = default;
};
//---------------------------------------------------------------------------
// Declaration of CFileReader
//---------------------------------------------------------------------------

class CFileReader : public CFileReaderPODTypes {
  using CBase = CFileReaderPODTypes;
public:
  using CBase::CBase;

  inline void readHeader();

  inline CFileReader& operator>>(bool& value);
  inline CFileReader& operator>>(short& value);
  inline CFileReader& operator>>(unsigned short& value);
  inline CFileReader& operator>>(int& value);
  inline CFileReader& operator>>(unsigned int& value);
  inline CFileReader& operator>>(long& value);
  inline CFileReader& operator>>(unsigned long& value);
  inline CFileReader& operator>>(long long& value);
  inline CFileReader& operator>>(unsigned long long& value);
  inline CFileReader& operator>>(float& value);
  inline CFileReader& operator>>(double& value);
  inline CFileReader& operator>>(long double& value);
  inline CFileReader& operator>>(char& value);
  inline CFileReader& operator>>(unsigned char& value);
  inline CFileReader& operator>>(wchar_t& value);
  //inline CFileReader& operator>>(void*& value);

  inline CFileReader& operator>>(std::string& String);
  inline CFileReader& operator>>(std::wstring& String);
  template<class TType1, class TType2>
  inline CFileReader& operator>>(std::pair<TType1, TType2>& Pair);
  template<class TType>
  inline CFileReader& operator>>(std::vector<TType>& Vector);
  template<class TType>
  inline CFileReader& operator>>(std::deque<TType>& Deque);
  template<class TType>
  inline CFileReader& operator>>(std::list<TType>& List);
  template<class TType, size_t TSize>
  inline CFileReader& operator>>(std::array<TType, TSize>& Array);
  template<class TKey, class TType, class TCompare>
  inline CFileReader& operator>>(std::map<TKey, TType, TCompare>& Map);
  template<class TType, class TContainer>
  inline CFileReader& operator>>(std::queue<TType, TContainer>& Queue);
  template<class TType, class TContainer, class TCompare>
  inline CFileReader& operator>>(
                        std::priority_queue<TType,
                                            TContainer,
                                            TCompare>& PriorityQueue);
  // TO DO
  // std::forward_list
  // std::stack
  // std::set
  // std::unordered_map
  // std::unordered_set
private:
  template<class TContainer>
  inline void readDirectContainer(TContainer* pContainer);
  template<class TContainer>
  inline void readAppendableContainer(TContainer* pContainer);

  inline bool isHeaderCompatible(const CFileHeader& FileHeader) const;
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CFileReaderPODTypes
//---------------------------------------------------------------------------

template<class TPODType>
void CFileReaderPODTypes::readPOD(TPODType* pData) {
  constexpr std::streamsize BlockSize = sizeof(TPODType) / sizeof(char);
  static_assert(sizeof(TPODType) % sizeof(char) == 0,
                "The type is not proportional to char size");
  File_.read(reinterpret_cast<char*>(pData), BlockSize);
}
//---------------------------------------------------------------------------
// Definition of CFileReader
//---------------------------------------------------------------------------

void CFileReader::readHeader() {
  CFileHeader tmpFileHeader;
  *this >> tmpFileHeader;
  if(!isHeaderCompatible(tmpFileHeader))
    throw std::exception ("Incompatible File Header\n");
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(bool& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(short& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned short& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(int& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned int& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(long& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned long& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(long long& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned long long& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(float& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(double& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(long double& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(char& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(unsigned char& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(wchar_t& value) {
  CBase::readPOD(&value);
  return *this;
}
//---------------------------------------------------------------------------

//CFileReader& CFileReader::operator>>(void*& value) {
//  CBase::read(&value);
//  return *this;
//}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(std::string& String) {
  readDirectContainer(&String);
  return *this;
}
//---------------------------------------------------------------------------

CFileReader& CFileReader::operator>>(std::wstring& String) {
  readDirectContainer(&String);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType1, class TType2>
CFileReader& CFileReader::operator>>(std::pair<TType1, TType2>& Pair) {
  *this >> Pair.first;
  *this >> Pair.second;
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
CFileReader& CFileReader::operator>>(std::vector<TType>& Vector) {
  readDirectContainer(&Vector);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
CFileReader& CFileReader::operator>>(std::deque<TType>& Deque) {
  readDirectContainer(&Deque);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
CFileReader& CFileReader::operator>>(std::list<TType>& List) {
  readAppendableContainer(&List);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType, size_t TSize>
CFileReader& CFileReader::operator>>(std::array<TType, TSize>& Array) {
  for(auto& element : Array)
    *this >> element;
  return *this;
}
//---------------------------------------------------------------------------

template<class TKey, class TType, class TCompare>
CFileReader& CFileReader::operator>>(std::map<TKey, TType, TCompare>& Map) {
  typename std::map<TKey, TType, TCompare>::size_type size;
  *this >> size;
  Map.clear();
  using CKey = typename std::remove_const<TKey>::type;
  using CType = typename std::remove_const<TType>::type;
  std::pair<CKey, CType> element;
  for (auto index = 0; index < size; ++index) {
    *this >> element;
    Map.insert(std::move(element));
  }
  return *this;
}
//---------------------------------------------------------------------------

template<class TType, class TContainer>
CFileReader& CFileReader::operator>>(std::queue<TType, TContainer>& Queue) {
  typename std::queue<TType, TContainer>::size_type size;
  *this >> size;
  typename std::queue<TType, TContainer> tmpQueue;
  typename std::remove_const<TType>::type element;
  for (auto index = 0; index < size; ++index) {
    *this >> element;
    tmpQueue.push(std::move(element));
  }
  Queue = std::move(tmpQueue);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType, class TContainer, class TCompare>
CFileReader& CFileReader::operator>>(
                        std::priority_queue<TType,
                                            TContainer,
                                            TCompare>& PriorityQueue) {
  typename std::priority_queue< TType,
                                TContainer,
                                TCompare>::size_type size;
  *this >> size;
  typename std::priority_queue< TType,
                                TContainer,
                                TCompare> tmpPriorityQueue;
  typename std::remove_const<TType>::type element;
  for (auto index = 0; index < size; ++index) {
    *this >> element;
    tmpPriorityQueue.push(std::move(element));
  }
  PriorityQueue = std::move(tmpPriorityQueue);
  return *this;
}
//---------------------------------------------------------------------------

template<class TContainer>
void CFileReader::readDirectContainer(TContainer* pContainer) {
  typename TContainer::size_type size;
  *this >> size;
  pContainer->resize(size);
  for(auto& element : *pContainer)
    *this >> element;
}
//---------------------------------------------------------------------------

template<class TContainer>
void CFileReader::readAppendableContainer(TContainer* pContainer) {
  typename TContainer::size_type size;
  *this >> size;
  pContainer->clear();
  typename std::remove_const<typename TContainer::value_type>::type element;
  for (auto index = 0; index < size; ++index) {
    *this >> element;
    pContainer->push_back(std::move(element));
  }
}
//---------------------------------------------------------------------------

bool CFileReader::isHeaderCompatible(const CFileHeader& FileHeader) const {
  CFileHeader DefaultHeader;
  DefaultHeader.setToDefault();
  if (FileHeader.size() > DefaultHeader.size())
    return false;
  for (auto index = 0; index < FileHeader.size(); ++index)
    if (FileHeader[index] != DefaultHeader[index])
      return false;
  return true;
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
