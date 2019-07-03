//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// GLobal Variables
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CThreadIDLogger ThreadIDLogger;
//---------------------------------------------------------------------------

namespace NSInterface {
//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------

extern CGUIHandler GUIHandler;
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------

TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
  : TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Panel3Resize(TObject *Sender) {
  RadioGroup2->Width = Panel3->ClientWidth / 2;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioGroup1Click(TObject *Sender) {
  if (RadioGroup1->ItemIndex == 0) {
    Panel3->Visible = false;
    Panel10->Visible = false;
  } else {
    Panel3->Visible = true;
    Panel10->Visible = true;
  }
  NSApplication::NSInterface::CGUIActionHandler::onTextModeChange();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender) {
  // Here I do not care about access of other threads since it happens
  // before the Application Run loop
  // TO DO
  // Move all of these to ApplicationStarter?
  using NSApplication::NSInterface::GUIHandler;
  GUIHandler.TextWriter.setRichEdit(RichEdit1);
  GUIHandler.LogWriter.setRichEdit(RichEdit3);
  GUIHandler.StateLogWriter.setRichEdit(RichEdit4);
  GUIHandler.ThreadLogWriter.setRichEdit(RichEdit2);
  GUIHandler.LogWriter2.setRichEdit(RichEdit5);
  GUIHandler.SeanceStatistics.setListViewWriter(ListView1);
  GUIHandler.StableZonesStatistics.setListViewWriter(ListView2);
  GUIHandler.TextModeReader.setModeGroups(RadioGroup1,
                                          RadioGroup2,
                                          RadioGroup3);
  GUIHandler.AnalysisTypeReader.setAnalysisTypeGroup(RadioGroup4);
  GUIHandler.TreeViewWriter.setTreeViewWriter(TreeView1);
  GUIHandler.SpeedHistogramPlotter.setPlotterBase(Series1);
  GUIHandler.SpeedChunkHandler.setHandler(TrackBar1);
  GUIHandler.SpeedDerivativePlotterUniform.setPlotterBase(Series2);
  GUIHandler.SpeedPlotterUniform.setPlotterBase(Series3);
  GUIHandler.SpeedDerivativePlotter.setPlotterBase(Series4);
  GUIHandler.SpeedPlotter.setPlotterBase(Series5);
  GUIHandler.SpeedStableZonesPlotter.setAreaPlotter(Chart2, Series5);
  GUIHandler.StandardSpeedDerivativePlotter.setPlotter(Series6);
  GUIHandler.StandardSpeedPlotter.setPlotter(Series7);
  GUIHandler.KlavogrammaPlotter.setChart(Chart1);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TreeView1DblClick(TObject *Sender) {
  NSApplication::NSInterface::CGUIActionHandler::onTreeViewDoubleClick();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioGroup2Click(TObject *Sender) {
  NSApplication::NSInterface::CGUIActionHandler::onTextModeChange();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioGroup3Click(TObject *Sender) {
  NSApplication::NSInterface::CGUIActionHandler::onTextModeChange();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioGroup4Click(TObject *Sender) {
  NSApplication::NSInterface::CGUIActionHandler::onAnalysisTypeChange();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton1Click(TObject *Sender) {
  NSApplication::NSInterface::CGUIActionHandler::onDensityComputeClick();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Chart2BeforeDrawSeries(TObject *Sender) {
  NSApplication::NSInterface::CGUIActionHandler::onMainPlotVisibilityChange();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrackBar1Change(TObject *Sender) {
  NSApplication::NSInterface::CGUIActionHandler::onSpeedTrackBarChange();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrackBar1KeyPress(
                                  TObject *Sender, System::WideChar &Key) {
  NSApplication::NSInterface::CGUIActionHandler::onSpeedTrackBarKeyPress(Key);
  // If I directly lock here, a mutex rises an exception.
  // std::system_error exception arises.
  // It is interesting
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Save1Click(TObject *Sender) {
  if (SaveDialog1->Execute())
    NSApplication::
      NSInterface::
        CGUIActionHandler::onFileSaving(SaveDialog1->FileName.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Load1Click(TObject *Sender) {
  if (OpenDialog1->Execute())
    NSApplication::
      NSInterface::
        CGUIActionHandler::onFileLoading(OpenDialog1->FileName.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ApplicationEvents1Activate(TObject *Sender) {
  NSApplication::
    NSInterface::
      CGUIActionHandler::onApplicatinActivate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ApplicationEvents1Deactivate(TObject *Sender) {
  NSApplication::
    NSInterface::
      CGUIActionHandler::onApplicationDeactivate();
}
//---------------------------------------------------------------------------


