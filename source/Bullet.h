#pragma once
#include "GameObject.h"

// Components
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "Damagable.h"

struct BulletOptions {
	float speed;
	float lifeTime;
	float damage;
	float impulse;
	std::string textureFile;
	sf::Color color;

	BulletOptions() {}

	BulletOptions(std::string _textureFile, float _speed, float _damage, float _impulse = 0, float _lifeTime = -1, sf::Color _color = sf::Color::White)
		: textureFile(_textureFile), speed(_speed), damage(_damage), impulse(_impulse), lifeTime(_lifeTime), color(_color) {

	}
};

class Bullet : public GameObject
{
public:
	std::string shooterName;

	float damage;
	float impulse;
	float time;

	Bullet(sf::Vector2f direction, std::string _shooterName, std::string bulletTextureFile, float _time, float _damage = 0, float _impulse = 0);
	Bullet(sf::Vector2f direction, std::string _shooterName, BulletOptions options);

	// Inherited
	void Update();
	void OnCollision(CollisionPoints points, GameObject* other);

private:
	Rigidbody* rigidbody;

	sf::Clock clock;
};

