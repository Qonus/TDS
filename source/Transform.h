#pragma once

#include <SFML/Graphics.hpp>

class Transform
{
public:
	Transform(
		sf::Vector2f _position = sf::Vector2f(),
		float _rotation = 0.f,
		sf::Vector2f _scale = sf::Vector2f(1, 1)
	) :
	position(_position), scale(_scale), rotation(_rotation) {
	}

	sf::Vector2f position;
	sf::Vector2f scale;
	float rotation;
};

