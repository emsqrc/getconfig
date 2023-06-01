//---------------------------------------------------------------------------

#include <vcl.h>
#include <set>
#pragma hdrstop

#include "Unit4.h"
#include "tfa.hpp"
#include "mstr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
bool e = false;
Tfa *ff;

bool selm, selo;

bool getModelAndOs(Tfa &f){
	e = false;
    ff = &f;
    Form4->Memo1->Lines->Clear();
	Form4->ListView1->Items->Clear();
	for(auto i = f.m.begin(); i!=f.m.end(); i++){
		TListItem *l =Form4->ListView1->Items->Add();
		l->Caption=i->first;
		l->SubItems->Add(f.mi[i->first]);
	}
	Form4->ListView2->Items->Clear();
	for(auto i = f.o.begin(); i!=f.o.end(); i++){
		TListItem *l =Form4->ListView2->Items->Add();
		l->Caption=i->first;
		l->SubItems->Add(f.oi[i->first]);
	}
	selm = false;
	selo = false;
	Form4->ShowModal();
	return e;
}

void coregF(){
	bool os = false;
    bool mod = false;
    for(auto i = ff->r.begin(); i!=ff->r.end(); i++){
	   Tmstr sm((*i).c_str());
       if(sm["RouterOS"]) os = true; else mod = true;
	}
	if(!os){
	  for(int i = 0; i<Form4->ListView2->Items->Count; i++){
		ff->r.insert(Form4->ListView2->Items->Item[i]->Caption);
	}
	}
	if(!mod){
	  for(int i = 0; i<Form4->ListView1->Items->Count; i++){
		 ff->r.insert(Form4->ListView1->Items->Item[i]->Caption);
	}
	}
}

void ShowFilters(){
    Form4->Memo1->Clear();
	for(auto i = ff->r.begin(); i!=ff->r.end(); i++){
	   Form4->Memo1->Lines->Add(*i);
	}
}

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
	e = true;
    coregF();
	Form4->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ListView1DblClick(TObject *Sender)
{
	if(ListView1->Selected) ff->r.insert(ListView1->Selected->Caption);
    ShowFilters();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ListView2DblClick(TObject *Sender)
{
	if(ListView2->Selected) ff->r.insert(ListView2->Selected->Caption);
	 ShowFilters();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::N1Click(TObject *Sender)
{
   for(int i = 0; i<ListView1->Items->Count; i++){
		if(ListView1->Items->Item[i]->Selected) ff->r.insert(ListView1->Items->Item[i]->Caption);
   }
   ShowFilters();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::N2Click(TObject *Sender)
{
	for(int i = 0; i<ListView2->Items->Count; i++){
		if(ListView2->Items->Item[i]->Selected) ff->r.insert(ListView2->Items->Item[i]->Caption);
   }
   ShowFilters();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ListView2CustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, bool &DefaultDraw)
{
	if(selm){
		if(ListView1->Selected){
			set<AnsiString> t = ff->m[ListView1->Selected->Caption];
			if(t.find(Item->Caption)!=t.end()){
				Sender->Canvas->Brush->Color=(TColor)0xffeeee;
				//Sender->Canvas->Font->Color=(TColor)0xff0000;
				Sender->Canvas->Font->Style = TFontStyles() << fsBold;
            }
		}
	}else if((ListView2->Selected)&&(ListView2->Selected->Caption==Item->Caption)) Sender->Canvas->Font->Style = TFontStyles() << fsBold;
}
//---------------------------------------------------------------------------



void __fastcall TForm4::ListView1Click(TObject *Sender)
{
	selm = true;
    selo = false;
	ListView2->Repaint();
	ListView1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormResize(TObject *Sender)
{
	ListView1->Width = Form4->ClientWidth/3;
    ListView2->Width = Form4->ClientWidth/3;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ListView1CustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, bool &DefaultDraw)
{
	if(selo){
		if(ListView2->Selected){
			set<AnsiString> t = ff->o[ListView2->Selected->Caption];
			if(t.find(Item->Caption)!=t.end()){
				Sender->Canvas->Brush->Color=(TColor)0xffeeee;
				//Sender->Canvas->Font->Color=(TColor)0xff0000;
				Sender->Canvas->Font->Style = TFontStyles() << fsBold;
            }
		}
	}else if((ListView1->Selected)&&(ListView1->Selected->Caption==Item->Caption)) Sender->Canvas->Font->Style = TFontStyles() << fsBold;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ListView2Click(TObject *Sender)
{
	selm = false;
    selo = true;
	ListView1->Repaint();
    ListView2->Repaint();
}
//---------------------------------------------------------------------------

