object Form4: TForm4
  Left = 0
  Top = 0
  Caption = #1060#1110#1083#1100#1090#1077#1088' ip '#1072#1076#1088#1077#1089
  ClientHeight = 275
  ClientWidth = 674
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object ListView1: TListView
    Left = 0
    Top = 0
    Width = 250
    Height = 275
    Align = alLeft
    Columns = <
      item
        AutoSize = True
        Caption = 'model'
      end
      item
        Caption = #1082#1110#1083#1100#1082#1110#1089#1090#1100
        Width = 60
      end>
    DoubleBuffered = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    ParentDoubleBuffered = False
    PopupMenu = PopupMenu1
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = ListView1Click
    OnCustomDrawItem = ListView1CustomDrawItem
    OnDblClick = ListView1DblClick
    ExplicitHeight = 405
  end
  object ListView2: TListView
    Left = 250
    Top = 0
    Width = 239
    Height = 275
    Align = alLeft
    Columns = <
      item
        AutoSize = True
        Caption = 'OS'
      end
      item
        Caption = #1082#1110#1083#1100#1082#1110#1089#1090#1100
        Width = 60
      end>
    DoubleBuffered = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    ParentDoubleBuffered = False
    PopupMenu = PopupMenu2
    TabOrder = 1
    ViewStyle = vsReport
    OnClick = ListView2Click
    OnCustomDrawItem = ListView2CustomDrawItem
    OnDblClick = ListView2DblClick
    ExplicitLeft = 246
    ExplicitHeight = 269
  end
  object GroupBox1: TGroupBox
    Left = 489
    Top = 0
    Width = 185
    Height = 275
    Align = alClient
    Caption = #1060#1110#1083#1100#1090#1088
    TabOrder = 2
    ExplicitLeft = 500
    ExplicitWidth = 180
    ExplicitHeight = 269
    object Memo1: TMemo
      Left = 2
      Top = 15
      Width = 181
      Height = 233
      Align = alClient
      ReadOnly = True
      TabOrder = 0
      ExplicitWidth = 329
      ExplicitHeight = 363
    end
    object Button1: TButton
      Left = 2
      Top = 248
      Width = 181
      Height = 25
      Align = alBottom
      Caption = 'OK'
      TabOrder = 1
      OnClick = Button1Click
      ExplicitTop = 378
      ExplicitWidth = 329
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 64
    Top = 264
    object N1: TMenuItem
      Caption = #1044#1086#1076#1072#1090#1080' '#1076#1086' '#1092#1110#1083#1100#1090#1088#1091
      OnClick = N1Click
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 248
    Top = 264
    object N2: TMenuItem
      Caption = #1044#1086#1076#1072#1090#1080' '#1076#1086' '#1092#1110#1083#1100#1090#1088#1091
      OnClick = N2Click
    end
  end
end
