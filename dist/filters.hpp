#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>


int edit_distance(std::string str1, std::string str2) {
    const int len1 = str1.size();
    const int len2 = str2.size();
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; ++i) {
        dp[i][0] = i;
    }

    for (int j = 0; j <= len2; ++j) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            dp[i][j] = std::min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (str1[i - 1] != str2[j - 1]) });
        }
    }

    return dp[len1][len2];
}

class TDevInfo{
AnsiString _model, _os, _serial;
public:

	TDevInfo(AnsiString conf){
	   TStringList *s = new TStringList();
	   s->Text = conf;
	   for(int i=0; i<s->Count; i++){
			if(s->Strings[i][1]!='#') break;
			Tmstr ms(((AnsiString)s->Strings[i]).c_str());
			if(ms["RouterOS"]){
				ms.extract("RouterOS*");
				_os = ms.charstr();
			}else if(ms["model"]){
				ms.extract("model*");
				ms.del("model");
                ms.del("=");
				ms.delall(" ");
				_model = ms.charstr();
			}else if(ms["serial"]){
				ms.extract("serial*");
				ms.del("serial");
                ms.del("number");
				ms.del("=");
				ms.delall(" ");
				_serial = ms.charstr();
			}
	   }
	   delete s;
	}

  AnsiString model(){
	return _model;
  }
  AnsiString os(){
	return _os;
  }
  AnsiString serial(){
	return _serial;
  }
};

using namespace std;


class TMapConf{
public:
    vector<AnsiString> mapindex;
	map<AnsiString, vector<AnsiString>> byf;
    AnsiString clear(AnsiString s){
	  Tmstr ms(s.c_str());
	  ms.replaceall("\n","");
	  ms.replaceall("\r","");
	  ms.replaceall("\b","");
	  ms.replaceall("\t","");
	  while(ms["  "]) ms.replaceall("  "," ");
	  while(ms[" ="]) ms.replaceall(" =","=");
	  while(ms["= "]) ms.replaceall("= ","=");
	  while(ms[0]==' ') ms.del(" ");
	  while(ms[ms.length()-1]==' ') ms.trunc(ms.length()-1);
	  return  ms.charstr();
   }
   void init(AnsiString c){
	TStringList *conf = new TStringList();
	conf->Text = c;
	AnsiString s;
    AnsiString key;
		for(int i=0; i<conf->Count; i++){
		   s=clear(conf->Strings[i]);
           if(s=="") continue;
		   if((s[1]=='/')||(s[1]==':')){
				vector<AnsiString> t;
				key = s;
				for(int j=i+1; j<conf->Count; j++){
				   s=clear(conf->Strings[j]);
                   if((s=="")||(s[1]=='#')) continue;
				   if((s[1]=='/')||(s[1]==':')){
						i=j-1;
						break;
				   }else{
						t.push_back(s);
				   }
				}
				byf.emplace(key,t);
                mapindex.push_back(key);
		   }
		}
    delete conf;
   }
	TMapConf(AnsiString conf){
        init(conf);
	}
	TMapConf(){
    }
	AnsiString Text(){
		TStringList *s = new TStringList();
		for(int i = 0; i<mapindex.size(); i++){
		   s->Add(mapindex[i]);
		   auto v = byf[mapindex[i]];
		   for(int j = 0;  j < v.size(); j++){
              s->Add(v[j]);
		   }
		}
		AnsiString as = s->Text;
		delete s;
        return as;
	}
	AnsiString Text(AnsiString key){
		TStringList *s = new TStringList();
		auto n = byf.find(key);
		if(n!=byf.end()){
		   s->Add(n->first);
		   auto v = n->second;
		   for(int j = 0;  j < v.size(); j++){
              s->Add(v[j]);
		   }
		}
		AnsiString as = s->Text;
		delete s;
        return as;
	}
};

void toList(AnsiString s, vector<AnsiString> &v){
        if(s=="") return;
		AnsiString t;
		bool e = false;
		for(int i=1; i<=s.Length(); i++){
			if((s[i]==' ')&&(!e)){
			   if(t!=""){
				 v.push_back(t);
				 t="";
			   }
			}else{ t+=s[i];}

			if(s[i]=='"'){
					if(e) e = false; else e=true;
			}
		}
		v.push_back(t);
	}

bool cmpStr(AnsiString s1, AnsiString s2, vector<AnsiString> rem){
	vector<AnsiString> v1, v2, temp;
	toList(s1,v1);
	toList(s2,v2);
	for(int i=0; i<v1.size(); i++){
		Tmstr sm(v1[i].c_str());
		bool r= true;
		for(int j=0; j<rem.size(); j++){
			if(sm.msearch(rem[j].c_str())){
				r = false;
				break;
			}
		}
		if(r) temp.push_back(v1[i]);
	}
	v1 = temp;
    temp.clear();
    for(int i=0; i<v2.size(); i++){
		Tmstr sm(v2[i].c_str());
		bool r= true;
		for(int j=0; j<rem.size(); j++){
			if(sm.msearch(rem[j].c_str())){
				r = false;
				break;
			}
		}
		if(r) temp.push_back(v2[i]);
	}
	v2 = temp;
	if(v1.size()!=v2.size()) return false;
	for(int i = 0; i<v1.size(); i++){
		if(v1[i]!=v2[i]) return false;
	}
    return true;
}

bool testParametr(AnsiString s, AnsiString where){
    if(where=="") return true;
	vector<AnsiString> v;
	toList(s,v);
	for(int i=0; i<v.size(); i++){
		if(v[i]==where) return true;
	}
    return false;
}


class Tfilters{
public:
TMapConf o, n;

	Tfilters(AnsiString confnew, AnsiString confold){
		o.init(confold);
		n.init(confnew);
	}

	AnsiString getParam(AnsiString key, AnsiString mask, TMapConf &c){
		auto i = c.byf.find(key);
		vector<AnsiString> vs;
		if(i!=c.byf.end()){
			auto v = i->second;
			for(int j=0; j<v.size(); j++){
			   Tmstr ms(v[j].Length());
               vs.clear();
			   toList(v[j],vs);
			   for(int n=0; n<vs.size(); n++){
				   ms = vs[n].c_str();
				   if(ms.msearch(mask.c_str())){
						ms.extract(mask.c_str());
						return ms.charstr();
				   }
			   }
			}
		}
        return "";
	}
	bool replaceWord(AnsiString key, AnsiString mask, AnsiString where){
		AnsiString strold = getParam(key, mask, o);
		AnsiString strnew = getParam(key, mask, n);
		if((strnew!="")&&(strold!="")){
           auto i = n.byf.find(key);
		   auto v = i->second;
		   for(int j=0; j<v.size(); j++){
			 if((v[j].Pos(strnew)>0)&&(testParametr(v[j],where))){
			   Tmstr ms(v[j].Length()*2);
			   ms = v[j].c_str();
			   ms.replace(strnew.c_str(),strold.c_str());
			   v[j] = ms.charstr();
               n.byf[key] = v;
			   return true;
			 }
           }
		}
		return false;
	}
	bool replaceWord(AnsiString key, AnsiString mask){
		return  replaceWord(key,mask,"");
	}

	bool tryString(AnsiString s, vector<AnsiString> &v){
		Tmstr ms(s.c_str());
		for(int i=0; i<v.size(); i++){
			if(!ms.msearch(v[i].c_str())) return false;
		}
        return true;
	}
	void insertBlock(AnsiString key){
	   int k = -1;
	   for(int i=0; i<o.mapindex.size(); i++){
			if(o.mapindex[i] == key){ k = i; break;}
	   }
	   if(k == -1){
		  n.mapindex.push_back(key);
	   }else{
		  AnsiString parentKey = "";
		  for(int i = k-1; i>=0; i--){
			if(n.byf.find(o.mapindex[i])!=n.byf.end()){ parentKey = o.mapindex[i]; break;}
		  }
		  if(parentKey == ""){
            n.mapindex.push_back(key);
		  }else{
            int kk = -1;
			for(int i=0; i<n.mapindex.size(); i++){
				if(n.mapindex[i]==parentKey) kk = i;
			}
			kk++;
			auto it = n.mapindex.begin()+kk;
            n.mapindex.insert(it,key);
		  }
	   }
       n.byf[key];
	}
	bool noRepeats(AnsiString key, AnsiString str){
		auto i = n.byf.find(key);
		if(i!=n.byf.end()){
		   auto m = i->second;
		   for(int j = 0; j<m.size(); j++){
               if(m[j]==str) return false;
		   }
           return true;
		}else return false;
	}
	void addToBlock(AnsiString key, vector<AnsiString> &v){
		if(o.byf.find(key)!=o.byf.end()){
			vector<AnsiString> t;
			if(n.byf.find(key)==n.byf.end()) insertBlock(key);
			auto i = n.byf[key];
			auto j = o.byf[key];
			t = i;
			for(int k=0; k<j.size(); k++){
				if(tryString(j[k],v)&&noRepeats(key, j[k])) t.push_back(j[k]);
			}
            n.byf[key] = t;
		}
	}
	bool pppoeLoginPass(){
       return (replaceWord("/interface pppoe-client","user=*")&&replaceWord("/interface pppoe-client","password=*"));
	}
    bool wifiSsidPass(){
       return (replaceWord("/interface wireless","ssid=*")&&replaceWord("/interface wireless security-profiles","wpa-pre-shared-key=*"));
	}
	bool pppoePort(){
	   return replaceWord("/interface pppoe-client","interface=*");
	}
	bool identity(){
		return replaceWord("/system identity","name=*");
	}
	bool ipLan(){
		bool r =replaceWord("/ip pool","ranges=*");
		r&=replaceWord("/ip address","address=*");
		r&=replaceWord("/ip address","network=*");
		r&=replaceWord("/ip dhcp-server network","address=*");
		r&=replaceWord("/ip dhcp-server network","gateway=*");
        r&=replaceWord("/ip dns static","address=*","name=router.lan");
		return r;
	}
	void addDstNat(){
		vector<AnsiString> v = {"action=dst-nat","chain=dstnat", "dst-port=","to-addresses="};
		AnsiString key = "/ip firewall nat";
        addToBlock(key,v);
	}
	void addStaticDhcp(){
		vector<AnsiString> v = {"address=","mac-address=", "server="};
		AnsiString key = "/ip dhcp-server lease";
		addToBlock(key,v);
	}
	void addArpStatic(){
		vector<AnsiString> v = {"address=","mac-address="};
		AnsiString key = "/ip arp";
		addToBlock(key,v);
	}
	void addBlockAll(AnsiString key){
		vector<AnsiString> v = {"*"};
		addToBlock(key,v);
	}
	void wifiAccessList(){
        vector<AnsiString> v = {"*"};
		addToBlock("/interface wireless access-list",v);
	}
	AnsiString getNewConfig(){
        return n.Text();
	}
	AnsiString getKeyF(AnsiString f){
		Tmstr ms(f.c_str());
		ms.extract("(*)");
		ms.del("(");
		ms.del(")");
		return ms.charstr();
	}
	AnsiString getMaskF(AnsiString f){
		Tmstr ms(f.c_str());
		ms.mdel("(*)");
		ms.delall(" ");
		ms.extract("*=");
        ms+="*";
		return ms.charstr();
	}
	void replaceFilter(AnsiString f){
		 TStringList *s = new TStringList();
         s->Text = f;
		 for(int i=0; i<s->Count; i++){
			if(s->Strings[i].Pos("***")>0){addBlockAll(getKeyF(s->Strings[i]));}
			else replaceWord(getKeyF(s->Strings[i]),getMaskF(s->Strings[i]));
		 }
		 delete s;
	}
};