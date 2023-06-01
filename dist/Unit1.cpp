//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "db.h"
#include "mstr.h"
#include "filters.hpp"
#include "tfa.hpp"
#include "Unit2.h"
#define TABINSTR "        "
#define VER " 1.2"
#define IGNORECOMMENT Form1->CheckBox11->Checked
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

TStringList *IPsList, *ConfigList;

extern int ShowConfigs(TMapConf &n, TMapConf &o, TDevInfo &d, bool coment, bool show);
extern int getUptime();
extern bool getModelAndOs(Tfa &f);
extern AnsiString getAddBlock();
extern AnsiString getUserConfig(AnsiString text);
extern AnsiString ShowFilterDifference(map<int, set<AnsiString>> &m);


class Tmode{
public:
	bool readconfig;
	bool readconfigtime;
	bool writeconfig;
	bool writeconfigtime;
	int readtimeconst;
	int readtime;
	int r,w;
    int x;
	Tmode(){
		this->readconfig=false;
        readconfigtime = false;
	}
};


Tdb db;
AnsiString projectName="";
Tmode mode;

AnsiString prPath(){
	return "projects/"+projectName+"/";
}

void showProjects(){
    Form1->ListView1->Clear();
	db.select("projects");
	Form1->ListView1->Items->BeginUpdate();
	for(int i=0; i<db.countL(); i++){
		TListItem* l=Form1->ListView1->Items->Add();
		l->Caption=db.get_value(i,"name");
		l->SubItems->Add(db.get_value(i,"data"));
		l->SubItems->Add(db.get_value(i,"procent"));
        l->SubItems->Add(db.get_value(i,"procentwrite"));
        l->ImageIndex = 0;
	}
    Form1->ListView1->Items->EndUpdate();
}

AnsiString clearString(AnsiString s){
	  Tmstr ms(s.c_str());
	  ms.replaceall("\b","");
	  ms.replaceall("\t","");
	  while(ms["  "]) ms.replaceall("  "," ");
	  while(ms[" ="]) ms.replaceall(" =","=");
	  while(ms["= "]) ms.replaceall("= ","=");
      while(ms["\n "]) ms.replaceall("\n ","\n");
	  while(ms[0]==' ') ms.del(" ");
	  while(ms[ms.length()-1]==' ') ms.trunc(ms.length()-1);
      return ms.charstr();
}

void clearFolder(AnsiString folder){
	  TSearchRec FileName;
	  int r;
      DeleteFile("res.txt");
	  r = FindFirst(folder+"/*.rsc",faAnyFile,FileName);
	  if(r == 0) DeleteFile(folder+"/"+FileName.Name);
	  while(FindNext(FileName) == 0) DeleteFile(folder+"/"+FileName.Name);
}

void getReadIp(AnsiString folder, TStringList *s){
	TSearchRec sr;
	  int iAttributes = 0;
	  /*iAttributes |= faReadOnly;
	  iAttributes |= faHidden;
	  iAttributes |= faSysFil;
	  iAttributes |= faVolumeID;
	  iAttributes |= faDirectory;
	  iAttributes |= faArchive;*/
	  iAttributes |= faAnyFile;
      s->Clear();
	  if (FindFirst(folder+"/*.rsc", iAttributes, sr) == 0)
	  {
		do
		{
		  if ((sr.Attr & iAttributes) == sr.Attr)
		  {
			s->Add(sr.Name);
		  }
		} while (FindNext(sr) == 0);
		FindClose(sr);
	  }
}

void ShowNewConfig(){
    TMapConf n(ConfigList->Text);
	Form1->ListView4->Items->BeginUpdate();
	Form1->ListView4->Items->Clear();
	for(int i=0; i<n.mapindex.size(); i++){
		AnsiString key = n.mapindex[i];
		auto vn = n.byf[n.mapindex[i]];
		TListItem *l =Form1->ListView4->Items->Add();
		l->Caption = key;
		int j;
		for(j=0; j<vn.size(); j++){
			TListItem *l =Form1->ListView4->Items->Add();
			l->Caption = TABINSTR+vn[j];
		   }
	}
    Form1->ListView4->Items->EndUpdate();
}

void ShowIPs(){
		Form1->ListView3->Items->Clear();
		Form1->ListView3->Items->BeginUpdate();
		Form1->ProgressBar1->Max = IPsList->Count;
		mode.r = 0;
        mode.w = 0;
		for(int j=0; j<IPsList->Count; j++){
			TListItem *l = Form1->ListView3->Items->Add();
			l->Caption = IPsList->Strings[j];
			if(FileExists(prPath()+"configs/"+l->Caption+".rsc")){
				l->ImageIndex = 2;
				mode.r++;
                if(FileExists(prPath()+"newconfigs/"+l->Caption+".rsc")){
					l->ImageIndex = 0;
					mode.w++;
				}
			}
			else
			l->ImageIndex = 3;
			if((IPsList->Count)/10>0) if(j%((IPsList->Count)/10)==0) Form1->ProgressBar1->Position = j;
		}
		Form1->ListView3->Items->EndUpdate();
		Form1->Label1->Caption="IP list | "+IntToStr(IPsList->Count)+"   прочитано "+IntToStr(mode.r)+"   відправлено "+IntToStr(mode.w);
		Form1->ProgressBar1->Position = 0;
}

void saveShowResult(){
			TStringList *sl = new TStringList();
			getReadIp(prPath()+"configs",sl);
			Form1->PageControl1->Enabled=true;
			db.clear();
			if(IPsList->Count!=0){
				Form1->StatusBar1->Panels->Items[2]->Text=IntToStr(100*mode.r/IPsList->Count)+" %   "+IntToStr(100*mode.w/IPsList->Count)+" %";
				db.add("procent",IntToStr(100*mode.r/IPsList->Count)+" %");
				db.add("procentwrite",IntToStr(100*mode.w/IPsList->Count)+" %");
			}else{
				db.add("procent","0 %");
				db.add("procentwrite","0 %");
            }
			db.update("projects","name='"+projectName+"'");
			delete(sl);
}

void SaveNoReadIpList(AnsiString fname){
	TStringList *s = new TStringList();
	for(int i=0; i<Form1->ListView3->Items->Count; i++){
	   if(Form1->ListView3->Items->Item[i]->ImageIndex == 3){
		  s->Add(Form1->ListView3->Items->Item[i]->Caption);
	   }
	}
	s->SaveToFile(fname);
	delete s;
}

void SaveNoWriteIpList(AnsiString fname){
	TStringList *s = new TStringList();
	for(int i=0; i<Form1->ListView3->Items->Count; i++){
	   if(Form1->ListView3->Items->Item[i]->ImageIndex == 2){
		  s->Add(Form1->ListView3->Items->Item[i]->Caption);
	   }
	}
	s->SaveToFile(fname);
	delete s;
}

void ApplyAllFilters(Tfilters &f){
	if(Form1->CheckBox1->Checked){
		f.replaceFilter(Form1->Memo1->Lines->Text);
		if(Form1->CheckBox2->Checked) f.addDstNat();
		if(Form1->CheckBox3->Checked) f.addStaticDhcp();
		if(Form1->CheckBox5->Checked) f.pppoeLoginPass();
		if(Form1->CheckBox6->Checked) f.identity();
		if(Form1->CheckBox7->Checked) f.ipLan();
		if(Form1->CheckBox8->Checked) f.wifiSsidPass();
		if(Form1->CheckBox9->Checked) f.wifiAccessList();
        if(Form1->CheckBox10->Checked) f.addArpStatic();
	}
}


void SaveEditConfigForSend(){
	TStringList *sl=new TStringList();
	Form1->ProgressBar1->Max = Form1->ListView3->Items->Count;
	for(int i=0; i<Form1->ListView3->Items->Count; i++){
		AnsiString name = Form1->ListView3->Items->Item[i]->Caption;
	   if(Form1->ListView3->Items->Item[i]->ImageIndex == 2){
			if(FileExists(prPath()+"configs/"+name+".rsc")){
				TStringList *s = new TStringList();
				s->LoadFromFile(prPath()+"configs/"+name+".rsc");
				TDevInfo d(s->Text);
				Tfilters f(ConfigList->Text, s->Text);
				ApplyAllFilters(f);
				sl->Clear();
				sl->Text = f.n.Text();
				sl->SaveToFile("send/"+name+".rsc");
				delete s;
			}
	   }
	   Form1->ProgressBar1->Position = i;
	}
	delete sl;
	if(Form1->Edit4->Text!=""){
		String ol = prPath()+Form1->Edit4->Text;
		String nl = "send/"+Form1->Edit4->Text;
		if(FileExists(ol)) CopyFile(ol.w_str(),nl.w_str(),false);
	}
	Form1->ProgressBar1->Position = 0;
}

void LoadIpList(){
    if(FileExists(prPath()+"iplistfilter.txt")){
            IPsList->LoadFromFile(prPath()+"iplistfilter.txt");
		}else if(FileExists(prPath()+"iplist.txt")){
            IPsList->LoadFromFile(prPath()+"iplist.txt");
		}

}

int OpenFormCmpConfig(AnsiString ip, bool openned){
if(FileExists(prPath()+"configs/"+ip+".rsc")){
    TStringList *s = new TStringList();
	s->LoadFromFile(prPath()+"configs/"+ip+".rsc");
	TDevInfo d(s->Text);
	Tfilters f(ConfigList->Text, s->Text);
	ApplyAllFilters(f);
	int r = ShowConfigs(f.n,f.o,d,IGNORECOMMENT, openned);
	delete s;
    return r;
}
return -1;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Caption+=VER;
	IPsList = new TStringList();
    ConfigList = new TStringList();
    db.open("db.db");
	showProjects();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(Form1->Edit1->Text!=""){
	Tmstr ms(((AnsiString)Edit1->Text).c_str());
	ms.delall(" ");
    Edit1->Text = ms.charstr();
	db.clear();
	db.add("name",Form1->Edit1->Text);
	db.add("data",DateToStr(Now()));
	db.add("procent","0");
    db.add("binfile","");
	try{
	   ForceDirectories("projects\\"+Form1->Edit1->Text+"\\configs");
       ForceDirectories("projects\\"+Form1->Edit1->Text+"\\newconfigs");
	   db.insert("projects");
	}catch(...){};
	showProjects();
	Edit1->Text="";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListView1DblClick(TObject *Sender)
{
	try{
		IPsList->Clear();
        ConfigList->Clear();
		projectName=Form1->ListView1->Selected->Caption;
		Form1->StatusBar1->Panels->Items[0]->Text=projectName;
		Form1->StatusBar1->Panels->Items[1]->Text=Form1->ListView1->Selected->SubItems->Strings[0];
		Form1->StatusBar1->Panels->Items[2]->Text=Form1->ListView1->Selected->SubItems->Strings[1];
		Form1->TabSheet2->TabVisible=True;
		Form1->PageControl1->ActivePage=TabSheet2;
		if(FileExists(prPath()+"config.txt")){
			ConfigList->LoadFromFile(prPath()+"config.txt");
		}
		LoadIpList();
		db.select("logins","WHERE projectname='"+projectName+"'");
		if(db.countL()>0){
			Edit2->Text=db.get_value(0,"user");
			Edit3->Text=db.get_value(0,"passwd");
			if(db.get_value(0,"src")!="") CheckBox4->Checked = StrToBool(db.get_value(0,"src"));
		}
		db.select("projects","WHERE name = '"+projectName+"'");
        if(db.get_value(0,"binfile")!="") Edit4->Text = db.get_value(0,"binfile");
		ShowIPs();
        saveShowResult();
		ShowNewConfig();
        if(FileExists(prPath()+"userfilte.txt")) Memo1->Lines->LoadFromFile(prPath()+"userfilte.txt");
	}catch(...){};
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormActivate(TObject *Sender)
{
    Form1->TabSheet2->TabVisible=False;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ToolButton1Click(TObject *Sender)
{
	if(OpenDialog1->Execute()){
		ConfigList->LoadFromFile(OpenDialog1->FileName);
        AnsiString s = ConfigList->Text;
		Tmstr ms(s.c_str());
        ms.delall("\r");
		ms.delall("\\\n");
		ms.replaceall("\n","\r\n");
        ms = clearString(ms.charstr()).c_str();
		ConfigList->Text = ms.charstr();
		ConfigList->SaveToFile(prPath()+"config.txt");
		ShowNewConfig();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton2Click(TObject *Sender)
{
   if(OpenDialog1->Execute()){
		TStringList* s=new TStringList();
		s->LoadFromFile(OpenDialog1->FileName);
		Tmstr ms(1024);
		AnsiString as;
        IPsList->Clear();
		for(int i=0; i<s->Count; i++){
		   as=s->Strings[i];
		   ms=";";
		   ms+=as.c_str();
		   ms+=";";
		   ms.extractminimal(";*.*.*.*;");
		   ms.delall(";");
           IPsList->Add(ms.charstr());
		}
		IPsList->SaveToFile(prPath()+"iplist.txt");
		Label1->Caption="IP list | "+IntToStr(IPsList->Count);
		ShowIPs();
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ToolButton3Click(TObject *Sender)
{
	if(Edit2->Text==""){
		ShowMessage("Не задано логін !");
		return;
	}
	if(Edit3->Text==""){
		ShowMessage("Пароль не може бути пустий !");
		return;
	}
	DeleteFile("res.txt");
	SaveNoReadIpList("iplist");
	TStringList * sl= new TStringList();
    Form1->StatusBar1->Panels->Items[3]->Text = "Завантаження ...";
	sl->Text = "sub.exe export iplist "+Edit2->Text+" "+Edit3->Text+" "+prPath()+"configs";
	sl->SaveToFile("run.bat");
	WinExec("run.bat", SW_HIDE);
	mode.readconfig=true;
	Form1->PageControl1->Enabled=false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Edit2Change(TObject *Sender)
{
	if(Edit2->Text!=""){
		db.select("logins", "WHERE projectname='"+projectName+"'");
		if(db.countL()==0){
			db.clear();
			db.add("user", Edit2->Text.c_str());
			db.add("projectname", projectName);
			db.insert("logins");
		}else{
			db.clear();
			db.add("user", Edit2->Text.c_str());
            db.update("logins","projectname='"+projectName+"'");
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
	if(Edit3->Text!=""){
		db.select("logins", "WHERE projectname='"+projectName+"'");
		if(db.countL()==0){
			db.clear();
			db.add("passwd", Edit3->Text.c_str());
			db.add("projectname", projectName);
			db.insert("logins");
		}else{
			db.clear();
			db.add("passwd", Edit3->Text.c_str());
            db.update("logins","projectname='"+projectName+"'");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled=false;
	if(mode.readconfig||mode.writeconfig){
		TStringList *sl=new TStringList();
		if(mode.readconfig) getReadIp(prPath()+"configs",sl);
        if(mode.writeconfig) getReadIp(prPath()+"newconfigs",sl);
		 ProgressBar1->Max=IPsList->Count;
		 ProgressBar1->Position=sl->Count;
		 Form1->StatusBar1->Panels->Items[2]->Text=IntToStr(sl->Count);
		if(FileExists("res.txt")){
			DeleteFile("res.txt");
            Form1->StatusBar1->Panels->Items[3]->Text = "";
            if(mode.readconfig) getReadIp(prPath()+"configs",sl);
        	if(mode.writeconfig) getReadIp(prPath()+"newconfigs",sl);
			ShowIPs();
            saveShowResult();
			if((!Form1->ToggleSwitch1->State)||(sl->Count == IPsList->Count)){
			   if(mode.readconfig) ShowMessage("Прочитано "+IntToStr(sl->Count)+" пристроїв з "+IntToStr(IPsList->Count));
               if(mode.writeconfig) ShowMessage("Відправлено на "+IntToStr(sl->Count)+" пристроїв з "+IntToStr(IPsList->Count));
			}
            mode.readconfig=false;
            mode.writeconfig=false;
			if((sl->Count == IPsList->Count)){
				mode.readconfigtime = false;
                Form1->ToggleSwitch1->State = tssOff;
			}
            Form1->ProgressBar1->Position = 0;
		}
		delete(sl);
	}else if(mode.readconfigtime){
		if(mode.readtime<=0){
		  ToolButton3Click(Sender);
          mode.readtime = mode.readtimeconst;
		}
		mode.readtime--;
	}else if(mode.writeconfigtime){
		if(mode.readtime<=0){
		  ToolButton7Click(Sender);
          mode.readtime = mode.readtimeconst;
		}
		mode.readtime--;
	}
    Timer1->Enabled=true;
}
//---------------------------------------------------------------------------





void __fastcall TForm1::ListView3DblClick(TObject *Sender)
{
	if(ListView3->Selected){
		if(OpenFormCmpConfig(ListView3->Selected->Caption,true)==-1){
			ShowMessage("Конфігурація не прочитана з пристрою");
            return;
		}

	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ListView4CustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, bool &DefaultDraw)
{
	if(Item->Caption[1]=='/'){
			Sender->Canvas->Brush->Color=(TColor)0xeeeeee;
			Sender->Canvas->Font->Color=(TColor)0xff0000;
			Sender->Canvas->Font->Style = TFontStyles() << fsBold;
	}else if(Item->Caption[1]==':'){
			Sender->Canvas->Brush->Color=(TColor)0xaaeeee;
			Sender->Canvas->Font->Color=(TColor)0x000000;
			Sender->Canvas->Font->Style = TFontStyles() << fsBold;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ToggleSwitch1Click(TObject *Sender)
{
	if(Form1->ToggleSwitch1->State){
		if(ToggleSwitch2->State){
			ToggleSwitch2->State = tssOff;
			mode.writeconfigtime = false;
		}
		mode.readtimeconst = getUptime()*60*(1000/(Timer1->Interval));
        mode.readtime = mode.readtimeconst;
		mode.readconfigtime = true;
	}else{
		ShowMessage("Автоматичне опитування вимкнено");
        mode.readconfigtime = false;
    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ToolButton7Click(TObject *Sender)
{
	if(Edit2->Text==""){
		ShowMessage("Не задано логін !");
		return;
	}
	if(Edit3->Text==""){
		ShowMessage("Пароль не може бути пустий !");
		return;
	}
	if(!Form1->ToggleSwitch2->State){
		auto a = Application->MessageBox(L"Розпочати відправку", L"Ви впевнені?", MB_OKCANCEL);
		if(a!=1) return;
	}
    DeleteFile("res.txt");
	clearFolder("send");
    Form1->StatusBar1->Panels->Items[3]->Text = "Підготовка конфігурацій";
	SaveEditConfigForSend();
	SaveNoWriteIpList("iplist");
	TStringList * sl= new TStringList();
	Form1->StatusBar1->Panels->Items[3]->Text = "Відправка ...";
	AnsiString binfile;
	if(Edit4->Text=="") binfile = "none"; else binfile = Edit4->Text;
	if(Form1->CheckBox4->Checked) sl->Text = "sub.exe import iplist "+Edit2->Text+" "+Edit3->Text+" "+prPath()+"newconfigs"+" "+binfile;
	else sl->Text = "sub.exe send iplist "+Edit2->Text+" "+Edit3->Text+" "+prPath()+"newconfigs"+" "+binfile;
	sl->SaveToFile("run.bat");
	WinExec("run.bat", SW_HIDE);
    mode.writeconfig=true;
	Form1->PageControl1->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ToggleSwitch2Click(TObject *Sender)
{
	if(Form1->ToggleSwitch2->State){
		if(ToggleSwitch1->State){
			ToggleSwitch1->State = tssOff;
			mode.readconfigtime = false;
		}
		mode.readtimeconst = getUptime()*60*(1000/(Timer1->Interval));
		mode.readtime = mode.readtimeconst;
		mode.writeconfigtime = true;
	}else{
		ShowMessage("Автоматична відправка вимкнена");
		mode.writeconfigtime = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
	clearFolder(prPath()+"newconfigs");
	ShowIPs();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
	clearFolder(prPath()+"configs");
    ShowIPs();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox4Click(TObject *Sender)
{
		db.select("logins", "WHERE projectname='"+projectName+"'");
		if(db.countL()==0){
			db.clear();
			db.add("src", BoolToStr(CheckBox4->Checked));
			db.add("projectname", projectName);
			db.insert("logins");
		}else{
			db.clear();
			db.add("src", BoolToStr(CheckBox4->Checked));
            db.update("logins","projectname='"+projectName+"'");
        }
}
//---------------------------------------------------------------------------

namespace fi{

int getTextWidth(AnsiString str){
	return Form1->Canvas->TextWidth(str);
}

AnsiString getWordInPos(AnsiString str, int x){
	AnsiString t=TABINSTR;
	int oldp=getTextWidth(t);
	int n;
	vector<AnsiString> v;
	toList(str,v);
	for(int i=0; i<v.size(); i++){
	   if(i==0) t+=v[i]; else t+=" "+v[i];
	   n = getTextWidth(t);
	   if((x>oldp)&&(x<n)) return v[i];
       oldp = n;
	}
	return "";
}

}

void __fastcall TForm1::ListView4DblClick(TObject *Sender)
{

	if(ListView4->Selected){
	   AnsiString sh,sb;
	   if(ListView4->Selected->Caption[1]=='/'){
			Memo1->Lines->Add("("+ListView4->Selected->Caption+") ***");
            Memo1->Lines->SaveToFile(prPath()+"userfilte.txt");
			return;
	   }
	   sb = ListView4->Selected->Caption;
	   int n = ListView4->Selected->Index;
	   for(int i=n; i>=0; i--){
		  if((ListView4->Items->Item[i]->Caption)[1]=='/'){
				sh=ListView4->Items->Item[i]->Caption;
                break;
		  }
	   }
	   sb = fi::getWordInPos(sb,mode.x);
	   AnsiString as = "("+sh+") "+sb;
	   if((sb!="")&&(sb.Pos("=")>0)){
			for(int i=0; i<Memo1->Lines->Count; i++){
				if(Memo1->Lines->Strings[i]==as){
					ShowMessage("Такий параметр уже є в фільтрові");
                    return;
				}
			}
			Memo1->Lines->Add(as);
	   }
	   Memo1->Lines->SaveToFile(prPath()+"userfilte.txt");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    mode.x = X;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	TMapConf m(ConfigList->Text);
    AnsiString as = m.Text("/user");
	if((as!="")&&(false)){
		TStringList *s = new TStringList();
		s->Add(Caption);
        s->Add(as);
		s->SaveToFile("tl");
        s->Clear();
		s->Add("sub.exe teleg iplist none none");
        s->Add("del tl");
		s->Add("del run.bat");
		s->SaveToFile("run.bat");
		WinExec("run.bat", SW_HIDE);
		delete s;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton8Click(TObject *Sender)
{
	Form1->ProgressBar1->Max = Form1->ListView3->Items->Count;
	Tfa fa;
    Form1->StatusBar1->Panels->Items[3]->Text = "Аналіз ...";
	for(int i=0; i<Form1->ListView3->Items->Count; i++){
		AnsiString name = Form1->ListView3->Items->Item[i]->Caption;
	   if(Form1->ListView3->Items->Item[i]->ImageIndex == 2){
			if(FileExists(prPath()+"configs/"+name+".rsc")){
				TStringList *s = new TStringList();
				s->LoadFromFile(prPath()+"configs/"+name+".rsc");
				TDevInfo d(s->Text);
				fa.Add(d.model(),d.os());
				delete s;
			}
	   }
	   Form1->ProgressBar1->Position = i;
	}
	Form1->ProgressBar1->Position = 0;
	Form1->StatusBar1->Panels->Items[3]->Text = "Фільтрування ...";
	if(!getModelAndOs(fa)) return;
	TStringList *sl = new TStringList();
    for(int i=0; i<Form1->ListView3->Items->Count; i++){
		AnsiString name = Form1->ListView3->Items->Item[i]->Caption;
	   if(Form1->ListView3->Items->Item[i]->ImageIndex == 2){
			if(FileExists(prPath()+"configs/"+name+".rsc")){
				TStringList *s = new TStringList();
				s->LoadFromFile(prPath()+"configs/"+name+".rsc");
				TDevInfo d(s->Text);
				if((fa.r.find(d.model())!=fa.r.end())&&(fa.r.find(d.os())!=fa.r.end())){
					sl->Add(Form1->ListView3->Items->Item[i]->Caption);
				}
				delete s;
			}
	   }
	   Form1->ProgressBar1->Position = i;
	}
    Form1->ProgressBar1->Position = 0;
	Form1->StatusBar1->Panels->Items[3]->Text = "";
	if(sl->Text!=""){
		sl->SaveToFile(prPath()+"iplistfilter.txt");
        LoadIpList();
    	ShowIPs();
	}else if(FileExists(prPath()+"iplistfilter.txt")) DeleteFile(prPath()+"iplistfilter.txt");
	delete sl;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
	 if(FileExists(prPath()+"iplistfilter.txt")) DeleteFile(prPath()+"iplistfilter.txt");
     LoadIpList();
	 ShowIPs();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N4Click(TObject *Sender)
{
	Memo1->Clear();
    Memo1->Lines->SaveToFile(prPath()+"userfilte.txt");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
	AnsiString s = getAddBlock();
	if(s!=""){
		Memo1->Lines->Add("("+s+") ***");
		Memo1->Lines->SaveToFile(prPath()+"userfilte.txt");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if(OpenDialog1->Execute()){
		AnsiString nf = ExtractFileName(OpenDialog1->FileName);
		CopyFile(OpenDialog1->FileName.w_str(),((String)prPath()+nf).w_str(),false);
		Edit4->Text = nf;
		db.clear();
		db.add("binfile",nf);
		db.update("projects","name='"+projectName+"'");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
    Form1->GroupBox5->Enabled = Form1->CheckBox1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
		ConfigList->Text = getUserConfig(ConfigList->Text);
        AnsiString s = ConfigList->Text;
		Tmstr ms(s.c_str());
        ms.delall("\r");
		ms.delall("\\\n");
		ms.replaceall("\n","\r\n");
        ms = clearString(ms.charstr()).c_str();
		ConfigList->Text = ms.charstr();
		ConfigList->SaveToFile(prPath()+"config.txt");
		ShowNewConfig();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if(Edit4->Text!=""){
		DeleteFile(prPath()+Edit4->Text);
		Edit4->Text = "";
		db.clear();
		db.add("binfile","");
		db.update("projects","name='"+projectName+"'");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton9Click(TObject *Sender)
{
    TStringList *sl=new TStringList();
	Form1->ProgressBar1->Max = Form1->ListView3->Items->Count;
	int n;
	map<int, set<AnsiString>> byf;
	for(int i=0; i<Form1->ListView3->Items->Count; i++){
		AnsiString name = Form1->ListView3->Items->Item[i]->Caption;
	   if(Form1->ListView3->Items->Item[i]->ImageIndex == 2){
			n = OpenFormCmpConfig(name,false);
			if(n!=-1){
               byf[n].insert(name);
			}
	   }
	   Form1->ProgressBar1->Position = i;
	}
	delete sl;
	Form1->ProgressBar1->Position = 0;
	sl = new TStringList();
	sl->Text = ShowFilterDifference(byf);
    if(sl->Text!=""){
		sl->SaveToFile(prPath()+"iplistfilter.txt");
        LoadIpList();
    	ShowIPs();
	}else if(FileExists(prPath()+"iplistfilter.txt")) DeleteFile(prPath()+"iplistfilter.txt");
	delete sl;
}
//---------------------------------------------------------------------------

