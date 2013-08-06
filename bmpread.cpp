#include "bmpread.hpp"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;
char* czytajbmp(string file, int* szer, int* wys, int* wym)
{
	FileHeader File;
	PictureHeader Picture;
	FILE *f = fopen(file.c_str(),"rb");
	system("cls");
	fread(&File.bfType,sizeof(File.bfType),1,f);
	fread(&File.bfSize,sizeof(File.bfSize),1,f);
	fread(&File.bfReserved1,sizeof(File.bfReserved1),1,f);
	fread(&File.bfReserved2,sizeof(File.bfReserved2),1,f);
	fread(&File.bfOffBits,sizeof(File.bfOffBits),1,f);
	fseek(f,14,SEEK_SET);
	fread(&Picture.biSize,sizeof(Picture.biSize),1,f);
	fread(&Picture.biWidth,sizeof(Picture.biWidth),1,f);
	fread(&Picture.biHeight,sizeof(Picture.biHeight),1,f);
	fread(&Picture.biPlanes,sizeof(Picture.biPlanes),1,f);
	fread(&Picture.biBitCount,sizeof(Picture.biBitCount),1,f);
	fread(&Picture.biCompression,sizeof(Picture.biCompression),1,f);
	fread(&Picture.biSizeImage,sizeof(Picture.biSizeImage),1,f);
	fread(&Picture.biXPelsPerMeter,sizeof(Picture.biXPelsPerMeter),1,f);
	fread(&Picture.biYPelsPerMeter,sizeof(Picture.biYPelsPerMeter),1,f);
	fread(&Picture.biClrUsed,sizeof(Picture.biClrUsed),1,f);
	fread(&Picture.biClrImportant,sizeof(Picture.biClrImportant),1,f);
	fseek(f,File.bfOffBits,SEEK_SET);
	char bmpImg;
	char wynik[Picture.biHeight*Picture.biWidth*3];
	int licz=0;
	int liczbity=0;
	for(int j=0; j<Picture.biHeight; j++)
	{
		for (int i=0; i<(Picture.biWidth)*3;i++) 
		{
			fread(&bmpImg, 1, 1, f);
			wynik[licz]=bmpImg;
			licz++;
			liczbity++;
		}
		int wmax=4-((Picture.biWidth*3)%4);
		if(wmax==4)
			wmax=0;
		for(int i=0; i<wmax; i++)
		{
			fread(&bmpImg, 1, 1, f);
			liczbity++;
		}
	}
	*szer=Picture.biWidth;
	*wys=Picture.biHeight;
	printf("\n");  
	fclose(f);
	int ppl=log2(double(max(Picture.biHeight, Picture.biWidth)));
	ppl+=1;
	int wymiary=pow(2, ppl);
	char* wynost=new char[wymiary*wymiary*4];
	int lcz2=0;
	int lcz1=0;
	for(int i=0; i<Picture.biHeight; i++)
	{
		for(int j=0; j<Picture.biWidth; j++)
		{
			wynost[lcz2]=wynik[lcz1];
			wynost[lcz2+1]=wynik[lcz1+1];
			wynost[lcz2+2]=wynik[lcz1+2];
			wynost[lcz2+3]=255;
			lcz2+=4;
			lcz1+=3;
		}
		for(int j=Picture.biWidth; j<wymiary; j++)
		{
			wynost[lcz2]=0;
			wynost[lcz2+1]=0;
			wynost[lcz2+2]=0;
			wynost[lcz2+3]=0;
			lcz2+=4;
		}
	}
	for(int i=Picture.biHeight; i<wymiary; i++)
	{
		for(int j=0; j<wymiary; j++)
		{	
			wynost[lcz2]=0;
			wynost[lcz2+1]=0;
			wynost[lcz2+2]=0;
			wynost[lcz2+3]=0;
			lcz2+=4;
		}
	}
	*wym=wymiary;
	return wynost;
}

