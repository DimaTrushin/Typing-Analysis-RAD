//---------------------------------------------------------------------------

#ifndef UnitGUIActionHandlerH
#define UnitGUIActionHandlerH
//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "../Keyboard/UnitKeyboardHandler.h"
//---------------------------------------------------------------------------

namespace NSApplication {
namespace NSInterface {

//---------------------------------------------------------------------------
// Declaration of CGUIActionHandler
//---------------------------------------------------------------------------

class CGUIActionHandler {
public:
  static void onTreeViewDoubleClick();
  static void onTextModeChange();
  static void onAnalysisTypeChange();
  static void onDensityComputeClick();
  static void onMainPlotVisibilityChange();
  static void onSpeedTrackBarChange();
  static void onSpeedTrackBarKeyPress(System::WideChar &Key);
  static void onFileSaving(const std::wstring& FileName);
  static void onFileLoading(const std::wstring& FileName);
  static void onApplicatinActivate();
  static void onApplicationDeactivate();
};
//---------------------------------------------------------------------------
} // NSInterface
//---------------------------------------------------------------------------
} // NSApplication
//---------------------------------------------------------------------------
#endif
