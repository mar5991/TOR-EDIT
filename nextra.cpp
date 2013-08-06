#include "nextra.hpp"
#include <set>
using namespace std;
bool nextra::setpunkt(string nazwa, PUNKT pkt)
{
	if(punkty.find(nazwa)!=punkty.end())
		return false;
	PUNKT_PLUS nowy;
	nowy.pkt=pkt;
	punkty[nazwa]=nowy;
	return true;
}
bool nextra::setkrzywa(string nazwa, string pkt_start, string pkt_stop)
{
	if(punkty.find(pkt_start)==punkty.end())
		return false;
	if(punkty.find(pkt_stop)==punkty.end())
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
	return true;
}
bool nextra::setpunkt_prop(string nazwa, string key, string value)
{
	if(punkty.find(nazwa)==punkty.end())
		return false;
	punkty[nazwa].prop[key]=value;
	return true;
}
bool nextra::setkrzywa_prop(string nazwa, string key, string value)
{
	if(linie.find(nazwa)==linie.end())
	{
		if(linioluki.find(nazwa)==linioluki.end())
			return false;
		linioluki[nazwa].prop[key]=value;
	}
	linie[nazwa].prop[key]=value;
	return true;
}
bool nextra::deletepunkt_prop(string nazwa, string key)
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
}
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
	if(linie.find(nazwa)==linie.end())
	{
		if(linioluki.find(nazwa)==linioluki.end())
			return false;
		LINIOLUK_PLUS it3=linioluki[nazwa];
		(punkty[it3.pkt1]).linie_powiazane.erase(punkty[it3.pkt1].linie_powiazane.find(nazwa));
		(punkty[it3.pkt2]).linie_powiazane.erase(punkty[it3.pkt2].linie_powiazane.find(nazwa));
	}
	LINIA_PLUS it3=linie[nazwa];
	punkty[it3.pkt1].linie_powiazane.erase(punkty[it3.pkt1].linie_powiazane.find(nazwa));
	punkty[it3.pkt2].linie_powiazane.erase(punkty[it3.pkt2].linie_powiazane.find(nazwa));
	return true;
}
bool nextra::getpunkt_all(void(*funkcja1)(string nazwa, PUNKT pkt))
{
	map <string, PUNKT_PLUS>::iterator it1=punkty.begin();
	while(it1!=punkty.end())
	{
		funkcja1(it1->first, (it1->second).pkt);
		it1++;
	}
	return true;
}
bool nextra::getkrzywa_all(void(*funkcja1)(string nazwa, LINIA pkt), void(*funkcja2)(string nazwa, LINIOLUK pkt))
{
	map<string, LINIA_PLUS>::iterator it1=linie.begin();
	while(it1!=linie.end())
	{
		funkcja1(it1->first, (it1->second).lin);
		it1++;
	}
	map<string, LINIOLUK_PLUS>::iterator it2=linioluki.begin();
	while(it2!=linioluki.end())
	{
		funkcja2(it2->first, (it2->second).llk);
		it2++;
	}
	return true;
}
bool nextra::getpunkt_key(string key, string value, void(*funkcja1)(string, PUNKT))
{
	map <string, PUNKT_PLUS>::iterator it1=punkty.begin();
	while(it1!=punkty.end())
	{
		if(it1->first==value)
			funkcja1(it1->first, (it1->second).pkt);
		it1++;
	}
	return true;
}

bool nextra::getpunkt_key(string key, string value, bool(*cmp)(string, string), void(*funkcja1)(string, PUNKT))
{
	map <string, PUNKT_PLUS>::iterator it1=punkty.begin();
	while(it1!=punkty.end())
	{
		if(cmp(it1->first, value))
			funkcja1(it1->first, (it1->second).pkt);
		it1++;
	}
	return true;
}

bool nextra::getkrzywa_key(string key, string value, void(*funkcja1)(string, LINIA), void(*funkcja2)(string, LINIOLUK))
{
	map<string, LINIA_PLUS>::iterator it1=linie.begin();
	while(it1!=linie.end())
	{
		if(value==it1->first)
			funkcja1(it1->first, (it1->second).lin);
		it1++;
	}
	map<string, LINIOLUK_PLUS>::iterator it2=linioluki.begin();
	while(it2!=linioluki.end())
	{
		if(value==it2->first)
			funkcja2(it2->first, (it2->second).llk);
		it2++;
	}
	return true;
}
bool nextra::getkrzywa_key(string key, string value, bool(*cmp)(string, string), void(*funkcja1)(string, LINIA), void(*funkcja2)(string, LINIOLUK))
{
	map<string, LINIA_PLUS>::iterator it1=linie.begin();
	while(it1!=linie.end())
	{
		if(cmp(it1->first, value))
			funkcja1(it1->first, (it1->second).lin);
		it1++;
	}
	map<string, LINIOLUK_PLUS>::iterator it2=linioluki.begin();
	while(it2!=linioluki.end())
	{
		if(cmp(it2->first, value))
			funkcja2(it2->first, (it2->second).llk);
		it2++;
	}
	return true;
}
