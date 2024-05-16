#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.h"

enum ColliderType {
	Rectangle,
	Circle,
};

class Collider : public Component
{
public:
	Collider(GameObject* object, ColliderType _type, Transform _offset = Transform());
	virtual ~Collider();

	// Getters
	GameObject* getObject();
	Transform getTransform();
	ColliderType getType();

protected:
	GameObject* object;
	Transform* transform;
	Transform offset;

	ColliderType type;
};

#endif //COLLIDER_H