//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <set>
#include <map>

extern int OpenFormCmpConfig(AnsiString ip, bool openned);
using namespace std;
TForm7 *Form7;
map<int, set<AnsiString>> *mm;
bool e = false;
//---------------------------------------------------------------------------

AnsiString ShowFilterDifference(map<int, set<AnsiString>> &m){
	mm = &m;
	e = false;
	for(auto i = m.begin(); i!=m.end(); i++){
		TListItem *l = Form7->ListView1->Items->Add();
		l->Caption = i->first;
        l->SubItems->Add((i->second).size());
	}
	Form7->ShowModal();
	if(e) return Form7->Memo1->Lines->Text;
    else return "";
}

__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm7::ListView1Click(TObject *Sender)
{
	if(ListView1->Selected){
		ListView2->Items->Clear();
		auto i = (*mm)[StrToInt(ListView1->Selected->Caption)];
		for(auto j = i.begin(); j!=i.end(); j++){
			 TListItem *l = ListView2->Items->Add();
			 l->Caption =*j;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm7::ListView2Click(TObject *Sender)
{
	if(ListView2->Selected){
		OpenFormCmpConfig(ListView2->Selected->Caption, true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm7::ListView1DblClick(TObject *Sender)
{
	if(ListView1->Selected){
		auto i = (*mm)[StrToInt(ListView1->Selected->Caption)];
		for(auto j = i.begin(); j!=i.end(); j++){
			 Memo1->Lines->Add(*j);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm7::N1Click(TObject *Sender)
{
    Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button1Click(TObject *Sender)
{
	e = true;
    Form7->Close();
}
//---------------------------------------------------------------------------
