//---------------------------------------------------------------------------

#ifndef UnitMainFormH
#define UnitMainFormH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Buttons.hpp>
#include "UnitGUIActionHandler.h"
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------

class TMainForm : public TForm {
__published:	// IDE-managed Components
  TStatusBar *StatusBar1;
  TPanel *Panel1;
  TSplitter *Splitter1;
  TPanel *Panel2;
  TRadioGroup *RadioGroup1;
  TPanel *Panel3;
  TRadioGroup *RadioGroup2;
  TRadioGroup *RadioGroup3;
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TTabSheet *TabSheet2;
  TPanel *Panel4;
  TSplitter *Splitter2;
  TPanel *Panel5;
  TRichEdit *RichEdit1;
  TChart *Chart1;
  TTreeView *TreeView1;
  TPanel *Panel6;
  TSplitter *Splitter3;
  TPanel *Panel7;
  TChart *Chart2;
  TPanel *Panel8;
  TSplitter *Splitter4;
  TPanel *Panel9;
  TRadioGroup *RadioGroup4;
  TSpeedButton *SpeedButton1;
  TFastLineSeries *Series1;
  TFastLineSeries *Series2;
  TFastLineSeries *Series3;
  TFastLineSeries *Series4;
  TFastLineSeries *Series5;
  TFastLineSeries *Series6;
  TFastLineSeries *Series7;
  TPanel *Panel10;
  TTrackBar *TrackBar1;
  TTabSheet *TabSheet3;
  TRichEdit *RichEdit3;
  TListView *ListView1;
  TListView *ListView2;
  TSplitter *Splitter5;
  TSplitter *Splitter6;
  TTabSheet *TabSheet4;
  TRichEdit *RichEdit2;
  TTabSheet *TabSheet5;
  TRichEdit *RichEdit4;
  TMainMenu *MainMenu1;
  TMenuItem *File1;
  TMenuItem *Save1;
  TMenuItem *Load1;
  TSaveDialog *SaveDialog1;
  TOpenDialog *OpenDialog1;
  TApplicationEvents *ApplicationEvents1;
  TTabSheet *TabSheet6;
  TRichEdit *RichEdit5;
  void __fastcall Panel3Resize(TObject *Sender);
  void __fastcall RadioGroup1Click(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall TreeView1DblClick(TObject *Sender);
  void __fastcall RadioGroup2Click(TObject *Sender);
  void __fastcall RadioGroup3Click(TObject *Sender);
  void __fastcall RadioGroup4Click(TObject *Sender);
  void __fastcall SpeedButton1Click(TObject *Sender);
  void __fastcall Chart2BeforeDrawSeries(TObject *Sender);
  void __fastcall TrackBar1Change(TObject *Sender);
  void __fastcall TrackBar1KeyPress(TObject *Sender, System::WideChar &Key);
  void __fastcall Save1Click(TObject *Sender);
  void __fastcall Load1Click(TObject *Sender);
  void __fastcall ApplicationEvents1Activate(TObject *Sender);
  void __fastcall ApplicationEvents1Deactivate(TObject *Sender);

private:	// User declarations
public:		// User declarations
  __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
