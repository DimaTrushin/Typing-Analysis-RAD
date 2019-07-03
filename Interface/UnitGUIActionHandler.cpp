//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "UnitGUIActionHandler.h"
#include "../UnitPerformanceLogger.h"
//---------------------------------------------------------------------------

namespace NSApplication {
//---------------------------------------------------------------------------
// Global Variable
//---------------------------------------------------------------------------

extern CThreadIDLogger ThreadIDLogger;
//---------------------------------------------------------------------------
namespace NSKernel {

extern CMaster Master;
//---------------------------------------------------------------------------
} // NSKernel
//---------------------------------------------------------------------------

namespace NSKeyboard {

extern CKeyboardHandler KeyboardHandler;
//---------------------------------------------------------------------------
} // NSKeyboard
//---------------------------------------------------------------------------

namespace NSInterface {
//---------------------------------------------------------------------------
// Global Variable
//---------------------------------------------------------------------------

extern CGUIHandler GUIHandler;

//---------------------------------------------------------------------------
// Definition of CGUIActionHandler
//---------------------------------------------------------------------------

void CGUIActionHandler::onTreeViewDoubleClick() {
  ThreadIDLogger.Log(L"onTreeViewDoubleClick");
  CPerformanceLogger Performance;
  auto actionLogger = Performance->LogBlock(L"onTreeViewDoubleClick");
  using NSKernel::Master;
  TTreeNode* HitNode;
  if (GUIHandler.TreeViewWriter.isHitOnSessionItem(&HitNode)) {
    Master.makeCurrentAnalysisData(*GUIHandler.
                                    TreeViewWriter.
                                      getSelectedSession(HitNode));
    Master.setCurrentMode();
    if (Master.isCurrentAnalysisDataDefined()) {
      Master.makeCurrentKlavogramma();
      Master.outputCurrentAnalysisDataOnGUI();
      Master.outputCurrentKlavogrammaOnGUI();
    }
  }
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onTextModeChange() {
  ThreadIDLogger.Log(L"onTextModeChange");
  CPerformanceLogger Performance;
  auto actionLogger = Performance->LogBlock(L"onTextModeChange");
  using NSKernel::Master;
  Master.setCurrentMode();
  if (Master.isCurrentAnalysisDataDefined()) {
    Master.makeCurrentKlavogramma();
    Master.outputCurrentAnalysisDataOnGUI();
    Master.outputCurrentKlavogrammaOnGUI();
  }
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onAnalysisTypeChange() {
  ThreadIDLogger.Log(L"onAnalysisTypeChange");
  NSKernel::Master.setCurrentAnalysisType();
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onDensityComputeClick() {
  ThreadIDLogger.Log(L"onDensityComputeClick");
  using NSKernel::Master;
  CPerformanceLogger Performance;
  Performance->Log( &Master,
                    L"makeCurrentSpeedApproximationData")->
                                    makeCurrentSpeedApproximationData();
  Performance->Log( &Master,
                    L"outputCurrentSpeedApproximationDataOnGUI")->
                            outputCurrentSpeedApproximationDataOnGUI();
  Performance->Log( &Master,
                    L"outputCurrentSpeedHistogramOnGUI")->
                                    outputCurrentSpeedHistogramOnGUI();
  Performance->Log( &Master,
                    L"outputStableZonesStatisticsOnGUI")->
                                    outputStableZonesStatisticsOnGUI();
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onMainPlotVisibilityChange() {
  ThreadIDLogger.Log(L"onMainPlotVisibilityChange");
  GUIHandler.SpeedStableZonesPlotter.changeVisibility();
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onSpeedTrackBarChange() {
  ThreadIDLogger.Log(L"onSpeedTrackBarChange");
  using NSKernel::Master;
  Master.setCurrentSpeedHistogramChunk();
  Master.outputCurrentSpeedHistogramOnGUI();
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onSpeedTrackBarKeyPress(System::WideChar &Key) {
  ThreadIDLogger.Log(L"onSpeedTrackBarKeyPress");
  if (Key == L' ')
    GUIHandler.SpeedChunkHandler.setToDefaultPosition();
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onFileSaving(const std::wstring& FileName) {
  ThreadIDLogger.Log(L"onFileSaving");
  try {
    CPerformanceLogger Performance;
    auto actionLogger = Performance->LogBlock(L"onFileSaving");
    NSKernel::Master.writeUserEnvironmentToFile(FileName);
  } catch(const std::exception& exeption) {
    std::string Message = "Cannot write to the file!\n";
    Message += exeption.what();
    ShowMessage(Message.c_str());
  } catch(...) {
    ShowMessage("Cannot write to the file!\nUnknown issue!");
  }
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onFileLoading(const std::wstring& FileName) {
  ThreadIDLogger.Log(L"onFileLoading");
  try {
    CPerformanceLogger Performance;
    auto actionLogger = Performance->LogBlock(L"onFileLoading");
    NSKernel::Master.readUserEnvironmentFromFile(FileName);
  } catch(const std::exception& exeption) {
    std::string Message = "Cannot read the file!\n";
    Message += exeption.what();
    ShowMessage(Message.c_str());
  } catch(...) {
    ShowMessage("Cannot read the file!\nUnknown issue!");
  }
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onApplicatinActivate() {
  ThreadIDLogger.Log(L"onApplicatinActivate");
  NSKeyboard::KeyboardHandler.DeActivate();
  NSKeyboard::KeyboardHandler.transferDataToUser();
}
//---------------------------------------------------------------------------

void CGUIActionHandler::onApplicationDeactivate() {
  ThreadIDLogger.Log(L"onApplicationDeactivate");
  NSKeyboard::KeyboardHandler.Activate();
}
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#pragma package(smart_init)
