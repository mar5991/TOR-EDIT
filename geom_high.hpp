#include "geom.hpp"
#include "program_pob.hpp"
#include <fstream>
#include <map>
#ifndef GEOM_HIGH
#define GEOM_HIGH
class narzedzie_do_rysowania
{
	public:
	virtual void rysuj_luk(LUK alfa, map <string, string> prop, bool zazn)
	{
	}
	virtual void rysuj_punkt(PUNKT alfa, map <string, string> prop, bool zazn)
	{
	}
	virtual void rysuj_linia(LINIA alfa, map <string, string> prop, bool zazn)
	{
	}
	virtual void rysuj_linioluk(LINIOLUK alfa, map <string, string> prop, bool zazn)
	{
	}
};
class PUNKT_HIGH;
class KRZYWA_HIGH
{
	protected:
	PUNKT_HIGH* sta;
	PUNKT_HIGH* sto;
	public:
	map <string, string> data;
	PUNKT_HIGH* start(){return sta;}
	PUNKT_HIGH* stop(){return sto;}
	int proper;
	KRZYWA_HIGH(PUNKT_HIGH* start, PUNKT_HIGH* stop);
	virtual double odleglosc_od_krzywej(PUNKT alfa);
	virtual double dlugosc();
	virtual PUNKT punkt_na_krzywej(PUNKT alfa);
	virtual PUNKT punktwodl(double odl);
	virtual double kierunekwodl(double odl);
	virtual double odleglosc_na_krzywej(PUNKT alfa);
	virtual void rysuj(narzedzie_do_rysowania* alfa, bool zazn);
	virtual void reverse()
	{
		PUNKT_HIGH* tmp=sta;
		sta=sto;
		sto=tmp;
	}
	virtual void podziel(KRZYWA_HIGH** alfa, KRZYWA_HIGH** beta, PUNKT_HIGH* przeciecie, double pprzec);
	virtual void aktualizuj()
	{
	}
	virtual void zapis(ostream* plik)
	{
		(*plik)<<0<<" "<<sta<<" "<<sto<<"\n";
		int s1=data.size();
		(*plik)<<s1<<" ";
		map<string, string>::iterator it1=data.begin();
		while(it1!=data.end())
		{
			(*plik)<<it1->first<<" "<<it1->second<<" ";
			it1++;
		}
		(*plik)<<endl;
	}
	virtual ~KRZYWA_HIGH();
	PUNKT_HIGH* p_start()
	{
		return sta;
	}
	PUNKT_HIGH* p_stop()
	{
		return sto;
	}
};
class PUNKT_HIGH
{
	PUNKT pkt;
	vector <KRZYWA_HIGH*> to_actualize;
	public:
	int proper;
	map <string, string> data;
	PUNKT_HIGH(double x, double y) : pkt(x,y), proper(0)
	{
	}
	virtual ~PUNKT_HIGH()
	{
		int s1=to_actualize.size();
		for(int i=s1-1; i>=0; i--)
		{
			delete to_actualize[i];
			to_actualize.erase(to_actualize.begin()+i);
		}
	}
	void zapis(ostream* plik)
	{
		(*plik)<<this<<" "<<pkt.x<<" "<<pkt.y<<endl;
		int s1=data.size();
		(*plik)<<s1<<" ";
		map<string, string>::iterator it1=data.begin();
		while(it1!=data.end())
		{
			(*plik)<<it1->first<<" "<<it1->second<<" ";
			it1++;
		}
		(*plik)<<endl;
	}
	void setpkt(double x, double y)
	{
		pkt.x=x;
		pkt.y=y;
		int s1=to_actualize.size();
		for(int i=0; i<s1; i++)
			to_actualize[i]->aktualizuj();
	}
	PUNKT punkt()
	{
		return pkt;
	}
	double x()
	{
		return pkt.x;
	}
	double y()
	{
		return pkt.y;
	}
	void dodaj_krzywa(KRZYWA_HIGH* alfa)
	{
		to_actualize.push_back(alfa);
	}
	void usun_krzywa(KRZYWA_HIGH* alfa)
	{
		int s1=to_actualize.size();
		for(int i=s1-1; i>=0; i--)
		{
			if(to_actualize[i]==alfa)
				to_actualize.erase(to_actualize.begin()+i);
		}
	}
};

class LINIOLUK_HIGH : public KRZYWA_HIGH
{
	double kierunek_start;
	double kierunek_stop;
	LINIOLUK luk;
	public:
	double odleglosc_od_krzywej(PUNKT alfa);
	PUNKT punkt_na_krzywej(PUNKT alfa);
	double dlugosc();
	PUNKT punktwodl(double odl);
	double kierunekwodl(double odl);
	double odleglosc_na_krzywej(PUNKT alfa);
	void zapis(ostream* plik);
	void aktualizuj();
	void rysuj(narzedzie_do_rysowania* alfa, bool zazn);
	void reverse();
	LINIOLUK_HIGH(PUNKT_HIGH* sta, PUNKT_HIGH* sto, double k1, double k2) : KRZYWA_HIGH(sta, sto), kierunek_start(k1), kierunek_stop(k2), luk(p_start()->punkt(), p_stop()->punkt(), kierunek_start, kierunek_stop)
	{}
};
#endif
