
#include "Collidar.h"

void Collider::setPosition(struct Vector2D pos) {
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

Collider::Collider() {
	pos.x = 0;
	pos.y = 0;
}

struct Vector2D Collider::getPosition() {
	return pos;
}

