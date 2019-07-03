object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 365
  ClientWidth = 589
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 185
    Top = 0
    Height = 346
    ExplicitLeft = 208
    ExplicitTop = 168
    ExplicitHeight = 100
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 346
    Width = 589
    Height = 19
    Panels = <>
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 346
    Align = alLeft
    TabOrder = 1
    object RadioGroup1: TRadioGroup
      Left = 1
      Top = 1
      Width = 183
      Height = 64
      Align = alTop
      Caption = 'Text Mode'
      ItemIndex = 1
      Items.Strings = (
        'Raw'
        'Full'
        'Printed')
      TabOrder = 0
      OnClick = RadioGroup1Click
    end
    object Panel3: TPanel
      Left = 1
      Top = 65
      Width = 183
      Height = 64
      Align = alTop
      TabOrder = 1
      OnResize = Panel3Resize
      object RadioGroup2: TRadioGroup
        Left = 1
        Top = 1
        Width = 90
        Height = 62
        Align = alLeft
        Caption = 'Shifts'
        ItemIndex = 1
        Items.Strings = (
          'Non'
          'All'
          'Essential')
        TabOrder = 0
        OnClick = RadioGroup2Click
      end
      object RadioGroup3: TRadioGroup
        Left = 91
        Top = 1
        Width = 91
        Height = 62
        Align = alClient
        Caption = 'Capslocks'
        ItemIndex = 1
        Items.Strings = (
          'Non'
          'All'
          'Essential')
        TabOrder = 1
        OnClick = RadioGroup3Click
      end
    end
    object TreeView1: TTreeView
      Left = 1
      Top = 129
      Width = 183
      Height = 216
      Align = alClient
      Indent = 19
      ReadOnly = True
      TabOrder = 2
      OnDblClick = TreeView1DblClick
      Items.NodeData = {
        03010000002A0000000000000000000000FFFFFFFFFFFFFFFF00000000000000
        000000000001065300650061006E0063006500}
    end
  end
  object Panel2: TPanel
    Left = 188
    Top = 0
    Width = 401
    Height = 346
    Align = alClient
    TabOrder = 2
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 399
      Height = 344
      ActivePage = TabSheet1
      Align = alClient
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'Text'
        object Splitter2: TSplitter
          Left = 0
          Top = 173
          Width = 391
          Height = 3
          Cursor = crVSplit
          Align = alBottom
          ExplicitTop = 198
        end
        object Panel4: TPanel
          Left = 0
          Top = 0
          Width = 391
          Height = 173
          Align = alClient
          TabOrder = 0
          object Splitter5: TSplitter
            Left = 1
            Top = 1
            Height = 171
            ExplicitLeft = 312
            ExplicitTop = 80
            ExplicitHeight = 100
          end
          object Splitter6: TSplitter
            Left = 247
            Top = 1
            Height = 171
            Align = alRight
            ExplicitLeft = 224
            ExplicitTop = 80
            ExplicitHeight = 100
          end
          object RichEdit1: TRichEdit
            Left = 4
            Top = 1
            Width = 243
            Height = 171
            Align = alClient
            Color = clMoneyGreen
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -19
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            ScrollBars = ssVertical
            TabOrder = 0
            Zoom = 100
          end
          object ListView1: TListView
            Left = 250
            Top = 1
            Width = 140
            Height = 171
            Align = alRight
            Columns = <
              item
                AutoSize = True
                Caption = 'Data'
              end
              item
                Caption = 'Value'
                Width = 70
              end>
            FlatScrollBars = True
            GridLines = True
            ReadOnly = True
            TabOrder = 1
            ViewStyle = vsReport
          end
        end
        object Panel5: TPanel
          Left = 0
          Top = 176
          Width = 391
          Height = 140
          Align = alBottom
          TabOrder = 1
          object Chart1: TChart
            Left = 1
            Top = 1
            Width = 389
            Height = 138
            AllowPanning = pmHorizontal
            Title.Text.Strings = (
              'Klavogramma')
            BottomAxis.Automatic = False
            BottomAxis.AutomaticMaximum = False
            BottomAxis.AutomaticMinimum = False
            LeftAxis.Automatic = False
            LeftAxis.AutomaticMaximum = False
            LeftAxis.AutomaticMinimum = False
            LeftAxis.Grid.Color = clBlack
            LeftAxis.GridCentered = True
            LeftAxis.Maximum = 9.000000000000000000
            View3D = False
            Zoom.Direction = tzdHorizontal
            Align = alClient
            TabOrder = 0
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Speed'
        ImageIndex = 1
        object Splitter3: TSplitter
          Left = 0
          Top = 197
          Width = 391
          Height = 3
          Cursor = crVSplit
          Align = alBottom
          ExplicitTop = 41
          ExplicitWidth = 275
        end
        object Panel6: TPanel
          Left = 0
          Top = 0
          Width = 391
          Height = 197
          Align = alClient
          TabOrder = 0
          object Chart2: TChart
            Left = 1
            Top = 1
            Width = 389
            Height = 195
            Legend.CheckBoxes = True
            Title.Text.Strings = (
              'Speed Distribution')
            BottomAxis.Automatic = False
            BottomAxis.AutomaticMaximum = False
            BottomAxis.AutomaticMinimum = False
            BottomAxis.Maximum = 2500.000000000000000000
            BottomAxis.Title.Caption = 'Speed (symb / min)'
            BottomAxis.Title.Position = tpEnd
            LeftAxis.Title.Caption = 'Conditional Probability'
            RightAxis.Visible = False
            TopAxis.Visible = False
            View3D = False
            OnBeforeDrawSeries = Chart2BeforeDrawSeries
            Align = alClient
            TabOrder = 0
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
            object Series1: TFastLineSeries
              Legend.Text = 'Histogram'
              LegendTitle = 'Histogram'
              Active = False
              SeriesColor = 25600
              LinePen.Color = 25600
              LinePen.Width = 2
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series2: TFastLineSeries
              Legend.Text = 'Derivative Uniform'
              LegendTitle = 'Derivative Uniform'
              Active = False
              SeriesColor = 11048782
              LinePen.Color = 11048782
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series3: TFastLineSeries
              Legend.Text = 'Density Uniform'
              LegendTitle = 'Density Uniform'
              Active = False
              SeriesColor = 4227327
              LinePen.Color = 4227327
              LinePen.Width = 2
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series4: TFastLineSeries
              Legend.Text = 'Derivative'
              LegendTitle = 'Derivative'
              LinePen.Color = 11048782
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series5: TFastLineSeries
              Legend.Text = 'Density'
              LegendTitle = 'Density'
              SeriesColor = clRed
              LinePen.Color = clRed
              LinePen.Width = 2
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series6: TFastLineSeries
              Legend.Text = 'Standard Derivative'
              LegendTitle = 'Standard Derivative'
              Active = False
              SeriesColor = 8286522
              LinePen.Color = 8286522
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series7: TFastLineSeries
              Legend.Text = 'Standard Density'
              LegendTitle = 'Standard Density'
              Active = False
              LinePen.Color = 919731
              LinePen.Width = 2
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
          end
        end
        object Panel7: TPanel
          Left = 0
          Top = 200
          Width = 391
          Height = 116
          Align = alBottom
          TabOrder = 1
          object Splitter4: TSplitter
            Left = 121
            Top = 1
            Height = 114
            ExplicitLeft = 312
            ExplicitTop = 312
            ExplicitHeight = 100
          end
          object Panel8: TPanel
            Left = 1
            Top = 1
            Width = 120
            Height = 114
            Align = alLeft
            TabOrder = 0
            object SpeedButton1: TSpeedButton
              Left = 1
              Top = 56
              Width = 118
              Height = 22
              Align = alTop
              Caption = 'Compute'
              OnClick = SpeedButton1Click
              ExplicitLeft = 81
              ExplicitTop = 60
              ExplicitWidth = 23
            end
            object Panel10: TPanel
              Left = 1
              Top = 1
              Width = 118
              Height = 55
              Align = alTop
              TabOrder = 0
              object RadioGroup4: TRadioGroup
                Left = 1
                Top = 1
                Width = 116
                Height = 53
                Align = alClient
                Caption = 'Analysis Mode'
                ItemIndex = 0
                Items.Strings = (
                  'Physical'
                  'Symbolical')
                TabOrder = 0
                OnClick = RadioGroup4Click
              end
            end
            object TrackBar1: TTrackBar
              Left = 1
              Top = 78
              Width = 118
              Height = 45
              Align = alTop
              DoubleBuffered = False
              Max = 100
              Min = 1
              ParentDoubleBuffered = False
              Position = 50
              TabOrder = 1
              OnChange = TrackBar1Change
              OnKeyPress = TrackBar1KeyPress
            end
          end
          object Panel9: TPanel
            Left = 124
            Top = 1
            Width = 266
            Height = 114
            Align = alClient
            TabOrder = 1
            object ListView2: TListView
              Left = 1
              Top = 1
              Width = 264
              Height = 112
              Align = alClient
              Columns = <
                item
                  AutoSize = True
                  Caption = 'Segment'
                end
                item
                  AutoSize = True
                  Caption = 'Local Maximum'
                end
                item
                  AutoSize = True
                  Caption = 'Density Value'
                end
                item
                  AutoSize = True
                  Caption = 'Zone Size'
                end>
              FlatScrollBars = True
              GridLines = True
              ReadOnly = True
              TabOrder = 0
              ViewStyle = vsReport
            end
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'Performance Log'
        ImageIndex = 2
        object RichEdit3: TRichEdit
          Left = 0
          Top = 0
          Width = 391
          Height = 316
          Align = alClient
          Color = clMoneyGreen
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          ScrollBars = ssVertical
          TabOrder = 0
          Zoom = 100
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'Log'
        ImageIndex = 3
        object RichEdit2: TRichEdit
          Left = 0
          Top = 0
          Width = 391
          Height = 316
          Align = alClient
          Color = clMoneyGreen
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          ScrollBars = ssVertical
          TabOrder = 0
          Zoom = 100
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'State Log'
        ImageIndex = 4
        object RichEdit4: TRichEdit
          Left = 0
          Top = 0
          Width = 391
          Height = 316
          Align = alClient
          Color = clMoneyGreen
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          ScrollBars = ssVertical
          TabOrder = 0
          Zoom = 100
        end
      end
      object TabSheet6: TTabSheet
        Caption = 'Log2'
        ImageIndex = 5
        object RichEdit5: TRichEdit
          Left = 0
          Top = 0
          Width = 391
          Height = 316
          Align = alClient
          Color = clMoneyGreen
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
          Zoom = 100
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 24
    Top = 160
    object File1: TMenuItem
      Caption = 'File'
      object Save1: TMenuItem
        Caption = 'Save'
        ShortCut = 16467
        OnClick = Save1Click
      end
      object Load1: TMenuItem
        Caption = 'Load'
        ShortCut = 16460
        OnClick = Load1Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'ta'
    Filter = 'TypingAnalysis|*.ta|All|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 32
    Top = 216
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'ta'
    Filter = 'TypingAnalysis|*.ta|All|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 32
    Top = 272
  end
  object ApplicationEvents1: TApplicationEvents
    OnActivate = ApplicationEvents1Activate
    OnDeactivate = ApplicationEvents1Deactivate
    Left = 96
    Top = 160
  end
end
