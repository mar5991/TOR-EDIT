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
#include "geom_high.hpp"
#include "map_prop.hpp"
#include "obrwidget.hpp"
#include "ster.hpp"
#include "ust_obiekt.hpp"
#include "bmpread.hpp"
#ifndef MAIN_WIN
#define MAIN_WIN
struct tmpwsp
{
	int x;
	int y;
	int szer;
	int wys;
	tmpwsp(int szerc, int wysc, int id_k, int margin, int minszer, int wys_poz)
	{
		wys=wys_poz-margin;
		int liczbawrzedzie=((szerc-margin)/minszer);
		int idrzadu=id_k/liczbawrzedzie;
		int idkolumny=id_k%liczbawrzedzie;
		szer=((szerc-margin)/liczbawrzedzie)-margin;
		y=idrzadu*wys_poz+margin;
		x=margin+(szer+margin)*idkolumny;
	}
};
class SimpleApp;
class wywolanie : public QPushButton
{
	Q_OBJECT
	SimpleApp* sapvv;
	string nazwa;
	string polecenie;
	public:
	wywolanie(SimpleApp* sa, QWidget* parent) : sapvv(sa), QPushButton(parent)
	{
     		connect(this, SIGNAL(clicked()), this, SLOT(wywolaj()));
		setText(QString::fromStdString(nazwa));
		hide();
	}
	void setnazwa(string na)
	{
		nazwa=na;
		if(nazwa!="")
			show();
		setText(QString::fromStdString(nazwa));
	}
	void setpolecenie(string na)
	{
		polecenie=na;
	}
	public slots:
	void wywolaj();
};
class ndr : public narzedzie_do_rysowania, public map_prop
{
	public:
	SimpleApp* sap;
	bool przyc;
	ustaw_kraw ust_sta_1;
	ustaw_siatka ust_sta_2;
	ndr(SimpleApp* sa, double szer, double wys);
	void wczytaj_properities(string linia_kom)
	{
		ust_sta_1.ustaw(linia_kom);
		ust_sta_2.ustaw(linia_kom);
	}
	void rysuj_luk(LUK alfa, map <string, string> prop, bool zazn)
	{
		ustaw_kraw teraz=ust_sta_1;
		teraz.ustaw(prop);
		double dokl=(starex(2)-starex(0))/alfa.promien();
		double grub=teraz.grubosc;
		if(!teraz.wielkosc_strzalki_rel)
			grub=nowex(grub)-nowex(0);
		glLineWidth(grub);
		glColor3ub(teraz.kolor[0], teraz.kolor[1], teraz.kolor[2]);
		if(zazn)
			glColor3ub(teraz.kolor_zazn[0], teraz.kolor_zazn[1], teraz.kolor_zazn[2]);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(teraz.factor_powt, teraz.factor);
		for(double i=0; i<abs(alfa.wycinek); i+=dokl)
		{
			glBegin(GL_LINES);
			glVertex2d(alfa.odlodkier(i).x, alfa.odlodkier(i).y);
			if(i+dokl<abs(alfa.wycinek))
				glVertex2d(alfa.odlodkier(i+dokl).x, alfa.odlodkier(i+dokl).y);
			else
				glVertex2d(alfa.koniec().x, alfa.koniec().y);
		}
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glLineWidth(1);
		int a1=alfa.dlugosc();
		if(teraz.strzalki)
		{
			double w_st=teraz.wielkosc_strzalki;
			if(teraz.wielkosc_strzalki_rel)
				w_st=starex(w_st)-starex(0);
			for(double i=w_st*teraz.gestosc_strzalek; i<a1; i+=w_st*teraz.gestosc_strzalek)
			{
				PUNKT pp=alfa.odlodpocz(i);
				LINIA lk(alfa.srodek(), pp);
				if(alfa.wycinek>0)
					rysuj_strzalka(alfa.odlodpocz(i), lk.kierunek()+M_PI/2, w_st);
				else	
					rysuj_strzalka(alfa.odlodpocz(i), lk.kierunek()-M_PI/2, w_st);
			}
			LINIA lk(alfa.srodek(), alfa.poczatek());
			if(teraz.czy_grot_poczatkowy)
					rysuj_strzalka(alfa.odlodpocz(0), lk.kierunek()+M_PI/2, w_st);
			lk=LINIA(alfa.srodek(), alfa.koniec());
			if(teraz.czy_grot_koncowy)
					rysuj_strzalka(alfa.odlodpocz(alfa.dlugosc()), lk.kierunek()+M_PI/2, w_st);

		}
	}
	void rysuj_punkt(PUNKT alfa, map <string, string> prop, bool zazn)
	{
		map <string, string>::iterator it1;
		prop["oneway"]="0";
		LUK beta(alfa, starex(7)-starex(0));
		rysuj_luk(beta, prop, zazn);
	}
	void rysuj_linia(LINIA alfa, map <string, string> prop, bool zazn)
	{
		ustaw_kraw teraz=ust_sta_1;
		teraz.ustaw(prop);
		double grub=teraz.grubosc;
		if(!teraz.wielkosc_strzalki_rel)
			grub=nowex(grub)-nowex(0);
		glLineWidth(grub);
		glColor3ub(teraz.kolor[0], teraz.kolor[1], teraz.kolor[2]);
		if(zazn)
			glColor3ub(teraz.kolor_zazn[0], teraz.kolor_zazn[1], teraz.kolor_zazn[2]);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(teraz.factor_powt, teraz.factor);
		glBegin(GL_LINES);
		glVertex2d(alfa.x1, alfa.y1);
		glVertex2d(alfa.x2, alfa.y2);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		double a1=alfa.dlugosc();
		glLineWidth(1);
		if(teraz.strzalki)
		{
			double w_st=teraz.wielkosc_strzalki;
			if(teraz.wielkosc_strzalki_rel)
				w_st=starex(w_st)-starex(0);
			for(double i=w_st*teraz.gestosc_strzalek; i<a1; i+=w_st*teraz.gestosc_strzalek)
			{
				rysuj_strzalka(alfa.odlodpocz(i), alfa.kierunek(), w_st);
			}
			if(teraz.czy_grot_poczatkowy)
					rysuj_strzalka(alfa.odlodpocz(0), alfa.kierunek(), w_st);
			if(teraz.czy_grot_koncowy)
					rysuj_strzalka(alfa.odlodpocz(alfa.dlugosc()), alfa.kierunek(), w_st);
		}
	}
	void rysuj_linioluk(LINIOLUK alfa, map <string, string> prop, bool zazn)
	{
		rysuj_linia(alfa.l1, prop, zazn);
		rysuj_luk(alfa.l2, prop, zazn);
		rysuj_linia(alfa.l3, prop, zazn);
	}
	void rysuj_strzalka(PUNKT alfa, double kierunek, double size);
	void rysuj_siatka();
	void w111change();
};
class CGLwidget;
class tryb
{
	public:
	CGLwidget* wid;
	tryb(CGLwidget* widget) : wid(widget){}
	virtual void wcisniete(int x, int y){}
	virtual void puszczone(int x, int y){}
	virtual void powrotdokorzeni() {}
	virtual void przesuniete(int x, int y){}
	virtual void klucz(int x);
};
class tryb1 : public tryb
{
	public:
	tryb1(CGLwidget* widget);
	void puszczone(int x, int y);
};
class tryb1a : public tryb
{
	public:
	int sx, sy;
	tryb1a(CGLwidget* widget, int x, int y);
	void puszczone(int x, int y);
	void przesuniete(int x, int y);
	void powrotdokorzeni();
};
class tryb2 : public tryb
{
	public:
	tryb2(CGLwidget* widget);
	void puszczone(int x, int y);
};
class tryb2a : public tryb
{
	int pol_p;
	public:
	tryb2a(CGLwidget* widget, int plp);
	void puszczone(int x, int y);
	void powrotdokorzeni();
};
class tryb3 : public tryb
{
	public:
	tryb3(CGLwidget* widget);
	void wcisniete(int x, int y);
	void puszczone(int x, int y);
};
class tryb4 : public tryb
{
	public:
	tryb4(CGLwidget* widget);
	void puszczone(int x, int y);
};
class tryb4a : public tryb
{
	public:
	int sta;
	tryb4a(CGLwidget* widget, int st);
	void puszczone(int x, int y);
	void powrotdokorzeni();
};
class tryb4b : public tryb
{
	public:
	int sta;
	int sto;
	tryb4b(CGLwidget* widget, int st, int stp);
	void puszczone(int x, int y);
	void powrotdokorzeni();
};
class tryb4c : public tryb
{
	public:
	int sta;
	int sto;
	double kier1;
	tryb4c(CGLwidget* widget, int st, int stp, double k1);
	void puszczone(int x, int y);
	void powrotdokorzeni();
};
class tryb5 : public tryb
{
	public:
	tryb5(CGLwidget* widget);
	void puszczone(int x, int y);
};
class tryb5a : public tryb
{
	PUNKT ppo;
	public:
	tryb5a(CGLwidget* widget, PUNKT pp);
	void puszczone(int x, int y);
	void powrotdokorzeni();
};
class tryb6 : public tryb
{
	string sciezka;
	public:
	tryb6(CGLwidget* widget, string scz) : sciezka(scz), tryb(widget) {}
	void puszczone(int x, int y);
};
class tryb7 : public tryb
{
	public:
	tryb7(CGLwidget* widget) : tryb(widget) {}
	void puszczone(int x, int y);
};
class tryb7a : public tryb
{
	PUNKT ppo;
	public:
	tryb7a(CGLwidget* widget, PUNKT pp) : tryb(widget), ppo(pp) {}
	void puszczone(int x, int y);
	void powrotdokorzeni();
};
class ustawatrybuty : public QWidget
{
	Q_OBJECT
	SimpleApp* sa;
	QLabel* teksty[50];
	QLineEdit* zmienne[50];
	QPushButton* dodajkategorie;
	QPushButton* zapisz;
	QLineEdit* nowakategoria;
	map <string, int> kolejnosc;
	vector <string> atrybuty;
	vector <string> podstawa;
	vector <map <string, string> > lista_old;
	public:
	ustawatrybuty(QWidget* parent, SimpleApp* sap) : QWidget(parent), sa(sap)
	{
		this->setMaximumWidth(0);
		for(int i=0; i<50; i++)
		{
			teksty[i]=new QLabel(this);
			teksty[i]->hide();
			teksty[i]->setGeometry(2, i*30+2, 96, 28);
			zmienne[i]=new QLineEdit(this);
			zmienne[i]->hide();
			zmienne[i]->setGeometry(100, i*30+2, 98, 28);
		}
		dodajkategorie=new QPushButton(tr("dodaj kat"), this);
		zapisz=new QPushButton(tr("zapisz"), this);
		nowakategoria=new QLineEdit(this);
		dodajkategorie->setGeometry(100, 2, 98, 28);
		nowakategoria->setGeometry(2, 2, 96, 28);
		zapisz->setGeometry(2, 32, 196, 28);
     		connect(dodajkategorie, SIGNAL(clicked()), this, SLOT(nkat()));
     		connect(zapisz, SIGNAL(clicked()), this, SLOT(zap()));
	}
	void ustaw(vector <map <string, string> > lista)
	{
		this->setMaximumWidth(210);
		if(lista.size()==0)
			this->setMaximumWidth(0);
		lista_old=lista;
		//czyszczenie zmiennych
		kolejnosc.clear();
		atrybuty.clear();
		podstawa.clear();
		//dodawanie
		int s1=lista.size();
		for(int i=0; i<s1; i++)
		{
			map <string, string>::iterator it1=lista[i].begin();
			while(it1!=lista[i].end())
			{
				if(kolejnosc.find(it1->first)==kolejnosc.end())
				{
					kolejnosc[it1->first]=atrybuty.size();
					atrybuty.push_back(it1->second);
					podstawa.push_back(it1->first);
				}
				it1++;
			}
		}
		//sprawdzanie powtarzalnosci
		s1=atrybuty.size();
		for(int i=0; i<s1; i++)
		{
			int s2=lista.size();
			bool ok=1;
			for(int j=0; j<s2; j++)
			{
				if(lista[j].find(podstawa[i])==lista[j].end())
					ok=0;
				else
					if(lista[j].find(podstawa[i])->second!=atrybuty[i])
						ok=0;
			}
			if(!ok)
				atrybuty[i]="VARIOUS!";
		}
		//dodawanie do GUI
		for(int i=0; i<s1; i++)
		{
			teksty[i]->show();
			zmienne[i]->show();
			teksty[i]->setText(QString::fromStdString(podstawa[i]));
			zmienne[i]->setText(QString::fromStdString(atrybuty[i]));
		}
		nowakategoria->setText(QString::fromStdString(""));
		dodajkategorie->setGeometry(100, (s1)*30+2, 98, 28);
		nowakategoria->setGeometry(2, (s1)*30+2, 96, 28);
		zapisz->setGeometry(2, (s1+1)*30+2, 196, 28);
		for(int i=s1; i<50; i++)
		{
			teksty[i]->hide();
			zmienne[i]->hide();
		}
	}
	vector <map <string, string> > wyslij()
	{
		//zczytywanie GUI
		int s1=atrybuty.size();
		for(int i=0; i<s1; i++)
		{
			atrybuty[i]=(zmienne[i]->text()).toStdString();
		}
		//dodawanie normalne do lista_old
		for(int i=0; i<s1; i++)
		{
			if(atrybuty[i]!="VARIOUS!")
			{
				int s2=lista_old.size();
				for(int j=0; j<s2; j++)
				{
					lista_old[j][podstawa[i]]=atrybuty[i];
				}
			}
		}
		//usuwanie pustych
		s1=lista_old.size();
		for(int i=0; i<s1; i++)
		{
			map<string, string>::iterator it1=lista_old[i].begin();
			vector <string> do_usuniecia;
			while(it1!=lista_old[i].end())
			{
				if(it1->second=="")
					do_usuniecia.push_back(it1->first);
				it1++;
			}
			int s2=do_usuniecia.size();
			for(int j=0; j<s2; j++)
			{
				if(lista_old[i].find(do_usuniecia[j])!=lista_old[i].end())
					lista_old[i].erase(lista_old[i].find(do_usuniecia[j]));
			}
		}
		return lista_old;
	}
	public slots:
	void nkat()
	{
		if (kolejnosc.find((nowakategoria->text()).toStdString())==kolejnosc.end())
		{
			kolejnosc[(nowakategoria->text()).toStdString()]=podstawa.size();
			podstawa.push_back((nowakategoria->text()).toStdString());
			atrybuty.push_back("");
			int s1=atrybuty.size();
			for(int i=s1-1; i<s1; i++)
			{
				teksty[i]->show();
				zmienne[i]->show();
				teksty[i]->setText(QString::fromStdString(podstawa[i]));
				zmienne[i]->setText(QString::fromStdString(atrybuty[i]));
			}
			dodajkategorie->setGeometry(100, (s1)*30+2, 98, 28);
			nowakategoria->setGeometry(2, (s1)*30+2, 96, 28);
			zapisz->setGeometry(2, (s1+1)*30+2, 196, 28);
		}
		nowakategoria->setText(QString::fromStdString(""));
	}
	void zap();
};
class CGLwidget : public QGLWidget
{
        Q_OBJECT
public:
	void wczytaj_properities(string linia_kom)
	{
		stringstream ss;
		ss<<linia_kom;
		string klucz;
		ss>>klucz;
		if(klucz=="BACKGROUND_COLOR")
		{
			ss>>tlo_color[0];
			ss>>tlo_color[1];
			ss>>tlo_color[2];
		}
		if(klucz=="IMAGE")
		{
			string sciezka;
			int ximage, yimage, wysimage, szerimage;
			ss>>sciezka;
			ss>>ximage;
			ss>>yimage;
			ss>>szerimage;
			ss>>wysimage;
			int xpix, ypix, wym_glob;
			char* odw=czytajbmp(sciezka, &xpix, &ypix, &wym_glob);
			obrazy.push_back(odw);
			wymiary_obraz_pix.push_back(pair <int, int>(xpix, ypix));
			wymiary_obraz_calk.push_back(pair <int, int>(szerimage, wysimage));
			wsp_start_obraz.push_back(pair <int, int>(ximage, yimage));
			apro_wym_obraz.push_back(wym_glob);
		}
	}
	int tlo_color[3];
	SimpleApp* sap;
	ndr* al;
	tryb* akttryb;
	vector <char*> obrazy;
	vector <pair <int, int> > wymiary_obraz_pix;
	vector <pair <int, int> > wsp_start_obraz;
	vector <pair <int, int> > wymiary_obraz_calk;
	vector <int> apro_wym_obraz;
	vector<tryb*> t_do_usuniecia;
        CGLwidget(ndr* alfa, SimpleApp* ap, QWidget *parent);
        ~CGLwidget();
	void rysujobraz(char* ref, int wys, int szer, int wys_pix, int szer_pix, int wym_bmp, int xstart, int ystart);
	void ustaw_tryb(tryb* t);
        QSize minimumSizeHint() const;
        QSize sizeHint() const;
        QSize maximumSizeHint() const;
protected:
        void resizeGL(int width, int height);
	void paintGL();
        void initializeGL();
	bool event (QEvent * event);
};
class SimpleApp : public QMainWindow, sterowanie, public MapaReceiver
{
      Q_OBJECT
public:
	void onPaint();
	bool loaded;
	ustawatrybuty* atr1;
	string sciezka;
	ndr* alfa;
	vector <wywolanie*> wywolania;
     	QWidget * widget;
     	QWidget * gornywidget;
     	QWidget * dolnywidget;
	QPushButton* a1;
	QLabel* text1;
	QRadioButton* opcja1;
	QLabel* text2;
	QLabel* text3;
	QPushButton* a2;
	QPushButton* a3;
	QPushButton* a4;
	QPushButton* a5;
	QPushButton* a6;
QPushButton* a7;
	QPushButton* a8;
	QTextEdit* te1;
	QPushButton* a9;
	QPushButton* a10;
	QPushButton* a11;
	QPushButton* a12;
	QPushButton* a13;
	QPushButton* a14;
	QPushButton* a15;
	QPushButton* a16;
	QPushButton* a17;
	QPushButton* a18;
	QPushButton* a19;
	QPushButton* a20;
	MapaWidget* ccc5;
	void listy_zmienione();
      	SimpleApp(QWidget *parent, string scz);
      	~SimpleApp();
	CGLwidget *glScene;
	void resize_gornywidget(int szer, int wys)
	{
		int margin=2;
		//UWAGA SZER I WYS SĄ ZE SOBĄ ZAMIENIONE
		int wyskom=100;
		int szerkom=27;
		tmpwsp wsp(szer, wys, 0, margin, wyskom, szerkom);
		
		
		wsp=tmpwsp(szer, wys, 0, margin, wyskom, szerkom);
		a1->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 1, margin, wyskom, szerkom);
		a2->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 2, margin, wyskom, szerkom);
		a3->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 3, margin, wyskom, szerkom);
		a4->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 4, margin, wyskom, szerkom);
		a5->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 5, margin, wyskom, szerkom);
		a6->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 6, margin, wyskom, szerkom);
		a7->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 7, margin, wyskom, szerkom);
		a8->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 8, margin, wyskom, szerkom);
		a9->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 9, margin, wyskom, szerkom);
		a10->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 10, margin, wyskom, szerkom);
		a11->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 11, margin, wyskom, szerkom);
		a12->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 12, margin, wyskom, szerkom);
		a13->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 13, margin, wyskom, szerkom);
		a14->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 14, margin, wyskom, szerkom);
		a15->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 15, margin, wyskom, szerkom);
		a16->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 16, margin, wyskom, szerkom);
		a17->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 17, margin, wyskom, szerkom);
		a18->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 18, margin, wyskom, szerkom);
		a19->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, 19, margin, wyskom, szerkom);
		a20->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		int licz=20;
		for(int i=0; i<wywolania.size(); i++)
		{
			wsp=tmpwsp(szer,wys,licz,margin,wyskom,szerkom);
			wywolania[i]->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
			licz++;
		}
		wsp=tmpwsp(szer, wys, licz, margin, wyskom, szerkom);
		opcja1->setGeometry(wsp.x, wsp.y, wsp.szer, wsp.wys);
		wsp=tmpwsp(szer, wys, licz, margin, wyskom, szerkom);
		gornywidget->setMaximumHeight(wsp.y+szerkom);
	}
protected:
	bool event (QEvent * event);
public slots:
	void mod1();
	void mod2();
	void mod3();
	void mod4();
	void mod5();
	void mod6();
	void mod7();
	void mod8();
	void mod9();
	void mod10();
	void mod11();
	void mod12();
	void mod13();
	void mod14();
	void mod15();
	void mod16();
	void mod17();
	void mod18();
	void mod19();
	void mod20();
	void modo1();
};
#endif
