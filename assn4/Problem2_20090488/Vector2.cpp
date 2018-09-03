#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& vec){
  Vector2 tmp;
  tmp.x = this->x+vec.x;
  tmp.y = this->y+vec.y;

  return tmp;
}

Vector2 Vector2::operator-(const Vector2& vec){
  Vector2 tmp;
  tmp.x = this->x-vec.x;
  tmp.y = this->y-vec.y;
  return tmp;
}

Vector2 Vector2::operator*(double num){
  Vector2 tmp;
  tmp.x = num*this->x;
  tmp.y = num*this->y;
  return tmp;
}

Vector2 Vector2::operator=(const Vector2& vec){
  this->x = vec.x;
  this->y = vec.y;
  return *this;
}

std::string Vector2::toString(){
  std::string tmp="(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
  return tmp;
}

Vector2 operator*(double num, const Vector2& vec){
  Vector2 tmp(num*vec.x, num*vec.y);
  return tmp;
}
