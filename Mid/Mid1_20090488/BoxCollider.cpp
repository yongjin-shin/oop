#include "BoxCollider.h"

BoxCollider::BoxCollider(struct Vector2D p1, struct Vector2D p2, struct
	Vector2D p3) {
	double _x[3] = { p1.x, p2.x, p3.x };
	double _y[3] = { p1.y, p2.y, p3.y };
	double tmp=0;

	//with the bubble sort, find the smallest value and the biggest value of both x and y
	for (int i = 0; i < 3-1; i++) {
		for (int j = 0; j < 3 - i - 1; j++) {
			if (_x[j] <= _x[j + 1]) {
				tmp = _x[j];
				_x[j] = _x[j + 1];
				_x[j + 1] = tmp;
			}
		}
	}

	for (int i = 0; i < 3 - 1; i++) {
		for (int j = 0; j < 3 - i - 1; j++) {
			if (_y[j] <= _y[j + 1]) {
				tmp = _y[j];
				_y[j] = _y[j + 1];
				_y[j + 1] = tmp;
			}
		}
	}

	Vector2D center;
	center.x = (_x[2] + _x[0]) / 2;
	center.y = (_y[2] + _y[0]) / 2;
	this->setPosition(center);
	 
	this->extent.x = center.x - p1.x;
	this->extent.y = center.y - p1.y;

}

struct Vector2D BoxCollider::getExtent() {
	return this->extent;
}
/*
void BoxCollider::printResult(BoxCollider b) {

}

void BoxCollider::printResult(CircleCollider c) {

}
*/
bool BoxCollider::intersect(BoxCollider b) {
	Vector2D b1_ext = b.getExtent();
	Vector2D b1_cent = b.getPosition();
	Vector2D dis;
	dis.x = b1_cent.x - this->getPosition().x; 
	dis.y = b1_cent.y - this->getPosition().y;
	double dis_len = sqrt(dis.x*dis.x + dis.y*dis.y);
	double b1_len = sqrt(b1_ext.x*b1_ext.x + b1_ext.y*b1_ext.y);
	double this_len = sqrt(this->getExtent().x*this->getExtent().x + this->getExtent().y*this->getExtent().y);

	
	if (dis.x > this->getExtent().x + b1_ext.x)
		return true;
	else if (dis.y > this->getExtent().y + b1_ext.y)
		return true;
	else if (dis_len > )

	return false;
}

/*bool BoxCollider::intersect(CircleCollider c) {

}*/

bool BoxCollider::contain(BoxCollider b) {

	return false;
}

/*bool BoxCollider::contain(CircleCollider c) {

}*/