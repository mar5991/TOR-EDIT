#ifndef BMPREAD_HPP
#define BMPREAD_HPP
#include <fstream>
#include <cmath>
#include <cstring>
using namespace std;
struct FileHeader 
{
	short bfType;
	int bfSize;
	short bfReserved1;
	short bfReserved2;
	short bfOffBits;
};

 
struct PictureHeader
{
	int biSize;
	int biWidth;
	int biHeight;
	short biPlanes;
	short biBitCount;
	int biCompression;
	int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	int biClrUsed;
	int biClrImportant;
};

struct KoloryRGB
{
	char R;
	char G;
	char B;
};

char* czytajbmp(string file, int* szer, int* wys, int* wym);
#endif
