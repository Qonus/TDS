#include "Math.h"

sf::Vector2f Math::multiplyVectors(sf::Vector2f a, sf::Vector2f b) {
	return sf::Vector2f(
		a.x * b.x,
		a.y * b.y
	);
}

sf::Vector2f Math::divideVectors(sf::Vector2f a, sf::Vector2f b) {
	return sf::Vector2f(
		a.x / b.x,
		a.y / b.y
	);
}

float Math::magnitude(sf::Vector2f v) {
	return sqrtf(powf(v.x, 2) + powf(v.y, 2));
}

sf::Vector2f Math::normalize(sf::Vector2f v) {
	float dist = magnitude(v);
	if (dist != 0)
		return (v / dist);
	return v;
}

// Rotations
float Math::deg2rad() {
	return PI / 180.f;
}

float Math::rad2deg() {
	return 180.f / PI;
}

float Math::DirectionToDegrees(sf::Vector2f dir) {
	float angle = atan2(dir.y, dir.x);
	float degrees = angle * rad2deg();
	return degrees;
}

float Math::DirectionToRadians(sf::Vector2f dir) {
	float angle = atan2(dir.y, dir.x);
	return angle;
}

sf::Vector2f Math::RotateVector(sf::Vector2f vector, float degrees) {
	/*float angle = degrees * deg2rad();
	float cs = cos(angle);
	float sn = sin(angle);
	sf::Vector2f a = sf::Vector2f(cs, sn);
	sf::Vector2f b = sf::Vector2f(-sn, cs);
	sf::Vector2f result = a * vector.x + b * vector.y;
	return result;*/

	float angle = degrees * deg2rad();
	double length = magnitude(vector);
	double newAngle = atan2(vector.y, vector.x) + angle;
	sf::Vector2f result = sf::Vector2f(length * cos(newAngle), length * sin(newAngle));
	return result;
}

bool Math::between(float var, float a, float b) {
	return (var <= a && var >= b) || (var <= b && var >= a);
}

bool Math::between(sf::Vector2f var, sf::Vector2f a, sf::Vector2f b) {
	return (between(var.x, a.x, b.x) && between(var.y, a.y, b.y));
}

float Math::clamp(float var, float min, float max) {
	if (var < min) var = min;
	else if (var > max) var = max;
	return var;
}

sf::Vector2f Math::clamp(sf::Vector2f var, sf::Vector2f min, sf::Vector2f max) {
	return sf::Vector2f(
		clamp(var.x, min.x, max.x),
		clamp(var.y, min.y, max.y)
	);
}

float Math::lerp(float a, float b, float t) {
	if (t == 0) return 0;
	return (b - a) / t + a;
}

sf::Vector2f Math::lerp(sf::Vector2f a, sf::Vector2f b, float t) {
	return sf::Vector2f(
		lerp(a.x, b.x, t),
		lerp(a.y, b.y, t)
	);
}

sf::Vector2f Math::reverseY(sf::Vector2f v) {
	return sf::Vector2f(v.x, -v.y);
}