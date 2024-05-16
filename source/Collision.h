#ifndef COLLISION_H
#define COLLISION_H

#include "Body.h"
#include "CollisionPoints.h"

struct Collision {
	Body* A;
	Body* B;
	CollisionPoints points;

	Collision(Body* a, Body* b, CollisionPoints _points) : A(a), B(b), points(_points) {

	}
};

#endif //COLLISION_H