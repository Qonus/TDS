#include "Bullet.h"

Bullet::Bullet(sf::Vector2f direction, std::string _shooterName, std::string bulletTextureFile, float _time, float _damage, float _impulse)
	: GameObject("Bullet"), shooterName(_shooterName), time(_time), damage(_damage), impulse(_impulse) {
	AddComponent<SpriteRenderer>(new SpriteRenderer(this, bulletTextureFile));

	rigidbody = new Rigidbody(this);
	AddComponent<Rigidbody>(rigidbody);
	rigidbody->AddForce(direction);

	AddComponent<CircleCollider>(new CircleCollider(this, 10.f));
	//AddComponent<RectangleCollider>(new RectangleCollider(this, sf::Vector2f(10.f, 10)));
}

Bullet::Bullet(sf::Vector2f direction, std::string shooterName, BulletOptions options)
	: Bullet(Math::normalize(direction) * options.speed, shooterName, options.textureFile, options.lifeTime, options.damage, options.impulse) {
}

void Bullet::Update() {
	GameObject::Update();
	if (time > 0 && clock.getElapsedTime().asSeconds() * Time::getTimeScale() >= time) {
		getManager()->RemoveGameObject(this);
	}
}

void Bullet::OnCollision(CollisionPoints points, GameObject* other) {
	if (other->getName() == shooterName || (other->getName() == "Bullet" && (dynamic_cast<Bullet*>(other)->shooterName == shooterName))) return;

	Damagable* damagable = dynamic_cast<Damagable*>(other);
	if (damagable) {
		damagable->Damage(damage, Math::normalize(rigidbody->velocity) * impulse);
		if (damagable->getState() == Invincible) return;
	}
	else {
		Rigidbody* otherRb = other->GetComponent<Rigidbody>();
		if (otherRb == nullptr) return;
		otherRb->AddForce(rigidbody->velocity);
	}

	if (other->getName() == "Bullet" && (dynamic_cast<Bullet*>(other)->shooterName != shooterName)) {
		getManager()->RemoveGameObject(other);
	}

	getManager()->RemoveGameObject(this);
}