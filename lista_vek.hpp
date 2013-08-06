#ifndef LISTA_VEK_HPP
#define LISTA_VEK_HPP
#include <vector>
#include <iostream>
using namespace std;
class lista_vek;
class obiekt_na_liscie
{
	public:
	virtual void dodano_obiekt(lista_vek* lst, int poz)
	{
	}
	virtual void usunieto_obiekt(lista_vek* lst)
	{
	}
	virtual void zmieniono_pozycje(lista_vek* lst, int npoz)
	{
	}
	virtual bool czy_nalezy_do_listy(lista_vek* lst)
	{
	}
	virtual vector <lista_vek*> uzywane()
	{
		vector <lista_vek*> uz;
		return uz;
	}
	virtual int pozycja(lista_vek* lst)
	{
		return -1;
	}
	virtual bool czy_do_listy(lista_vek* lst){}
	virtual ~obiekt_na_liscie();
};
class obiekt_na_liscie_classic : public obiekt_na_liscie
{
	vector<pair<lista_vek*, int> > onl;
	int wyszukaj_liste(lista_vek* lst)
	{
		int s1=onl.size();
		for(int i=0; i<s1; i++)
		{
			if(onl[i].first==lst)
				return i;
		}
		return -1;
	}
	void dodano_obiekt(lista_vek* lst, int poz)
	{
		pair<lista_vek*, int> p(lst, poz);
		onl.push_back(p);
	}
	void usunieto_obiekt(lista_vek* lst)
	{
		int nk=wyszukaj_liste(lst);
		if(nk!=-1)
			onl.erase(onl.begin()+nk);
	}
	void zmieniono_pozycje(lista_vek* lst, int npoz)
	{
		int nk=wyszukaj_liste(lst);
		if(nk!=-1)
			onl[nk].second=npoz;
	}
	bool czy_nalezy_do_listy(lista_vek* lst)
	{
		return(wyszukaj_liste(lst)!=-1);
	}
	virtual int pozycja(lista_vek* lst)
	{
		int nk=wyszukaj_liste(lst);
		if(nk==-1)
			return -1;
		return onl[nk].second;
	}
	vector <lista_vek*> uzywane()
	{
		vector <lista_vek*> wynil;
		int s1=onl.size();
		for(int i=s1-1; i>=0; i--)
		{
			wynil.push_back(onl[i].first);
		}
		return wynil;
	}
	public:
	bool czy_do_listy(lista_vek* lst)
	{
		return czy_nalezy_do_listy(lst);
	}
	virtual ~obiekt_na_liscie_classic();
};
class lista_vek
{
	vector <obiekt_na_liscie*> obiekty;
	int id_kol(obiekt_na_liscie* id)
	{
		return id->pozycja(this);
	}
	lista_vek& operator=(lista_vek& foo)
	{
	}
	lista_vek(lista_vek& foo)
	{
	}
	virtual void lista_zmieniona()
	{
	}
	public:
	lista_vek(){}
	void wyczysc_liste()
	{
		int s1=obiekty.size();
		for(int i=s1-1; i>=0; i--)
			usun_obiekt(obiekty[i]);
		lista_zmieniona();
	}
	int size()
	{
		return obiekty.size();
	}
	obiekt_na_liscie* obiekt(int id)
	{
		if(id>=obiekty.size())
			return 0;
		if(id<0)
			return 0;
		return obiekty[id];
	}
	bool czy_nalezy(obiekt_na_liscie* id)
	{
		return (id->pozycja(this)!=-1);
	}
	void dodaj_obiekt(obiekt_na_liscie* id)
	{
		if(!czy_nalezy(id))
		{
			obiekty.push_back(id);
			id->dodano_obiekt(this, obiekty.size()-1);
			lista_zmieniona();
		}
	}
	void usun_obiekt(obiekt_na_liscie* id)
	{
		int id_k=id_kol(id);
		if(id_k==-1)
			return;
		obiekty[id_k]=0;
		id->usunieto_obiekt(this);
		if(id_k!=obiekty.size()-1)
		{
			obiekty[id_k]=obiekty[obiekty.size()-1];
			obiekty[id_k]->zmieniono_pozycje(this, id_k);
		}
		obiekty.pop_back();
		lista_zmieniona();
	}
	virtual ~lista_vek()
	{
		int s1=obiekty.size();
		for(int i=s1-1; i>=0; i--)
			usun_obiekt(obiekty[i]);
	}
};	
#endif
