#ifndef __COLLIDAR_H__
#define __COLLIDAR_H__

#include <iostream>
#include <string>
#include <cmath>

struct Vector2D
{
	double x, y;
};

class Collider
{
private:
	struct Vector2D pos;
protected:
	void setPosition(struct Vector2D pos);
public:
	Collider();
	struct Vector2D getPosition();
};

#endif