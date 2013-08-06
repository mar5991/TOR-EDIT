#ifndef GEOM
#define GEOM
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define sqr(x) ((x)*(x))
using namespace std;

double stand_kierunek(double wart); // konwertuje wartość w radianach do przedziału <-PI; PI>
double odl_mkier_niez_ruchem_wskaz(double kier1, double kier2);
double odl_mkier_zgod_ruchem_wskaz(double kier1, double kier2);

struct PUNKT
{
	double x;
	double y;
	bool operator==(PUNKT p);
	PUNKT(double xx, double yy);
	bool czywprost(PUNKT lewydolny, PUNKT prawygorny); //czy punkt leży w prostokącie, prostokąt określony jako dwa punkty lewydolny i prawygorny
};

struct KRZYWA
{
	virtual double odleglosc_od_krzywej(PUNKT alfa){};
	virtual PUNKT punkt_na_krzywej(PUNKT alfa){};
	virtual double dlugosc(){};
	virtual PUNKT start(){};
	virtual PUNKT stop(){};
	virtual PUNKT punktwodl(double odl){};
	virtual double kierunekwodl(double odl){};
	virtual double odleglosc_na_krzywej(PUNKT alfa){};
};

struct LINIA : KRZYWA
{
	LINIA() {}
	double x1;
	double x2;
	double y1;
	double y2;
	LINIA(double xx1, double yy1, double xx2, double yy2);
	LINIA(PUNKT alfa, PUNKT beta);
	LINIA(PUNKT alfa, double kierunek, double odl);
	PUNKT poczatek(); // zwraca punkt początkowy
	PUNKT koniec(); //zwraca punkt końcowy
	PUNKT start()
	{
		cout<<"start!"<<poczatek().x<<" "<<poczatek().y<<endl;
		return poczatek();
	}
	PUNKT stop()
	{
		return koniec();
	}
	double dlugosc();
	PUNKT odlodpocz(double k); //zwraca punkt leżący na odległości k od początku
	LINIA reverse(); //zamień początek i koniec
	void do_prostokata(PUNKT* lewydolny, PUNKT* prawygorny);
	double odleglosc_prosta(PUNKT beta);
	int pprze_prosta2(LINIA beta, PUNKT* pprzec); //0 - nie, 1 - tak, 2 - nieskonczenie, pprzec - wskaźnik na punkt przecięcia prostych
	int pprze(LINIA beta, PUNKT* pprzec);
	int pprze_prosta(LINIA beta, PUNKT* pprzec);
	double kierunek();
	PUNKT punkt_na_prostej(PUNKT beta);
	double odleglosc(PUNKT beta);
	PUNKT punkt_na_odc(PUNKT beta);
	double wjakiejodl(PUNKT beta);
	LINIA obroc(double kierun); // zwraca linię obróconą o kierun
	bool poktorejstronie(PUNKT beta); //po której stronie prostej (patrząc od początku w kierunku końca) znajduje się punkt: 1 - po prawej, 0 - po lewej
	double odleglosc_od_krzywej(PUNKT alfa)
	{
		return odleglosc(alfa);
	}
	PUNKT punkt_na_krzywej (PUNKT alfa)
	{
		return punkt_na_prostej(alfa);
	}
	PUNKT punktwodl(double odl)
	{
		return odlodpocz(odl);
	}
	double kierunekwodl(double odl)
	{
		cout<<"alalaon"<<endl;
		return kierunek();
	}
	double odleglosc_na_krzywej(PUNKT alfa)
	{
		return wjakiejodl(alfa);
	}
};

struct LUK : KRZYWA
{
	LUK() {}
	double x_sr; //współrzędna x środka łuku
	double y_sr; //współrzędna y środka łuku
	double x_st; //współrzędna x punktu startowego na łuku
	double y_st; //współrzędna y punktu startowego na łuku
	double wycinek; //wartość w radianach, określa długość łuku. liczba ujemna: łuk biegnie przeciwnie do ruchu wskazówek zegara
	LUK(PUNKT srodek, double r); //tworzy pełen okrąg o środku 'środek' i promieniu 'r'
	double promien();
	PUNKT srodek();
	PUNKT poczatek();
	double kierunek_start();
	bool czy_kierunek_do_luku(double kier);
	double dlugosc();
	PUNKT odlodkier(double kierunek);
	PUNKT koniec();
	PUNKT start()
	{
		return poczatek();
	}
	PUNKT stop()
	{
		return koniec();
	}
	PUNKT odlodpocz(double odl);
	PUNKT punkt_okrag(PUNKT alfa);
	double odl_okrag(PUNKT alfa);
	PUNKT punkt_luk(PUNKT alfa);
	double wjakiejodl(PUNKT alfa);
	double odl_luk(PUNKT alfa);
	LUK(PUNKT srodek, PUNKT alfa, double wycin) : x_sr(srodek.x), y_sr(srodek.y), x_st(alfa.x), y_st(alfa.y), wycinek(wycin)
	{}
	LUK(PUNKT alfa, PUNKT beta, PUNKT gamma, bool czy_okrag);
	LUK(PUNKT alfa, PUNKT beta, PUNKT srodek, int type);
	/*  tworzy łuk od alfa do beta ze środkiem sr, type=0 : zgodnie z ruchem
	 *  type=1 : niezgodnie z ruchem wskazówek, type=2 : najkrócej
	 *  type=3 : najdłużej, type=4 : pełen okrąg */
	LUK(LINIA srednica); //tworzy pełen okrąg oparty na srednicy
	double odleglosc_od_krzywej(PUNKT alfa)
	{
		return odl_luk(alfa);
	}
	PUNKT punkt_na_krzywej(PUNKT alfa)
	{
		return punkt_luk(alfa);
	}
	PUNKT punktwodl(double odl)
	{
		return odlodpocz(odl);
	}
	double kierunekwodl(double odl)
	{
		PUNKT pp=odlodpocz(odl);
		LINIA lk(srodek(), pp);
		if(wycinek>0)
			return stand_kierunek(lk.kierunek()+M_PI/2);
		return stand_kierunek(lk.kierunek()-M_PI/2);
	}
	double odleglosc_na_krzywej(PUNKT alfa)
	{
		return wjakiejodl(alfa);
	}
};
struct LINIOLUK : KRZYWA
{
	LINIA l1;
	LUK l2;
	LINIA l3;
	double kierunek_start;
	double kierunek_stop;
	public:
	PUNKT start()
	{
		return l1.start();
	}
	PUNKT stop()
	{
		return l3.stop();
	}
	LINIA linia1()
	{
		return l1;
	}
	LUK luk()
	{
		return l2;
	}
	LINIA linia2()
	{
		return l3;
	}
	double odleglosc_od_krzywej(PUNKT alfa)
	{
		double k1, k2, k3;
		k1=l1.odleglosc(alfa);
		k3=l3.odleglosc(alfa);
		k2=l2.odl_luk(alfa);
		return min(min(k1,k2),k3);
	}
	PUNKT punkt_na_krzywej(PUNKT alfa)
	{	
		double k1, k2, k3;
		k1=l1.odleglosc(alfa);
		k3=l3.odleglosc(alfa);
		k2=l2.odl_luk(alfa);
		PUNKT a1=l1.punkt_na_odc(alfa);
		PUNKT a2=l2.punkt_luk(alfa);
		PUNKT a3=l3.punkt_na_odc(alfa);
		double k_min=min(min(k1,k2),k3);
		if(k1==k_min)
			return a1;
		if(k2==k_min)
			return a2;
		return a3;
	}
	double dlugosc()
	{
		return l1.dlugosc()+l2.dlugosc()+l3.dlugosc();
	}
	PUNKT punktwodl(double odl)
	{
		if(odl<l1.dlugosc())
			return l1.odlodpocz(odl);
		odl-=l1.dlugosc();
		if(odl<l2.dlugosc())
			return l2.odlodpocz(odl);
		odl-=l2.dlugosc();
		return l3.odlodpocz(odl);
	}
	double kierunekwodl(double odl)
	{
		if(odl<0.001)
			return kierunek_start;
		if(odl>dlugosc()-0.001)
			return kierunek_stop;
		if(odl<l1.dlugosc())
			return l1.kierunek();
		odl-=l1.dlugosc();
		if(odl<l2.dlugosc())
		{
			PUNKT pp=l2.odlodpocz(odl);
			LINIA lk(l2.srodek(), pp);
			if(l2.wycinek>0)
				return stand_kierunek(lk.kierunek()+M_PI/2);
			return stand_kierunek(lk.kierunek()-M_PI/2);
		}
		odl-=l2.dlugosc();
		return l3.kierunek();
	}
	double odleglosc_na_krzywej(PUNKT alfa)
	{	
		double k1, k2, k3;
		k1=l1.odleglosc(alfa);
		k3=l3.odleglosc(alfa);
		k2=l2.odl_luk(alfa);
		PUNKT a1=l1.punkt_na_odc(alfa);
		PUNKT a2=l2.punkt_luk(alfa);
		PUNKT a3=l3.punkt_na_odc(alfa);
		cout<<k1<<" "<<k2<<" "<<k3<<endl;
		double k_min=min(min(k1,k2),k3);
		if(k1==k_min)
			return l1.wjakiejodl(a1);
		if(k2==k_min)
			return l2.wjakiejodl(a2)+l1.dlugosc();
		return l3.wjakiejodl(a3)+l1.dlugosc()+l2.dlugosc();
	}
	LINIOLUK(PUNKT start, PUNKT stop, double k1, double k2)
	{
		kierunek_start=k1;
		kierunek_stop=k2;
		LINIA poczatkowa(start, kierunek_start, 1);
		LINIA koncowa(stop, stand_kierunek(kierunek_stop-M_PI), 100);
		PUNKT pprzec(0,0);
		int wart=poczatkowa.pprze_prosta2(koncowa, &pprzec);
		if(wart==1)
		{
			LINIA pbis(pprzec, start);
			LINIA kbis(pprzec, stop);
			double dlk=min(pbis.dlugosc(), kbis.dlugosc());
			PUNKT k1=pbis.odlodpocz(dlk);
			PUNKT k2=kbis.odlodpocz(dlk);
			LINIA prom1(k1, stand_kierunek(pbis.kierunek()+M_PI/2), 100);
			LINIA prom2(k2, stand_kierunek(kbis.kierunek()+M_PI/2), 100);
			l1=LINIA(start, k1);
			l3=LINIA(k2, stop);
			PUNKT srokr(0, 0);
			prom1.pprze_prosta2(prom2, &srokr);
			l2=LUK(k1, k2, srokr, 2);
		}
		else
		{
			l1=LINIA(start, stop);
			l2=LUK(stop, stop, stop, 2);
			l3=LINIA(stop, stop);
		}
	}
};
struct WIELOKAT
{
	vector <PUNKT> punkty;
	WIELOKAT(vector <PUNKT> pkt) : punkty(pkt) {}
	double pole()
	{
		int s1=punkty.size();
		double wynik=0;
		for(int i=0; i<s1; i++)
			wynik+=punkty[i].x*punkty[(i+1)%s1].y-punkty[(i+1)%s1].x*punkty[i].y;
		return wynik;
	}
};
#endif
