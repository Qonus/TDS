#include "Collider.h"

Collider::Collider(GameObject* _object, ColliderType _type, Transform _offset) : object(_object), type(_type), offset(_offset) {
	transform = object->getTransform();
}

Collider::~Collider() {

}

// Getters
GameObject* Collider::getObject() {
	return object;
}

Transform Collider::getTransform() {
	Transform result;
	result.position = transform->position + offset.position;
	result.rotation = transform->rotation + offset.rotation;
	result.scale = Math::multiplyVectors(transform->scale, offset.scale);

	return result;
}
ColliderType Collider::getType() {
	return type;
}