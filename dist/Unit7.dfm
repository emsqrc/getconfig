object Form7: TForm7
  Left = 0
  Top = 0
  Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1082#1086#1085#1092#1110#1075#1091#1088#1072#1094#1110#1103#1093
  ClientHeight = 258
  ClientWidth = 692
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object ListView1: TListView
    Left = 0
    Top = 0
    Width = 265
    Height = 258
    Align = alLeft
    Columns = <
      item
        AutoSize = True
        Caption = #1050#1110#1083#1100#1082#1110#1089#1090#1100' '#1074#1110#1076#1084#1110#1085#1085#1086#1089#1090#1077#1081
      end
      item
        AutoSize = True
        Caption = #1050#1110#1083#1100#1082#1110#1089#1090#1100' '#1082#1086#1085#1092#1110#1075#1091#1088#1072#1094#1110#1081
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = ListView1Click
    OnDblClick = ListView1DblClick
    ExplicitHeight = 249
  end
  object ListView2: TListView
    Left = 265
    Top = 0
    Width = 242
    Height = 258
    Align = alClient
    Columns = <>
    TabOrder = 1
    ViewStyle = vsList
    OnClick = ListView2Click
    ExplicitWidth = 256
  end
  object GroupBox1: TGroupBox
    Left = 507
    Top = 0
    Width = 185
    Height = 258
    Align = alRight
    Caption = #1060#1110#1083#1100#1090#1088
    TabOrder = 2
    ExplicitLeft = 552
    ExplicitTop = 48
    ExplicitHeight = 105
    object Memo1: TMemo
      Left = 2
      Top = 15
      Width = 181
      Height = 216
      Align = alClient
      PopupMenu = PopupMenu1
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
      ExplicitLeft = -11
      ExplicitTop = -251
      ExplicitWidth = 196
      ExplicitHeight = 420
    end
    object Button1: TButton
      Left = 2
      Top = 231
      Width = 181
      Height = 25
      Align = alBottom
      Caption = #1054#1050
      TabOrder = 1
      OnClick = Button1Click
      ExplicitLeft = 32
      ExplicitTop = 232
      ExplicitWidth = 75
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 608
    Top = 184
    object N1: TMenuItem
      Caption = #1054#1095#1080#1089#1090#1080#1090#1080
      OnClick = N1Click
    end
  end
end
