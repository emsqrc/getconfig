//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
bool e = false;

AnsiString getAddBlock(){
	e = false;
	Form5->ShowModal();
    if(e) return Form5->Edit1->Text; else return "";
}
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button1Click(TObject *Sender)
{
	e = true;
    Form5->Close();
}
//---------------------------------------------------------------------------
