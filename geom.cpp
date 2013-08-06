#include "geom.hpp"
double stand_kierunek(double wart) // konwertuje wartość w radianach do przedziału <-PI; PI>
{
	if(wart<0)
	{
		int licz=(wart*-1)/(2*M_PI)+1;
		wart+=(double)licz*2*M_PI;
	}
	wart+=M_PI;
	wart/=2*M_PI;
	int wartt=wart;
	wart-=(double)wartt;
	wart*=2*M_PI;
	wart-=M_PI;
	return wart;
}

double odl_mkier_niez_ruchem_wskaz(double kier1, double kier2)
{
	kier1=stand_kierunek(kier1);
	kier2=stand_kierunek(kier2);
	if(kier2>kier1)
		return kier2-kier1;
	return (M_PI-kier1)+(kier2+M_PI);
}

double odl_mkier_zgod_ruchem_wskaz(double kier1, double kier2)
{	
	kier1=stand_kierunek(kier1);
	kier2=stand_kierunek(kier2);
	if(kier2<kier1)
		return kier1-kier2;
	return kier1+M_PI+(M_PI-kier2);
}
bool PUNKT::operator==(PUNKT p)
{
	if(this->x==p.x && this->y==p.y)
		return true;
	return false;
}
PUNKT::PUNKT(double xx, double yy)
{
	x=xx;
	y=yy;
}
bool PUNKT::czywprost(PUNKT lewydolny, PUNKT prawygorny)
{
	if(x>=lewydolny.x && x<=prawygorny.x)
		if(y>=lewydolny.y && y<=prawygorny.y)
			return true;
	return false;
}
LINIA::LINIA(double xx1, double yy1, double xx2, double yy2)
{
	x1=xx1;
	y1=yy1;
	x2=xx2;
	y2=yy2;
}
LINIA::LINIA(PUNKT alfa, PUNKT beta)
{
	x1=alfa.x;
	y1=alfa.y;
	x2=beta.x;
	y2=beta.y;
}
LINIA::LINIA(PUNKT alfa, double kierunek, double odl)
{
	kierunek=stand_kierunek(kierunek);
	double xa=cos(kierunek);
	double ya=sin(kierunek);
	xa*=odl;
	ya*=odl;
	x1=alfa.x;
	x2=x1+xa;
	y1=alfa.y;
	y2=y1+ya;
}
PUNKT LINIA::poczatek()
{
	PUNKT k(x1, y1);
	return k;
}	
PUNKT LINIA::koniec()
{
	PUNKT k(x2, y2);
	return k;
}
double LINIA::dlugosc()
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
PUNKT LINIA::odlodpocz(double k)
{
	return PUNKT(((x2-x1)*k/dlugosc())+x1, (((y2-y1)*k/dlugosc()))+y1);
}
LINIA LINIA::reverse()
{
	LINIA c(x2, y2, x1, y1);
	return c;
}
void LINIA::do_prostokata(PUNKT* lewydolny, PUNKT* prawygorny)
{
	lewydolny->x=min(x1,x2);
	prawygorny->x=max(x1,x2);
	lewydolny->y=min(y1,y2);
	prawygorny->y=max(y1,y2);
}
double LINIA::odleglosc_prosta(PUNKT beta)
{
	double A=y2-y1;
	double B=x2-x1;
	return abs(A*(beta.x-x1)+B*(y1-beta.y))/sqrt(A*A + B*B);
}
int LINIA::pprze_prosta2(LINIA beta, PUNKT* pprzec)
{
	double ilo1=(x1-x2)*(beta.y1-beta.y2)-(y1-y2)*(beta.x1-beta.x2);
	double ilo2=(beta.x2-x2)*(beta.y1-beta.y2)-(beta.y2-y2)*(beta.x1-beta.x2);
	if(ilo1==0)
	{
		pprzec=NULL;
		if(ilo2==0)
		{
			return 2;
		}
		return 0;
	}
	double wp=double(ilo2)/double(ilo1);
	double xx=wp*x1+(1-wp)*x2;
	double yy=wp*y1+(1-wp)*y2;
	PUNKT p(xx, yy);
	*pprzec=p;
	return 1;
}
int LINIA::pprze(LINIA beta, PUNKT* pprzec)
{
	int wart=pprze_prosta2(beta, pprzec);
	if(wart==0)
		return 0;
	if(wart==2)
		return 2;
	PUNKT lda(0, 0);
	PUNKT pga(0, 0);
	PUNKT ldb(0, 0);
	PUNKT pgb(0, 0);
	do_prostokata(&lda, &pga);
	beta.do_prostokata(&ldb, &pgb);
	if(pprzec->czywprost(lda,pga) && pprzec->czywprost(ldb,pgb))
		return 1;
	pprzec=NULL;
	return 0;
}
int LINIA::pprze_prosta(LINIA beta, PUNKT* pprzec)
{
	int wart=pprze_prosta2(beta, pprzec);
	if(wart==0)
		return 0;
	if(wart==2)
		return 2;
	PUNKT ldb(0, 0);
	PUNKT pgb(0, 0);
	beta.do_prostokata(&ldb, &pgb);
	if(pprzec->czywprost(ldb,pgb))
		return 1;
	pprzec=NULL;
	return 0;
}
double LINIA::kierunek()
{
	if((x2-x1)!=0)
	{
		double wart=(y2-y1)/(x2-x1);
		double wynik=atan(wart);
		if(x2-x1<0)
		{
			wynik+=M_PI;
		}
		return stand_kierunek(wynik);
	}
	if(y2-y1>0)
		return M_PI/2;
	return -M_PI/2;
}
PUNKT LINIA::punkt_na_prostej(PUNKT beta)
{
	LINIA l(beta, stand_kierunek(kierunek()+M_PI/2), 100);
	PUNKT wynik(0, 0);
	pprze_prosta2(l, &wynik);
	return wynik;
}
double LINIA::odleglosc(PUNKT beta)
{
	PUNKT p=punkt_na_prostej(beta);
	PUNKT ld(0, 0);
	PUNKT pg(0, 0);
	do_prostokata(&ld, &pg);
	if(p.czywprost(ld, pg))
	{
		return odleglosc_prosta(beta);
	}
	else
	{
		LINIA f1(poczatek(), beta);
		LINIA f2(koniec(), beta);
		return min(f1.dlugosc(), f2.dlugosc());
	}
}
PUNKT LINIA::punkt_na_odc(PUNKT beta)
{
	PUNKT p=punkt_na_prostej(beta);
	PUNKT ld(0, 0);
	PUNKT pg(0, 0);
	do_prostokata(&ld, &pg);
	if(p.czywprost(ld, pg))
	{
		return p;
	}
	else
	{
		LINIA f1(poczatek(), beta);
		LINIA f2(koniec(), beta);
		if(f1.dlugosc()<f2.dlugosc())
			return poczatek();
		return koniec();
	}
}
double LINIA::wjakiejodl(PUNKT beta)
{
	beta=punkt_na_odc(beta);
	LINIA l1(poczatek(), beta);
	return l1.dlugosc();
}
LINIA LINIA::obroc(double kierun)
{
	return LINIA(poczatek(), stand_kierunek(kierunek()+kierun), dlugosc());
}
bool LINIA::poktorejstronie(PUNKT beta)
{
	return (x2-x1)*(beta.y-y1)-(y2-y1)*(beta.x-x1)<=0;
}
LUK::LUK(PUNKT srodek, double r)
{
	x_sr=srodek.x;
	y_sr=srodek.y;
	x_st=x_sr+r;
	y_st=y_sr;
	wycinek=M_PI*2;
}
double LUK::promien()
{
	LINIA l(srodek(), poczatek());
	return l.dlugosc();
}
PUNKT LUK::srodek()
{
	return PUNKT(x_sr, y_sr);
}
PUNKT LUK::poczatek()
{
	return PUNKT(x_st, y_st);
}
double LUK::kierunek_start()
{
	LINIA l(srodek(), poczatek());
	return l.kierunek();
}
bool LUK::czy_kierunek_do_luku(double kier)
{
	LINIA l1(srodek(), poczatek());
	if(wycinek<0)
		return odl_mkier_zgod_ruchem_wskaz(l1.kierunek(), kier)<=wycinek*-1;
	return odl_mkier_niez_ruchem_wskaz(l1.kierunek(), kier)<=wycinek;
}
double LUK::dlugosc()
{
	return abs(wycinek)*promien();
}
PUNKT LUK::odlodkier(double kierunek)
{
	LINIA l1(srodek(), poczatek());
	if(wycinek>0)
		return l1.obroc(kierunek).koniec();
	return l1.obroc(kierunek*-1).koniec();
}
PUNKT LUK::koniec()
{
	return odlodkier(abs(wycinek));
}
PUNKT LUK::odlodpocz(double odl)
{
	double kier=odl/promien();
	return odlodkier(kier);
}
PUNKT LUK::punkt_okrag(PUNKT alfa)
{
	LINIA l(srodek(), alfa);
	return l.odlodpocz(promien());
}
double LUK::odl_okrag(PUNKT alfa)
{
	LINIA l(srodek(), alfa);
	return abs(l.dlugosc()-promien());
}
PUNKT LUK::punkt_luk(PUNKT alfa)
{
	LINIA l(srodek(), alfa);
	if(czy_kierunek_do_luku(l.kierunek()))
		return punkt_okrag(alfa);
	LINIA la(alfa, poczatek());
	LINIA lb(alfa, koniec());
	if(la.dlugosc()<lb.dlugosc())
		return poczatek();
	return koniec();
}
double LUK::wjakiejodl(PUNKT alfa)
{
	alfa=punkt_luk(alfa);
	LINIA l1(srodek(), alfa);
	double dkier=stand_kierunek(odl_mkier_niez_ruchem_wskaz(kierunek_start(), l1.kierunek()));
	if(wycinek>0)
		return promien()*dkier;
	return promien()*dkier*-1;
}
double LUK::odl_luk(PUNKT alfa)
{
	LINIA l(srodek(), alfa);
	if(czy_kierunek_do_luku(l.kierunek()))
		return odl_okrag(alfa);
	LINIA la(alfa, poczatek());
	LINIA lb(alfa, koniec());
	return min(la.dlugosc(), lb.dlugosc());
}
LUK::LUK(PUNKT alfa, PUNKT beta, PUNKT gamma, bool czy_okrag)
{
	LINIA l1a(beta, gamma);
	PUNKT p1=l1a.odlodpocz(l1a.dlugosc()/2);
	LINIA l1(alfa, p1);
	LINIA l2a(gamma, alfa);
	PUNKT p2=l2a.odlodpocz(l2a.dlugosc()/2);
	LINIA l2(beta, p2);
	PUNKT sr(0, 0);
	l2.pprze_prosta2(l1, &sr);
	x_sr=sr.x;
	y_sr=sr.y;
	LINIA k1(sr, alfa);
	LINIA k2(sr, beta);
	LINIA k3(sr, gamma);
	x_st=alfa.x;
	y_st=alfa.y;
	if (odl_mkier_niez_ruchem_wskaz(k1.kierunek(), k2.kierunek())<odl_mkier_niez_ruchem_wskaz(k1.kierunek(), k3.kierunek()))
	wycinek=odl_mkier_niez_ruchem_wskaz(k1.kierunek(), k3.kierunek());
	else
		wycinek=odl_mkier_zgod_ruchem_wskaz(k1.kierunek(), k3.kierunek())*-1;
	if(czy_okrag)
		wycinek=M_PI*2;
}
LUK::LUK(PUNKT alfa, PUNKT beta, PUNKT srodek, int type)
{
	x_sr=srodek.x;
	y_sr=srodek.y;
	x_st=alfa.x;
	y_st=alfa.y;
	LINIA k1(srodek, alfa);
	LINIA k2(srodek, beta);
	if(type==0)
	{
		wycinek=odl_mkier_zgod_ruchem_wskaz(k1.kierunek(), k2.kierunek())*-1;
	}
	if(type==1)
	{
		wycinek=odl_mkier_niez_ruchem_wskaz(k1.kierunek(), k2.kierunek());
	}
	if(type==2)
	{
		wycinek=stand_kierunek(odl_mkier_niez_ruchem_wskaz(k1.kierunek(), k2.kierunek()));
	}
	if(type==3)
	{
		double wynik=odl_mkier_niez_ruchem_wskaz(k1.kierunek(), k2.kierunek());
		if(wynik>M_PI)
			wycinek=wynik;
		else
			wycinek=wynik-M_PI;
	}
	if(type==4)
	{
		wycinek=M_PI*2;
	}
}
LUK::LUK(LINIA srednica)
{
	PUNKT sr=srednica.odlodpocz(srednica.dlugosc()/2);
	double r=srednica.dlugosc()/2;
	x_sr=sr.x;
	y_sr=sr.y;
	x_st=x_sr;
	y_st=x_sr+r;
	wycinek=M_PI*2;
}

/*
double ilowekt(LINIA alfa, PUNKT beta) //zwraca iloczyn wektorowy linii i punktu
{
	return (alfa.x2-alfa.x1)*(beta.y-alfa.y1)-(alfa.y2-alfa.y1)*(beta.x-alfa.x1);
}

double ilowekt(PUNKT a1, PUNKT a2, PUNKT beta) // zwraca iloczyn wektorowy trzech punktów - a1 punkt centralny
{
	return (a2.x-a1.x)*(beta.y-a1.y)-(a2.y-a1.y)*(beta.x-a1.x);
}

bool czynaodc(LINIA alfa, PUNKT beta) //czy punkt beta leży na odcinku alfa
{
	return (ilowekt(alfa, beta)==0 && czywprost(beta, alfa.poczatek(), alfa.koniec()));
}

//bool czyrownolegle (LINIA alfa, LINIA beta)

//PUNKT pprzec (LINIA alfa, LINIA beta)

bool czyprzec (LINIA alfa, LINIA beta) //czy odcinki się przecinają //ZZZZZZZZZZ
{
	if(czynaodc(alfa, beta.poczatek()) || czynaodc(alfa, beta.koniec()) || czynaodc(beta, alfa.poczatek()) || czynaodc(beta, alfa.koniec()))
		return true;
	if(poktorejstronie(alfa, beta.poczatek())!=poktorejstronie(alfa, beta.koniec()))
		if(poktorejstronie(beta, alfa.poczatek())!=poktorejstronie(beta, alfa.koniec()))
			return true;
	return false;
}

double polewielok(vector <PUNKT> wie) //zwraca pole wielokąta
{
	int s1=wie.size();
	double sum=0;
	for(int i=0; i<s1; i++)
		sum+=(wie[i].x*wie[(i+1)%s1].y-wie[(i+1)%s1].x*wie[i].y);
	return sum/2;
}
//bool czyprzecpro (LINIA alfa, LINIA beta) //odcinek i prosta

bool czywwielok(vector <PUNKT>& wielokat, PUNKT pkt) //czy punkt leży W wielokącie (wnętrze)
{
	int s1=wielokat.size();
	int lprzec=0;
	LINIA gen(pkt.x, pkt.y, pkt.x+1, 1000000007);
	for(int i=0; i<s1; i++)
	{
		LINIA sbn(wielokat[i], wielokat[(i+1)%s1]);
		if(czyprzec(sbn, gen))
			lprzec++;
	}
	if(lprzec%2==0)
		return false;
	return true;
}

bool czynawielok(vector <PUNKT>& wielokat, PUNKT pkt) //czy punkt leży NA wielokącie (wnętrze + boki)
{
	int s1=wielokat.size();
	for(int i=0; i<s1; i++)
	{
		LINIA sbn(wielokat[i], wielokat[(i+1)%s1]);
		if(czynaodc(sbn, pkt))
			return true;
	}
	return czywwielok(wielokat, pkt);
}

bool czywwielokwyp(vector <PUNKT>& w, PUNKT pkt) //czy punkt leży W wielokącie wypukłym (tylko wnętrze; n log n)
{
	int a=1;
	int s1=w.size();
	int b=s1-1;
	int c;
	if(ilowekt(w[0], w[a], w[b])>0)
	{
		//swap
	}
	if(ilowekt(w[0], w[a], pkt)>=0 || ilowekt(w[0], w[b], pkt)<0)
		return false;
	while(abs(a-b)>1)
	{
		c=(a+b)/2;
		if(ilowekt(w[0], w[c], pkt)>0)
			b=c;
		else
			a=c;
	}
	return ilowekt(w[a], w[b], pkt)<=0;
}

int pprost(LINIA alfa, LINIA beta, PUNKT* pprzec) //0 - nie, 1 - tak, 2 - nieskonczenie, pprzec - wskaźnik na punkt przecięcia prostych
{
	int ilo1=(alfa.x1-alfa.x2)*(beta.y1-beta.y2)-(alfa.y1-alfa.y2)*(beta.x1-beta.x2);
	int ilo2=(beta.x2-alfa.x2)*(beta.y1-beta.y2)-(beta.y2-alfa.y2)*(beta.x1-beta.x2);
	if(ilo1==0)
	{
		if(ilo2==0)
			return 2;
		return 0;
	}
	double wp=double(ilo2)/double(ilo1);
	double xx=wp*alfa.x1+(1-wp)*alfa.x2;
	double yy=wp*alfa.y1+(1-wp)*alfa.y2;
	PUNKT p(xx, yy);
	*pprzec=p;
	return 1;
}

vector <PUNKT> prostaokrag (PUNKT cen, double pro, LINIA l) //zwraca punkty przecięcia prostej l i okręgu o środku cen i promieniu pro
{
	double a=sqr(l.x1)+sqr(l.y1)+sqr(l.x2)+sqr(l.y2) - 2*(l.x1*l.x2+l.y1*l.y2);
	double b=2*(cen.x*(l.x2-l.x1) + cen.y*(l.y2-l.y1) + l.x1*l.x2 + l.y1*l.y2 - sqr(l.x2)-sqr(l.y2));
	double c=-sqr(pro) + sqr(l.x2)+sqr(l.y2)+sqr(cen.x)+sqr(cen.y)-2*(cen.x*l.x2 + cen.y*l.y2);
	double d=b*b-4*a*c;
	double t=-b/(2*a);
	double e=sqrt(abs(d))/(2*a);
	vector <PUNKT> wynik;
	if(d<0)
		return wynik;
	if(d==0)
	{
		wynik.push_back(PUNKT(t*l.x1+(1-t)*l.x2, t*l.y1+(1-t)*l.y2));
	}
	if(d>0)
	{
		wynik.push_back(PUNKT((t+e)*l.x1+(1-t-e)*l.x2, (t+e)*l.y1+(1-t-e)*l.y2));
		wynik.push_back(PUNKT((t-e)*l.x1+(1-t+e)*l.x2, (t-e)*l.y1+(1-t+e)*l.y2));
	}
	return wynik;
}

bool okrag (PUNKT a1, PUNKT a2, PUNKT a3, PUNKT& cen, double& r) //dla trzech punktów a1,2,3 tworzy okrąg. punkt środkowy zapisywany w cen, promień w r; false jeśli się nie da utworzyć (współliniowość)
{
	PUNKT p(0, 0);
	cout<<(a1.x+a2.x)/2<<" "<<(a1.y+a2.y)/2<<" "<<(a1.x+a2.x)/2 + a2.y-a1.y<<" "<<(a1.y+a2.y)/2 + a1.x-a2.x<<endl;
	cout<<(a1.x+a3.x)/2<<" "<<(a1.y+a3.y)/2<<" "<<(a1.x+a3.x)/2 + a3.y-a1.y<<" "<<(a1.y+a3.y)/2 + a1.x-a3.x<<endl;
	if(pprost(LINIA((a1.x+a2.x)/2, (a1.y+a2.y)/2, (a1.x+a2.x)/2 + a2.y-a1.y, (a1.y+a2.y)/2 + a1.x-a2.x), LINIA((a1.x+a3.x)/2, (a1.y+a3.y)/2, (a1.x+a3.x)/2 + a3.y-a1.y, (a1.y+a3.y)/2 + a1.x-a3.x), &p)!=1)
		return false;
	cen=p;
	r=sqrt(sqr(a1.x-cen.x)+sqr(a1.y-cen.y));
	return true;
}

PUNKT centrum(0,0);

bool fsrt(PUNKT a, PUNKT b)
{
	return ilowekt(centrum, a, b)>0;
}

vector <PUNKT> srtkat(vector <PUNKT> start, LINIA lcen) //sortowanie kątowe - od prawej do lewej względem linii lcen
{
	vector <PUNKT> left;
	vector <PUNKT> right;
	int s1=start.size();
	for(int i=0; i<s1; i++)
	{
		if(poktorejstronie(lcen, start[i]))
			right.push_back(start[i]);
		else
			left.push_back(start[i]);
	}
	centrum=lcen.poczatek();
	sort(left.begin(), left.end(), fsrt);
	sort(right.begin(), right.end(), fsrt);
	vector <PUNKT> wynik;
	int s2=left.size();
	for(int i=0; i<s2; i++)
		wynik.push_back(left[i]);	
	s2=right.size();
	for(int i=0; i<s2; i++)
		wynik.push_back(right[i]);
	return wynik;
}

vector <PUNKT> wypotocz(vector <PUNKT> lst)
{
	int s1=lst.size();
	int nkol=0;
	int minx=2000000000;
	for(int i=0; i<s1; i++)
	{
		if(lst[i].x<minx)
		{
			minx=lst[i].x;
			nkol=i;
		}
	}
	LINIA l(lst[nkol].x, lst[nkol].y, lst[nkol].x-1, lst[nkol].y);
	vector <PUNKT> foo=srtkat(lst, l);
	vector <PUNKT> wyniki;
	wyniki.push_back(foo[0]);
	wyniki.push_back(foo[1]);
	s1=foo.size();
	for(int i=2; i<s1; i++)
	{
		LINIA k(foo[i-2], foo[i-1]);
		if(poktorejstronie(k, foo[i]))
		{
			wyniki.pop_back();
		}
		wyniki.push_back(foo[i]);
	}
	return wyniki;
}*/
/*
int main()
{
}*/

//ODLEGŁOSĆ PUNKTU OD ELEMENTU
//PUNKT ODPOWIADAJĄCY NA ELEMENCIE
//PUNKT NA ODLEGŁOŚCI
//ODLEGŁOŚĆ OD PUNKTU POCZĄTKOWEGO
