object Form4: TForm4
  Left = 0
  Top = 0
  Caption = #1048#1052'-58 '#1072#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080#1081' '#1088#1077#1078#1080#1084
  ClientHeight = 561
  ClientWidth = 1138
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
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Ab180Meter1: TAb180Meter
    Left = 0
    Top = 55
    Width = 252
    Height = 181
    Digit = -1
    LimitUpper = 1000.000000000000000000
    LimitLower = -1.000000000000000000
    SectorSettings.Sector1To = 800
    SectorSettings.Sector2Color = clRed
    SectorSettings.Sector2From = 800
    SectorSettings.Sector2To = 1000
    SectorSettings.Sector3From = 0
    SectorSettings.Sector3To = 0
    SectorSettings.Offset = 0
    SectorSettings.WidthOffset = 0
    SignalSettings.DigitalTo = 10000
    SignalSettings.Name1 = #1057#1082#1086#1088#1086#1089#1090#1100' '#1074#1072#1083#1072
    SignalSettings.Name2 = '0'
    SignalSettings.ValueFormat = '##0.0'
    SignalSettings.ValueFrom = 0.001000000047497451
    SignalSettings.ValueTo = 10.000000000000000000
    SignalSettings.ValueUnit = #1093'1000 '#1086#1073'/'#1084#1080#1085
    MinMax.UseSectorCol = False
    MinMax.MinVisible = False
    MinMax.MaxVisible = False
    Value = 0.000099999997473788
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    AutoSize = False
    FontUnit.Charset = DEFAULT_CHARSET
    FontUnit.Color = clBlack
    FontUnit.Height = -13
    FontUnit.Name = 'System'
    FontUnit.Style = []
    BevelInner.Style = bsLowered
    BevelInner.Spacing = 5
    BevelInner.BevelLine = blInner
    BevelInner.Width = 2
    BevelInner.SurfaceGrad.Visible = False
    BevelInner.SurfaceGrad.Style = gsHorizontal1
    BevelOuter.Style = bsRaised
    BevelOuter.Spacing = 5
    BevelOuter.BevelLine = blOuter
    BevelOuter.Width = 2
    BevelOuter.SurfaceGrad.Visible = False
    BevelOuter.SurfaceGrad.Style = gsHorizontal1
    Options = [opBevelInner, opBevelOuter, opName1, opName2, opOverflow, opLimit, opSector, opUnit]
    ScaleSettings.Color = clBlack
    ScaleSettings.PointerColor = clLime
    ScaleSettings.DrawLine = True
    ScaleSettings.Font.Charset = DEFAULT_CHARSET
    ScaleSettings.Font.Color = clWindowText
    ScaleSettings.Font.Height = -19
    ScaleSettings.Font.Name = 'Arial'
    ScaleSettings.Font.Style = []
    ScaleSettings.PosLeftTop = False
    ScaleSettings.Steps = 5
    ScaleSettings.SubSteps = 2
    ScaleSettings.ValueFormat = '##0'
    ScaleSettings.ValueFormatLog = '0e-0'
  end
  object Label1: TLabel
    Left = 258
    Top = 87
    Width = 118
    Height = 26
    Caption = #1044#1072#1074#1083#1077#1085#1080#1077' '#1074' '#1090#1086#1088#1084#1086#1079#1085#1086#1084' '#1094#1080#1083#1080#1085#1076#1088#1077', '#1082#1075
    WordWrap = True
  end
  object Label2: TLabel
    Left = 258
    Top = 120
    Width = 122
    Height = 26
    Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1099#1077' '#1086#1073#1086#1088#1086#1090#1099' '#1074#1072#1083#1072', '#1086#1073'/'#1084#1080#1085
    WordWrap = True
  end
  object Label3: TLabel
    Left = 258
    Top = 154
    Width = 93
    Height = 26
    Caption = #1056#1072#1073#1086#1095#1080#1077' '#1086#1073#1086#1088#1086#1090#1099', '#1086#1073'/'#1084#1080#1085
    WordWrap = True
  end
  object Label4: TLabel
    Left = 258
    Top = 188
    Width = 103
    Height = 26
    Caption = #1042#1088#1077#1084#1103' '#1086#1093#1083#1072#1078#1076#1077#1085#1080#1103', '#1084#1080#1085':'#1089#1077#1082
    Layout = tlCenter
    WordWrap = True
  end
  object AbLED1: TAbLED
    Left = 451
    Top = 31
    Width = 179
    Height = 17
    Caption = '~220'#1042
    Checked = False
    Flashing = False
    Frequency = ff1Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    LED_Position = lpLeft
    Spacing = 5
  end
  object AbLED2: TAbLED
    Left = 337
    Top = 0
    Width = 175
    Height = 25
    Caption = #1055#1080#1090#1072#1085#1080#1077' '#1087#1088#1080#1074#1086#1076#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Pitch = fpVariable
    Font.Style = []
    ParentFont = False
    Checked = False
    Flashing = False
    Frequency = ff1Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    OnStatusChanged = AbLED2StatusChanged
    LED_Position = lpLeft
    Spacing = 5
  end
  object AbLED3: TAbLED
    Left = 451
    Top = 5
    Width = 73
    Height = 20
    Caption = #1040#1074#1072#1088#1080#1103
    Checked = False
    Flashing = True
    Frequency = ff1Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    OnStatusChanged = AbLED3StatusChanged
    LED.ColorOn = clRed
    LED_Position = lpLeft
    Spacing = 5
  end
  object AbToggleSwitch2: TAbToggleSwitch
    Left = 258
    Top = 0
    Width = 73
    Height = 25
    BevelOuter.Style = bsLowered
    BevelOuter.Spacing = 1
    BevelOuter.BevelLine = blInner
    BevelOuter.Width = 1
    BevelOuter.Color = clBtnShadow
    BevelOuter.SurfaceGrad.Visible = False
    BevelOuter.SurfaceGrad.Style = gsHorizontal1
    BtnColorHighlight = clBtnHighlight
    BtnColorShadow = clBtnShadow
    BtnColorFace = clBtnFace
    BtnBevelWidth = 2
    Mode = mSwitch
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Checked = False
    OnClick = AbToggleSwitch2Click
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object Label5: TLabel
    Left = 258
    Top = 62
    Width = 112
    Height = 13
    Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1080#1089#1087#1099#1090#1072#1085#1080#1103
    Layout = tlCenter
    WordWrap = True
  end
  object Label6: TLabel
    Left = 8
    Top = 5
    Width = 72
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = #1057#1074#1103#1079#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object AbToggleSwitch3: TAbToggleSwitch
    Left = 258
    Top = 31
    Width = 73
    Height = 25
    BevelOuter.Style = bsLowered
    BevelOuter.Spacing = 1
    BevelOuter.BevelLine = blInner
    BevelOuter.Width = 1
    BevelOuter.Color = clBtnShadow
    BevelOuter.SurfaceGrad.Visible = False
    BevelOuter.SurfaceGrad.Style = gsHorizontal1
    BtnColorHighlight = clBtnHighlight
    BtnColorShadow = clBtnShadow
    BtnColorFace = clBtnFace
    BtnBevelWidth = 2
    Mode = mSwitch
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Checked = False
    OnStatusChanged = AbToggleSwitch3StatusChanged
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object AbLED4: TAbLED
    Left = 337
    Top = 31
    Width = 88
    Height = 25
    Caption = #1054#1093#1083#1072#1078#1076#1077#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Pitch = fpVariable
    Font.Style = []
    ParentFont = False
    Checked = False
    Flashing = False
    Frequency = ff1Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    OnStatusChanged = AbLED2StatusChanged
    LED_Position = lpLeft
    Spacing = 5
  end
  object AbToggleSwitch1: TAbToggleSwitch
    Left = 8
    Top = 24
    Width = 72
    Height = 25
    BevelOuter.Style = bsLowered
    BevelOuter.Spacing = 1
    BevelOuter.BevelLine = blInner
    BevelOuter.Width = 1
    BevelOuter.Color = clBtnShadow
    BevelOuter.SurfaceGrad.Visible = False
    BevelOuter.SurfaceGrad.Style = gsHorizontal1
    BtnColorHighlight = clBtnHighlight
    BtnColorShadow = clBtnShadow
    BtnColorFace = clBtnFace
    BtnBevelWidth = 2
    Mode = mSwitch
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Checked = False
    OnClick = AbToggleSwitch1Click
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object RichEdit1: TRichEdit
    Left = 0
    Top = 245
    Width = 524
    Height = 316
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 1
    Zoom = 100
  end
  object Button1: TButton
    Left = 90
    Top = 0
    Width = 50
    Height = 49
    Caption = #1057#1090#1072#1088#1090
    TabOrder = 0
    OnClick = l
  end
  object Edit1: TEdit
    Left = 409
    Top = 97
    Width = 52
    Height = 21
    Alignment = taRightJustify
    TabOrder = 2
    Text = '0'
  end
  object Edit2: TEdit
    Left = 409
    Top = 128
    Width = 52
    Height = 21
    Alignment = taRightJustify
    TabOrder = 3
    Text = '0'
  end
  object Edit3: TEdit
    Left = 409
    Top = 159
    Width = 52
    Height = 21
    Alignment = taRightJustify
    TabOrder = 4
    Text = '0'
  end
  object Сохранить: TButton
    Left = 258
    Top = 214
    Width = 75
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 5
    OnClick = СохранитьClick
  end
  object Button2: TButton
    Left = 202
    Top = 0
    Width = 50
    Height = 49
    Caption = #1057#1090#1086#1087
    TabOrder = 6
    OnClick = Button2Click
  end
  object MaskEdit1: TMaskEdit
    Left = 409
    Top = 191
    Width = 52
    Height = 21
    Alignment = taCenter
    EditMask = '!90:00;1; '
    MaxLength = 5
    TabOrder = 7
    Text = '  :  '
  end
  object ComboBox1: TComboBox
    Left = 382
    Top = 66
    Width = 79
    Height = 21
    AutoComplete = False
    Style = csDropDownList
    DropDownCount = -1
    TabOrder = 8
    OnChange = ComboBox1Change
  end
  object MaskEdit2: TMaskEdit
    Left = 409
    Top = 218
    Width = 52
    Height = 21
    Alignment = taCenter
    EditMask = '!90:00;1; '
    MaxLength = 5
    ReadOnly = True
    TabOrder = 9
    Text = '  :  '
  end
  object Chart1: TChart
    Left = 530
    Top = 8
    Width = 600
    Height = 553
    Border.Visible = True
    Legend.Alignment = laTop
    Legend.DrawBehind = True
    Legend.LegendStyle = lsSeries
    Legend.Symbol.Continuous = True
    Legend.TextStyle = ltsValue
    Title.Text.Strings = (
      #1044#1080#1072#1075#1088#1072#1084#1084#1072' '#1090#1086#1088#1084#1086#1078#1077#1085#1080#1103)
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.DateTimeFormat = 'hh:nn'
    BottomAxis.LabelsMultiLine = True
    BottomAxis.LabelsOnAxis = False
    BottomAxis.Maximum = 0.000003014664071751
    BottomAxis.Minimum = -0.000003014284071752
    BottomAxis.PositionUnits = muPixels
    BottomAxis.Title.Position = tpStart
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 0.000003014664071751
    LeftAxis.Minimum = -0.000003014284071752
    Pages.AutoScale = True
    RightAxis.Automatic = False
    RightAxis.AutomaticMaximum = False
    RightAxis.AutomaticMinimum = False
    RightAxis.Maximum = 0.000003014664071751
    RightAxis.Minimum = -0.000003014284071752
    TopAxis.Automatic = False
    TopAxis.AutomaticMaximum = False
    TopAxis.AutomaticMinimum = False
    TopAxis.Maximum = 0.000004258706670645
    TopAxis.Minimum = -0.000004257166146399
    View3D = False
    Zoom.Animated = True
    Zoom.MouseWheel = pmwNormal
    Align = alCustom
    BevelInner = bvRaised
    UseDockManager = False
    AutoSize = True
    TabOrder = 10
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      18
      15
      18)
    ColorPaletteIndex = 13
    object Очистить: TButton
      Left = 696
      Top = 8
      Width = 75
      Height = 17
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      TabOrder = 0
    end
    object Button4: TButton
      Left = 512
      Top = 4
      Width = 75
      Height = 25
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      TabOrder = 1
      OnClick = Button4Click
    end
    object Series1: TLineSeries
      Title = #1054#1089#1077#1074#1086#1077' '#1091#1089#1080#1083#1080#1077
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
      Data = {0000000000}
    end
    object Series2: TLineSeries
      Title = #1058#1086#1088#1084#1086#1079#1085#1086#1081' '#1084#1086#1084#1077#1085#1090
      Brush.BackColor = clDefault
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
      Data = {0000000000}
    end
  end
  object Button3: TButton
    Left = 146
    Top = 0
    Width = 50
    Height = 49
    Caption = #1055#1072#1091#1079#1072
    TabOrder = 11
    OnClick = Button3Click
  end
  object MainMenu1: TMainMenu
    Left = 377
    Top = 160
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N2: TMenuItem
        Caption = #1043#1083#1072#1074#1085#1086#1077' '#1084#1077#1085#1102
        OnClick = N2Click
      end
      object N5: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1083#1086#1075
        OnClick = N5Click
      end
      object AltF41: TMenuItem
        Caption = #1042#1099#1093#1086#1076' (Alt+F4)'
        OnClick = AltF41Click
      end
    end
    object N3: TMenuItem
      Caption = #1054#1082#1085#1086
      object N4: TMenuItem
        Caption = #1056#1091#1095#1085#1086#1081' '#1088#1077#1078#1080#1084
        OnClick = N4Click
      end
    end
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 488
    Top = 88
  end
  object Timer2: TTimer
    Enabled = False
    OnTimer = Timer2Timer
    Left = 488
    Top = 136
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 10
    OnTimer = Timer3Timer
    Left = 488
    Top = 192
  end
end
