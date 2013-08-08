#ifndef NNDR
#define NNDR
#include <stdlib.h>
#include <GL/glu.h>
#include <stdio.h>
#include <QMenuBar>
#include <string.h> 
#include <QApplication>
#include <QtGui>
#include <iomanip>
#include <QtOpenGL>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct krzywa_prop
{
	int col_r;
	int col_g;
	int col_b;
	int grubosc;
};

class rysowanie_linii
{
	krzywa_prop general;
	krzywa_prop general_setted;
	bool find(string key, map<string, string> prop)
	{
		if(prop.find(key)==prop.end())
			return false;
		return true;
	}
	int stringtoint(string alfa)
	{
		stringstream ss;
		ss<<alfa;
		int wynik;
		ss>>wynik;
		return wynik;
	}
	krzywa_prop odczytaj_prop(map <string, string> prop)
	{
		krzywa_prop wynik=general;
		if(find("X11_color_r"))
			wynik.col_r=stringtoint(prop["X11_color_r"]);
		if(find("X11_color_g"))
			wynik.col_g=stringtoint(prop["X11_color_g"]);
		if(find("X11_color_b"))
			wynik.col_b=stringtoint(prop["X11_color_b"]);
		if(find("X11_grubosc"))
			wynik.grubosc=stringtoint(prop["X11_grubosc"]);
			return wynik;
	}
	krzywa_prop odczytaj_prop_setted(map <string, string> prop)
	{
		krzywa_prop wynik=general_setted;
		if(find("X11_zaz_color_r"))
			wynik.col_r=stringtoint(prop["X11_zaz_color_r"]);
		if(find("X11_zaz_color_g"))
			wynik.col_g=stringtoint(prop["X11_zaz_color_g"]);
		if(find("X11_zaz_color_b"))
			wynik.col_b=stringtoint(prop["X11_zaz_color_b"]);
		if(find("X11_zaz_grubosc"))
			wynik.grubosc=stringtoint(prop["X11_zaz_grubosc"]);
			return wynik;
	}
	public:
	rysowanie_linii()
	{
		general.col_r=0;
		general.col_g=0;
		general.col_b=0;
		general.grubosc=1;
		general_setted.col_r=255;
		general_setted.col_g=0;
		general_setted.col_b=0;
		general_setted.grubosc=1;

	}
	void set_gen_color(int col_r, int col_g, int col_b)
	{
		general.col_r=col_r;
		general.col_g=col_g;
		general.col_b=col_b;
	}
	void set_gen_grubosc(int grubosc)
	{
		general.grubosc=grubosc;
	}
	void rysuj(LINIA lin, bool zaz, map<string, string> prop)
	{
		krzywa_prop wynik=odczytaj_prop(prop);
		if(zaz)
			wynik=odczytaj_prop(prop);
		glColor3ub(wynik.col_r, wynik.col_g, wynik.col_b);
		glLineWidth(wynik.grubosc);
		glBegin(GL_LINES);
		glVertex2f(lin.x1, lin.y1);
		glVertex2f(lin.x2, lin.y2);
		glEnd();
	}
};

class rysowanie_punktu
{
	public:
	void rysuj(PUNKT pkt, bool zaz, map<string, string> prop) {}
}
class rysowanie_linioluku
{
	public:
	void rysuj(LINIOLUK lln, bool zaz, map<string, string> prop) {}
}
#endif
