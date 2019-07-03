//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitContainerWithCommonData.h"
//---------------------------------------------------------------------------
//#include <vcl.h>

namespace NSApplication {
namespace NSLibrary {
/*
class CTester {
public:
  using MyDeque = CContainerWithCommonData<int, char>;
  CTester() {
    MyDeque Deq;
    Deq.push_back(1, 'a');
    Deq.push_back(2, 'a');
    Deq.push_back(3, 'b');
    Deq.push_back(4, 'b');
    Deq.push_back(5, 'a');
    Deq.push_back(6, 'c');
    UnicodeString Text = L"";
    for (const auto& element : Deq) {
      Text += L"elem = ";
      Text += element.Element;
      Text += L" com = ";
      Text += element.CommonData;
      Text += L'\n';
    }
    for (auto iter = Deq.cbegin(); iter != Deq.cend(); iter+=1) {
      Text += L"elem = ";
      Text += (*iter).Element;
      Text += L" com = ";
      Text += (*iter).CommonData;
      Text += L'\n';
    }
    ShowMessage(Text.c_str());
  }
};
CTester Tester;
*/
//---------------------------------------------------------------------------
} // NSLibrary
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
