object Form8: TForm8
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1055#1088#1086#1074#1077#1076#1077#1085#1080#1077' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
  ClientHeight = 323
  ClientWidth = 420
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 404
    Height = 57
    Alignment = taCenter
    AutoSize = False
    Caption = #1048#1089#1087#1099#1090#1072#1085#1080#1103' '#1048#1052'-58 '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 74
    Width = 112
    Height = 19
    Caption = #1060#1048#1054' '#1086#1087#1077#1088#1072#1090#1086#1088#1072':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 107
    Width = 56
    Height = 19
    Caption = #1048#1079#1076#1077#1083#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 8
    Top = 140
    Width = 67
    Height = 19
    Caption = #1052#1072#1090#1077#1088#1080#1072#1083
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 173
    Width = 115
    Height = 19
    Caption = #1055#1072#1088#1090#1080#1103' '#1089#1087#1077#1082#1072#1085#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 8
    Top = 206
    Width = 80
    Height = 19
    Caption = #1050#1086#1085#1090#1088'. '#1090#1077#1083#1086
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 247
    Top = 206
    Width = 93
    Height = 19
    Caption = #1058#1074#1105#1088#1076#1086#1089#1090#1100' HB'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 126
    Top = 71
    Width = 286
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnKeyDown = Edit1KeyDown
  end
  object Button1: TButton
    Left = 112
    Top = 273
    Width = 209
    Height = 42
    Align = alCustom
    Caption = #1043#1086#1090#1086#1074#1086
    TabOrder = 6
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 126
    Top = 104
    Width = 286
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnKeyDown = Edit1KeyDown
  end
  object Edit3: TEdit
    Left = 126
    Top = 137
    Width = 286
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnKeyDown = Edit1KeyDown
  end
  object Edit4: TEdit
    Left = 126
    Top = 170
    Width = 286
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnKeyDown = Edit1KeyDown
  end
  object Edit5: TEdit
    Left = 126
    Top = 203
    Width = 115
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnKeyDown = Edit1KeyDown
  end
  object Edit6: TEdit
    Left = 344
    Top = 203
    Width = 68
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnKeyDown = Edit1KeyDown
  end
  object ADOCommand1: TADOCommand
    Connection = Form10.ADOConnection1
    Parameters = <>
    Left = 368
    Top = 280
  end
end
