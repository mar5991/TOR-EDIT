#ifndef NEXTRA
#define NEXTRA
#include "geom.hpp"
#include <map>
#include <set>
#include <vector>
using namespace std;
struct PUNKT_PLUS
{
	PUNKT pkt;
	set <string> linie_powiazane;
	map <string, string> prop;
	PUNKT_PLUS() : pkt(0,0) {}
};
struct LINIA_PLUS
{
	LINIA lin;
	string pkt1;
	string pkt2;
	map <string, string> prop;
	LINIA_PLUS() : lin(PUNKT(0,0), PUNKT(1,1)) {}
};
struct LINIOLUK_PLUS
{
	LINIOLUK llk;
	string pkt1;
	string pkt2;
	double k1;
	double k2;
	map <string, string> prop;
	LINIOLUK_PLUS() : llk(PUNKT(0,0), PUNKT(1,1), 0, 1) {}
};
class nextra
{
	map <string, PUNKT_PLUS> punkty;
	map <string, LINIA_PLUS> linie;
	map <string, LINIOLUK_PLUS> linioluki;
	public:
	bool setpunkt(string nazwa, PUNKT pkt);
	bool setkrzywa(string nazwa, string pkt_start, string pkt_stop);
	bool setkrzywa(string nazwa, string pkt_start, string pkt_stop, double k1, double k2);
	bool setpunkt_prop(string nazwa, string key, string value);
	bool setkrzywa_prop(string nazwa, string key, string value);
	bool deletepunkt_prop(string nazwa, string key);
	bool deletekrzywa_prop(string nazwa, string key);
	bool changepunkt(string nazwa, PUNKT newpoz);
	bool deletepunkt(string nazwa);
	bool deletekrzywa(string nazwa);
	bool getpunkt_all(void(*funkcja1)(string nazwa, PUNKT pkt));
	bool getkrzywa_all(void(*funkcja1)(string nazwa, LINIA pkt), void(*funkcja2)(string nazwa, LINIOLUK pkt));
	int getpunkt_size();
	int getkrzywa_size();
	map <string, string> getpunkt_prop(string nazwa, void(*funkcja1)(PUNKT));
	map <string, string> getkrzywa_prop(string nazwa, void(*funkcja1)(LINIA), void(*funkcja2)(LINIOLUK));
	bool getpunkt_key(string key, string value, void(*funkcja1)(string, PUNKT));
	bool getpunkt_key(string key, string value, bool(*cmp)(string, string), void(*funkcja1)(string, PUNKT));
	bool getkrzywa_key(string key, string value, void(*funkcja1)(string, LINIA), void(*funkcja2)(string, LINIOLUK));
	bool getkrzywa_key(string key, string value, bool(*cmp)(string, string), void(*funkcja1)(string, LINIA), void(*funkcja2)(string, LINIOLUK));
};
#endif
