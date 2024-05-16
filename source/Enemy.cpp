#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"

Enemy::Enemy(GameObject* _player, Weapon _weapon, float _speed, float _attackRange, float maxHealth)
	: GameObject("Enemy") , Damagable(maxHealth), player(_player), attackRange(_attackRange), weapon(_weapon), speed(_speed) {
	//BulletOptions bullet = BulletOptions("weapon_axe.png", 700, 10, 500, 10, sf::Color(230, 150, 150));
	//weapon = Weapon(bullet, 0.2f, 10, 30);

	AddComponent<SpriteRenderer>(new SpriteRenderer(this, "red_character.png"));

	rigidbody = new Rigidbody(this, Dynamic, 1, 1.2f);
	AddComponent<Rigidbody>(rigidbody);

	AddComponent<CircleCollider>(new CircleCollider(this, 40.f));
}

void Enemy::HandleInput(sf::Event* event) {
	GameObject::HandleInput(event);
}

void Enemy::FixedUpdate() {
	GameObject::FixedUpdate();
	if (player->getName() == "") return;
	sf::Vector2f direction = player->getTransform()->position - transform->position;
	if (Math::magnitude(direction) > attackRange) {
		// GET CLOSER
		rigidbody->AddForce(speed * Math::normalize(direction) * Time::getFixedTime() * 1000.f);
	}
	else if (weapon.canShoot()) {
		// SHOOT
		std::vector<Bullet*> bullets = weapon.Shoot(this, direction, Transform(sf::Vector2f(), 90, sf::Vector2f(.5f, .5f)));
		for (Bullet* newBullet : bullets)
		{
			newBullet->GetComponent<Rigidbody>()->AddTorque(-1000);
		}
	}
}

void Enemy::Update() {
	GameObject::Update();
}

void Enemy::Draw(sf::RenderWindow* window) {
	GameObject::Draw(window);
}

void Enemy::OnCollision(CollisionPoints points, GameObject* other) {
	if (other->getName() == "Bullet") return;
	GameObject::OnCollision(points, other);
}

void Enemy::Damage(float damage, sf::Vector2f impulse) {
	Damagable::Damage(damage, impulse);
	rigidbody->AddForce(impulse);
}

void Enemy::OnDeath() {
	Damagable::OnDeath();
	getManager()->RemoveGameObject(this);
}