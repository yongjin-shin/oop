#ifndef __BOX_COLLIDER_H__
#define __BOX_COLLIDER_H__
#include "CircleCollider.h"

class BoxCollider : public Collider
{
private:
	struct Vector2D extent;
public:
	BoxCollider(struct Vector2D p1, struct Vector2D p2, struct
		Vector2D p3);
	struct Vector2D getExtent();
//	void printResult(BoxCollider b);
//	void printResult(CircleCollider c);
	bool intersect(BoxCollider b);
//	bool intersect(CircleCollider c);
	bool contain(BoxCollider b);
//	bool contain(CircleCollider c);
};

#endif