object Form1: TForm1
  Left = 240
  Top = 135
  Caption = #1048#1085#1077#1088#1094#1080#1086#1085#1085#1099#1081' '#1089#1090#1077#1085#1076' '#1048#1052'-58'
  ClientHeight = 469
  ClientWidth = 286
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  WindowState = wsMaximized
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    286
    469)
  PixelsPerInch = 96
  TextHeight = 13
  object GridPanel1: TGridPanel
    Left = -2
    Top = 0
    Width = 291
    Height = 469
    Anchors = []
    BevelOuter = bvNone
    Caption = 'GridPanel1'
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAuto
      end>
    ControlCollection = <
      item
        Column = 0
        Control = Button1
        Row = 0
      end
      item
        Column = 0
        Control = Button2
        Row = 1
      end
      item
        Column = 0
        Control = Button3
        Row = 2
      end
      item
        Column = 0
        Control = Button4
        Row = 3
      end
      item
        Column = 0
        Control = Button5
        Row = 4
      end
      item
        Column = 0
        Control = Button6
        Row = 5
      end>
    UseDockManager = False
    DockSite = True
    ExpandStyle = emAddColumns
    Locked = True
    RowCollection = <
      item
        Value = 16.666289440831100000
      end
      item
        Value = 16.665444539634890000
      end
      item
        Value = 16.666655688669860000
      end
      item
        Value = 16.669686837634560000
      end
      item
        Value = 16.665256826562920000
      end
      item
        Value = 16.666666666666670000
      end>
    ShowCaption = False
    TabOrder = 0
    DesignSize = (
      291
      469)
    object Button1: TButton
      Left = 63
      Top = 6
      Width = 165
      Height = 65
      Anchors = []
      Caption = #1055#1088#1086#1074#1077#1076#1077#1085#1080#1077' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 63
      Top = 84
      Width = 165
      Height = 65
      Anchors = []
      Caption = #1048#1089#1087#1099#1090#1072#1085#1080#1103' '#1074' '#1088#1091#1095#1085#1086#1084' '#1088#1077#1078#1080#1084#1077
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 63
      Top = 162
      Width = 165
      Height = 65
      Margins.Left = 65
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 45
      Anchors = []
      BiDiMode = bdLeftToRight
      Caption = #1040#1088#1093#1080#1074' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
      ImageAlignment = iaCenter
      ParentBiDiMode = False
      TabOrder = 2
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 63
      Top = 240
      Width = 165
      Height = 65
      Anchors = []
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
      TabOrder = 3
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 63
      Top = 318
      Width = 165
      Height = 65
      Anchors = []
      Caption = #1054#1073#1097#1080#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080
      TabOrder = 4
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 63
      Top = 397
      Width = 164
      Height = 65
      Anchors = []
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 5
      OnClick = Button6Click
    end
  end
  object ADODataSet1: TADODataSet
    Connection = Form10.ADOConnection1
    Parameters = <>
    Left = 136
    Top = 240
  end
  object ADODataSet2: TADODataSet
    Connection = Form10.ADOConnection1
    Parameters = <>
    Left = 136
    Top = 192
  end
end
