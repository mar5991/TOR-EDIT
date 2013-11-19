#include "nextra.hpp"
#include <set>
using namespace std;
int nextra::punktysize()
{
	return punkty.size();
}
int nextra::liniesize()
{
	return linie.size();
}
int nextra::liniolukisize()
{
	return linioluki.size();
}
bool nextra::setpunkt(string nazwa, PUNKT pkt)
{
	if(punkty.find(nazwa)!=punkty.end())
		return false;
	PUNKT_PLUS nowy;
	nowy.pkt=pkt;
	punkty[nazwa]=nowy;
	return true;
}

string nextra::randnazwa()
{
	string wynik;
	for(int i=0; i<10; i++)
	{
		char kkp=rand()%26+97;
		wynik+=kkp;
	}
	return wynik;
}

bool nextra::setkrzywa(string nazwa, string pkt_start, string pkt_stop)
{
	if(punkty.find(pkt_start)==punkty.end())
		return false;
	if(punkty.find(pkt_stop)==punkty.end())
		return false;
	if(linioluki.find(nazwa)!=linioluki.end())
		return false;
	if(linie.find(nazwa)!=linie.end())
		return false;
	LINIA_PLUS nowa;
	nowa.pkt1=pkt_start;
	nowa.pkt2=pkt_stop;
	punkty[pkt_start].linie_powiazane.insert(nazwa);
	punkty[pkt_stop].linie_powiazane.insert(nazwa);
	nowa.lin=LINIA(punkty[pkt_start].pkt, punkty[pkt_stop].pkt);
	linie[nazwa]=nowa;
	return true;
}
bool nextra::setkrzywa(string nazwa, string pkt_start, string pkt_stop, double k1, double k2)
{
	if(punkty.find(pkt_start)==punkty.end())
		return false;
	if(punkty.find(pkt_stop)==punkty.end())
		return false;
	if(linie.find(nazwa)!=linie.end())
		return false;
	if(linioluki.find(nazwa)!=linioluki.end())
		return false;
	LINIOLUK_PLUS nowa;
	nowa.pkt1=pkt_start;
	nowa.pkt2=pkt_stop;
	nowa.k1=k1;
	nowa.k2=k2;
	punkty[pkt_start].linie_powiazane.insert(nazwa);
	punkty[pkt_stop].linie_powiazane.insert(nazwa);
	nowa.llk=LINIOLUK(punkty[pkt_start].pkt, punkty[pkt_stop].pkt, k1, k2);
	linioluki[nazwa]=nowa;
	cout<<"DODANO "<<nazwa<<" "<<(linioluki.find(nazwa)==linioluki.end())<<endl;
	cout<<"D2DAN2 "<<(linie.find(nazwa)==linie.end())<<endl;
	return true;
}
bool nextra::setpunkt_prop(string nazwa, string key, string value)
{
	if(punkty.find(nazwa)==punkty.end())
		return false;
	punkty[nazwa].prop[key]=value;
	if(value=="")
	{
		punkty[nazwa].prop.erase(punkty[nazwa].prop.find(key));
			return true;
	}
	return true;
}
bool nextra::setkrzywa_prop(string nazwa, string key, string value)
{
	if(linie.find(nazwa)==linie.end())
	{
		cout<<"s1"<<endl;
		if(linioluki.find(nazwa)==linioluki.end())
			return false;
		linioluki[nazwa].prop[key]=value;
		if(value=="")
		{
			linioluki[nazwa].prop.erase(linioluki[nazwa].prop.find(key));
				return true;
		}
		return true;
	}
	linie[nazwa].prop[key]=value;
	if(value=="")
	{
		linie[nazwa].prop.erase(linie[nazwa].prop.find(key));
			return true;
	}

	return true;
}
/*bool nextra::deletepunkt_prop(string nazwa, string key)
{
	if(punkty.find(nazwa)==punkty.end())
		return false;
	map<string, string>::iterator it1=punkty[nazwa].prop.find(key);
	if(it1==punkty[nazwa].prop.end())
		return false;
	punkty[nazwa].prop.erase(it1);
	return true;
}
bool nextra::deletekrzywa_prop(string nazwa, string key)
{
	if(linie.find(nazwa)==linie.end())
	{
		if(linioluki.find(nazwa)==linioluki.end())
			return false;
		map<string, string>::iterator it1=linioluki[nazwa].prop.find(key);
		if(it1==linioluki[nazwa].prop.end())
			return false;
		linioluki[nazwa].prop.erase(it1);
	}
	map<string, string>::iterator it1=linie[nazwa].prop.find(key);
	if(it1==linie[nazwa].prop.end())
			return false;
	linie[nazwa].prop.erase(it1);
	return true;
}*/
bool nextra::changepunkt(string nazwa, PUNKT newpoz)
{
	if(punkty.find(nazwa)==punkty.end())
		return false;
	map<string, PUNKT_PLUS>::iterator it1=punkty.find(nazwa);
	(it1->second).pkt=newpoz;
	set<string>::iterator it2=(it1->second).linie_powiazane.begin();
	while(it2!=(it1->second).linie_powiazane.end())
	{
		if(linie.find(*it2)!=linie.end())
		{
			LINIA_PLUS it3=linie[*it2];
			it3.lin=LINIA(punkty[it3.pkt1].pkt, punkty[it3.pkt2].pkt);
			linie[*it2]=it3;
		}
		else
		{
			LINIOLUK_PLUS it3=linioluki[*it2];
			it3.llk=LINIOLUK(punkty[it3.pkt1].pkt, punkty[it3.pkt2].pkt, it3.k1, it3.k2);
			linioluki[*it2]=it3;
		}
		it2++;
	}
	return true;
}
bool nextra::deletepunkt(string nazwa)
{
	cout<<"DELETING "<<nazwa<<endl;
	if(punkty.find(nazwa)==punkty.end())
		return false;
	map<string, PUNKT_PLUS>::iterator it1=punkty.find(nazwa);
	set<string>::iterator it2=(it1->second).linie_powiazane.begin();
	while(it2!=(it1->second).linie_powiazane.end())
	{
		deletekrzywa(*it2);
		it2++;
	}
	punkty.erase(it1);
	return true;
}
bool nextra::deletekrzywa(string nazwa)
{
	cout<<"DELETING_krzywa "<<nazwa<<endl;
	if(linie.find(nazwa)==linie.end())
	{
		cout<<"alfa"<<endl;
		if(linioluki.find(nazwa)==linioluki.end())
			return false;
		cout<<"beta"<<endl;
		LINIOLUK_PLUS it3=linioluki[nazwa];
		(punkty[it3.pkt1]).linie_powiazane.erase(punkty[it3.pkt1].linie_powiazane.find(nazwa));
		(punkty[it3.pkt2]).linie_powiazane.erase(punkty[it3.pkt2].linie_powiazane.find(nazwa));
		linioluki.erase(linioluki.find(nazwa));
		return true;
	}
	cout<<"gamma"<<endl;
	LINIA_PLUS it3=linie[nazwa];
	punkty[it3.pkt1].linie_powiazane.erase(punkty[it3.pkt1].linie_powiazane.find(nazwa));
	punkty[it3.pkt2].linie_powiazane.erase(punkty[it3.pkt2].linie_powiazane.find(nazwa));
	linie.erase(linie.find(nazwa));
	return true;
}
bool nextra::getpunkt(string nazwa, PUNKT& pkt)
{
	if(punkty.find(nazwa)==punkty.end())
		return false;
	pkt=punkty[nazwa].pkt;
	return true;
}
int nextra::getkrzywa(string nazwa, LINIA& lin, LINIOLUK& llk)
{
	if(linie.find(nazwa)==linie.end())
	{
		if(linioluki.find(nazwa)==linioluki.end())
			return 0;
		LINIOLUK_PLUS it3=linioluki[nazwa];
		llk=it3.llk;
		return 1;
	}
	LINIA_PLUS it3=linie[nazwa];
	lin=it3.lin;
	return 2;
}
pair <string, string> nextra::getkrzywass(string nazwa)
{
	if(linie.find(nazwa)==linie.end())
	{
		if(linioluki.find(nazwa)==linioluki.end())
			return pair<string, string>("", "");
		LINIOLUK_PLUS it3=linioluki[nazwa];
		return pair<string, string>(it3.pkt1, it3.pkt2);
	}
	LINIA_PLUS it3=linie[nazwa];
	return pair<string, string>(it3.pkt1, it3.pkt2);
}
map <string, string> nextra::getpunkt_prop(string nazwa)
{
	map<string, string> wyniktmp;
	if(punkty.find(nazwa)==punkty.end())
		return wyniktmp;
	return punkty[nazwa].prop;
}
map <string, string> nextra::getkrzywa_prop(string nazwa)
{	
	map<string, string> wyniktmp;
	if(linie.find(nazwa)==linie.end())
	{
		if(linioluki.find(nazwa)==linioluki.end())
			return wyniktmp;
		LINIOLUK_PLUS it3=linioluki[nazwa];
		return it3.prop;
	}
	LINIA_PLUS it3=linie[nazwa];
	return it3.prop;

}
bool nextra::getpunkt_all(funkcja_receiver& fr1)
{
	map <string, PUNKT_PLUS>::iterator it1=punkty.begin();
	while(it1!=punkty.end())
	{
		fr1.funkcja3(it1->first, (it1->second).pkt);
		it1++;
	}
	return true;
}
bool nextra::getkrzywa_all(funkcja_receiver& fr1)
{
	map<string, LINIA_PLUS>::iterator it1=linie.begin();
	cout<<linie.size()<<endl;
	while(it1!=linie.end())
	{
		fr1.funkcja1(it1->first, (it1->second).lin);
		it1++;
	}
	map<string, LINIOLUK_PLUS>::iterator it2=linioluki.begin();
	while(it2!=linioluki.end())
	{
		fr1.funkcja2(it2->first, (it2->second).llk);
		it2++;
	}
	return true;
}
bool nextra::getpunkt_key(string key, string value, funkcja_receiver& fr1)
{
	map <string, PUNKT_PLUS>::iterator it1=punkty.begin();
	while(it1!=punkty.end())
	{
		string keycmp;
		if((it1->second).prop.find(key)!=(it1->second).prop.end())
			keycmp=(it1->second).prop[key];
		if(keycmp==value)
			fr1.funkcja3(it1->first, (it1->second).pkt);
		it1++;
	}
	return true;
}

bool nextra::getpunkt_keycmp(string key, string value, funkcja_receiver& fr1)
{
	map <string, PUNKT_PLUS>::iterator it1=punkty.begin();
	while(it1!=punkty.end())
	{	
		string keycmp;
		if((it1->second).prop.find(key)!=(it1->second).prop.end())
			keycmp=(it1->second).prop[key];
		if(fr1.cmp(keycmp, value))
			fr1.funkcja3(it1->first, (it1->second).pkt);
		it1++;
	}
	return true;
}

bool nextra::getkrzywa_key(string key, string value, funkcja_receiver& fr1)
{
	map<string, LINIA_PLUS>::iterator it1=linie.begin();
	while(it1!=linie.end())
	{	
		string keycmp;
		if((it1->second).prop.find(key)!=(it1->second).prop.end())
			keycmp=(it1->second).prop[key];
		if(value==keycmp)
			fr1.funkcja1(it1->first, (it1->second).lin);
		it1++;
	}
	map<string, LINIOLUK_PLUS>::iterator it2=linioluki.begin();
	while(it2!=linioluki.end())
	{	
		string keycmp;
		if((it2->second).prop.find(key)!=(it2->second).prop.end())
			keycmp=(it2->second).prop[key];
		if(value==keycmp)
			fr1.funkcja2(it2->first, (it2->second).llk);
		it2++;
	}
	return true;
}
bool nextra::getkrzywa_keycmp(string key, string value, funkcja_receiver& fr1)
{
	map<string, LINIA_PLUS>::iterator it1=linie.begin();
	while(it1!=linie.end())
	{	
		string keycmp;
		if((it1->second).prop.find(key)!=(it1->second).prop.end())
			keycmp=(it1->second).prop[key];
		if(fr1.cmp(keycmp, value))
			fr1.funkcja1(it1->first, (it1->second).lin);
		it1++;
	}
	map<string, LINIOLUK_PLUS>::iterator it2=linioluki.begin();
	while(it2!=linioluki.end())
	{	
		string keycmp;
		if((it2->second).prop.find(key)!=(it2->second).prop.end())
			keycmp=(it2->second).prop[key];
		if(fr1.cmp(keycmp, value))
			fr1.funkcja2(it2->first, (it2->second).llk);
		it2++;
	}
	return true;
}
