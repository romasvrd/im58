object Form10: TForm10
  Left = 265
  Top = 47
  AutoSize = True
  Caption = #1040#1088#1093#1080#1074' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
  ClientHeight = 635
  ClientWidth = 425
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 425
    Height = 635
    DataSource = DataSource1
    Options = [dgTitles, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    OnKeyDown = DBGrid1KeyDown
    Columns = <
      item
        ButtonStyle = cbsNone
        DropDownRows = 0
        Expanded = False
        FieldName = #1060#1048#1054
        ReadOnly = False
        Width = 221
        Visible = True
      end
      item
        DropDownRows = 0
        Expanded = False
        FieldName = 'DateTime'
        Title.Caption = #1044#1072#1090#1072' '#1080' '#1074#1088#1077#1084#1103' '#1085#1072#1095#1072#1083#1072' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
        Width = 181
        Visible = True
      end>
  end
  object ADODataSet1: TADODataSet
    Connection = ADOConnection1
    CursorType = ctStatic
    CommandText = 
      'select  '#1060#1048#1054', id, DateTime, '#1048#1079#1076#1077#1083#1080#1077', '#1052#1072#1090#1077#1088#1080#1072#1083', '#1055#1072#1088#1090#1080#1103', '#1050#1086#1085#1090#1088'_'#1090#1077#1083#1086 +
      ', '#1058#1074#1077#1088#1076#1086#1089#1090#1100', '#1055#1088#1086#1075#1088#1072#1084#1084#1072'_'#1080#1089#1087#1099#1090#1072#1085#1080#1103' from after10 order by DateTime ' +
      'DESC'
    FieldDefs = <
      item
        Name = #1060#1048#1054
        DataType = ftWideString
        Size = 255
      end
      item
        Name = 'id'
        Attributes = [faReadonly, faFixed]
        DataType = ftAutoInc
      end
      item
        Name = 'DateTime'
        Attributes = [faFixed]
        DataType = ftDateTime
      end
      item
        Name = #1048#1079#1076#1077#1083#1080#1077
        DataType = ftWideString
        Size = 255
      end
      item
        Name = #1052#1072#1090#1077#1088#1080#1072#1083
        DataType = ftWideString
        Size = 255
      end
      item
        Name = #1055#1072#1088#1090#1080#1103
        DataType = ftWideString
        Size = 255
      end
      item
        Name = #1050#1086#1085#1090#1088'_'#1090#1077#1083#1086
        DataType = ftWideString
        Size = 255
      end
      item
        Name = #1058#1074#1077#1088#1076#1086#1089#1090#1100
        DataType = ftWideString
        Size = 255
      end
      item
        Name = #1055#1088#1086#1075#1088#1072#1084#1084#1072'_'#1080#1089#1087#1099#1090#1072#1085#1080#1103
        DataType = ftWideString
        Size = 255
      end>
    Parameters = <>
    StoreDefs = True
    Left = 244
    Top = 422
    object ADODataSet1ФИО: TWideStringField
      FieldName = #1060#1048#1054
      Size = 255
    end
    object ADODataSet1id: TAutoIncField
      FieldName = 'id'
      ReadOnly = True
    end
    object ADODataSet1DateTime: TDateTimeField
      FieldName = 'DateTime'
    end
    object ADODataSet1Изделие: TWideStringField
      FieldName = #1048#1079#1076#1077#1083#1080#1077
      Size = 255
    end
    object ADODataSet1Материал: TWideStringField
      FieldName = #1052#1072#1090#1077#1088#1080#1072#1083
      Size = 255
    end
    object ADODataSet1Партия: TWideStringField
      FieldName = #1055#1072#1088#1090#1080#1103
      Size = 255
    end
    object ADODataSet1Контр_тело: TWideStringField
      FieldName = #1050#1086#1085#1090#1088'_'#1090#1077#1083#1086
      Size = 255
    end
    object ADODataSet1Твердость: TWideStringField
      FieldName = #1058#1074#1077#1088#1076#1086#1089#1090#1100
      Size = 255
    end
    object ADODataSet1Программа_испытания: TWideStringField
      FieldName = #1055#1088#1086#1075#1088#1072#1084#1084#1072'_'#1080#1089#1087#1099#1090#1072#1085#1080#1103
      Size = 255
    end
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.ACE.OLEDB.12.0;Data Source=.\Win32\Debug\arch' +
      'ive.mdb;Persist Security Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.ACE.OLEDB.12.0'
    Left = 164
    Top = 422
  end
  object DataSource1: TDataSource
    DataSet = ADODataSet1
    Left = 316
    Top = 422
  end
  object ADOCommand1: TADOCommand
    CommandText = 
      'insert into [every]([DateTime],[pressure],[force],[speed],[turns' +
      '],[coef_stable],[coef_fric],[middle_moment],[max_moment],[brakeI' +
      'D]) values('#39'25.03.2015 18:16'#39','#39'1,06240437904749'#39','#39'85,08618621948' +
      '44'#39','#39'0'#39','#39'0'#39','#39'0,073785803237858'#39','#39'0,0402052229968878'#39','#39'91,4130457' +
      '677902'#39','#39'146'#39','#39'10'#39')'
    Connection = ADOConnection1
    Parameters = <>
    Left = 160
    Top = 352
  end
  object DataSource2: TDataSource
    DataSet = ADODataSet2
    Left = 308
    Top = 318
  end
  object ADODataSet2: TADODataSet
    Connection = ADOConnection1
    CursorType = ctStatic
    CommandText = 'select max(id) from after10'
    FieldDefs = <
      item
        Name = 'Expr1000'
        Attributes = [faFixed]
        DataType = ftInteger
      end>
    ParamCheck = False
    Parameters = <>
    StoreDefs = True
    Left = 236
    Top = 318
    object ADODataSet2Expr1000: TIntegerField
      FieldName = 'Expr1000'
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 192
    Top = 168
    object N1: TMenuItem
      Caption = #1054#1090#1082#1088#1099#1090#1100
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = N2Click
    end
  end
end
