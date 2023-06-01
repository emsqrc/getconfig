object Form2: TForm2
  Left = 0
  Top = 0
  Caption = #1050#1086#1085#1092#1110#1075#1091#1088#1072#1094#1110#1111
  ClientHeight = 607
  ClientWidth = 1079
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
    Width = 1079
    Height = 588
    Align = alClient
    Columns = <
      item
        AutoSize = True
        Caption = #1053#1086#1074#1072
      end
      item
        AutoSize = True
        Caption = #1057#1090#1072#1088#1072
      end>
    DoubleBuffered = True
    ReadOnly = True
    RowSelect = True
    ParentDoubleBuffered = False
    TabOrder = 0
    ViewStyle = vsReport
    OnCustomDrawItem = ListView1CustomDrawItem
    ExplicitHeight = 607
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 588
    Width = 1079
    Height = 19
    Panels = <
      item
        Width = 200
      end>
    ExplicitLeft = 352
    ExplicitTop = 560
    ExplicitWidth = 0
  end
end
