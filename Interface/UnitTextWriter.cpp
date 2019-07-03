//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitTextWriter.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Definitions of CTextWriter
//---------------------------------------------------------------------------

CTextWriter::CTextWriter(TRichEdit* pRichEdit)
  : pRichEditToPrint(pRichEdit) {
}
//---------------------------------------------------------------------------

bool CTextWriter::isRichEditDefined() const {
  return pRichEditToPrint != nullptr;
}
//---------------------------------------------------------------------------

void CTextWriter::setRichEdit(TRichEdit* pRichEdit) {
  pRichEditToPrint = pRichEdit;
}
//---------------------------------------------------------------------------

void CTextWriter::Clear() {
  pRichEditToPrint->Clear();
}
//---------------------------------------------------------------------------

void CTextWriter::printPlaneText(const UnicodeString& Text) {
  moveSelectedToEnd();
  SetSelectedFormat(CStringFormat());
  pRichEditToPrint->SelText = Text;
}
//---------------------------------------------------------------------------

void CTextWriter::printFormattedString(const CFormattedString& Text) {
  moveSelectedToEnd();
  for (const auto& TextPair : Text)
    PrintPair(TextPair);
}
//---------------------------------------------------------------------------

void CTextWriter::newLine() {
  SetSelectedFormat(CStringFormat());
  pRichEditToPrint->SelText = L"\n";
}
//---------------------------------------------------------------------------

void CTextWriter::PrintPair(const CTextWithFormat& TextPair) const {
  SetSelectedFormat(TextPair.first);
  pRichEditToPrint->SelText = TextPair.second.c_str();
}
//---------------------------------------------------------------------------

void CTextWriter::SetSelectedFormat(const CStringFormat& TextFormat) const {
  CHARFORMAT2W CharFormat;
  // Инициализируем размер
  CharFormat.cbSize = sizeof(CHARFORMAT2W);
  // Заполняем структуру информацией о цвете текста и фона
  CharFormat.dwMask = CFM_COLOR | CFM_BACKCOLOR;
  CharFormat.dwEffects = 0; // отключаем CFE_AUTOCOLOR
  CharFormat.crTextColor = TextFormat.TextColor;
  CharFormat.crBackColor = TextFormat.BackColor;
  // Отправляем сообщение в RichEdit о смене стиля
  SendMessage(pRichEditToPrint->Handle,
              EM_SETCHARFORMAT,
              static_cast<WPARAM>(SCF_SELECTION),
              reinterpret_cast<LPARAM>(&CharFormat));
}
//---------------------------------------------------------------------------

void CTextWriter::moveSelectedToEnd() {
  pRichEditToPrint->SelStart = pRichEditToPrint->GetTextLen();
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
