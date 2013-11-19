#include "ster.hpp"
double todouble (string data)
{
	stringstream dx;
	dx<<data;
	double wynik;
	dx>>wynik;
	return wynik;
}
int toint (string data)
{
	stringstream dx;
	dx<<data;
	int wynik;
	dx>>wynik;
	return wynik;
}
string tostring(double data)
{
	stringstream ss;
	ss<<data;
	string wyn;
	ss>>wyn;
	return wyn;
}
string tostring(int data)
{
	stringstream ss;
	ss<<data;
	string wyn;
	ss>>wyn;
	return wyn;
}
