#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <iostream>
#include <string>

class Vector2 {
private:
      double x, y;
public:
Vector2(){x=0.0; y=0.0;}
Vector2(double x, double y){this->x=x; this->y=y;}
Vector2 operator+(const Vector2&);
Vector2 operator-(const Vector2&);
Vector2 operator*(double);
friend Vector2 operator*(double, const Vector2&);
Vector2 operator=(const Vector2&);
std::string toString();
double const get_x() const {return x;}
double const get_y() const {return y;}
};

#endif
