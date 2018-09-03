#include "Link.h"

//default constructor
Link::Link(double l, double theta, Link* child){
  this->length = l;
  this->theta = theta;
  this->child = child;
}

//if child is nullptr(case of the first node), just start at (0,0)
//otherwise start the child's end point
Vector2 Link::getEndPoint(){
  Vector2 result;
  Vector2 init;

  if(this->child == nullptr){
    result = Matrix3x3::rotate(theta)*(Matrix3x3::scale(length, length)*(Matrix3x3::translate(0,1)*init));
  }
  else{
    result = Matrix3x3::rotate(theta)*(Matrix3x3::scale(length, length)*(Matrix3x3::translate(0,1)*init))+child->getEndPoint();
  }

  return result;
}
