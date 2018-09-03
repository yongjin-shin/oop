#pragma once
#include "BMPImage.h"
#include <utility>
#include <vector>
#include <math.h>

#define KKK 0.04

typedef pair<int, int> point;

class Harris {
private:
	string file_name;
	BMPImage target;
	vector<point> corner;
	int width;
	int height;
	double** gau_xx; double** gau_yy; double** gau_xy;
	double** Ixx; double** Iyy; double** Ixy;
	double** Ix; double** Iy;

public:
	Harris(string file_name);
	~Harris() {}
	BMPImage get_image() { return target; }
	double** setPadding(double** given);
	double** get3x3(double** a, int h, int w);
	double conv(double** a, const double b[][3]);
	void single_I();
	void double_I();
	void gaussian();
	void find_corner();
	void print_corner();


};


//void SetPadding();
//double** r_pad; double** g_pad; double** b_pad;