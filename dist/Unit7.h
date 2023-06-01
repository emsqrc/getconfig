//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm7 : public TForm
{
__published:	// IDE-managed Components
	TListView *ListView1;
	TListView *ListView2;
	TMemo *Memo1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TGroupBox *GroupBox1;
	TButton *Button1;
	void __fastcall ListView1Click(TObject *Sender);
	void __fastcall ListView2Click(TObject *Sender);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm7(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
