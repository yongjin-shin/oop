#include "Harris.h"

Harris::Harris(string file_name){
	target = BMPImage(file_name);
	this->file_name = file_name;
	width = target.getInfoH().biWidth;
	height = target.getInfoH().biHeight;
}

double** Harris::setPadding(double** given) {
	double** tmp;
	int new_width = width + 2;
	int new_height = height + 2;

	tmp = new double*[new_height];
	for (int h = 0; h < new_height; h++) {
		tmp[h] = new double[new_width];

		if (h == 0) {
			for (int w = 0; w < width; w++) {
				tmp[h][w + 1] = given[0][w];
			}
		}
		else if (h == new_height - 1) {
			for (int w = 0; w < width; w++) {
				tmp[h][w + 1] = given[height - 1][w];
			}
		}
		else 
			for (int w = 0; w < width; w++)
				tmp[h][w + 1] = given[h - 1][w];

			tmp[h][0] = tmp[h][1];
			tmp[h][new_height - 1] = tmp[h][new_height - 2];
	}
	return tmp;
}

//convolution calculator
//get the value of one piexel
double Harris::conv(double** a, const double b[][3]) {
	double tmp=0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp += a[i][j] * b[i][j];
		}
	}
	return tmp;
}

//get 3x3 matrix from the matrix enlarged by setPadding
//which have the center[h][w]
double** Harris::get3x3(double** a, int h, int w) {
	double** tmp;
	tmp = new double*[3];
	for (int i = 0; i < 3; i++)
		tmp[i] = new double[3];

	tmp[0][0] = a[h][w];
	tmp[0][1] = a[h][w + 1];
	tmp[0][2] = a[h][w + 2];
	tmp[1][0] = a[h+1][w];
	tmp[1][1] = a[h+1][w+1];
	tmp[1][2] = a[h+1][w+2];
	tmp[2][0] = a[h + 2][w];
	tmp[2][1] = a[h + 2][w+1];
	tmp[2][2] = a[h + 2][w+2];

	return tmp;
}

//find each values of Ix, Iy, Ixy
void Harris::single_I() {
	const double y_dir[3][3] = { { -1, 0, 1 },{ -2,0,2 },{ -1,0,1 } };
	const double x_dir[3][3] = { { 1, 2, 1 },{ 0,0,0 },{ -1,-2,-1 } };

	//get r,g,b pointers and setPadding to enlarge
	double** r = target.getR();
	double** r_pad = setPadding(r);
	double** g = target.getG();
	double** g_pad = setPadding(g);
	double** b = target.getB();
	double** b_pad = setPadding(b);

	//set up (r,g,b) x (x,y) pointers
	double** ix_r; ix_r = new double*[height];
	double** ix_g; ix_g = new double*[height];
	double** ix_b; ix_b = new double*[height];

	double** iy_r; iy_r = new double*[height];
	double** iy_g; iy_g = new double*[height];
	double** iy_b; iy_b = new double*[height];
	

	for (int h = 0; h < height; h++) {
		iy_r[h] = new double[width];
		iy_g[h] = new double[width];
		iy_b[h] = new double[width];

		ix_r[h] = new double[width];
		ix_g[h] = new double[width];
		ix_b[h] = new double[width];

		for (int w = 0; w < width; w++) {
			double** r_3x3 = get3x3(r_pad, h, w);
			double** g_3x3 = get3x3(g_pad, h, w);
			double** b_3x3 = get3x3(b_pad, h, w);

			//y direction derivational
			iy_r[h][w] = conv(r_3x3, y_dir);
			iy_g[h][w] = conv(g_3x3, y_dir);
			iy_b[h][w] = conv(b_3x3, y_dir);

			//x direction derivational
			ix_r[h][w] = conv(r_3x3, x_dir);
			ix_g[h][w] = conv(g_3x3, x_dir);
			ix_b[h][w] = conv(b_3x3, x_dir);
		}
	}

	Iy = new double*[height];
	Ix = new double*[height];
	for (int h = 0; h < height; h++) {
		Iy[h] = new double[width];
		Ix[h] = new double[width];

		for (int w = 0; w < width; w++) {
			//get Iy
			Iy[h][w] = sqrt(iy_r[h][w] * iy_r[h][w] + iy_g[h][w] * iy_g[h][w] + iy_b[h][w] * iy_b[h][w]);
			
			//get Ix
			Ix[h][w] = sqrt(ix_r[h][w] * ix_r[h][w] + ix_g[h][w] * ix_g[h][w] + ix_b[h][w] * ix_b[h][w]);
		}
	}
}

//with using single_I function
//find Ixx, Iyy, Ixy
void Harris::double_I() {
	this->single_I();

	Ixx = new double*[height];
	Iyy = new double*[height];
	Ixy = new double*[height];
	for (int h = 0; h < height; h++) {
		Ixx[h] = new double[width];
		Iyy[h] = new double[width];
		Ixy[h] = new double[width];
		
		for(int w = 0; w < width; w++) {
			Ixx[h][w] = Ix[h][w] * Ix[h][w];
			Iyy[h][w] = Iy[h][w] * Iy[h][w];
			Ixy[h][w] = Ix[h][w] * Iy[h][w];
		}
	}
}

//With using double_I
//find each matirxes after conducting gaussian filter
void Harris::gaussian() {
	this->double_I();

	const double g1 = (double)1 / (double)16;
	const double g2 = (double)2 / (double)16;
	const double g4 = (double)4 / (double)16;

	const double gau[3][3] = { {g1, g2, g1},{g2, g4, g2},{g1, g2, g1} };
	double** ixx_pad = setPadding(Ixx);
	double** iyy_pad = setPadding(Iyy);
	double** ixy_pad = setPadding(Ixy);

	gau_xx = new double*[height];
	gau_yy = new double*[height];
	gau_xy = new double*[height];

	for (int h = 0; h < height; h++) {
		gau_xx[h] = new double[width];
		gau_yy[h] = new double[width];
		gau_xy[h] = new double[width];

		for (int w = 0; w < width; w++) {
			double** xx_3x3 = get3x3(ixx_pad, h, w);
			double** yy_3x3 = get3x3(iyy_pad, h, w);
			double** xy_3x3 = get3x3(ixy_pad, h, w);

			gau_xx[h][w] = conv(xx_3x3, gau);
			gau_yy[h][w] = conv(yy_3x3, gau);
			gau_xy[h][w] = conv(xy_3x3, gau);
		}
	}
}

void Harris::find_corner() {
	this->gaussian();
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if ((gau_xx[h][w] * gau_yy[h][w] - gau_xy[h][w] * gau_xy[h][w])- KKK* (gau_xx[h][w] + gau_yy[h][w])*(gau_xx[h][w] + gau_yy[h][w])> 0.7) {
				point tmp(h, w);
				corner.push_back(tmp);
			}
		}
	}
}

void Harris::print_corner() {
	this->find_corner();
	for (int i = 0; i < corner.size(); i++)
		target.setPixel(corner[i].second, corner[i].first, '0', '0', '0');
	target.saveBMP(file_name+"_result.bmp");
}