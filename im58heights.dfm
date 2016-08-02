object Form3: TForm3
  Left = 146
  Top = 55
  AutoSize = True
  BorderStyle = bsDialog
  Caption = #1042#1099#1089#1086#1090#1099' '#1086#1073#1088#1072#1079#1094#1086#1074' '#1080' '#1082#1086#1085#1090#1088'.'#1090#1077#1083
  ClientHeight = 449
  ClientWidth = 277
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid1: TStringGrid
    Left = 0
    Top = 0
    Width = 277
    Height = 228
    ColCount = 4
    DoubleBuffered = True
    RowCount = 9
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs, goAlwaysShowEditor]
    ParentDoubleBuffered = False
    ScrollBars = ssNone
    TabOrder = 0
    OnSetEditText = StringGrid1SetEditText
    RowHeights = (
      24
      24
      24
      24
      24
      24
      24
      24
      24)
  end
  object StringGrid2: TStringGrid
    Left = 0
    Top = 230
    Width = 277
    Height = 178
    ColCount = 4
    DoubleBuffered = True
    RowCount = 7
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs, goAlwaysShowEditor]
    ParentDoubleBuffered = False
    TabOrder = 1
    OnSetEditText = StringGrid2SetEditText
    ColWidths = (
      64
      64
      64
      64)
    RowHeights = (
      24
      24
      24
      24
      24
      24
      24)
  end
  object Button5: TButton
    Left = 0
    Top = 414
    Width = 277
    Height = 35
    Caption = #1043#1086#1090#1086#1074#1086
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button5Click
  end
  object ADOCommand1: TADOCommand
    Connection = Form10.ADOConnection1
    Parameters = <>
    Left = 96
    Top = 88
  end
end
