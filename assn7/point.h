#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<class T>
class Point{
public:
        T x;
        T y;
        Point() { x = 0; y = 0; }
        Point(T x, T y){this->x=x; this->y=y;}
        ~Point() {}
        Point operator+(Point<T> p);
        Point operator-(Point<T> p);
        bool operator==(Point<T> p);

};

template<class T>
Point<T> Point<T>::operator+(Point<T> p){
  T a = this->x + p.x;
  T b = this->y + p.y;
  return Point(a,b);
}

template<class T>
Point<T> Point<T>::operator-(Point<T> p){
  T a = this->x - p.x;
  T b = this->y - p.y;
  return Point(a,b);
}

template<class T>
inline bool Point<T>::operator==(Point<T> p){
        if (this->x == p.x && this->y == p.y)
                return true;

        return false;
}



#endif // POINT_H
