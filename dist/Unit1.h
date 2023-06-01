//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TButton *Button1;
	TEdit *Edit1;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox1;
	TListView *ListView1;
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TImageList *ImageList1;
	TToolButton *ToolButton2;
	TOpenDialog *OpenDialog1;
	TGroupBox *GroupBox3;
	TProgressBar *ProgressBar1;
	TToolButton *ToolButton3;
	TGroupBox *GroupBox4;
	TEdit *Edit2;
	TEdit *Edit3;
	TTimer *Timer1;
	TScrollBox *ScrollBox1;
	TGroupBox *GroupBox5;
	TToolButton *ToolButton4;
	TListView *ListView3;
	TListView *ListView4;
	TImageList *ImageList2;
	TImageList *ImageList3;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TToggleSwitch *ToggleSwitch1;
	TToggleSwitch *ToggleSwitch2;
	TGroupBox *GroupBox7;
	TCheckBox *CheckBox4;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMemo *Memo1;
	TCheckBox *CheckBox1;
	TToolButton *ToolButton5;
	TToolButton *ToolButton8;
	TMenuItem *N3;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TPopupMenu *PopupMenu2;
	TMenuItem *N4;
	TMenuItem *N5;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox7;
	TPanel *Panel1;
	TEdit *Edit4;
	TButton *Button2;
	TPopupMenu *PopupMenu3;
	TMenuItem *N6;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox9;
	TButton *Button3;
	TCheckBox *CheckBox10;
	TCheckBox *CheckBox11;
	TToolButton *ToolButton9;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton3Click(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall Edit3Change(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ListView3DblClick(TObject *Sender);
	void __fastcall ListView4CustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, bool &DefaultDraw);
	void __fastcall ToggleSwitch1Click(TObject *Sender);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall ToggleSwitch2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall CheckBox4Click(TObject *Sender);
	void __fastcall ListView4DblClick(TObject *Sender);
	void __fastcall ListView4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ToolButton8Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall ToolButton9Click(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
