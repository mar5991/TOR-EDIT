#include <cstring>
#include <QString>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "ust_obiekt.hpp"
using namespace std;
vector <int> wczytaj_kolor(string color)
{
	vector <int> wynik(3);
	stringstream tmp1;
	tmp1<<hex<<color;
	unsigned int wynx=0;
	bool ok=0;
	QString fdd=QString::fromStdString(color);
	wynx=fdd.toUInt(&ok, 16);
	wynik[2]=wynx%256;
	wynx/=256;
	wynik[1]=wynx%256;
	wynx/=256;
	wynik[0]=wynx%256;
	return wynik;
}
