//---------------------------------------------------------------------------

#ifndef UnitFileWriterH
#define UnitFileWriterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <string>
//#include <vector>
#include <deque>
#include <list>
#include <array>
#include <map>
#include <queue>
#include "UnitFileHeader.h"
#include <boost/filesystem/fstream.hpp>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Declaration of CFileWriterBase
//---------------------------------------------------------------------------

class CFileWriterBase {
public:
  CFileWriterBase() = default;
  CFileWriterBase(const std::wstring& FileName);
  void open(const std::wstring& FileName);
  void close();
  bool isOpen() const;
protected:
  ~CFileWriterBase() = default;
  boost::filesystem::ofstream File_;
  //std::ofstream File_;
};
//---------------------------------------------------------------------------
// Declaration of CFileWriterPODTypes
//---------------------------------------------------------------------------

class CFileWriterPODTypes : public CFileWriterBase {
  using CBase = CFileWriterBase;
public:
  using CBase::CBase;

  // TO DO
  // MUST BE protected otherwise there is no guaranty that the header works
  template<class TPODType>
  inline void writePOD(const TPODType& Data);
protected:
  ~CFileWriterPODTypes() = default;
};
//---------------------------------------------------------------------------
// Declaration of CFileWriter
//---------------------------------------------------------------------------

class CFileWriter : public CFileWriterPODTypes {
  using CBase = CFileWriterPODTypes;
public:
  using CBase::CBase;

  inline void writeHeader();

  inline CFileWriter& operator<<(bool value);
  inline CFileWriter& operator<<(short value);
  inline CFileWriter& operator<<(unsigned short value);
  inline CFileWriter& operator<<(int value);
  inline CFileWriter& operator<<(unsigned int value);
  inline CFileWriter& operator<<(long value);
  inline CFileWriter& operator<<(unsigned long value);
  inline CFileWriter& operator<<(long long value);
  inline CFileWriter& operator<<(unsigned long long value);
  inline CFileWriter& operator<<(float value);
  inline CFileWriter& operator<<(double value);
  inline CFileWriter& operator<<(long double value);
  inline CFileWriter& operator<<(char value);
  inline CFileWriter& operator<<(unsigned char value);
  inline CFileWriter& operator<<(wchar_t value);
  //inline CFileWriter& operator<<(void* value);

  inline CFileWriter& operator<<(const std::string& String);
  inline CFileWriter& operator<<(const std::wstring& String);
  template<class TType1, class TType2>
  inline CFileWriter& operator<<(const std::pair<TType1, TType2>& Pair);
  template<class TType>
  inline CFileWriter& operator<<(const std::vector<TType>& Vector);
  template<class TType>
  inline CFileWriter& operator<<(const std::deque<TType>& Deque);
  template<class TType>
  inline CFileWriter& operator<<(const std::list<TType>& List);
  template<class TType, size_t TSize>
  inline CFileWriter& operator<<(const std::array<TType, TSize>& Array);
  template<class TKey, class TType, class TCompare>
  inline CFileWriter& operator<<(const std::map<TKey, TType, TCompare>& Map);
  template<class TType, class TContainer>
  inline CFileWriter& operator<<(const std::queue<TType, TContainer>& Queue);
  template<class TType, class TContainer, class TCompare>
  inline CFileWriter& operator<<(
                  const std::priority_queue<TType,
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
  inline void writeContainer(const TContainer& Container);
};
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSLibrary {
//---------------------------------------------------------------------------
// Definition of CFileWriterPODTypes
//---------------------------------------------------------------------------

template<class TPODType>
void CFileWriterPODTypes::writePOD(const TPODType& Data) {
  constexpr std::streamsize BlockSize = sizeof(TPODType) / sizeof(char);
  static_assert(sizeof(TPODType) % sizeof(char) == 0,
                "The type is not proportional to char size");
  File_.write(reinterpret_cast<const char*>(&Data), BlockSize);
}
//---------------------------------------------------------------------------
// Definition of CFileWriter
//---------------------------------------------------------------------------

void CFileWriter::writeHeader() {
  CFileHeader FileHeader;
  FileHeader.setToDefault();
  *this << FileHeader;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(bool value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(short value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(unsigned short value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(int value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(unsigned int value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(long value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(unsigned long value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(long long value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(unsigned long long value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(float value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(double value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(long double value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(char value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(unsigned char value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(wchar_t value) {
  CBase::writePOD(value);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(const std::string& String) {
  writeContainer(String);
  return *this;
}
//---------------------------------------------------------------------------

CFileWriter& CFileWriter::operator<<(const std::wstring& String) {
  writeContainer(String);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType1, class TType2>
CFileWriter& CFileWriter::operator<<(const std::pair<TType1, TType2>& Pair) {
  *this << Pair.first;
  *this << Pair.second;
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
CFileWriter& CFileWriter::operator<<(const std::vector<TType>& Vector) {
  writeContainer(Vector);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
CFileWriter& CFileWriter::operator<<(const std::deque<TType>& Deque) {
  writeContainer(Deque);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType>
CFileWriter& CFileWriter::operator<<(const std::list<TType>& List) {
  writeContainer(List);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType, size_t TSize>
CFileWriter& CFileWriter::operator<<(const std::array<TType, TSize>& Array) {
  for (const auto& element : Array)
    *this << element;
  return *this;
}
//---------------------------------------------------------------------------

template<class TKey, class TType, class TCompare>
CFileWriter& CFileWriter::operator<<(
                                  const std::map<TKey, TType, TCompare>& Map) {
  writeContainer(Map);
  return *this;
}
//---------------------------------------------------------------------------

template<class TType, class TContainer>
CFileWriter& CFileWriter::operator<<(
                                  const std::queue<TType, TContainer>& Queue) {
  *this << Queue.size();
  auto tmpQueue = Queue;
  while(!tmpQueue.empty()) {
    *this << tmpQueue.front();
    tmpQueue.pop();
  }
  return *this;
}
//---------------------------------------------------------------------------

template<class TType, class TContainer, class TCompare>
CFileWriter& CFileWriter::operator<<(
                  const std::priority_queue<TType,
                                            TContainer,
                                            TCompare>& PriorityQueue) {
  *this << PriorityQueue.size();
  auto tmpPriorityQueue = PriorityQueue;
  while(!tmpPriorityQueue.empty()) {
    *this << tmpPriorityQueue.top();
    tmpPriorityQueue.pop();
  }
  return *this;
}
//---------------------------------------------------------------------------

template<class TContainer>
void CFileWriter::writeContainer(const TContainer& Container) {
  *this << Container.size();
  for (const auto& element : Container)
    *this << element;
}
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
