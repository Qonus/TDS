#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* gameObject, float _radius, Transform offset)
	: Collider(gameObject, Circle, offset), radius(_radius)
{

}