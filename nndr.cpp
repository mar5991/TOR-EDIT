#include "nndr.hpp"
void rysowanie_siatki::rysuj()
{
	double kierunek=ust->kier;
	double w111=ust->w111;
	PUNKT alfa1=ust->transferuj(PUNKT(ust->starex(0), ust->starey(0)));
	PUNKT alfa2=ust->transferuj(PUNKT(ust->starex(0), ust->starey(ust->wobrazu())));
	PUNKT alfa3=ust->transferuj(PUNKT(ust->starex(ust->sobrazu()), ust->starey(0)));
	PUNKT alfa4=ust->transferuj(PUNKT(ust->starex(ust->sobrazu()), ust->starey(ust->wobrazu())));
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
	glColor3ub(co_r, co_g, co_b);
	int licz1=0;
	for(double start=dolnyzakres; start<=gornyzakres; start+=w111/5)
	{
		if(licz1%5!=0)
		{
			PUNKT p1(lewyzakres, start);
			PUNKT p2(prawyzakres, start);
			p1=ust->odtransferuj(p1);
			p2=ust->odtransferuj(p2);
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
			p1=ust->odtransferuj(p1);
			p2=ust->odtransferuj(p2);
			glBegin(GL_LINES);
			glVertex2d(p1.x, p1.y);
			glVertex2d(p2.x, p2.y);
			glEnd();
		}
		licz1++;
	}
	glLineWidth(2);
	for(double start=dolnyzakres; start<=gornyzakres; start+=w111)
	{
		PUNKT p1(lewyzakres, start);
		PUNKT p2(prawyzakres, start);
		p1=ust->odtransferuj(p1);
		p2=ust->odtransferuj(p2);
		glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
		glEnd();
	}
	for(double start=lewyzakres; start<=prawyzakres; start+=w111)
	{	
		PUNKT p1(start, gornyzakres);
		PUNKT p2(start, dolnyzakres);
		p1=ust->odtransferuj(p1);
		p2=ust->odtransferuj(p2);
		glBegin(GL_LINES);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p2.x, p2.y);
		glEnd();
	}
	glLineWidth(1);

}

