#include "main.hpp"
#include <fstream>
#include <cstdio>
#include "bmpread.hpp"
#define IS_BIT_SET(k,n) ((k) & (1 << (n)))
#define SET_BIT(k,n) (k |= (1 << (n)))
#define RESET_BIT(k,n) (k &= ~(1 << (n)))
sterowanie* ste;

void tryb1a::powrotdokorzeni() {wid->ustaw_tryb(new tryb1(wid));}
void tryb2a::powrotdokorzeni() {wid->ustaw_tryb(new tryb2(wid));}
void tryb4a::powrotdokorzeni() {wid->ustaw_tryb(new tryb4(wid));}
void tryb4b::powrotdokorzeni() {wid->ustaw_tryb(new tryb4(wid));}
void tryb4c::powrotdokorzeni() {wid->ustaw_tryb(new tryb4(wid));}
void tryb5a::powrotdokorzeni() {wid->ustaw_tryb(new tryb5(wid));}
void tryb7a::powrotdokorzeni() {wid->ustaw_tryb(new tryb7(wid));}
void tryb::klucz(int x)
{
	ndr* al=wid->al;
	if(x==Qt::Key_Delete)
	{
		ste->usun_zaznaczenie();
		powrotdokorzeni();
	}
	if(x==Qt::Key_R)
	{
		ste->reverse();
		powrotdokorzeni();
	}
	if(x==Qt::Key_L)
	{
		ste->dodaj_linioluk();
		powrotdokorzeni();
	}
	if(x==Qt::Key_Escape)
	{
		ste->zeruj_zaznaczenie();
		powrotdokorzeni();
	}
	if(x==Qt::Key_P)
	{
		int l1=ste->liczba_krz_zaz();
		if(l1==1)
		{	
			int pkt1=(ste->k_zaz())[0];
			al->start=ste->krzywa_start(pkt1);
			al->kier=stand_kierunek(M_PI/2-ste->kierunekwodl(pkt1, 0));
		}
		powrotdokorzeni();
	}
	if(x==Qt::Key_K)
	{
		int l1=ste->liczba_krz_zaz();
		if(l1==1)
		{
			int pkt1=(ste->k_zaz())[0];
			al->start=ste->krzywa_stop(pkt1);
			al->kier=stand_kierunek(M_PI/2-ste->kierunekwodl(pkt1, ste->dlugosc(pkt1)));
		}	
		powrotdokorzeni();
	}
	if(x==Qt::Key_Q)
	{
		wid->ustaw_tryb(new tryb3(wid));
	}
	if(x==Qt::Key_W)
	{
		wid->ustaw_tryb(new tryb2(wid));
	}
	if(x==Qt::Key_E)
	{
		wid->ustaw_tryb(new tryb4(wid));
	}
	if(x==Qt::Key_T)
	{
		wid->ustaw_tryb(new tryb1(wid));
	}
	if(x==Qt::Key_L)
	{
		wid->ustaw_tryb(new tryb5(wid));
	}
	if(x==Qt::Key_H)
	{
		wid->ustaw_tryb(new tryb7(wid));
	}
	if(x==Qt::Key_Z)
	{
		al->start=PUNKT(0,0);
		al->kier=0;
		powrotdokorzeni();
	}
	if(x==Qt::Key_D)
	{
		vector <map <string, string> > wyn;
		vector <int> tmp=ste->k_zaz();
		int s1=tmp.size();
		for(int i=0; i<s1; i++)
		{
			wyn.push_back(ste->prop_krz(tmp[i]));
		}
		tmp=ste->p_zaz();
		s1=tmp.size();
		for(int i=0; i<s1; i++)
		{
			wyn.push_back(ste->prop_pkt(tmp[i]));
		}
		wid->sap->atr1->ustaw(wyn);
		powrotdokorzeni();
	}
	if(x==Qt::Key_Plus)
	{
		al->powiekszzoom(2);
	}
	if(x==Qt::Key_Minus)
	{
		al->powiekszzoom(0.5);
	}
}
//TRYB1 - PRZESUWANIE MAPY
tryb1::tryb1(CGLwidget* widget) : tryb(widget) {wid->sap->text3->setText(QString::fromStdString("aaa"));}
void tryb1::puszczone(int x, int y) 
{
	wid->ustaw_tryb(new tryb1a(wid, x,y));
}
void tryb1a::przesuniete(int x, int y)
{
	ndr* al=wid->al;
	al->przesuncentrum(-al->starex(x)+al->starex(sx), -al->starey(y)+al->starey(sy));
	sx=x;
	sy=y;
}
tryb1a::tryb1a(CGLwidget* widget, int x, int y) : tryb(widget), sx(x), sy(y) {}
void tryb1a::puszczone(int x, int y) 
{
	wid->ustaw_tryb(new tryb1(wid));
}
//TRYB 2 - DODAWANIE ODCINKA
tryb2::tryb2(CGLwidget* widget) : tryb(widget)
{
}
void tryb2::puszczone(int x, int y)
{
	ndr* al=wid->al;
	int a1=ste->wyszukajpunkt(al->stare(PUNKT(x,y), 0), al->starex(7)-al->starex(0));
	if(a1==-1)
		a1=ste->dodajpunkt(al->stare(PUNKT(x,y), al->przyc));
	wid->ustaw_tryb(new tryb2a(wid, a1));
}
tryb2a::tryb2a(CGLwidget* widget, int plp) : tryb(widget), pol_p(plp) {}
void tryb2a::puszczone(int x, int y) 
{
	ndr* al=wid->al;
	int a1=ste->wyszukajpunkt(al->stare(PUNKT(x,y), 0), al->starex(7)-al->starex(0));
	if(a1==-1)
		a1=ste->dodajpunkt(al->stare(PUNKT(x,y), al->przyc));
	int k1=ste->dodaj_odcinek(pol_p, a1);
	wid->ustaw_tryb(new tryb2(wid));
}
//TRYB 3 - ZAZNACZANIE
tryb3::tryb3(CGLwidget* widget) : tryb(widget)
{
}
void tryb3::wcisniete(int x, int y) {}
void tryb3::puszczone(int x, int y)
{
	ndr* al=wid->al;
	int p1=ste->wyszukajpunkt(al->stare(PUNKT(x,y), 0), al->starex(7)-al->starex(0));
	if(p1!=-1)
	{
		if(ste->czy_pkt_do_zaz(p1))
			ste->usun_pkt_z_zaz(p1);
		else
			ste->dodaj_pkt_do_zaz(p1);
	}
	else
	{
		int k1=ste->wyszukajkrzywa(al->stare(PUNKT(x,y), 0), al->starex(7)-al->starex(0));
		if(k1!=-1)
		{
			if(ste->czy_krz_do_zaz(k1))
				ste->usun_krz_z_zaz(k1);
			else
				ste->dodaj_krz_do_zaz(k1);
		}
		/*else
		{
			if(ste->liczba_pkt_zaz()==1)
			{
				ste->przesun_zaznaczenie(al->stare(PUNKT(x,y), al->przyc));
				wid->ustaw_tryb(new tryb3(wid));
			}
		}*/
	}
}
//TRYB 4 - DODAWANIE LINIOLUKU
tryb4::tryb4(CGLwidget* widget) : tryb(widget)
{
}
void tryb4::puszczone(int x, int y)
{	
	ndr* al=wid->al;
	int p1=ste->wyszukajpunkt(al->stare(PUNKT(x,y), 0), al->starex(7)-al->starex(0));
	if(p1==-1)
		p1=ste->dodajpunkt(al->stare(PUNKT(x,y), al->przyc));
	wid->ustaw_tryb(new tryb4a(wid, p1));
}
tryb4a::tryb4a(CGLwidget* widget, int st) : tryb(widget), sta(st) {}
void tryb4a::puszczone(int x, int y) 
{
	ndr* al=wid->al;
	int p1=ste->wyszukajpunkt(al->stare(PUNKT(x,y), 0), al->starex(7)-al->starex(0));
	if(p1==-1)
		p1=ste->dodajpunkt(al->stare(PUNKT(x,y), al->przyc));
	wid->ustaw_tryb(new tryb4b(wid, sta, p1));
}
tryb4b::tryb4b(CGLwidget* widget, int st, int stp) : tryb(widget), sta(st), sto(stp) {}
void tryb4b::puszczone(int x, int y) 
{
	double kwyn;
	ndr* al=wid->al;
	int k1=ste->wyszukajkrzywa(al->stare(PUNKT(x,y), 0), al->starex(10)-al->starex(0));
	if(k1!=-1)
	{
		double alfa1=ste->odleglosc_na_krzywej(k1, al->stare(PUNKT(x,y),0));
		if(alfa1<ste->dlugosc(k1)/2)
			kwyn=ste->kierunekwodl(k1, 0);
		else
			kwyn=ste->kierunekwodl(k1, ste->dlugosc(k1));
	}
	else
	{
		LINIA l1(ste->wsp_pkt(sta), al->stare(PUNKT(x,y), al->przyc));
		kwyn=l1.kierunek();
	}
	wid->ustaw_tryb(new tryb4c(wid, sta, sto, kwyn));
}
tryb4c::tryb4c(CGLwidget* widget, int st, int stp, double k1) : tryb(widget), sta(st), sto(stp), kier1(k1) {}
void tryb4c::puszczone(int x, int y) 
{
	double kwyn;
	ndr* al=wid->al;
	int k1=ste->wyszukajkrzywa(al->stare(PUNKT(x,y), 0), al->starex(10)-al->starex(0));
	if(k1!=-1)
	{
		double alfa1=ste->odleglosc_na_krzywej(k1, al->stare(PUNKT(x,y),0));
		if(alfa1<ste->dlugosc(k1)/2)
			kwyn=ste->kierunekwodl(k1, 0);
		else
			kwyn=ste->kierunekwodl(k1, ste->dlugosc(k1));
	}
	else
	{
		LINIA l1(ste->wsp_pkt(sto), al->stare(PUNKT(x,y), al->przyc));
		kwyn=l1.kierunek();
	}
	ste->dodaj_linioluk(sta, sto, kier1, kwyn);
	wid->ustaw_tryb(new tryb4(wid));
}
//TRYB 5 - ZAZNACZANIE REGIONU
tryb5::tryb5(CGLwidget* widget) : tryb(widget) {}
void tryb5::puszczone(int x, int y)
{
	ndr* al=wid->al;
	PUNKT next=al->stare(PUNKT(x,y));
	wid->ustaw_tryb(new tryb5a(wid, next));
}
tryb5a::tryb5a(CGLwidget* widget, PUNKT pp) : tryb(widget), ppo(pp) {}
void tryb5a::puszczone(int x, int y)
{
	ndr* al=wid->al;
	PUNKT next=al->stare(PUNKT(x,y));
	ste->zaznaczogr(ppo, next);
	wid->ustaw_tryb(new tryb5(wid));
}
void tryb6::puszczone(int x, int y)
{
	ndr* al=wid->al;
	ste->wczyt(sciezka, al->stare(PUNKT(x,y), al->przyc));
}
void tryb7::puszczone(int x, int y)
{
	ndr* al=wid->al;
	PUNKT next=al->stare(PUNKT(x,y), al->przyc);
	if(ste->liczba_pkt_zaz()==1)
	{
		vector <int> wt=ste->p_zaz();
		ste->przesun_zaznaczenie(ste->wsp_pkt(wt[0]), next);
	}
	else
		wid->ustaw_tryb(new tryb7a(wid, next));
}
void tryb7a::puszczone(int x, int y)
{
	ndr* al=wid->al;
	PUNKT next=al->stare(PUNKT(x,y), al->przyc);
	ste->przesun_zaznaczenie(ppo, next);
	wid->ustaw_tryb(new tryb7(wid));
}
ndr::ndr(SimpleApp* sa, double szer, double wys) : sap(sa), map_prop(szer, wys, -1000, 2100, 2100, -1000) 
{
	przyc=0;
}
void ndr::rysuj_siatka()
{
	double kierunek=kier;
	PUNKT alfa1=transferuj(PUNKT(starex(0), starey(0)));
	PUNKT alfa2=transferuj(PUNKT(starex(0), starey(wobrazu())));
	PUNKT alfa3=transferuj(PUNKT(starex(sobrazu()), starey(0)));
	PUNKT alfa4=transferuj(PUNKT(starex(sobrazu()), starey(wobrazu())));
	double lewyzakres=min(min(alfa1.x, alfa2.x), min(alfa3.x, alfa4.x));
	lewyzakres/=w111;
	int lz=lewyzakres;
	lz--;
	lewyzakres=(double)lz;
	lewyzakres*=w111;
	double prawyzakres=max(max(alfa1.x, alfa2.x), max(alfa3.x, alfa4.x));
	double dolnyzakres=min(min(alfa1.y, alfa2.y), min(alfa3.y, alfa4.y));
	double gornyzakres=max(max(alfa1.y, alfa2.y), max(alfa3.y, alfa4.y));
	dolnyzakres/=w111;
	int dl=dolnyzakres;
	dl--;
	dolnyzakres=(double)dl;
	dolnyzakres*=w111;
	glColor3ub(ust_sta_2.kolor1[0], ust_sta_2.kolor1[1], ust_sta_2.kolor1[2]);
	int licz1=0;
	for(double start=dolnyzakres; start<=gornyzakres; start+=w111/5)
	{
		if(licz1%5!=0)
		{
			PUNKT p1(lewyzakres, start);
			PUNKT p2(prawyzakres, start);
			p1=odtransferuj(p1);
			p2=odtransferuj(p2);
			glBegin(GL_LINES);
			glVertex2d(p1.x, p1.y);
			glVertex2d(p2.x, p2.y);
			glEnd();
		}
		licz1++;
	}
	licz1=0;
	for(double start=lewyzakres; start<=prawyzakres; start+=w111/5)
	{
		if(licz1%5!=0)
		{
			PUNKT p1(start, gornyzakres);
			PUNKT p2(start, dolnyzakres);
			p1=odtransferuj(p1);
			p2=odtransferuj(p2);
			glBegin(GL_LINES);
			glVertex2d(p1.x, p1.y);
			glVertex2d(p2.x, p2.y);
			glEnd();
		}
		licz1++;
	}
	glLineWidth(2);
	glColor3ub(ust_sta_2.kolor2[0], ust_sta_2.kolor2[1], ust_sta_2.kolor2[2]);
	for(double start=dolnyzakres; start<=gornyzakres; start+=w111)
	{
		PUNKT p1(lewyzakres, start);
		PUNKT p2(prawyzakres, start);
		p1=odtransferuj(p1);
		p2=odtransferuj(p2);
		glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
		glEnd();
	}
	glColor3ub(ust_sta_2.kolor2[0], ust_sta_2.kolor2[1], ust_sta_2.kolor2[2]);
	for(double start=lewyzakres; start<=prawyzakres; start+=w111)
	{	
		PUNKT p1(start, gornyzakres);
		PUNKT p2(start, dolnyzakres);
		p1=odtransferuj(p1);
		p2=odtransferuj(p2);
		glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
		glEnd();
	}
	glLineWidth(1);
}
void ndr::rysuj_strzalka(PUNKT alfa, double kierunek, double size) //niebędzie działać w przypadku zdeformowanych ygreków
{
	LINIA a1(alfa, stand_kierunek(kierunek-M_PI/4.0*3.0), size);
	LINIA a2(alfa, stand_kierunek(kierunek+M_PI/4.0*3.0), size);
	LINIA ac(alfa, kierunek, size);
	PUNKT p1=a1.koniec();
	PUNKT p2=a2.koniec();
	PUNKT pc=ac.koniec();
	glBegin(GL_POLYGON);
	glVertex2f(p1.x, p1.y);
	glVertex2f(pc.x, pc.y);
	glVertex2f(alfa.x, alfa.y);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(p2.x, p2.y);
	glVertex2f(pc.x, pc.y);
	glVertex2f(alfa.x, alfa.y);
	glEnd();
}
void ndr::w111change()
{
	sap->text2->setText("cz_kra: "+QString::number(w111)+", po_kra: "+QString::number(w111/5));
}
void ustawatrybuty::zap()
{
	cout<<"A#"<<endl;
	vector <map <string, string> > wyn=wyslij();
	cout<<"B#"<<wyn.size()<<endl;
	vector <int> sp1=ste->k_zaz();
	int s1=sp1.size();
	for(int i=0; i<s1; i++)
		ste->set_prop_krz(sp1[i], wyn[i]);
	vector <int> sp2=ste->p_zaz();
	int s2=sp2.size();
	for(int i=0; i<s2; i++)
		ste->set_prop_pkt(sp2[i], wyn[i]);

}
void SimpleApp::listy_zmienione()
{
	//if(loaded)
	//	glScene->akttryb->klucz(Qt::Key_D);
}
void SimpleApp::onPaint()
{
	ste->rysuj(alfa);
}
SimpleApp::SimpleApp(QWidget *parent, string scz):QMainWindow(parent), sciezka(scz)
{

	ccc5=new MapaWidget(this, this);
	this->setGeometry(0, 0, 500, 500);
	loaded=0;
	ste=this;
	cout<<"wczytywanie..."<<endl;
	if(sciezka!="")
		ste->wczyt(sciezka);
	cout<<"wczytano"<<endl;
	QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
	gornywidget=new QWidget();
	dolnywidget=new QWidget();
	text2=new QLabel(tr(""), dolnywidget);
	text3=new QLabel(tr(""), dolnywidget);
	alfa=new ndr(this, 600, 600);
	te1=new QTextEdit(gornywidget);
	a1=new QPushButton(tr("Powiększ [+]"), gornywidget);
	a2=new QPushButton(tr("Pomniejsz [-]"), gornywidget);
	a3=new QPushButton(tr("Zaznacz [Q]"), gornywidget);
	a4=new QPushButton(tr("Dodaj linie [W]"), gornywidget);
	a5=new QPushButton(tr("Dodaj llkuk [E]"), gornywidget);
	a6=new QPushButton(tr("Przesun [T]"), gornywidget);
	a7=new QPushButton(tr("Zer siatkę [Z]"), gornywidget);
	a8=new QPushButton(tr("Zazn prost [L]"), gornywidget);
	a9=new QPushButton(tr("Usuń [D]"), gornywidget);
	a10=new QPushButton(tr("Zapisz"), gornywidget);
	atr1=new ustawatrybuty(0, this);
	a11=new QPushButton(tr("[R]"), gornywidget);
	a12=new QPushButton(tr("[L]"), gornywidget);
	a13=new QPushButton(tr("[Esc]"), gornywidget);
	a14=new QPushButton(tr("[P]"), gornywidget);
	a15=new QPushButton(tr("[K]"), gornywidget);
	a16=new QPushButton(tr("Zapisz jako"), gornywidget);
	a17=new QPushButton(tr("Zapisz ZAZ"), gornywidget);
	a18=new QPushButton(tr("Wczytaj..."), gornywidget);
	a19=new QPushButton(tr("Przesun ZAZ [H]"), gornywidget);
	a20=new QPushButton(tr("20"), gornywidget);
	opcja1=new QRadioButton(tr("Prz.do.siat"), gornywidget);
	text1=new QLabel(tr("(--, --)"), dolnywidget);
	text1->setGeometry(2, 2, 200, 26);
	text2->setGeometry(204, 2, 200, 26);
	text3->setGeometry(406, 2, 200, 26);
	te1->hide();
	widget=new QWidget();
	setCentralWidget(widget);
	QGridLayout *mainLayoutt = new QGridLayout();
	glScene=new CGLwidget(alfa, this, this);
	mainLayoutt->addWidget(gornywidget, 0, 0, 1, 2);
	mainLayoutt->addWidget(glScene, 1, 0);
	mainLayoutt->addWidget(atr1, 1, 1);
	mainLayoutt->addWidget(ccc5, 1, 2);
	mainLayoutt->addWidget(dolnywidget, 2, 0);
	widget->setLayout(mainLayoutt);
	gornywidget->setMaximumHeight(95);
	dolnywidget->setMaximumHeight(30);
	//glScene->setGeometry(10, 50, 600, 600);
     	connect(a1, SIGNAL(clicked()), this, SLOT(mod1()));
     	connect(a2, SIGNAL(clicked()), this, SLOT(mod2()));
     	connect(a3, SIGNAL(clicked()), this, SLOT(mod3()));
     	connect(a4, SIGNAL(clicked()), this, SLOT(mod4()));
     	connect(a5, SIGNAL(clicked()), this, SLOT(mod5()));
     	connect(a6, SIGNAL(clicked()), this, SLOT(mod6()));
     	connect(a6, SIGNAL(clicked()), this, SLOT(mod6()));
     	connect(a7, SIGNAL(clicked()), this, SLOT(mod7()));
     	connect(a8, SIGNAL(clicked()), this, SLOT(mod8()));
     	connect(a9, SIGNAL(clicked()), this, SLOT(mod9()));
     	connect(a10, SIGNAL(clicked()), this, SLOT(mod10()));
     	connect(a11, SIGNAL(clicked()), this, SLOT(mod11()));
     	connect(a12, SIGNAL(clicked()), this, SLOT(mod12()));
     	connect(a13, SIGNAL(clicked()), this, SLOT(mod13()));
     	connect(a14, SIGNAL(clicked()), this, SLOT(mod14()));
     	connect(a15, SIGNAL(clicked()), this, SLOT(mod15()));
     	connect(a16, SIGNAL(clicked()), this, SLOT(mod16()));
     	connect(a17, SIGNAL(clicked()), this, SLOT(mod17()));
     	connect(a18, SIGNAL(clicked()), this, SLOT(mod18()));
     	connect(a19, SIGNAL(clicked()), this, SLOT(mod19()));
     	connect(a20, SIGNAL(clicked()), this, SLOT(mod20()));
     	connect(opcja1, SIGNAL(clicked()), this, SLOT(modo1()));
	fstream plikt;
	plikt.open("/home/marcin/.toreditrc", ios::in);
	if(plikt.is_open())
	{
		while(!plikt.eof())
		{
			char texty[1000];
			plikt.getline(texty, 1000);
			string stp=texty;
			alfa->wczytaj_properities(stp);
			glScene->wczytaj_properities(stp);
			stringstream ss;
			ss<<stp;
			string mainx;
			ss>>mainx;
			if(mainx=="POLECENIE")
			{
				string po2;
				ss>>po2;
				wywolanie* wyw=new wywolanie(this, gornywidget);
				wyw->setnazwa(po2);
				wywolania.push_back(wyw);
				char dalej[1000];
				ss.getline(dalej, 1000);
				string dal=dalej;
				wyw->setpolecenie(dal);
			}
		}
	}
	loaded=1;
	resize_gornywidget(gornywidget->width(), gornywidget->height());
}
void SimpleApp::mod1()
{
	glScene->akttryb->klucz(Qt::Key_Plus);
	glScene->updateGL();
}
void SimpleApp::mod2()
{
	glScene->akttryb->klucz(Qt::Key_Minus);
	glScene->updateGL();
}
void SimpleApp::mod3() {glScene->ustaw_tryb(new tryb3(glScene));}
void SimpleApp::mod4() {glScene->ustaw_tryb(new tryb2(glScene));}
void SimpleApp::mod5() {glScene->ustaw_tryb(new tryb4(glScene));}
void SimpleApp::mod6() {glScene->ustaw_tryb(new tryb1(glScene));}
void SimpleApp::mod7()
{
	glScene->akttryb->klucz(Qt::Key_Z);
	glScene->updateGL();
}
void SimpleApp::mod8() {glScene->ustaw_tryb(new tryb5(glScene));}
void SimpleApp::mod9() 
{
	glScene->akttryb->klucz(Qt::Key_Delete);
	glScene->updateGL();
}
void SimpleApp::mod10()
{
	if(sciezka=="")
	{
		QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz plik..."), "$HOME", tr("All files (*.*)"));
		sciezka=fileName.toStdString();
	}
	if(sciezka!="")
		ste->zapis(sciezka.c_str());
}
void SimpleApp::mod11() 
{
	glScene->akttryb->klucz(Qt::Key_R);
	glScene->updateGL();
}
void SimpleApp::mod12() 
{
	glScene->akttryb->klucz(Qt::Key_L);
	glScene->updateGL();
}
void SimpleApp::mod13() 
{
	glScene->akttryb->klucz(Qt::Key_Escape);
	glScene->updateGL();
}
void SimpleApp::mod14() 
{
	glScene->akttryb->klucz(Qt::Key_P);
	glScene->updateGL();
}
void SimpleApp::mod15() 
{
	glScene->akttryb->klucz(Qt::Key_K);
	glScene->updateGL();
}
void SimpleApp::mod16() 
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz jako..."), "$HOME", tr("All files (*.*)"));
	string scz=fileName.toStdString();
	if(scz!="")
	{
		sciezka=scz;
		ste->zapis(sciezka.c_str());
	}
}
void SimpleApp::mod17() 
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz jako..."), "$HOME", tr("All files (*.*)"));
	string scz=fileName.toStdString();
	if(scz!="")
	{
		ste->zapis_zaznaczone(scz.c_str());
	}
}
void SimpleApp::mod18() 
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Otworz"), "$HOME", tr("All files (*.*)"));
	string scz=fileName.toStdString();
	if(scz!="")
	{
		glScene->ustaw_tryb(new tryb6(glScene, scz));
	}
}
void SimpleApp::mod19() 
{
	glScene->ustaw_tryb(new tryb7(glScene));
}
void SimpleApp::mod20() 
{
	/*ste->wyslij_do_wtyczki("/home/marcin/programowanie/cpp/ProjektyWłasne/TOR-WTYCZKI/dijkstra2");
	//glScene->akttryb->klucz(Qt::Key_D);
	glScene->updateGL();*/
	QMainWindow* wnd=new QMainWindow();
	wnd->show();
}
void SimpleApp::modo1() 
{
	if(alfa->przyc==1)
		alfa->przyc=0;
	else
		alfa->przyc=1;
}

bool SimpleApp::event (QEvent * event)
{
	event ->accept();
	if (event -> type () == QEvent::KeyPress)
	{
		int x;
		x=(static_cast <QKeyEvent*>(event) -> key());
		glScene->akttryb->klucz(x);
		glScene->updateGL();
		return true;
	}
	if (event -> type () == QEvent::Resize)
	{
		resize_gornywidget(gornywidget->width(), gornywidget->height());
		return true;
	}
	return QWidget::event(event);
}
bool CGLwidget::event (QEvent * event)
{
		event -> accept ();
		if (event -> type () == QEvent::MouseButtonPress)
		{
			int x,y;
			x=(static_cast <QMouseEvent*>(event) -> x ());
			y=(static_cast <QMouseEvent*>(event) -> y ());
			akttryb->wcisniete(x,y);
			updateGL();
			return true;
		}
		if (event -> type () == QEvent::MouseMove)
		{
			int x,y;
			x=(static_cast <QMouseEvent*>(event) -> x ());
			y=(static_cast <QMouseEvent*>(event) -> y ());
			akttryb->przesuniete(x,y);
			sap->text1->setText("("+QString::number(al->starex(x))+", "+QString::number(al->starey(y))+")");
			updateGL();
			return true;
		}
		
		if (event -> type () == QEvent::MouseButtonRelease)
		{
			int x,y;
			x=(static_cast <QMouseEvent*>(event) -> x ());
			y=(static_cast <QMouseEvent*>(event) -> y ());
			akttryb->puszczone(x,y);
			updateGL();
			return true;
		}
		return QWidget::event(event);
}

SimpleApp::~SimpleApp()
{
	if(sciezka=="")
	{
		QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz plik..."), "$HOME", tr("All files (*.*)"));
		sciezka=fileName.toStdString();
	}
	if(sciezka!="")
		ste->zapis(sciezka.c_str());
}
CGLwidget::CGLwidget(ndr* alfa, SimpleApp* ap, QWidget *parent)
        : sap(ap), al(alfa), QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	tlo_color[0]=0;
	tlo_color[1]=0;
	tlo_color[2]=0;
	akttryb=(new tryb3(this));
	setMouseTracking(true);
}
void CGLwidget::ustaw_tryb(tryb* t)
{
	t_do_usuniecia.push_back(akttryb);
	akttryb=t;
	int s2=t_do_usuniecia.size();
	for(int i=s2-1; i>=5; i--)
	{
		t_do_usuniecia.pop_back();
	}
}
CGLwidget::~CGLwidget()
{
}
QSize CGLwidget::minimumSizeHint() const
{
        return QSize(200, 200);
}


QSize CGLwidget::sizeHint() const
{
        return QSize(200, 200);

}

QSize CGLwidget::maximumSizeHint() const
{
        return QSize(200, 200);
}
void CGLwidget::initializeGL()
{
   glShadeModel(GL_SMOOTH);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void CGLwidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	glColor3ub(al->ust_sta_2.back_color[0], al->ust_sta_2.back_color[1], al->ust_sta_2.back_color[2]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(al->starex(0), al->starex(width()), al->starey(height()), al->starey(0));
   	glBegin(GL_POLYGON);
	glVertex2f(al->starex(0), al->starey(0));
	glVertex2f(al->starex(width()), al->starey(0));
	glVertex2f(al->starex(width()), al->starey(height()));
	glVertex2f(al->starex(0), al->starey(height()));
	glEnd();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	GLint range[2];
	range[0]=1;
	range[1]=64;
	glGetIntegerv(GL_ALIASED_LINE_WIDTH_RANGE, range);
	glGetIntegerv(GL_SMOOTH_LINE_WIDTH_RANGE, range);
	float sizes[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, sizes);
	cout<<sizes[0]<<" "<<sizes[1]<<endl;*/
	int s1=obrazy.size();
	for(int i=0; i<s1; i++)
		rysujobraz(obrazy[i], wymiary_obraz_calk[i].second, wymiary_obraz_calk[i].first, wymiary_obraz_pix[i].second, wymiary_obraz_pix[i].first, apro_wym_obraz[i], wsp_start_obraz[i].first, wsp_start_obraz[i].second);
	al->rysuj_siatka();
	ste->rysuj(al);
}
void CGLwidget::rysujobraz(char* ref, int wys, int szer, int wys_pix, int szer_pix, int wym_bmp, int xstart, int ystart)
{
	// definicja tekstury
	glTexImage2D(GL_TEXTURE_2D,0, 4,wym_bmp,wym_bmp,0,GL_BGRA,GL_UNSIGNED_BYTE, ref);
	// ustalenie parametrów tekstury
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);//GL_LINEAR
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	// ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);	
	// włączenie teksturowania
	glDisable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glTexCoord2i( 0, 1 ); glVertex2f(xstart, ystart+wys-((double)wym_bmp/(double)wys_pix)*wys);
	glTexCoord2i( 0, 0 ); glVertex2f(xstart, ystart+wys);
	glTexCoord2i( 1, 0 ); glVertex2f(xstart+((double)wym_bmp/(double)szer_pix)*szer, ystart+wys);
	glTexCoord2i( 1, 1 ); glVertex2f(xstart+((double)wym_bmp/(double)szer_pix)*szer, ystart+wys-((double)wym_bmp/(double)wys_pix)*wys);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void CGLwidget::resizeGL(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   al->setsw(width, height);
   gluOrtho2D(al->starex(0), al->starex(width), al->starey(height), al->starey(0));
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
void wywolanie::wywolaj()
{
	if(polecenie!="")
		ste->wyslij_do_wtyczki(polecenie);
	sapvv->glScene->akttryb->klucz(Qt::Key_D);
	sapvv->glScene->updateGL();
}
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
