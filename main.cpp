#include "main.hpp"
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "bmpread.hpp"
#include "program_pob.hpp"
sterowanie* ste;

polHand::polHand(SimpleApp* parn) : QWidget(parn)
{
	pole_t=new QLabel(this);
	pole_t->setGeometry(0, 0, 300, 300);
	exist=0;
	oczekiwanie_tryb=0;
	par=parn;
}

void polHand::handlePrzycisk(double x, double y)
{
	if(exist && oczekiwanie_tryb==1)
	{
		oczekiwanie_tryb=0;
		string alfa;
		alfa=tostring(x)+" "+tostring(y)+"\n";
		komunikacjaOdpowiedz(alfa);
	}
}

void WewnetrzneKomendy::easy_dodajlinie(double x1, double y1, double x2, double y2)
{
	double odl;
	string alpha1=str->najblizszy_punkt(PUNKT(x1,y1), odl);
	if(odl>przeliczodl(10))
	{
		alpha1=str->randnazwa();
		str->setpunkt(alpha1, PUNKT(x1,y1));
	}
	string alpha2=str->najblizszy_punkt(PUNKT(x2,y2), odl);
	if(odl>przeliczodl(10))
	{
		alpha2=str->randnazwa();
		str->setpunkt(alpha2, PUNKT(x2,y2));
	}
	str->setkrzywa(str->randnazwa(), alpha1, alpha2);

}
void WewnetrzneKomendy::easy_dodajlinioluk(PUNKT p1, PUNKT p2, double k1, double k2)
{
	double odl;
	string alpha1=str->najblizszy_punkt(p1, odl);
	if(odl>przeliczodl(10))
	{
		alpha1=str->randnazwa();
		str->setpunkt(alpha1, p1);
	}
	string alpha2=str->najblizszy_punkt(p2, odl);
	if(odl>przeliczodl(10))
	{
		alpha2=str->randnazwa();
		str->setpunkt(alpha2, p2);
	}
	str->setkrzywa(str->randnazwa(), alpha1, alpha2, k1, k2);
}
void WewnetrzneKomendy::easy_dodajlinioluk(PUNKT p1, PUNKT p2, PUNKT p3, PUNKT p4)
{
	double odl;
	string alpha1=str->najblizszy_punkt(p1, odl);
	if(odl>30)
	{
		alpha1=str->randnazwa();
		str->setpunkt(alpha1, p1);
	}
	string alpha2=str->najblizszy_punkt(p2, odl);
	if(odl>30)
	{
		alpha2=str->randnazwa();
		str->setpunkt(alpha2, p2);
	}
	LINIA kt1(p1, p3);
	LINIA kt2(p2, p4);
	string alpha3;
	double odl3;
	string alpha4;
	double odl4;
	alpha3=str->najblizsza_krzywa(p3, odl3);
	alpha4=str->najblizsza_krzywa(p4, odl4);
	double kk1=kt1.kierunek();
	double kk2=kt2.kierunek();
	if(odl3<30)
	{
		LINIA la1;
		LINIOLUK la2(PUNKT(0,0), PUNKT(1,1), 0,0);
		int la3=str->getkrzywa(alpha3, la1, la2);
		if(la3==2)
		{
			kk1=la1.kierunek();
		}
		else
		{
			PUNKT pkr1=la2.punkt_na_krzywej(p3);
			double pkr2=la2.odleglosc_na_krzywej(pkr1);
			if(pkr2<la2.dlugosc()/2)
				kk1=la2.kierunekwodl(0);
			else
				kk1=la2.kierunekwodl(la2.dlugosc());
		}
	}
	if(odl4<30)
	{
		LINIA la1;
		LINIOLUK la2(PUNKT(0,0), PUNKT(1,1), 0,0);
		int la3=str->getkrzywa(alpha4, la1, la2);
		if(la3==2)
		{
			kk2=la1.kierunek();
		}
		else
		{
			PUNKT pkr1=la2.punkt_na_krzywej(p4);
			double pkr2=la2.odleglosc_na_krzywej(pkr1);
			if(pkr2<la2.dlugosc()/2)
				kk2=la2.kierunekwodl(0);
			else
				kk2=la2.kierunekwodl(la2.dlugosc());
		}
	}
	str->setkrzywa(str->randnazwa(), alpha1, alpha2, kk1, kk2);
}

void polHand::kill()
{
	if(exist)
		delete aktualny;
	exist=0;
}

vector <string> totab(stringstream& data)
{
	vector <string> wynik;
	string aktu;
	while(data>>aktu)
	{
		wynik.push_back(aktu);
	}
	return wynik;
}

string WewnetrzneKomendy::easy_polecenie(vector <string> polecenia)
{
	int s9=polecenia.size();
	for(int p=0; p<s9; p++)
	{
		cout<<"polecenie "<<polecenia[p]<<endl;
	}
	string wynik;
	if(polecenia.size()==0)
		return wynik;
	if(polecenia[0]=="DLI" && polecenia.size()==5)
	{
		double x1=todouble(polecenia[1]);
		double y1=todouble(polecenia[2]);
		double x2=todouble(polecenia[3]);
		double y2=todouble(polecenia[4]);
		easy_dodajlinie(x1,y1,x2,y2);
	}
	if(polecenia[0]=="DLK" && polecenia.size()==9)
	{
		double x1=todouble(polecenia[1]);
		double y1=todouble(polecenia[2]);
		double x2=todouble(polecenia[3]);
		double y2=todouble(polecenia[4]);
		double x3=todouble(polecenia[5]);
		double y3=todouble(polecenia[6]);
		double x4=todouble(polecenia[7]);
		double y4=todouble(polecenia[8]);
		easy_dodajlinioluk(PUNKT(x1,y1), PUNKT(x2,y2), PUNKT(x3,y3), PUNKT (x4, y4));
	}
	if(polecenia[0]=="ELK" && polecenia.size()==7)
	{
		double x1=todouble(polecenia[1]);
		double y1=todouble(polecenia[2]);
		double x2=todouble(polecenia[3]);
		double y2=todouble(polecenia[4]);
		double k1=todouble(polecenia[5]);
		double k2=todouble(polecenia[6]);
		easy_dodajlinioluk(PUNKT(x1,y1), PUNKT(x2,y2), k1, k2);
	}
	if(polecenia[0]=="ZAZ" && polecenia.size()==5)
	{
		cout<<"pppp"<<endl;
		double x1=todouble(polecenia[1]);
		double y1=todouble(polecenia[2]);
		double odl1=100000;
		string alpha1=str->najblizszy_punkt(PUNKT(x1,y1), odl1);
		double odl2=100000;
		string alpha2=str->najblizsza_krzywa(PUNKT(x1,y1), odl2);
		if(odl1<(przeliczodl(10)))
		{
			str->setpunkt_prop(alpha1, polecenia[3], polecenia[4]);
		}
		else
		{
			str->setkrzywa_prop(alpha2, polecenia[3], polecenia[4]);
		}
	}
	if(polecenia[0]=="SIA" && polecenia.size()==3)
	{
		double x1=todouble(polecenia[1]);
		double y1=todouble(polecenia[2]);
		return easy_kieruneksiatka(PUNKT(x1,y1));
	}
	/*if(polecenia[0]=="YMU" && polecenia.size()>1)
	{
		int licznik=toint(polecenia[1]);
		if(polecenia.size()<(licznik+2))
			return wynik;
		for(int i=0; i<licznik; i++)
		{
			clkgrn(toint(polecenia[i+2]));
		}
	}*/
	return wynik;
}

double WewnetrzneKomendy::przeliczodl(double data)
{
	return (data/app->ccc5->zom());
}

void polHand::handlepoleeditor()
{
	int s1=edycja.size();
	//TODO 
	for(int i=0; i<s1; i++)
	{
		edycja[i]->hide();
		edycjaopis[i]->hide();
		delete edycja[i];
		delete edycjaopis[i];
	}
	edycja.clear();
	edycjaopis.clear();
}

void polHand::komunikacjaPytanie()
{
	bool ok=1;
	while(ok)
	{
		stringstream data;
		bool kkk=aktualny->wczytaj(data);
		stringstream data2;
		if(!kkk)
		{
			kill();
			return;
		}
		else
		{
			char apk[10000];
			data.getline(apk, 5000);
			data2<<apk;
			cout<<"akk"<<apk<<endl;
		}
		vector <string> wyn=totab(data2);
		if(wyn.size()>0)
		{
			if(wyn[0]=="CLICK")
			{
				oczekiwanie_tryb=1;
				return;
			}
			if(wyn[0]=="POLE")
			{
				pole_t->hide();
				int liczba=toint(wyn[1]);
				for(int g=0; g<liczba; g++)
				{
					string txt1=wyn[g+2];
					QLineEdit* nt=new QLineEdit(this);
					QLabel* nk=new QLabel(this);
					nt->setGeometry(5, 60*g+5, 295, 25);
					nk->setGeometry(5, 60*g+35, 295, 25);
					nt->show();
					nk->show();
					nk->setText(QString::fromStdString(txt1));
					edycja.push_back(nt);
					edycjaopis.push_back(nk);
				}
				oczekiwanie_tryb=2;
				return;
			}
			if(wyn[0]=="ECHE")
			{
				pole_t->show();
				pole_t->setText(QString::fromStdString(wyn[1]));
				stringstream pel;
				pel<<"V "<<endl;
				aktualny->zapisz(pel);
			}
			else
			{
				if(par->wk1->isAvailable(wyn[0]))
				{
					string wyna=par->wk1->easy_polecenie(wyn);
					par->ccc5->update_request();
					stringstream pel;
					pel<<"V "<<wyna<<endl;
					aktualny->zapisz(pel);
				}
				else
				{
					string wyna=par->centrala->easy_polecenie(wyn);
					par->ccc5->update_request();
					stringstream pel;
					pel<<"V "<<wyna<<endl;
					aktualny->zapisz(pel);
				}
			}
		}
	}
}

void polHand::komunikacjaOdpowiedz(string txt)
{
	stringstream plik;
	plik<<txt<<"\n";
	aktualny->zapisz(plik);
	komunikacjaPytanie();
}

void polHand::start(string polecenie)
{
	aktualny=new program_pob(polecenie);
	exist=1;
	komunikacjaPytanie();
}

void WewnetrzneKomendy::clkgrn(int id)
{
	app->onClickGrn(id);
}
string WewnetrzneKomendy::easy_kieruneksiatka(PUNKT p3)
{
	string alpha3;
	double odl3;
	PUNKT start(0,0);
	alpha3=str->najblizsza_krzywa(p3, odl3);
	double kk1=0;
	if(odl3<30)
	{
		LINIA la1;
		LINIOLUK la2(PUNKT(0,0), PUNKT(1,1), 0,0);
		int la3=str->getkrzywa(alpha3, la1, la2);
		if(la3==2)
		{
			kk1=la1.kierunek();
			PUNKT pkr1=la1.punkt_na_krzywej(p3);
			double pkr2=la1.odleglosc_na_krzywej(pkr1);
			if(pkr2<la1.dlugosc()/2)
			{
				start=la1.punktwodl(0);
			}
			else
			{
				start=la1.punktwodl(la1.dlugosc());
			}
		}
		else
		{
			PUNKT pkr1=la2.punkt_na_krzywej(p3);
			double pkr2=la2.odleglosc_na_krzywej(pkr1);
			if(pkr2<la2.dlugosc()/2)
			{
				kk1=la2.kierunekwodl(0);
				start=la2.punktwodl(0);
			}
			else
			{
				kk1=la2.kierunekwodl(la2.dlugosc());
				start=la2.punktwodl(la2.dlugosc());
			}
		}
	}
	app->ccc5->kier=-1*kk1;
	app->ccc5->start=start;
	string wynik;
	return wynik;
}
Przyciskgora::Przyciskgora(SimpleApp* parent, int id) : QPushButton(parent), ide(id), par(parent)
{
	connect(this, SIGNAL(clicked()), this, SLOT(click()));
}
SimpleApp::SimpleApp(QWidget *parent, string scz):QMainWindow(parent), sciezka(scz)
{
	centrala=new sterowanie;
	if(scz!="")
		centrala->wczytaj(scz);
	ccc5=new MapaWidget(this, this);
	ryslin=new rysowanie_linii(ccc5);
	rysllk=new rysowanie_linioluku(ccc5);
	ryspkt=new rysowanie_punktu(ccc5);
	ryssia=new rysowanie_siatki(ccc5, 255, 0, 0);
	hand=new polHand(this);
	hand->setGeometry(800, 0, 300, 300);
	wk1=new WewnetrzneKomendy(centrala, this);
	ccc5->setGeometry(0, 0, 777, 777);
	fstream plikt;
	plikt.open("/home/marcin/.toredit2rc", ios::in);
	int licznik_but=0;
	while(!plikt.eof())
	{
		string linia;
		getline(plikt, linia);
		stringstream sst;
		sst<<linia;
		string typ;
		sst>>typ;
		if(typ=="BUT")
		{
			string key_podst;
			string name;
			sst>>name;
			string tmp;
			vector <string> nastepne;
			while(sst>>tmp)
			{
				nastepne.push_back(tmp);
			}
			int s9=nastepne.size();
			for(int p=0; p<s9; p++)
			{
				key_podst+=nastepne[p]+" ";
			}
			Przyciskgora* prc=new Przyciskgora(this, licznik_but);
			prc->key_podst=key_podst;
			prc->setText(QString::fromStdString(name));
			prc->setGeometry(1100, licznik_but*35, 100, 30);
			przyciski.push_back(prc);
			licznik_but++;
		}
	}
}
void SimpleApp::onClickGrn(int id)
{
	hand->kill();
	hand->start(przyciski[id]->key_podst);
}
void SimpleApp::onPaint()
{
	ryssia->rysuj();
	vector<pair<LINIA, string> >linie=centrala->wszystkielinie();
	int s1=linie.size();
	for(int i=0; i<s1; i++)
	{
		map<string, string> prop=centrala->getkrzywa_prop(linie[i].second);
		bool zaz=0;
		if(prop["X11_set"]=="yes")
			zaz=1;
		ryslin->rysuj(linie[i].first, zaz, prop);
	}
	vector<pair<LINIOLUK, string> >linioluki=centrala->wszystkielinioluki();
	vector<pair<PUNKT, string> > punkty=centrala->wszystkiepunkty();
	s1=linioluki.size();
	for(int i=0; i<s1; i++)
	{
		map<string, string> prop=centrala->getkrzywa_prop(linioluki[i].second);
		bool zaz=0;
		if(prop["X11_set"]=="yes")
			zaz=1;
		rysllk->rysuj(linioluki[i].first, zaz, prop);
	}
	s1=punkty.size();
	for(int i=0; i<s1; i++)
	{
		map<string, string> prop=centrala->getpunkt_prop(punkty[i].second);
		bool zaz=0;
		if(prop["X11_set"]=="yes")
		{
			cout<<"zaznaczone!"<<endl;
			zaz=1;
		}
		ryspkt->rysuj(punkty[i].first, zaz, prop);
	}
}

void Przyciskgora::click()
{
	par->onClickGrn(ide);
}

void SimpleApp::onMouseClick(double x, double y)
{
	hand->handlePrzycisk(x, y);
}
SimpleApp::~SimpleApp()
{}

int main (int argc, char *argv[])
{
	sterowanie str;
	string sciezka;
	if (argv[1]!=NULL)
	{
		sciezka=argv[1];
	}
  	QApplication app( argc, argv);
	SimpleApp window(0, sciezka);
	window.show();
  	return app.exec();
}
