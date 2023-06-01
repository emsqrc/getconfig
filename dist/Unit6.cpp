//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;

 AnsiString getUserConfig(AnsiString text){
	Form6->Memo1->Lines->Text = text;
	for(int i=0; i<Form6->Memo1->Lines->Count; i++){
		if((Form6->Memo1->Lines->Strings[i]!="")&&(Form6->Memo1->Lines->Strings[i][1]!='/')&&(Form6->Memo1->Lines->Strings[i][1]!='#')) Form6->Memo1->Lines->Strings[i] = "    "+Form6->Memo1->Lines->Strings[i];
	}
	Form6->ShowModal();
    return Form6->Memo1->Lines->Text;
 }

//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
