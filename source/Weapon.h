#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Bullet.h"

#include "Rigidbody.h"

class Weapon
{
public:
	sf::Clock fireRateClock;
	float fireRate;
	float range;
	int bulletsPerShot;

	float recoil;

	// Bullet
	BulletOptions bullet;

	Weapon();
	Weapon(BulletOptions _bullet, float _fireRate = 0, float _recoil = 0, float _range = 0, int _bulletsPerShot = 1);

	virtual std::vector<Bullet*> Shoot(GameObject* object, sf::Vector2f direction, Transform offset = Transform());

	// Getters
	bool canShoot();

protected:
};

#endif //WEAPON_H