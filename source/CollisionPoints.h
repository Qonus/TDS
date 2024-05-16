#ifndef COLLISION_POINTS_H
#define COLLISION_POINTS_H

#include <SFML/Graphics.hpp>
#include "Math.h"

struct CollisionPoints {
	sf::Vector2f A;
	sf::Vector2f B;
	sf::Vector2f normal;
	float depth;
	bool hasCollision;

	CollisionPoints(
		sf::Vector2f a = sf::Vector2f(), 
		sf::Vector2f b = sf::Vector2f(),
		bool _hasCollision = false
	) : 
		hasCollision(_hasCollision), A(a), B(b)
	{
		Fill();
	}

	void Fill() {
		sf::Vector2f dir = A - B;
		normal = Math::normalize(dir);
		depth = (hasCollision ? 1 : -1) * Math::magnitude(dir);
	}

	CollisionPoints reverse() {
		return CollisionPoints(B, A, hasCollision);
	}
};

#endif //COLLISION_POINTS_H