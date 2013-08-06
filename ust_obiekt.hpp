#ifndef UST_OBIEKT_HPP
#define UST_OBIEKT_HPP
#include <cstring>
#include <QString>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
vector <int> wczytaj_kolor(string color);
struct ustaw_kraw
{
	int kolor[3];
	int kolor_zazn[3];
	bool strzalki;
	double wielkosc_strzalki;
	double grubosc;
	bool wielkosc_strzalki_rel; //relatywizm wielkości strzalki - 1: stała wielkość na ekranie niezależnie od zoom'u
	bool czy_grot_poczatkowy;
	bool czy_grot_koncowy;
	double gestosc_strzalek; // czestosc_wyst_strzalek - jest uzależniona tez od wielkosci strzalki
	int factor;
	int factor_powt;
	ustaw_kraw()
	{
		strzalki=0;
		kolor[0]=0;
		kolor[1]=0;
		kolor[2]=0;
		kolor_zazn[0]=255;
		kolor_zazn[1]=0;
		kolor_zazn[2]=0;
		wielkosc_strzalki=5;
		wielkosc_strzalki_rel=1;
		czy_grot_poczatkowy=0;
		czy_grot_koncowy=0;
		gestosc_strzalek=10;
		grubosc=1;
		factor=0xFFFFFF;
		factor_powt=1;
	}
	void ustaw(string linia_kom)
	{
		stringstream ss;
		ss<<linia_kom;
		string klucz;
		ss>>klucz;
		if(klucz=="DEF_COLOR")
		{
			ss>>kolor[0];
			ss>>kolor[1];
			ss>>kolor[2];
		}
		if(klucz=="ZAZ_COLOR")
		{
			ss>>kolor_zazn[0];
			ss>>kolor_zazn[1];
			ss>>kolor_zazn[2];
		}
		if(klucz=="STRZALKI")
			ss>>strzalki;
		if(klucz=="STRZALKI_DANE")
		{
			ss>>wielkosc_strzalki;
			ss>>wielkosc_strzalki_rel;
			ss>>czy_grot_poczatkowy;
			ss>>czy_grot_koncowy;
			ss>>gestosc_strzalek;
		}
		if(klucz=="GRUBOSC")
			ss>>grubosc;
		if(klucz=="LINE_FACTOR")
		{
			ss>>hex>>factor;
			ss>>factor_powt;
		}
	}
	void ustaw(map <string, string> prop)
	{
		map <string, string>::iterator it1;
		it1=prop.find("color");
		if(it1!=prop.end())
		{
			string abc=it1->second;
			vector <int> atk=wczytaj_kolor(abc);
			kolor[0]=atk[0];
			kolor[1]=atk[1];
			kolor[2]=atk[2];
		}
		it1=prop.find("oneway");
		if(it1!=prop.end())
		{
			stringstream ss;
			string abc=it1->second;
			ss<<abc;
			ss>>strzalki;
		}
		it1=prop.find("grubosc");
		if(it1!=prop.end())
		{
			stringstream ss;
			string abc=it1->second;
			ss<<abc;
			ss>>grubosc;
		}
		it1=prop.find("factor");
		if(it1!=prop.end())
		{
			stringstream ss;
			string abc=it1->second;
			ss<<abc;
			ss>>hex>>factor;
		}
		it1=prop.find("factor_powt");
		if(it1!=prop.end())
		{
			stringstream ss;
			string abc=it1->second;
			ss<<abc;
			ss>>factor_powt;
		}
		//TODO FACTOR_POWT
		//dane o stzalkach TODO
	}
};
struct ustaw_siatka
{
	int kolor1[3];
	int kolor2[3];
	int back_color[3];
	ustaw_siatka()
	{	
		back_color[0]=255;
		back_color[1]=255;
		back_color[2]=255;
		kolor1[0]=200;
		kolor1[1]=200;
		kolor1[2]=200;
		kolor2[0]=140;
		kolor2[1]=140;
		kolor2[2]=140;
	}
	void ustaw(string linia_kom)
	{
		stringstream ss;
		ss<<linia_kom;
		string klucz;
		ss>>klucz;
		if(klucz=="SIATKA_KOL1")
		{
			ss>>kolor1[0];
			ss>>kolor1[1];
			ss>>kolor1[2];
		}
		if(klucz=="SIATKA_KOL2")
		{
			ss>>kolor2[0];
			ss>>kolor2[1];
			ss>>kolor2[2];
		}
		if(klucz=="BACK_COLOR")
		{
			ss>>back_color[0];
			ss>>back_color[1];
			ss>>back_color[2];
		}
	}
};
#endif
