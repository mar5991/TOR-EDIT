#include <iostream>
#include "geom.hpp"
using namespace std;
#ifndef MAP_PROP
#define MAP_PROP
class map_prop
{
	double centerx;
	double centery;
	double zoom;
	double szerobrazu;
	double wysobrazu;
	double setw111()
	{
		w111=1;
		int lcz=0;
		if(zom()<1)
		{
			while(w111>zom())
			{
				if(lcz%2==0)
					w111/=2;
				else
					w111/=5;
				lcz++;
			}
		}
		else
		{
			while(w111<zom())
			{
				if(lcz%2==0)
					w111*=2;
				else
					w111*=5;
				lcz++;
			}
		}
		w111/=200;
		w111=1/w111;
		w111change();
		//w111/=5;
	}
	public:
	virtual void w111change()
	{
	}
	PUNKT start;
	double kier;
	double w111;
	map_prop(double so, double wo, double l, double p, double g, double d) : start(0,0)
	{
		kier=0;
		szerobrazu=so;
		wysobrazu=wo;
		setprostokat(l,p,g,d);
	}
	void setsw(double so, double wo)
	{
		szerobrazu=so;
		wysobrazu=wo;
	}
	void przesuncentrum(double wartx, double warty)
	{
		centerx+=wartx;
		centery+=warty;
	}
	double zom()
	{
		return zoom;
	}
	void setzoom(double wart)
	{
		zoom=wart;
		setw111();
	}
	void powiekszzoom(double wsp)
	{
		zoom*=wsp;
		setw111();
	}
	void setprostokat(double lewy, double prawy, double gora, double dol)
	{
		centerx=(lewy+prawy)/2;
		centery=(gora+dol)/2;
		zoom=min(szerobrazu/(prawy-lewy), wysobrazu/(gora-dol));
		setw111();
	}
	double sobrazu()
	{
		return szerobrazu;
	}
	double wobrazu()
	{
		return wysobrazu;
	}
	double nowex(double stare)
	{
		return szerobrazu/2+(stare-centerx)*zoom;
	}
	double nowey(double stare)
	{
		return wysobrazu/2+(stare-centery)*zoom;
	}
	double starex(double nowe)
	{
		return (nowe-szerobrazu/2)/zoom+centerx;
	}
	PUNKT stare(PUNKT cel)
	{
		return PUNKT(starex(cel.x), starey(cel.y));
	}
	PUNKT stare(PUNKT cel, bool przyc)
	{
		if(!przyc)
			return stare(cel);
		return siatka(stare(cel));
	}
	double starey(double nowe)
	{
		return (nowe-wysobrazu/2)/zoom+centery;
	}
	PUNKT transferuj (PUNKT cel)
	{
		cel.x-=start.x;
		cel.y-=start.y;
		LINIA l1(PUNKT(0,0), cel);
		l1=l1.obroc(kier);
		return l1.koniec();
	}
	PUNKT odtransferuj(PUNKT cel)
	{
		LINIA l1(PUNKT(0,0), cel);
		l1=l1.obroc(kier*(-1.0));
		cel=l1.koniec();
		cel.x+=start.x;
		cel.y+=start.y;
		return cel;
	}
	PUNKT siatka(PUNKT cel)
	{
		w111/=5;
		PUNKT ptr=transferuj(cel);
		double lewyzakres=ptr.x;
		lewyzakres/=w111;
		int lz=lewyzakres;
		double wartwyjsciowa=5;
		int ikonc=0;
		for(int i=-2; i<=2; i++)
		{
			double wejscie=abs(lewyzakres-double(lz+i));
			if(wejscie<wartwyjsciowa)
			{
				wartwyjsciowa=wejscie;
				ikonc=i;
			}
		}
		lz+=ikonc;
		lewyzakres=double(lz);
		lewyzakres*=w111;


		double dolnyzakres=ptr.y;
		dolnyzakres/=w111;
		lz=dolnyzakres;
		wartwyjsciowa=5;
		ikonc=0;
		for(int i=-2; i<=2; i++)
		{
			double wejscie=abs(dolnyzakres-double(lz+i));
			if(wejscie<wartwyjsciowa)
			{
				wartwyjsciowa=wejscie;
				ikonc=i;
			}
		}
		lz+=ikonc;
		dolnyzakres=double(lz);
		dolnyzakres*=w111;
		w111*=5;
		return odtransferuj(PUNKT(lewyzakres, dolnyzakres));
	}
};
#endif
