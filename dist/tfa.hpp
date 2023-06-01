#include <vector>
#include <set>
#include <map>

using namespace std;
class Tfa{
public:
	map<AnsiString,set<AnsiString>> m, o;
    map<AnsiString, int> mi, oi;
	set<AnsiString> r;
	void Add(AnsiString sm, AnsiString so){
		set<AnsiString> t;
		t = m[sm];
		t.insert(so);
		m[sm] = t;
		t=o[so];
		t.insert(sm);
		o[so] = t;
		mi[sm]++;
        oi[so]++;
	}
	void AddRes(AnsiString s){
        r.insert(s);
	}
	int os(AnsiString model){
        return m[model].size();
	}
	int model(AnsiString os){
		set<AnsiString> t;
        return m[os].size();
	}
};

