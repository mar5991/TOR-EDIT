#include "geom_high.hpp"
KRZYWA_HIGH::KRZYWA_HIGH(PUNKT_HIGH* start, PUNKT_HIGH* stop) : sta(start), sto(stop), proper(0)
{
	sta->dodaj_krzywa(this);
	sto->dodaj_krzywa(this);
}
KRZYWA_HIGH::~KRZYWA_HIGH()
{
	sta->usun_krzywa(this);
	sto->usun_krzywa(this);
}
double KRZYWA_HIGH::odleglosc_od_krzywej(PUNKT alfa)
{
	LINIA l1(sta->punkt(), sto->punkt());
	return l1.odleglosc(alfa);
}
double KRZYWA_HIGH::dlugosc()
{
	LINIA l1(sta->punkt(), sto->punkt());
	return l1.dlugosc();
}
PUNKT KRZYWA_HIGH::punkt_na_krzywej(PUNKT alfa)
{
	LINIA l1(sta->punkt(), sto->punkt());
	return l1.punkt_na_odc(alfa);
}
PUNKT KRZYWA_HIGH::punktwodl(double odl)
{
	LINIA l1(sta->punkt(), sto->punkt());
	return l1.odlodpocz(odl);
}
double KRZYWA_HIGH::kierunekwodl(double odl)
{
	LINIA l1(sta->punkt(), sto->punkt());
	return l1.kierunek();
}
double KRZYWA_HIGH::odleglosc_na_krzywej(PUNKT alfa)
{
	LINIA l1(sta->punkt(), sto->punkt());
	return l1.wjakiejodl(alfa);
}
void KRZYWA_HIGH::rysuj(narzedzie_do_rysowania* alfa, bool zazn)
{
	LINIA l1(sta->punkt(), sto->punkt());
	alfa->rysuj_linia(l1, data, zazn);
}
void KRZYWA_HIGH::podziel(KRZYWA_HIGH** alfa, KRZYWA_HIGH** beta, PUNKT_HIGH* przeciecie, double pprzec)
{
	PUNKT pp=punktwodl(pprzec);
	przeciecie->setpkt(pp.x, pp.y);
	*alfa=new KRZYWA_HIGH(sta, przeciecie);
	*beta=new KRZYWA_HIGH(przeciecie, sto);
}
	double LINIOLUK_HIGH::odleglosc_od_krzywej(PUNKT alfa)
	{
		return luk.odleglosc_od_krzywej(alfa);
	}
	PUNKT LINIOLUK_HIGH::punkt_na_krzywej(PUNKT alfa)
	{
		return luk.punkt_na_krzywej(alfa);	
	}
	double LINIOLUK_HIGH::dlugosc()
	{
		return luk.dlugosc();
	}
	PUNKT LINIOLUK_HIGH::punktwodl(double odl)
	{
		return luk.punktwodl(odl);
	}
	double LINIOLUK_HIGH::kierunekwodl(double odl)
	{
		return luk.kierunekwodl(odl);
	}
	double LINIOLUK_HIGH::odleglosc_na_krzywej(PUNKT alfa)
	{
		return luk.odleglosc_na_krzywej(alfa);	
	}
	void LINIOLUK_HIGH::zapis(ostream* plik)
	{
		(*plik)<<1<<" "<<sta<<" "<<sto<<" "<<kierunek_start<<" "<<kierunek_stop<<"\n";
		int s1=data.size();
		(*plik)<<s1<<" ";
		map<string, string>::iterator it1=data.begin();
		while(it1!=data.end())
		{
			(*plik)<<it1->first<<" "<<it1->second<<" ";
			it1++;
		}
		(*plik)<<"\n";

	}
	void LINIOLUK_HIGH::aktualizuj()
	{
		luk=LINIOLUK(p_start()->punkt(), p_stop()->punkt(), kierunek_start, kierunek_stop);
	}
	void LINIOLUK_HIGH::rysuj(narzedzie_do_rysowania* alfa, bool zazn)
	{
		alfa->rysuj_linioluk(luk, data, zazn);
	}
	void LINIOLUK_HIGH::reverse()
	{
		PUNKT_HIGH* tmp=sta;
		sta=sto;
		sto=tmp;
		double tmp1=kierunek_stop;
		kierunek_stop=stand_kierunek(M_PI+kierunek_start);
		kierunek_start=stand_kierunek(M_PI+tmp1);
		aktualizuj();
	}

