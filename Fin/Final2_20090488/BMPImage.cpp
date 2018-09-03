#include "BMPImage.h"

ostream& operator<<(ostream& os, BITMAPFILEHEADER& file_h) {
	os << "bfType: " << file_h.bfType << endl;
	os << "bfSize: " << file_h.bfSize << endl;
	os << "bfReserved1: " << file_h.bfReserved1 << endl;
	os << "bfReserved2: " << file_h.bfReserved2 << endl;
	os << "bfOffBits: " << file_h.bfOffBits << endl;
	return os;
}

ostream& operator<<(ostream& os, BITMAPINFOHEADER& info_h) {
	os << "biSize: " << info_h.biSize << endl;
	os << "biWidth: " << info_h.biWidth << endl;
	os << "biHeight: " << info_h.biHeight << endl;
	os << "biPlanes: " << info_h.biPlanes << endl;
	os << "biBitCount: " << info_h.biBitCount << endl;
	os << "biCompression: " << info_h.biCompression << endl;
	os << "biSizeImage: " << info_h.biSizeImage << endl;
	os << "biXPelsPerMeter: " << info_h.biXPelsPerMeter << endl;
	os << "biYPelsPerMeter: " << info_h.biYPelsPerMeter << endl;
	os << "biClrUsed: " << info_h.biClrUsed << endl;
	os << "biClrImportant: " << info_h.biClrImportant << endl;
	return os;
}

void BMPImage::saveBMP(string file_name) {
	ofstream outfile(file_name, ios::binary);

	// Write Bitmap File Header
	outfile.write((char*)&(this->file_h.bfType), 2);
	outfile.write((char*)&(this->file_h.bfSize), 4);
	outfile.write((char*)&(this->file_h.bfReserved1), 2);
	outfile.write((char*)&(this->file_h.bfReserved2), 2);
	outfile.write((char*)&(this->file_h.bfOffBits), 4);

	// Write Bitmap Information Header
	outfile.write((char*)&(this->info_h.biSize), 4);
	outfile.write((char*)&(this->info_h.biWidth), 4);
	outfile.write((char*)&(this->info_h.biHeight), 4);
	outfile.write((char*)&(this->info_h.biPlanes), 2);
	outfile.write((char*)&(this->info_h.biBitCount), 2);
	outfile.write((char*)&(this->info_h.biCompression), 4);
	outfile.write((char*)&(this->info_h.biSizeImage), 4);
	outfile.write((char*)&(this->info_h.biXPelsPerMeter), 4);
	outfile.write((char*)&(this->info_h.biYPelsPerMeter), 4);
	outfile.write((char*)&(this->info_h.biClrUsed), 4);
	outfile.write((char*)&(this->info_h.biClrImportant), 4);

	int pad = (24 * info_h.biWidth + 31) / 32 * 4 - info_h.biWidth * 3;

	// Write pixel information
	for (int i = 0; i < info_h.biHeight; i++) {
		for (int j = 0; j < info_h.biWidth; j++) {
			unsigned char temp_r = r[info_h.biHeight - i - 1][j] * 255;
			unsigned char temp_g = g[info_h.biHeight - i - 1][j] * 255;
			unsigned char temp_b = b[info_h.biHeight - i - 1][j] * 255;
			outfile.write((char*)&temp_b, 1);
			outfile.write((char*)&temp_g, 1);
			outfile.write((char*)&temp_r, 1);
		}
		char temp = 0;
		for (int j = 0; j < pad; j++) {
			outfile.write(&temp, 1);
		}
	}
	outfile.close();
}

int BMPImage::readBMP(string file_name) {
	ifstream infile(file_name, ios::binary);
	if (!infile.is_open()) {
		cerr << "There are no file!!" << endl;
		return -1;
	}
	// Read BItmap File Header
	infile.read((char*)&(this->file_h.bfType), 2);
	infile.read((char*)&(this->file_h.bfSize), 4);
	infile.read((char*)&(this->file_h.bfReserved1), 2);
	infile.read((char*)&(this->file_h.bfReserved2), 2);
	infile.read((char*)&(this->file_h.bfOffBits), 4);

	// Read Bitmap Information Header
	infile.read((char*)&(this->info_h.biSize), 4);
	infile.read((char*)&(this->info_h.biWidth), 4);
	infile.read((char*)&(this->info_h.biHeight), 4);
	infile.read((char*)&(this->info_h.biPlanes), 2);
	infile.read((char*)&(this->info_h.biBitCount), 2);
	infile.read((char*)&(this->info_h.biCompression), 4);
	infile.read((char*)&(this->info_h.biSizeImage), 4);
	infile.read((char*)&(this->info_h.biXPelsPerMeter), 4);
	infile.read((char*)&(this->info_h.biYPelsPerMeter), 4);
	infile.read((char*)&(this->info_h.biClrUsed), 4);
	infile.read((char*)&(this->info_h.biClrImportant), 4);

	cout << file_h << endl;
	cout << info_h << endl;

	int pad = (24 * info_h.biWidth + 31) / 32 * 4 - info_h.biWidth * 3;

	// Read Pixel Information 
	r = new double*[info_h.biHeight];
	g = new double*[info_h.biHeight];
	b = new double*[info_h.biHeight];
	for (int i = 0; i < info_h.biHeight; i++) {
		r[info_h.biHeight - i - 1] = new double[info_h.biWidth];
		g[info_h.biHeight - i - 1] = new double[info_h.biWidth];
		b[info_h.biHeight - i - 1] = new double[info_h.biWidth];
		for (int j = 0; j < info_h.biWidth; j++) {
			unsigned char temp_r, temp_g, temp_b;
			infile.read((char*)&temp_b, 1);
			infile.read((char*)&temp_g, 1);
			infile.read((char*)&temp_r, 1);
			r[info_h.biHeight - i - 1][j] = temp_r / 255.0;
			g[info_h.biHeight - i - 1][j] = temp_g / 255.0;
			b[info_h.biHeight - i - 1][j] = temp_b / 255.0;
		}
		for (int j = 0; j < pad; j++) {
			char temp;
			infile.read(&temp, 1);
		}
	}

	infile.close();
	return 0;
}

ostream& operator<<(ostream& os, BMPImage img) {
	os << img.getFileH() << endl;
	os << img.getInfoH() << endl;
	os << "Red" << endl;
	for (int i = 0; i < img.getInfoH().biHeight; i++) {
		for (int j = 0; j < img.getInfoH().biWidth; j++) {
			os << (int)img.r[i][j] << " ";
		}
		os << endl;
	}
	os << "Green" << endl;
	for (int i = 0; i < img.getInfoH().biHeight; i++) {
		for (int j = 0; j < img.getInfoH().biWidth; j++) {
			os << (int)img.g[i][j] << " ";
		}
		os << endl;
	}
	os << "Blue" << endl;
	for (int i = 0; i < img.getInfoH().biHeight; i++) {
		for (int j = 0; j < img.getInfoH().biWidth; j++) {
			os << (int)img.b[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

void BMPImage::setPixel(int x, int y, char r, char g, char b) {
	this->r[y][x] = r / 255.0;
	this->g[y][x] = g / 255.0;
	this->b[y][x] = b / 255.0;
}