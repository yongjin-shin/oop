#ifndef _LINK_H_
#define _LINK_H_

#include "Matrix3x3.h"

class Link {
private:
  double length;
  double theta;
  Link* child;

public:
  Link(double l, double theta, Link* child);
  Vector2 getEndPoint();
};

#endif
