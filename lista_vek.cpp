#include "lista_vek.hpp"
obiekt_na_liscie::~obiekt_na_liscie()
{
	/*vector<lista_vek*> uz=uzywane();
	int s1=uz.size();
	for(int i=0; i<s1; i++)
	{
		uz[i]->usun_obiekt(this);
	}*/
}
obiekt_na_liscie_classic::~obiekt_na_liscie_classic()
{
	vector<lista_vek*> uz=uzywane();
	int s1=uz.size();
	for(int i=0; i<s1; i++)
	{
		uz[i]->usun_obiekt(this);
	}
}
