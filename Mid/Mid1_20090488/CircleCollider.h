#ifndef __CIRCLE_COLLIDER_H__
#define __CIRCLE_COLLIDER_H__
#include "Collidar.h"

class CircleCollider : public Collider
{
private:
	double radius;
public:
	CircleCollider(struct Vector2D p1, struct Vector2D p2,
	struct Vector2D p3);
	double getRadius();
	void printResult(CircleCollider c);
	bool intersect(CircleCollider c);
	bool contain(CircleCollider c);
};

#endif
