#include "geom_high.hpp"
#include "lista_vek.hpp"
#include "program_pob.hpp"
#ifndef STER_HPP
#define STER_HPP
class sterowanie;
class listavekbis : public lista_vek
{
	sterowanie* ster;
	void lista_zmieniona();
	public:
	listavekbis(sterowanie* ste) : lista_vek()
	{
		ster=ste;
	}
};
class PUNKT_RP : public obiekt_na_liscie_classic
{
	public:
	PUNKT_HIGH* punkt;
	PUNKT_RP(double x, double y)
	{
		punkt=new PUNKT_HIGH(x,y);
	}
	PUNKT_RP(PUNKT_HIGH* pkt)
	{
		punkt=pkt;
	}
	virtual ~PUNKT_RP()
	{
		delete punkt;
	}
};
class KRZYWA_RP : public obiekt_na_liscie_classic
{
	public:
	KRZYWA_HIGH* krzywa;
	KRZYWA_RP(PUNKT_RP* start, PUNKT_RP* stop, double kier1, double kier2)
	{
		krzywa=new LINIOLUK_HIGH(start->punkt, stop->punkt, kier1, kier2);
	}
	KRZYWA_RP(PUNKT_RP* start, PUNKT_RP* stop)
	{
		krzywa=new KRZYWA_HIGH(start->punkt, stop->punkt);
	}
	KRZYWA_RP(KRZYWA_HIGH* kr)
	{
		krzywa=kr;
	}
	virtual ~KRZYWA_RP()
	{
		delete krzywa;
	}
};
class sterowanie
{
	listavekbis punkty;
	listavekbis krzywe;
	listavekbis punkty_zaznaczone;
	listavekbis krzywe_zaznaczone;
	int dodaj_odcinek(PUNKT_RP* start, PUNKT_RP* stop);
	PUNKT_RP* wyszukajhigh(PUNKT_HIGH* foo);
	int dodaj_linioluk(PUNKT_HIGH* start, PUNKT_HIGH* stop, double kier1, double kier2);
	void usunpunkt(PUNKT_HIGH* alfa);
	void usun_krzywa (KRZYWA_HIGH* krz);
	public:
	sterowanie() : punkty(this), krzywe(this), punkty_zaznaczone(this), krzywe_zaznaczone(this)
	{
	}
	void wyslij_do_wtyczki(string polecenie);
	virtual void listy_zmienione();
	vector <int> k_zaz();
	vector <int> p_zaz();
	PUNKT wsp_pkt(int id);
	void dodaj_pkt_do_zaz(int nr);
	void dodaj_krz_do_zaz(int nr);
	int liczba_krz_zaz();
	int liczba_pkt_zaz();
	bool czy_krz_do_zaz(int i);
	bool czy_pkt_do_zaz(int i);
	void usun_krz_z_zaz(int i);
	void usun_pkt_z_zaz(int i);
	void zeruj_zaznaczenie();
	void reverse();
	void zaznaczogr(PUNKT lewydolny, PUNKT prawygorny);
	void zaznaczklucz(string key, string wartosc);
	int wyszukajpunkt(PUNKT alfa, double przyciaganie);
	int wyszukajpunktlubdodaj(PUNKT alfa, double przyciaganie);
	int dodajpunkt(PUNKT alfa);
	int wyszukajkrzywa(PUNKT alfa, double przyciaganie);
	void przesun_zaznaczenie(PUNKT alfa, PUNKT beta);
	int dodaj_odcinek();
	int dodaj_odcinek(int start_id, int stop_id);
	int dodaj_linioluk();
	int dodaj_linioluk(int start_id, int stop_id, double kier1, double kier2);
	void usun_zaznaczenie();
	void usun_calosc();
	void rysuj(narzedzie_do_rysowania* alfa);
	void zapis (string sciezka);
	void zapis_zaznaczone (string sciezka);
	void wczyt (string sciezka);
	void wczyt (string sciezka, PUNKT centrum);
	double odleglosc_od_krzywej(int id, PUNKT alfa);
	double dlugosc(int id);
	PUNKT punkt_na_krzywej(int id, PUNKT alfa);
	PUNKT punktwodl(int id, double odl);
	double kierunekwodl(int id, double odl);
	double odleglosc_na_krzywej(int id, PUNKT alfa);
	PUNKT krzywa_start(int id);
	PUNKT krzywa_stop(int id);
	map <string, string> prop_krz(int id);
	void set_prop_krz(int id, map<string, string> prop);
	map <string, string> prop_pkt(int id);
	void set_prop_pkt(int id, map<string, string> prop);
	/*void obroc(PUNKT start_obrot, PUNKT stop_obrot)
	{
		LINIA l1(start_obrot, stop_obrot);
		double kierunek=l1.kierunek();
		int s1=punkty.size();
		for(int i=0; i<s1; i++)
		{
			LINIA lt(start_obrot, ((PUNKT_RP*)(punkty.obiekt(i)))->punkt->punkt());
			lt.obroc(kierunek);
			(((PUNKT_RP*)(punkty.obiekt(i)))->punkt)->setpkt(lt.koniec().x, lt.koniec().y);
		}
		//TODO ZMIANA KIERUNKÓW LINIOŁUKÓW
	}*/
};
#endif
