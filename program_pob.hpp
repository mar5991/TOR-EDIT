#ifndef PROGRAM_POB_HPP
#define PROGRAM_POB_HPP
#include <cstdio>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;
class program_pob
{
	FILE* ff;
	int fdes;
	public:
	program_pob(string polecenie)
	{
		string sciezka="fifo3";
		mkfifo(sciezka.c_str(), 0777);
		polecenie+=" < "+sciezka;
		ff=popen(polecenie.c_str(), "r");
		fdes=open(sciezka.c_str(), O_WRONLY);
	}
	void zapisz(stringstream& beta)
	{
		write(fdes, (beta.str()).c_str(), (beta.str()).length());
	}
	/*void operator<<(const program_pob& test, string& alfa)
	{
		write(fdes, alfa.c_str(), alfa.length());
	}
	void operator<<(const program_pob& test, ostream& alfa)
	{
		stringstream beta;
		beta<<alfa;
		write(fdes, (beta.str()).c_str(), (beta.str()).length());
	}
	void operator<<(const program_pob& test, int alfa)
	{
		stringstream beta;
		beta<<alfa;
		write(fdes, (beta.str()).c_str(), (beta.str()).length());
	}
	void operator<<(const program_pob& test, double alfa)
	{
		stringstream beta;
		beta<<alfa;
		write(fdes, (beta.str()).c_str(), (beta.str()).length());
	}
	void operator<<(const program_pob& test, float alfa)
	{
		stringstream beta;
		beta<<alfa;
		write(fdes, (beta.str()).c_str(), (beta.str()).length());
	}*/
	/*template <class TEST> void operator<<(const program_pob& test, TEST alfa)
	{
		stringstream beta;
		beta<<alfa;
		write(fdes, (beta.str()).c_str(), (beta.str()).length());
	}*/
	void wczytaj(stringstream& is)
	{
		char linia[2000000];
		int licz=0;
		char k='.';
		while(k!=EOF)
		{
			cout<<licz<<endl;
			k=fgetc(ff);
			linia[licz]=k;
			licz++;
		}
		//fgets(linia, 5000, ff);
		is<<linia;
	}
};
#endif
