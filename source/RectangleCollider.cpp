#include "RectangleCollider.h"

RectangleCollider::RectangleCollider(GameObject* gameObject, sf::Vector2f _size, Transform offset)
	: Collider(gameObject, Rectangle, offset), size(_size)
{
	
}

// Getters
sf::Vector2f RectangleCollider::getSize() {
	return Math::multiplyVectors(getTransform().scale, size);
}