//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitListViewWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {
//---------------------------------------------------------------------------
// Definition of CListViewWriterBase
//---------------------------------------------------------------------------

CListViewWriterBase::CListViewWriterBase(TListView* ListView)
  : pListView(ListView) {
}
//---------------------------------------------------------------------------

bool CListViewWriterBase::isDefined() const {
  return pListView != nullptr;
}
//---------------------------------------------------------------------------

void CListViewWriterBase::setListViewWriter(TListView* ListView) {
  assert(!isDefined());
  pListView = ListView;
  assert(isDefined());
}
//---------------------------------------------------------------------------

void CListViewWriterBase::Clear() {
  if(!isDefined())
    return;
  pListView->Items->BeginUpdate();
  pListView->Items->Clear();
  pListView->Items->EndUpdate();
}
//---------------------------------------------------------------------------
// Definition of CListViewWriter2
//---------------------------------------------------------------------------

CListViewWriter2::CListViewWriter2(TListView* ListView)
  : CListViewWriterBase(ListView) {
  assert(!isDefined() || pListView->Columns->Count == 2);
}
//---------------------------------------------------------------------------

void CListViewWriter2::addEntry(const UnicodeString& FirstEntry,
                                const UnicodeString& SecondEntry) {
  auto Item = pListView->Items->Add();
  Item->Caption = FirstEntry;
  Item->SubItems->Add(SecondEntry);
}
//---------------------------------------------------------------------------
// Definition of CListViewWriter4
//---------------------------------------------------------------------------

CListViewWriter4::CListViewWriter4(TListView* ListView)
  : CListViewWriterBase(ListView) {
  assert(!isDefined() || pListView->Columns->Count == 4);
}
//---------------------------------------------------------------------------

void CListViewWriter4::addEntry(const UnicodeString& FirstEntry,
                                const UnicodeString& SecondEntry,
                                const UnicodeString& ThirdEntry,
                                const UnicodeString& FourthEntry) {
  auto Item = pListView->Items->Add();
  Item->Caption = FirstEntry;
  Item->SubItems->Add(SecondEntry);
  Item->SubItems->Add(ThirdEntry);
  Item->SubItems->Add(FourthEntry);
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
