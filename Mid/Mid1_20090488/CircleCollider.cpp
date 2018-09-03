#include "CircleCollider.h"

CircleCollider::CircleCollider(struct Vector2D p1, struct Vector2D p2,
struct Vector2D p3) {
	struct Vector2D center;
	center.x = (p1.x + p2.x + p3.x) / 3;
	center.y = (p1.y + p2.y + p3.y) / 3;
	setPosition(center);

	double x_diff = p1.x - center.x;
	double y_diff = p1.y - center.y;

	this->radius = sqrt(x_diff*x_diff + y_diff*y_diff);
}

double CircleCollider::getRadius() {
	return this->radius;
}

void CircleCollider::printResult(CircleCollider c) {
	if (!this->intersect(c) && this->contain(c))
		std::cout << "Conatianing" << std::endl;
	else
		std::cout << "Intersecting" << std::endl;

}

bool CircleCollider::intersect(CircleCollider c) {
	Vector2D dis;
	dis.x = c.getPosition().x - this->getPosition().x;
	dis.y = c.getPosition().y - this->getPosition().y;
	double dis_length = sqrt(dis.x*dis.x + dis.y*dis.y);
	double sum_radis = c.getRadius() + this->getRadius();

	if (dis_length <= sum_radis)
		return false;
	else
		return true;
}

bool CircleCollider::contain(CircleCollider c) {
	Vector2D dis;
	dis.x = c.getPosition().x - this->getPosition().x;
	dis.y = c.getPosition().y - this->getPosition().y;
	double dis_length = sqrt(dis.x*dis.x + dis.y*dis.y);
	double sub_radis = c.getRadius() - this->getRadius();

	if (sub_radis < 0)
		sub_radis *= -1;

	if (dis_length <= sub_radis)
		return true;
	else
		return false;
}