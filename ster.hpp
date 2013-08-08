#include "geom_high.hpp"
#include "program_pob.hpp"
#include "nextra.hpp"
#include <set>
#ifndef STER_HPP
#define STER_HPP
class sterowanie : nextra
{
	set <string> punkty_zaznaczone;
	set <string> krzywe_zaznaczone;
	public:
	sterowanie()
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
};
#endif
