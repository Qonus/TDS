#include "Weapon.h"

Weapon::Weapon() {

}

Weapon::Weapon(BulletOptions _bullet, float _fireRate, float _recoil, float _range, int _bulletsPerShot)
	: bullet(_bullet), fireRate(_fireRate), recoil(_recoil), range(_range), bulletsPerShot(_bulletsPerShot) {

}

std::vector<Bullet*> Weapon::Shoot(GameObject* object, sf::Vector2f direction, Transform offset) {
	// SHOOT
	std::vector<Bullet*> bullets;

	sf::Vector2f bulletDir;
	for (int i = 0; i < bulletsPerShot; i++)
	{
		bulletDir = Math::RotateVector(direction, RANDF(-range / 2.f, range / 2.f));

		bullets.emplace_back(new Bullet(bulletDir, object->getName(), bullet));

		object->getManager()->AddGameObject(
			bullets[i],
			Transform(
				object->getTransform()->position + offset.position,
				Math::DirectionToDegrees(Math::reverseY(bulletDir)) + offset.rotation,
				offset.scale
			)
		);

		bullets[i]->GetComponent<SpriteRenderer>()->setColor(bullet.color);
	}

	// Apply Recoil
	Rigidbody* rb = object->GetComponent<Rigidbody>();
	if (rb != nullptr) {
		rb->AddForce(Math::normalize(direction) * recoil * -10.f);
	}

	fireRateClock.restart();

	return bullets;
}

// Getters
bool Weapon::canShoot() {
	return (fireRateClock.getElapsedTime().asSeconds() >= fireRate);
}