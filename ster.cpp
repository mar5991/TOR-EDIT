#include "ster.hpp"
void listavekbis::lista_zmieniona()
{
	ster->listy_zmienione();
}
	int sterowanie::dodaj_odcinek(PUNKT_RP* start, PUNKT_RP* stop)
	{
		krzywe.dodaj_obiekt(new KRZYWA_RP(start, stop));
		return krzywe.size()-1;
	}
	PUNKT_RP* sterowanie::wyszukajhigh(PUNKT_HIGH* foo)
	{
		int s1=punkty.size();
		for(int i=0; i<s1; i++)
		{
			if(((PUNKT_RP*)(punkty.obiekt(i)))->punkt==foo)
				return ((PUNKT_RP*)(punkty.obiekt(i)));
		}
		return 0;
	}
	int sterowanie::dodaj_linioluk(PUNKT_HIGH* start, PUNKT_HIGH* stop, double kier1, double kier2)
	{
		if(start==stop)
			return -1;
		KRZYWA_HIGH* foo=new LINIOLUK_HIGH(start, stop, kier1, kier2);
		krzywe.dodaj_obiekt(new KRZYWA_RP(foo));
		return krzywe.size()-1;
	}
	void sterowanie::usunpunkt(PUNKT_HIGH* alfa)
	{
		int s2=krzywe.size();
		for(int i=s2-1; i>=0; i--)
		{
			KRZYWA_HIGH* kt=((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa;
			if(kt->start()==alfa || kt->stop()==alfa)
			{
				delete ((KRZYWA_RP*)(krzywe.obiekt(i)));
			}
		}
		int s1=punkty.size();
		for(int i=s1-1; i>=0; i--)
		{
			if(alfa==((PUNKT_RP*)(punkty.obiekt(i)))->punkt)
			{
				delete punkty.obiekt(i);
			}
		}
	}
	void sterowanie::usun_krzywa (KRZYWA_HIGH* krz)
	{
		int s1=krzywe.size();
		for(int i=s1-1; i>=0; i--)
		{
			if(((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa==krz)
			{
				delete ((KRZYWA_RP*)(krzywe.obiekt(i)));
				return;
			}
		}
	}
	void sterowanie::wyslij_do_wtyczki(string polecenie)
	{
		program_pob prog(polecenie);
		stringstream program;
		int s1=punkty.size();
		int s2=krzywe.size();
		program<<s1;
		program<<" ";
		program<<s2;
		program<<endl;
		for(int i=0; i<s1; i++)
		{
			if(czy_pkt_do_zaz(i))
				program<<"1 ";
			else
				program<<"0 ";
			((PUNKT_RP*)(punkty.obiekt(i)))->punkt->zapis(&program);
		}
		for(int i=0; i<s2; i++)
		{
			if(czy_krz_do_zaz(i))
				program<<"1 ";
			else
				program<<"0 ";
			((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->zapis(&program);
		}
		program<<endl;
		program<<endl;
		prog.zapisz(program);
		usun_calosc();
		stringstream plik;
		prog.wczytaj(plik);
		plik>>s1>>s2;
		map <string, int> mapadrogowa;
		cout<<"ok1x"<<endl;
		for(int i=0; i<s1; i++)
		{
			bool zaz;
			string alfa;
			double x, y;
			plik>>zaz>>alfa>>x>>y;
			mapadrogowa[alfa]=punkty.size();
			PUNKT_HIGH* foo=new PUNKT_HIGH(x,y);
			PUNKT_RP* fp=new PUNKT_RP(foo);
			punkty.dodaj_obiekt(fp);
			int a1=punkty.size()-1;
			int sk;
			plik>>sk;
			for(int j=0; j<sk; j++)
			{
				string ap, bp;
				plik>>ap>>bp;
				PUNKT_HIGH* pt1=((PUNKT_RP*)(punkty.obiekt(a1)))->punkt;
				pt1->data[ap]=bp;
			}
			if(zaz)
				punkty_zaznaczone.dodaj_obiekt(fp);
		}
		cout<<"ok1y"<<endl;
		for(int i=0; i<s2; i++)
		{
			bool zaz;
			int type;
			plik>>zaz>>type;
			if(type==0)
			{
				string alfa, beta;
				plik>>alfa>>beta;
				int a1=dodaj_odcinek(((PUNKT_RP*)(punkty.obiekt(mapadrogowa[alfa]))), ((PUNKT_RP*)(punkty.obiekt(mapadrogowa[beta]))));
				int sk;
				plik>>sk;
				for(int j=0; j<sk; j++)
				{
					string ap, bp;
					plik>>ap>>bp;
					KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(a1)))->krzywa;
					kt1->data[ap]=bp;
				}
			}
			if(type==1)
			{
				string alfa, beta;
				plik>>alfa>>beta;
				double k1, k2;
				plik>>k1>>k2;
				int a1=dodaj_linioluk(((PUNKT_RP*)(punkty.obiekt(mapadrogowa[alfa])))->punkt, ((PUNKT_RP*)(punkty.obiekt(mapadrogowa[beta])))->punkt, k1, k2);
				int sk;
				plik>>sk;
				for(int j=0; j<sk; j++)
				{
					string ap, bp;
					plik>>ap>>bp;
					KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(a1)))->krzywa;
					kt1->data[ap]=bp;
				}
			}
			if(zaz)
				krzywe_zaznaczone.dodaj_obiekt(krzywe.obiekt(krzywe.size()-1));
		}
		cout<<"ok1z"<<endl;
	}

	void sterowanie::listy_zmienione() {}
	vector <int> sterowanie::k_zaz()
	{
		vector <int> wynik;
		int s1=krzywe_zaznaczone.size();
		for(int i=0; i<s1; i++)
			wynik.push_back((krzywe_zaznaczone.obiekt(i))->pozycja(&krzywe));
		return wynik;
	}
	vector <int> sterowanie::p_zaz()
	{
		vector <int> wynik;
		int s1=punkty_zaznaczone.size();
		for(int i=0; i<s1; i++)
			wynik.push_back((punkty_zaznaczone.obiekt(i))->pozycja(&punkty));
		return wynik;
	}
	PUNKT sterowanie::wsp_pkt(int id)
	{
		return ((PUNKT_RP*)(punkty.obiekt(id)))->punkt->punkt();
	}
	void sterowanie::dodaj_pkt_do_zaz(int nr)
	{
		punkty_zaznaczone.dodaj_obiekt(punkty.obiekt(nr));
	}
	void sterowanie::dodaj_krz_do_zaz(int nr)
	{
		krzywe_zaznaczone.dodaj_obiekt(krzywe.obiekt(nr));
	}
	int sterowanie::liczba_krz_zaz()
	{
		return krzywe_zaznaczone.size();
	}
	int sterowanie::liczba_pkt_zaz()
	{
		return punkty_zaznaczone.size();
	}
	bool sterowanie::czy_krz_do_zaz(int i)
	{
		return krzywe.obiekt(i)->czy_do_listy(&krzywe_zaznaczone);
	}
	bool sterowanie::czy_pkt_do_zaz(int i)
	{
		return punkty.obiekt(i)->czy_do_listy(&punkty_zaznaczone);
	}
	void sterowanie::usun_krz_z_zaz(int i)
	{
		krzywe_zaznaczone.usun_obiekt(krzywe.obiekt(i));
	}
	void sterowanie::usun_pkt_z_zaz(int i)
	{
		punkty_zaznaczone.usun_obiekt(punkty.obiekt(i));
	}
	void sterowanie::zeruj_zaznaczenie()
	{
		punkty_zaznaczone.wyczysc_liste();
		krzywe_zaznaczone.wyczysc_liste();
	}
	void sterowanie::reverse()
	{
		int s1=krzywe_zaznaczone.size();
		for(int i=0; i<s1; i++)
		{
			((KRZYWA_RP*)(krzywe_zaznaczone.obiekt(i)))->krzywa->reverse();
		}
	}
	void sterowanie::zaznaczogr(PUNKT lewydolny, PUNKT prawygorny)
	{
		double lewo=min(lewydolny.x, prawygorny.x);
		double prawo=max(lewydolny.x, prawygorny.x);
		double dol=min(lewydolny.y, prawygorny.y);
		double gora=max(lewydolny.y, prawygorny.y);
		lewydolny=PUNKT(lewo, dol);
		prawygorny=PUNKT(prawo, gora);
		int s1=punkty.size();
		for(int i=0; i<s1; i++)
		{
			PUNKT alfa=((PUNKT_RP*)(punkty.obiekt(i)))->punkt->punkt();
			if(alfa.x>lewydolny.x && alfa.x<prawygorny.x)
				if(alfa.y>lewydolny.y && alfa.y<prawygorny.y)
				{
					punkty_zaznaczone.dodaj_obiekt(punkty.obiekt(i));
				}
		}
		s1=krzywe.size();
		for(int i=0; i<s1; i++)
		{
			PUNKT_RP* p1=wyszukajhigh(((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->start());
			PUNKT_RP* p2=wyszukajhigh(((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->stop());
			if(p1->czy_do_listy(&punkty_zaznaczone) && p2->czy_do_listy(&punkty_zaznaczone))
			{
				krzywe_zaznaczone.dodaj_obiekt(krzywe.obiekt(i));
			}
		}
	}
	void sterowanie::zaznaczklucz(string key, string wartosc)
	{
		int s1=punkty.size();
		for(int i=0; i<s1; i++)
		{
			map<string, string>::iterator it1=(((PUNKT_RP*)(punkty.obiekt(i)))->punkt->data).find(key);
			if(it1!=(((PUNKT_RP*)(punkty.obiekt(i)))->punkt->data).end())
				if(it1->second==wartosc)
					dodaj_pkt_do_zaz(i);
		}
		s1=krzywe.size();
		for(int i=0; i<s1; i++)
		{
			map<string, string>::iterator it1=(((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->data).find(key);
			if(it1!=(((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->data).end())
				if(it1->second==wartosc)
					dodaj_krz_do_zaz(i);

		}
	}
	int sterowanie::wyszukajpunkt(PUNKT alfa, double przyciaganie)
	{
		int wynik=-1;
		int s1=punkty.size();
		double dlmax=przyciaganie;
		for(int i=0; i<s1; i++)
		{
			LINIA l1(alfa, ((PUNKT_RP*)(punkty.obiekt(i)))->punkt->punkt());
			if(l1.dlugosc()<dlmax)
			{
				dlmax=l1.dlugosc();
				wynik=i;
			}
		}
		return wynik;
	}
	int sterowanie::wyszukajpunktlubdodaj(PUNKT alfa, double przyciaganie)
	{
		int foo=wyszukajpunkt(alfa,przyciaganie);
		if(foo==-1)
			return dodajpunkt(alfa);
		return foo;
	}
	int sterowanie::dodajpunkt(PUNKT alfa)
	{
		PUNKT_RP* foo=new PUNKT_RP(alfa.x, alfa.y);
		punkty.dodaj_obiekt(foo);
		return punkty.size()-1;
	}
	int sterowanie::wyszukajkrzywa(PUNKT alfa, double przyciaganie)
	{
		int wynik=-1;
		int s1=krzywe.size();
		double dlmax=przyciaganie;
		for(int i=0; i<s1; i++)
		{
			if(((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->odleglosc_od_krzywej(alfa)<dlmax)
			{
				dlmax=((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->odleglosc_od_krzywej(alfa);
				wynik=i;
			}
		}
		return wynik;
	}
	void sterowanie::przesun_zaznaczenie(PUNKT alfa, PUNKT beta)
	{
		PUNKT w_przes(beta.x-alfa.x, beta.y-alfa.y);
		int s1=punkty_zaznaczone.size();
		for(int i=0; i<s1; i++)
		{
			PUNKT_HIGH* p1=((PUNKT_RP*)(punkty_zaznaczone.obiekt(i)))->punkt;
			p1->setpkt(p1->punkt().x+w_przes.x, p1->punkt().y+w_przes.y);
		}
	}
	int sterowanie::dodaj_odcinek()
	{
		if(punkty_zaznaczone.size()==2)
			return dodaj_odcinek((PUNKT_RP*)(punkty_zaznaczone.obiekt(0)), (PUNKT_RP*)(punkty_zaznaczone.obiekt(1)));
		return -1;
	}
	int sterowanie::dodaj_odcinek(int start_id, int stop_id)
	{
		return dodaj_odcinek(((PUNKT_RP*)(punkty.obiekt(start_id))),((PUNKT_RP*)(punkty.obiekt(stop_id))));
	}
	int sterowanie::dodaj_linioluk()
	{
		if(krzywe_zaznaczone.size()==2)
		{
			KRZYWA_HIGH* k1=((KRZYWA_RP*)(krzywe_zaznaczone.obiekt(0)))->krzywa;
			KRZYWA_HIGH* k2=((KRZYWA_RP*)(krzywe_zaznaczone.obiekt(1)))->krzywa;
		return dodaj_linioluk(k1->p_start(), k2->p_stop(), k1->kierunekwodl(0), k2->kierunekwodl(k2->dlugosc()));
		}
		return -1;
	}
	int sterowanie::dodaj_linioluk(int start_id, int stop_id, double kier1, double kier2)
	{
		return dodaj_linioluk(((PUNKT_RP*)(punkty.obiekt(start_id)))->punkt,((PUNKT_RP*)(punkty.obiekt(stop_id)))->punkt, kier1,kier2);
	}
	void sterowanie::usun_zaznaczenie()
	{
		int s1=krzywe_zaznaczone.size();
		for(int i=s1-1; i>=0; i--)
			delete krzywe_zaznaczone.obiekt(i);
		s1=punkty_zaznaczone.size();
		for(int i=s1-1; i>=0; i--)
		{
			usunpunkt(((PUNKT_RP*)(punkty_zaznaczone.obiekt(i)))->punkt);
		}
	}
	void sterowanie::usun_calosc()
	{
		int s1=krzywe.size();
		for(int i=s1-1; i>=0; i--)
			delete krzywe.obiekt(i);
		s1=punkty.size();
		for(int i=s1-1; i>=0; i--)
		{
			usunpunkt(((PUNKT_RP*)(punkty.obiekt(i)))->punkt);
		}
	}
	void sterowanie::rysuj(narzedzie_do_rysowania* alfa)
	{
		int s1=krzywe.size();
		for(int i=0; i<s1; i++)
			((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->rysuj(alfa, czy_krz_do_zaz(i));
		int s2=punkty.size();
		for(int i=0; i<s2; i++)
			alfa->rysuj_punkt(((PUNKT_RP*)(punkty.obiekt(i)))->punkt->punkt(), ((PUNKT_RP*)(punkty.obiekt(i)))->punkt->data, czy_pkt_do_zaz(i));
	}
	void sterowanie::zapis(string sciezka)
	{
		fstream plik(sciezka.c_str(), iostream::out);
		int s1=punkty.size();
		int s2=krzywe.size();
		plik<<s1<<" "<<s2<<endl;
		for(int i=0; i<s1; i++)
		{
			PUNKT alfa=((PUNKT_RP*)(punkty.obiekt(i)))->punkt->punkt();
			((PUNKT_RP*)(punkty.obiekt(i)))->punkt->zapis(&plik);
		}
		for(int i=0; i<s2; i++)
			((KRZYWA_RP*)(krzywe.obiekt(i)))->krzywa->zapis(&plik);
	}
	void sterowanie::zapis_zaznaczone(string sciezka)
	{
		fstream plik(sciezka.c_str(), iostream::out);
		int s1=punkty_zaznaczone.size();
		int s2=krzywe_zaznaczone.size();
		plik<<s1<<" "<<s2<<endl;
		for(int i=0; i<s1; i++)
		{
			PUNKT alfa=((PUNKT_RP*)(punkty_zaznaczone.obiekt(i)))->punkt->punkt();
			((PUNKT_RP*)(punkty_zaznaczone.obiekt(i)))->punkt->zapis(&plik);
		}
		for(int i=0; i<s2; i++)
			((KRZYWA_RP*)(krzywe_zaznaczone.obiekt(i)))->krzywa->zapis(&plik);
	}
	void sterowanie::wczyt(string sciezka)
	{
		wczyt(sciezka, PUNKT(0,0));
	}
	void sterowanie::wczyt(string sciezka, PUNKT centrum)
	{
		fstream plik(sciezka.c_str(), iostream::in);
		int s1, s2;
		plik>>s1>>s2;
		cout<<s1<<" "<<s2<<endl;
		map <string, int> mapadrogowa;
		for(int i=0; i<s1; i++)
		{
			string alfa;
			double x, y;
			plik>>alfa>>x>>y;
			mapadrogowa[alfa]=punkty.size();
			PUNKT_HIGH* foo=new PUNKT_HIGH(centrum.x+x,centrum.y+y);
			PUNKT_RP* prp=new PUNKT_RP(foo);
			punkty.dodaj_obiekt(prp);
			int a1=punkty.size()-1;
			int sk;
			plik>>sk;
			for(int j=0; j<sk; j++)
			{
				string ap, bp;
				plik>>ap>>bp;
				PUNKT_HIGH* pt1=((PUNKT_RP*)(punkty.obiekt(a1)))->punkt;
				pt1->data[ap]=bp;
			}
		}
		for(int i=0; i<s2; i++)
		{
			int type;
			plik>>type;
			if(type==0)
			{
				string alfa, beta;
				plik>>alfa>>beta;
				int a1=dodaj_odcinek(((PUNKT_RP*)(punkty.obiekt(mapadrogowa[alfa]))), ((PUNKT_RP*)(punkty.obiekt(mapadrogowa[beta]))));
				int sk;
				plik>>sk;
				for(int j=0; j<sk; j++)
				{
					string ap, bp;
					plik>>ap>>bp;
					KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(a1)))->krzywa;
					kt1->data[ap]=bp;
				}
			}
			if(type==1)
			{
				string alfa, beta;
				plik>>alfa>>beta;
				double k1, k2;
				plik>>k1>>k2;
				int a1=dodaj_linioluk(((PUNKT_RP*)(punkty.obiekt(mapadrogowa[alfa])))->punkt, ((PUNKT_RP*)(punkty.obiekt(mapadrogowa[beta])))->punkt, k1, k2);
				int sk;
				plik>>sk;
				for(int j=0; j<sk; j++)
				{
					string ap, bp;
					plik>>ap>>bp;
					KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(a1)))->krzywa;
					kt1->data[ap]=bp;
				}
			}
		}
	}
	double sterowanie::odleglosc_od_krzywej(int id, PUNKT alfa)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->odleglosc_od_krzywej(alfa);
	}
	double sterowanie::dlugosc(int id)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->dlugosc();
	}
	PUNKT sterowanie::punkt_na_krzywej(int id, PUNKT alfa)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->punkt_na_krzywej(alfa);
	}
	PUNKT sterowanie::punktwodl(int id, double odl)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->punktwodl(odl);
	}
	double sterowanie::kierunekwodl(int id, double odl)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->kierunekwodl(odl);
	}
	double sterowanie::odleglosc_na_krzywej(int id, PUNKT alfa)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->odleglosc_na_krzywej(alfa);
	}
	PUNKT sterowanie::krzywa_start(int id)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->start()->punkt();
	}
	PUNKT sterowanie::krzywa_stop(int id)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->stop()->punkt();
	}
	map <string, string> sterowanie::prop_krz(int id)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		return kt1->data;
	}
	void sterowanie::set_prop_krz(int id, map<string, string> prop)
	{
		KRZYWA_HIGH* kt1=((KRZYWA_RP*)(krzywe.obiekt(id)))->krzywa;
		kt1->data=prop;
	}
	map <string, string> sterowanie::prop_pkt(int id)
	{
		PUNKT_HIGH* pt1=((PUNKT_RP*)(punkty.obiekt(id)))->punkt;
		return pt1->data;
	}
	void sterowanie::set_prop_pkt(int id, map<string, string> prop)
	{	
		PUNKT_HIGH* pt1=((PUNKT_RP*)(punkty.obiekt(id)))->punkt;
		pt1->data=prop;
	}

