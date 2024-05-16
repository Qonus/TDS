#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "CollisionPoints.h"

// Colliders
#include "CircleCollider.h"
#include "RectangleCollider.h"

// Ray collisions
struct Ray {
	sf::Vector2f origin;
	sf::Vector2f direction;

	Ray(sf::Vector2f _origin, sf::Vector2f _direction) : origin(_origin), direction(_direction) {

	}
};

struct RaycastHit {
	std::vector<sf::Vector2f> points;
	sf::Vector2f normal;
	bool hasHit;
	Collider* collider;

	RaycastHit() : hasHit(false) {}
};

RaycastHit DetectRayCollision(Ray ray, Collider* collider);
RaycastHit RayCircle(Ray ray, CircleCollider* circle);
RaycastHit RayRay(Ray ray1, Ray ray2);
RaycastHit RayRectangle(Ray ray, RectangleCollider* rectangle);

CollisionPoints CircleCircle(Collider* a, Collider* b);
CollisionPoints RectangleCircle(Collider* a, Collider* b);
CollisionPoints RectangleRectangle(Collider* a, Collider* b);

using Collision_Detection_func = CollisionPoints(*)(Collider*, Collider*);

struct Collision_Detection_funcs
{
	Collision_Detection_func container[2][2] = {
		{RectangleRectangle, RectangleCircle},
		{nullptr           , CircleCircle}
	};
};

CollisionPoints DetectCollision(Collider* a, Collider* b);

#endif //COLLISION_DETECTION_H