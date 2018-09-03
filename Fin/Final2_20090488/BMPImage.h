#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <vector>

typedef unsigned char BYTE;
typedef unsigned short BYTE2;
typedef unsigned int BYTE4;

using namespace std;

typedef struct BITMAPFILEHEADER {
	BYTE2 bfType;
	BYTE4 bfSize;
	BYTE2 bfReserved1;
	BYTE2 bfReserved2;
	BYTE4 bfOffBits;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER {
	BYTE4 biSize;
	BYTE4 biWidth;
	BYTE4 biHeight;
	BYTE2 biPlanes;
	BYTE2 biBitCount;
	BYTE4 biCompression;
	BYTE4 biSizeImage;
	BYTE4 biXPelsPerMeter;
	BYTE4 biYPelsPerMeter;
	BYTE4 biClrUsed;
	BYTE4 biClrImportant;
} BITMAPINFOHEADER;


class BMPImage {
private:
	BITMAPFILEHEADER file_h;
	BITMAPINFOHEADER info_h;
	double **r, **g, **b;
public:
	BMPImage() {};
	BMPImage(string file_name) { readBMP(file_name); };
	int readBMP(string file_name);
	void saveBMP(string file_name);
	void setPixel(int x, int y, char r, char g, char b);
	BITMAPFILEHEADER& getFileH() { return file_h; };
	BITMAPINFOHEADER& getInfoH() { return info_h; };
	double** getR() { return r; }
	double** getG() { return g; }
	double** getB() { return b; }
	friend ostream& operator<<(ostream&, BMPImage);
}; 

