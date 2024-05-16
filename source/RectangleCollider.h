#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include "Collider.h"

class RectangleCollider : public Collider {
public:
	RectangleCollider(GameObject* gameObject, sf::Vector2f _size = sf::Vector2f(), Transform offset = Transform());

	// Getters
	sf::Vector2f getSize();
private:
	sf::Vector2f size;
};

#endif //RECTANGLE_COLLIDER_H