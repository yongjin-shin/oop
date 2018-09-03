#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include <math.h>
#define PI 3.14159265
#include "Vector2.h"

class Matrix3x3 {
private:
  double element[3][3];

public:
Matrix3x3();
Matrix3x3(double element[][3]);
Matrix3x3 operator+(const Matrix3x3&);
Matrix3x3 operator-(const Matrix3x3&);
Matrix3x3 operator*(const Matrix3x3&);
Vector2 operator*(const Vector2&);
Matrix3x3 operator*(const double);
Matrix3x3& operator=(const Matrix3x3&);
Matrix3x3 inverse();
std::string toString();
friend Matrix3x3 operator*(double, const Matrix3x3&);
static Matrix3x3 identity();
static Matrix3x3 translate(double x, double y);
static Matrix3x3 rotate(double theta);
static Matrix3x3 scale(double sx, double sy);
};


#endif
