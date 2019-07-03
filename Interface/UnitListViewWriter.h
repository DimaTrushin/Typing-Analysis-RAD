//---------------------------------------------------------------------------

#ifndef UnitListViewWriterH
#define UnitListViewWriterH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <vcl.h>
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CListViewWriterBase
//---------------------------------------------------------------------------

class CListViewWriterBase {
public:
  CListViewWriterBase(TListView* ListView = nullptr);

  bool isDefined() const;
  void setListViewWriter(TListView* ListView);
  void Clear();
protected:
  TListView* pListView;
};
//---------------------------------------------------------------------------
// Declaration of CListViewWriter2
//---------------------------------------------------------------------------

class CListViewWriter2 : public CListViewWriterBase {
public:
  CListViewWriter2(TListView* ListView = nullptr);
  template<class TEntryContainer>
  void addDataContiner(const TEntryContainer& Data);
protected:
  void addEntry(const UnicodeString& FirstEntry,
                const UnicodeString& SecondEntry);
};
//---------------------------------------------------------------------------
// Declaration of CListViewWriter4
//---------------------------------------------------------------------------

class CListViewWriter4 : public CListViewWriterBase {
public:
  CListViewWriter4(TListView* ListView = nullptr);
  template<class TEntryContainer>
  void addDataContiner(const TEntryContainer& Data);
protected:
  void addEntry(const UnicodeString& FirstEntry,
                const UnicodeString& SecondEntry,
                const UnicodeString& ThirdEntry,
                const UnicodeString& FourthEntry);
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Definition of CListViewWriter2
//---------------------------------------------------------------------------

template<class TEntryContainer>
void
CListViewWriter2::addDataContiner(const TEntryContainer& Data) {
  pListView->Items->BeginUpdate();
  for(const auto& datum : Data)
    addEntry(datum[0], datum[1]);
  pListView->Items->EndUpdate();
}
//---------------------------------------------------------------------------
// Definition of CListViewWriter4
//---------------------------------------------------------------------------

template<class TEntryContainer>
void CListViewWriter4::addDataContiner(const TEntryContainer& Data) {
  pListView->Items->BeginUpdate();
  for(const auto& datum : Data)
    addEntry(datum[0], datum[1], datum[2], datum[3]);
  pListView->Items->EndUpdate();
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
