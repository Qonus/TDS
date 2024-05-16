#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

#define RANDI(Min,Max)  (rand()%((Max)-(Min)+1)+(Min))
#define RANDF(Min,Max)  ((static_cast<float>(std::rand()) / RAND_MAX) * (Max - Min) + Min)
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

class Math
{
public:
	static sf::Vector2f multiplyVectors(sf::Vector2f a, sf::Vector2f b);
	static sf::Vector2f divideVectors(sf::Vector2f a, sf::Vector2f b);
	static float magnitude(sf::Vector2f v);
	static sf::Vector2f normalize(sf::Vector2f v);

	// Rotations
	static float deg2rad();
	static float rad2deg();
	static float DirectionToDegrees(sf::Vector2f dir);
	static float DirectionToRadians(sf::Vector2f dir);
	static sf::Vector2f RotateVector(sf::Vector2f vector, float degrees);

	static bool between(float var, float a, float b);
	static bool between(sf::Vector2f var, sf::Vector2f a, sf::Vector2f b);
	static float clamp(float var, float min, float max);
	static sf::Vector2f clamp(sf::Vector2f var, sf::Vector2f min, sf::Vector2f max);

	static float lerp(float a, float b, float t);
	static sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t);
	static sf::Vector2f reverseY(sf::Vector2f v);
};