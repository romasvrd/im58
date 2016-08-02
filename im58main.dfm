object Form9: TForm9
  Left = 0
  Top = 0
  AutoSize = True
  Caption = #1048#1052'-58 '#1088#1091#1095#1085#1086#1081' '#1088#1077#1078#1080#1084
  ClientHeight = 521
  ClientWidth = 1138
  Color = clBtnFace
  DragMode = dmAutomatic
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  Scaled = False
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object AbToggleSwitch1: TAbToggleSwitch
    Left = 216
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
    OnStatusChanged = AbToggleSwitch1StatusChanged
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object AbToggleSwitch3: TAbToggleSwitch
    Left = 216
    Top = 96
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
    OnStatusChanged = AbToggleSwitch8Changed
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object AbToggleSwitch4: TAbToggleSwitch
    Left = 0
    Top = 0
    Width = 73
    Height = 25
    Hint = 
      #1055#1088#1080#1074#1086#1076', '#1084#1086#1076#1091#1083#1100' '#1076#1080#1089#1082#1088#1077#1090#1085#1099#1093' '#1074#1093#1086#1076#1086#1074', '#1084#1086#1076#1091#1083#1100' '#1076#1080#1089#1082#1088#1077#1090#1085#1099#1093' '#1074#1099#1093#1086#1076#1086#1074' '#1080' '#1062#1040 +
      #1055
    ShowHint = True
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
    OnClick = AbToggleSwitch4Click
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object AbDBLED4: TAbDBLED
    Left = 81
    Top = 0
    Width = 129
    Height = 25
    Hint = 
      #1055#1088#1080#1074#1086#1076', '#1084#1086#1076#1091#1083#1100' '#1076#1080#1089#1082#1088#1077#1090#1085#1099#1093' '#1074#1093#1086#1076#1086#1074', '#1084#1086#1076#1091#1083#1100' '#1076#1080#1089#1082#1088#1077#1090#1085#1099#1093' '#1074#1099#1093#1086#1076#1086#1074' '#1080' '#1062#1040 +
      #1055
    ShowHint = True
    Caption = 'COM-'#1055#1086#1088#1090' 1'
    Checked = False
    Flashing = False
    Frequency = ff1Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    OnStatusChanged = AbDBLED4StatusChanged
    LED_Position = lpLeft
    Spacing = 5
    DataReadOnly = False
  end
  object AbToggleSwitch5: TAbToggleSwitch
    Left = 0
    Top = 48
    Width = 73
    Height = 25
    Hint = #1058#1072#1093#1086#1084#1077#1090#1088' '#1080' '#1088#1077#1075#1080#1089#1090#1088#1072#1090#1086#1088
    ShowHint = True
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
    OnClick = AbToggleSwitch5Click
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object AbDBLED5: TAbDBLED
    Left = 79
    Top = 47
    Width = 119
    Height = 25
    Hint = #1058#1072#1093#1086#1084#1077#1090#1088' '#1080' '#1088#1077#1075#1080#1089#1090#1088#1072#1090#1086#1088
    ShowHint = True
    Caption = 'COM-'#1087#1086#1088#1090' 2'
    Checked = False
    Flashing = False
    Frequency = ff2Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    OnStatusChanged = AbDBLED5StatusChanged
    LED_Position = lpLeft
    Spacing = 5
    DataReadOnly = False
  end
  object AbToggleSwitch10: TAbToggleSwitch
    Left = 0
    Top = 96
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
    OnClick = AbToggleSwitch10Click
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1042#1099#1082#1083
    TextOn = #1042#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object AbDBLED6: TAbDBLED
    Left = 79
    Top = 99
    Width = 129
    Height = 17
    Caption = #1054#1087#1088#1086#1089' '#1074#1093#1086#1076#1086#1074
    Checked = False
    Flashing = False
    Frequency = ff1Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    OnStatusChanged = AbDBLED6StatusChanged
    LED_Position = lpLeft
    Spacing = 5
    DataReadOnly = False
  end
  object Label1: TLabel
    Left = 295
    Top = 0
    Width = 92
    Height = 25
    AutoSize = False
    Caption = #1057#1094#1077#1087#1083#1077#1085#1080#1077' '#1084#1091#1092#1090#1099
    Layout = tlCenter
  end
  object Label13: TLabel
    Left = 295
    Top = 96
    Width = 54
    Height = 25
    AutoSize = False
    Caption = #1057#1072#1084#1086#1087#1080#1089#1077#1094
    Layout = tlCenter
  end
  object AbToggleSwitch6: TAbToggleSwitch
    Left = 432
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
    OnStatusChanged = AbToggleSwitch6StatusChanged
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1074#1099#1082#1083
    TextOn = #1074#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object AbToggleSwitch7: TAbToggleSwitch
    Left = 432
    Top = 48
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
    OnStatusChanged = AbToggleSwitch7StatusChanged
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1074#1099#1082#1083
    TextOn = #1074#1082#1083
    ColorOn = clLime
    ColorOff = clRed
  end
  object Label3: TLabel
    Left = 511
    Top = 0
    Width = 110
    Height = 25
    AutoSize = False
    Caption = #1062#1080#1083#1080#1085#1076#1088' '#1090#1086#1088#1084#1086#1078#1077#1085#1080#1103
    Layout = tlCenter
  end
  object Label5: TLabel
    Left = 511
    Top = 47
    Width = 111
    Height = 25
    AutoSize = False
    Caption = #1062#1080#1083#1080#1085#1076#1088' '#1086#1093#1083#1072#1078#1076#1077#1085#1080#1103
    Layout = tlCenter
  end
  object Ab180Meter1: TAb180Meter
    Left = 0
    Top = 141
    Width = 252
    Height = 186
    Digit = 0
    LimitUpper = 650.000000000000000000
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
    SignalSettings.ValueTo = 10.000000000000000000
    SignalSettings.ValueUnit = #1093'1000 '#1086#1073'/'#1084#1080#1085
    MinMax.UseSectorCol = False
    MinMax.MinVisible = False
    MinMax.MaxVisible = False
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
  object Label4: TLabel
    Left = 511
    Top = 96
    Width = 38
    Height = 25
    AutoSize = False
    Caption = #1055#1088#1080#1074#1086#1076
    Layout = tlCenter
  end
  object AbToggleSwitch112: TAbToggleSwitch
    Left = 432
    Top = 96
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
    OnStatusChanged = AbToggleSwitch112StatusChanged
    Orientation = boHorizontal
    SwapGraphic = True
    TextOff = #1057#1090#1086#1087
    TextOn = #1057#1090#1072#1088#1090
    ColorOn = clLime
    ColorOff = clRed
  end
  object Label30: TLabel
    Left = 112
    Top = 60
    Width = 3
    Height = 13
  end
  object AbLED3: TAbLED
    Left = 874
    Top = 0
    Width = 97
    Height = 20
    Caption = #1040#1074#1072#1088#1080#1103
    Checked = False
    Flashing = True
    Frequency = ff1Hz
    StatusInt = 0
    StatusBit = 0
    GroupIndex = 0
    Mode = mIndicator
    LED.ColorOn = clRed
    LED_Position = lpLeft
    Spacing = 5
  end
  object AbLED1: TAbLED
    Left = 874
    Top = 26
    Width = 203
    Height = 17
    Caption = #1055#1080#1090#1072#1085#1080#1077' ~220'#1042
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
    Left = 295
    Top = 47
    Width = 122
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
  object AbToggleSwitch2: TAbToggleSwitch
    Left = 216
    Top = 48
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
  object lbl1: TLabel
    Left = 8
    Top = 299
    Width = 22
    Height = 16
    Caption = 'Ch1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object Label6: TLabel
    Left = 164
    Top = 299
    Width = 22
    Height = 16
    Caption = 'Ch2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object AbHSlider1: TAbHSlider
    Left = 0
    Top = 323
    Width = 252
    Height = 102
    ShowHint = True
    ChangeLarge = 100
    ChangeSmall = 10
    OnValueChange = AbHSlider1ValueChange
    SignalSettings.DigitalTo = 4500
    SignalSettings.Name1 = #1057#1082#1086#1088#1086#1089#1090#1100' '#1087#1088#1080#1074#1086#1076#1072
    SignalSettings.Name2 = #1086#1073'/'#1084#1080#1085
    SignalSettings.ValueFormat = '####'
    SignalSettings.ValueTo = 9000.000000000000000000
    SignalSettings.ValueUnit = #1093'10 '#1086#1073'/'#1084#1080#1085
    CursorSlide = 10
    EnabledKeys = [_VK_PRIOR, _VK_NEXT, _VK_END, _VK_HOME, _VK_LEFT, _VK_DOWN, _VK_UP, _VK_RIGHT]
    TabOrder = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    BevelOuter.Style = bsRaised
    BevelOuter.Spacing = 5
    BevelOuter.BevelLine = blOuter
    BevelOuter.Width = 2
    BevelOuter.SurfaceGrad.Visible = False
    BevelOuter.SurfaceGrad.Style = gsHorizontal1
    ButtonSize = 30
    ColorTrench = clGreen
    Options = [opBevelOuter, opName1, opScaleText]
    ScaleSettings.Color = clBlack
    ScaleSettings.PointerColor = clLime
    ScaleSettings.DrawLine = False
    ScaleSettings.Font.Charset = DEFAULT_CHARSET
    ScaleSettings.Font.Color = clWindowText
    ScaleSettings.Font.Height = -11
    ScaleSettings.Font.Name = 'Arial'
    ScaleSettings.Font.Style = []
    ScaleSettings.PosLeftTop = False
    ScaleSettings.Steps = 5
    ScaleSettings.SubSteps = 5
    ScaleSettings.ValueFormat = '#'
    ScaleSettings.ValueFormatLog = '0e-0'
    object Edit1: TEdit
      Left = 192
      Top = 75
      Width = 57
      Height = 24
      Alignment = taRightJustify
      NumbersOnly = True
      TabOrder = 0
      Text = '0'
      OnKeyDown = Edit1KeyDown
    end
  end
  object AbHSlider2: TAbHSlider
    Left = 0
    Top = 419
    Width = 252
    Height = 102
    Value = 4.000000000000000000
    OnValueChange = AbHSlider2ValueChange
    SignalSettings.DigitalFrom = 40
    SignalSettings.DigitalTo = 200
    SignalSettings.Name1 = #1044#1072#1074#1083#1077#1085#1080#1077
    SignalSettings.Name2 = '('#1090#1086#1082' '#1085#1072' '#1062#1040#1055', '#1084#1040')'
    SignalSettings.ValueFormat = '##0.0'
    SignalSettings.ValueFrom = 4.000000000000000000
    SignalSettings.ValueTo = 20.000000000000000000
    SignalSettings.ValueUnit = #1082#1075#1089#1084'^2'
    EnabledKeys = [_VK_PRIOR, _VK_NEXT, _VK_END, _VK_HOME, _VK_LEFT, _VK_DOWN, _VK_UP, _VK_RIGHT]
    TabOrder = 1
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    BevelOuter.Style = bsRaised
    BevelOuter.Spacing = 5
    BevelOuter.BevelLine = blOuter
    BevelOuter.Width = 2
    BevelOuter.SurfaceGrad.Visible = False
    BevelOuter.SurfaceGrad.Style = gsHorizontal1
    ButtonSize = 30
    ColorTrench = clGreen
    Options = [opBevelOuter, opName1, opScaleText]
    ScaleSettings.Color = clBlack
    ScaleSettings.PointerColor = clLime
    ScaleSettings.DrawLine = False
    ScaleSettings.Font.Charset = DEFAULT_CHARSET
    ScaleSettings.Font.Color = clWindowText
    ScaleSettings.Font.Height = -11
    ScaleSettings.Font.Name = 'Arial'
    ScaleSettings.Font.Style = []
    ScaleSettings.PosLeftTop = False
    ScaleSettings.Steps = 8
    ScaleSettings.SubSteps = 4
    ScaleSettings.ValueFormat = '#####'
    ScaleSettings.ValueFormatLog = '0e-0'
    object Edit2: TEdit
      Left = 192
      Top = 75
      Width = 57
      Height = 24
      Alignment = taRightJustify
      TabOrder = 0
      Text = '4'
      OnKeyDown = Edit2KeyDown
    end
    object ComboBox1: TComboBox
      Left = 3
      Top = 75
      Width = 62
      Height = 24
      AutoComplete = False
      Style = csDropDownList
      DropDownCount = 3
      ItemIndex = 0
      TabOrder = 1
      Text = #1084#1040
      OnChange = ComboBox1Change
      Items.Strings = (
        #1084#1040
        #1073#1072#1088
        #1082#1075#1089)
    end
  end
  object GroupBox7: TGroupBox
    Left = 655
    Top = 0
    Width = 209
    Height = 121
    Caption = #1040#1088#1093#1080#1074' '#1088#1077#1075#1080#1089#1090#1088#1072#1090#1086#1088#1072
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 2
    object Label12: TLabel
      Left = 3
      Top = 23
      Width = 76
      Height = 13
      Caption = #1057#1095#1080#1090#1072#1090#1100' '#1090#1086#1084'...'
    end
    object ProgressBar1: TProgressBar
      Left = 136
      Top = 50
      Width = 70
      Height = 25
      DoubleBuffered = False
      ParentDoubleBuffered = False
      ParentShowHint = False
      Smooth = True
      MarqueeInterval = 50
      Step = 50
      ShowHint = False
      TabOrder = 3
    end
    object Button2: TButton
      Left = 152
      Top = 21
      Width = 54
      Height = 23
      Caption = #1057#1095#1080#1090#1072#1090#1100
      TabOrder = 0
      OnClick = Button2Click
    end
    object Edit3: TEdit
      Left = 107
      Top = 20
      Width = 34
      Height = 21
      Alignment = taRightJustify
      TabOrder = 1
    end
    object Memo1: TMemo
      Left = 5
      Top = 81
      Width = 201
      Height = 37
      ReadOnly = True
      TabOrder = 2
    end
    object Button4: TButton
      Left = 3
      Top = 50
      Width = 127
      Height = 25
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1087#1086#1089#1083#1077#1076#1085#1080#1081
      TabOrder = 4
      OnClick = Button4Click
    end
  end
  object Chart1: TChart
    Left = 255
    Top = 141
    Width = 491
    Height = 380
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
    BottomAxis.Maximum = 0.000482329126334130
    BottomAxis.Minimum = -0.000482328746334130
    BottomAxis.PositionUnits = muPixels
    BottomAxis.Title.Position = tpStart
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 0.000482329126334130
    LeftAxis.Minimum = -0.000482328746334130
    Pages.AutoScale = True
    RightAxis.Automatic = False
    RightAxis.AutomaticMaximum = False
    RightAxis.AutomaticMinimum = False
    RightAxis.Maximum = 0.000482329126334130
    RightAxis.Minimum = -0.000482328746334130
    TopAxis.Automatic = False
    TopAxis.AutomaticMaximum = False
    TopAxis.AutomaticMinimum = False
    TopAxis.Maximum = 0.000681289077946115
    TopAxis.Minimum = -0.000681287537421868
    View3D = False
    Zoom.Animated = True
    Zoom.MouseWheel = pmwNormal
    Align = alCustom
    BevelInner = bvRaised
    UseDockManager = False
    AutoSize = True
    TabOrder = 3
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      18
      15
      18)
    ColorPaletteIndex = 13
    object Очистить: TButton
      Left = 392
      Top = 16
      Width = 90
      Height = 21
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = ОчиститьClick
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
  object GroupBox6: TGroupBox
    Left = 755
    Top = 136
    Width = 110
    Height = 385
    Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077' '#1074#1093#1086#1076#1086#1074
    TabOrder = 4
    object CheckBox13: TCheckBox
      Left = 3
      Top = 286
      Width = 41
      Height = 20
      Caption = 'DI 12'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 4
    end
    object CheckBox1: TCheckBox
      Left = 3
      Top = 21
      Width = 54
      Height = 17
      Caption = 'DI 0'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 0
    end
    object CheckBox10: TCheckBox
      Left = 3
      Top = 220
      Width = 41
      Height = 17
      Caption = 'DI 9'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 1
    end
    object CheckBox11: TCheckBox
      Left = 3
      Top = 242
      Width = 41
      Height = 17
      Caption = 'DI 10'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 2
    end
    object CheckBox14: TCheckBox
      Left = 3
      Top = 308
      Width = 41
      Height = 17
      Caption = 'DI 13'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 5
    end
    object CheckBox15: TCheckBox
      Left = 3
      Top = 330
      Width = 97
      Height = 17
      Caption = 'DI 14'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 6
    end
    object CheckBox16: TCheckBox
      Left = 3
      Top = 353
      Width = 97
      Height = 17
      Caption = 'DI 15'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 7
    end
    object CheckBox2: TCheckBox
      Left = 3
      Top = 43
      Width = 97
      Height = 17
      Caption = 'DI 1'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 8
    end
    object CheckBox3: TCheckBox
      Left = 3
      Top = 65
      Width = 41
      Height = 17
      Caption = 'DI 2'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 9
    end
    object CheckBox4: TCheckBox
      Left = 3
      Top = 87
      Width = 49
      Height = 17
      Caption = 'DI 3'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 10
    end
    object CheckBox5: TCheckBox
      Left = 3
      Top = 109
      Width = 97
      Height = 17
      Caption = 'DI 4'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 11
    end
    object CheckBox6: TCheckBox
      Left = 3
      Top = 131
      Width = 97
      Height = 17
      Caption = 'DI 5'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 12
    end
    object CheckBox7: TCheckBox
      Left = 3
      Top = 153
      Width = 41
      Height = 17
      Caption = 'DI 6'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 13
    end
    object CheckBox8: TCheckBox
      Left = 3
      Top = 175
      Width = 41
      Height = 17
      Caption = 'DI 7'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 14
    end
    object CheckBox9: TCheckBox
      Left = 3
      Top = 198
      Width = 41
      Height = 17
      Caption = 'DI 8'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 15
    end
    object CheckBox12: TCheckBox
      Left = 3
      Top = 264
      Width = 41
      Height = 17
      Caption = 'DI 11'
      Ctl3D = True
      Enabled = False
      ParentCtl3D = False
      TabOrder = 3
    end
  end
  object GroupBox8: TGroupBox
    Left = 871
    Top = 49
    Width = 267
    Height = 434
    Caption = #1062#1080#1082#1083' '#1090#1086#1088#1084#1086#1078#1077#1085#1080#1103
    TabOrder = 5
    object Label2: TLabel
      Left = 3
      Top = 80
      Width = 118
      Height = 26
      Caption = #1044#1072#1074#1083#1077#1085#1080#1077' '#1074' '#1090#1086#1088#1084#1086#1079#1085#1086#1084' '#1094#1080#1083#1080#1085#1076#1088#1077', '#1082#1075
      WordWrap = True
    end
    object Label11: TLabel
      Left = 3
      Top = 113
      Width = 112
      Height = 26
      Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1099#1077' '#1086#1073#1086#1088#1086#1090#1099' '#1074#1072#1083#1072', '#1086#1073'/'#1084#1080#1085
      WordWrap = True
    end
    object Label14: TLabel
      Left = 3
      Top = 145
      Width = 93
      Height = 26
      Caption = #1056#1072#1073#1086#1095#1080#1077' '#1086#1073#1086#1088#1086#1090#1099', '#1086#1073'/'#1084#1080#1085
      WordWrap = True
    end
    object Label15: TLabel
      Left = 3
      Top = 177
      Width = 103
      Height = 26
      Caption = #1042#1088#1077#1084#1103' '#1086#1093#1083#1072#1078#1076#1077#1085#1080#1103', '#1084#1080#1085':'#1089#1077#1082
      Layout = tlCenter
      WordWrap = True
    end
    object Label16: TLabel
      Left = 3
      Top = 57
      Width = 69
      Height = 13
      Caption = #1058#1080#1087' '#1082#1077#1088#1072#1084#1080#1082#1080
      Layout = tlCenter
      WordWrap = True
    end
    object Button1: TButton
      Left = 3
      Top = 23
      Width = 102
      Height = 28
      Caption = #1057#1090#1072#1088#1090
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button3: TButton
      Left = 160
      Top = 21
      Width = 104
      Height = 28
      Caption = #1057#1090#1086#1087
      TabOrder = 1
      OnClick = Button3Click
    end
    object Edit4: TEdit
      Left = 212
      Top = 80
      Width = 52
      Height = 21
      Alignment = taRightJustify
      TabOrder = 2
      Text = '0'
    end
    object Edit5: TEdit
      Left = 212
      Top = 112
      Width = 52
      Height = 21
      Alignment = taRightJustify
      TabOrder = 3
      Text = '0'
    end
    object Edit6: TEdit
      Left = 212
      Top = 145
      Width = 52
      Height = 21
      Alignment = taRightJustify
      TabOrder = 4
      Text = '0'
    end
    object MaskEdit1: TMaskEdit
      Left = 212
      Top = 178
      Width = 51
      Height = 21
      Alignment = taCenter
      EditMask = '!90:00;1; '
      MaxLength = 5
      TabOrder = 5
      Text = '00:00'
    end
    object ComboBox2: TComboBox
      Left = 160
      Top = 53
      Width = 104
      Height = 21
      AutoComplete = False
      Style = csDropDownList
      DropDownCount = -1
      TabOrder = 6
      OnChange = ComboBox2Change
    end
    object RichEdit1: TRichEdit
      Left = 3
      Top = 238
      Width = 261
      Height = 195
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 7
      Zoom = 100
    end
    object Button6: TButton
      Left = 3
      Top = 207
      Width = 75
      Height = 25
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      TabOrder = 8
      OnClick = Button6Click
    end
    object MaskEdit2: TMaskEdit
      Left = 213
      Top = 211
      Width = 51
      Height = 21
      Alignment = taCenter
      EditMask = '!90:00;1; '
      MaxLength = 5
      TabOrder = 9
      Text = '00:00'
    end
  end
  object Button5: TButton
    Left = 871
    Top = 489
    Width = 267
    Height = 29
    Caption = #1042#1086#1079#1074#1088#1072#1090' '#1074' '#1075#1083#1072#1074#1085#1086#1077' '#1084#1077#1085#1102
    TabOrder = 6
    OnClick = Button5Click
  end
  object Button7: TButton
    Left = 546
    Top = 65
    Width = 75
    Height = 25
    Caption = 'Button7'
    TabOrder = 7
    Visible = False
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 547
    Top = 31
    Width = 75
    Height = 25
    Caption = 'Button8'
    TabOrder = 8
    Visible = False
    OnClick = Button8Click
  end
  object Edit7: TEdit
    Left = 36
    Top = 296
    Width = 49
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    Text = '0'
  end
  object Edit8: TEdit
    Left = 192
    Top = 296
    Width = 49
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    Text = '0'
  end
  object MainMenu1: TMainMenu
    Left = 376
    Top = 95
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N8: TMenuItem
        Caption = #1043#1083#1072#1074#1085#1086#1077' '#1084#1077#1085#1102
        OnClick = N8Click
      end
      object AltF41: TMenuItem
        Caption = #1042#1099#1093#1086#1076' (Alt+F4)'
        OnClick = AltF41Click
      end
    end
    object N2: TMenuItem
      Caption = #1057#1077#1088#1074#1080#1089
      object COM1: TMenuItem
        Caption = #1054#1073#1097#1080#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
        OnClick = COM1Click
      end
      object N4: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
        OnClick = N4Click
      end
    end
    object N9: TMenuItem
      Caption = #1054#1082#1085#1086
      object N10: TMenuItem
        Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080#1081' '#1088#1077#1078#1080#1084
        OnClick = N10Click
      end
    end
    object N6: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object N7: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = N7Click
      end
    end
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 600
    Top = 88
  end
end
