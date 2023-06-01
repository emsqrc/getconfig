//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "mstr.h"
#include "filters.hpp"
#include <set>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

bool c = false;

//---------------------------------------------------------------------------
int getDifference(){
	int n=0;
	for(int i = 0; i<Form2->ListView1->Items->Count; i++){
		if(((Form2->ListView1->Items->Item[i]->Caption[1]=='/'))||((Form2->ListView1->Items->Item[i]->SubItems->Strings[0][1]=='/'))) continue;
		if(c){
			if(!cmpStr(Form2->ListView1->Items->Item[i]->Caption,Form2->ListView1->Items->Item[i]->SubItems->Strings[0],{"comment="})) n++;
		}else{
			if(Form2->ListView1->Items->Item[i]->Caption!=Form2->ListView1->Items->Item[i]->SubItems->Strings[0]) n++;
        }
	}
    return n;
}

int ShowConfigs(TMapConf &n, TMapConf &o, TDevInfo &d, bool coment, bool show){
    c = coment;
    Form2->Caption = d.os() + "   " + d.model() + "   " + d.serial();
	Form2->ListView1->Items->BeginUpdate();
	Form2->ListView1->Items->Clear();
	for(int i=0; i<n.mapindex.size(); i++){
		AnsiString key = n.mapindex[i];
		auto vn = n.byf[n.mapindex[i]];
		auto jp = o.byf.find(key);
		if(jp!=o.byf.end()){
		   auto vo = jp->second;
		   TListItem *l =Form2->ListView1->Items->Add();
		   l->Caption = key;
		   l->SubItems->Add(key);
		   int j;
		   for(j=0; j<vn.size(); j++){
			   TListItem *l =Form2->ListView1->Items->Add();
			   l->Caption = "        "+vn[j];
			   if(j<vo.size()) l->SubItems->Add("        "+vo[j]);
			   else l->SubItems->Add(" ");
		   }
		   for(j=j; j<vo.size(); j++){
			   TListItem *l =Form2->ListView1->Items->Add();
			   l->Caption = " ";
			   l->SubItems->Add("        "+vo[j]);
		   }
		}else{
           TListItem *l =Form2->ListView1->Items->Add();
		   l->Caption = key;
		   l->SubItems->Add(" ");
           int j;
		   for(j=0; j<vn.size(); j++){
			   TListItem *l =Form2->ListView1->Items->Add();
			   l->Caption = "        "+vn[j];
			   l->SubItems->Add(" ");
		   }
        }

	}
	for(int i=0; i<o.mapindex.size(); i++){    //дорисовка старого
		AnsiString key = o.mapindex[i];
		auto vo = o.byf[o.mapindex[i]];
		auto jp = n.byf.find(key);
		if(jp==n.byf.end()){
		   TListItem *l =Form2->ListView1->Items->Add();
		   l->Caption = " ";
		   l->SubItems->Add(key);
		   for(int j=0; j<vo.size(); j++){
               TListItem *l =Form2->ListView1->Items->Add();
			   l->Caption = " ";
			   l->SubItems->Add("        "+vo[j]);
           }
		}
	}

   Form2->ListView1->Items->EndUpdate();
   int rn = getDifference();
   Form2->StatusBar1->Panels->Items[0]->Text = "  рядків відрізняється: "+IntToStr(rn);
   if(show) Form2->ShowModal();
   return rn;
}

__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ListView1CustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, bool &DefaultDraw)
{
	if((Item->Caption[1]=='/')||(Item->SubItems->Strings[0][1]=='/')){
			Sender->Canvas->Brush->Color=(TColor)0xeeeeee;
			Sender->Canvas->Font->Color=(TColor)0xff0000;
			Sender->Canvas->Font->Style = TFontStyles() << fsBold;
	}else if((Item->Caption[1]==':')||(Item->SubItems->Strings[0][1]==':')){
			Sender->Canvas->Brush->Color=(TColor)0xaaeeee;
			Sender->Canvas->Font->Color=(TColor)0x000000;
			Sender->Canvas->Font->Style = TFontStyles() << fsBold;
	}else{
		if(c){
			if(cmpStr(Item->Caption,Item->SubItems->Strings[0],{"comment="})){
				Sender->Canvas->Font->Color=(TColor)0x008000;
			}else{
				Sender->Canvas->Font->Color=(TColor)0x0000a0;
			}
		}else{
			if(Item->Caption==Item->SubItems->Strings[0]){
				Sender->Canvas->Font->Color=(TColor)0x008000;
			}else{
				Sender->Canvas->Font->Color=(TColor)0x0000a0;
			}
        }
    }
}
//---------------------------------------------------------------------------
