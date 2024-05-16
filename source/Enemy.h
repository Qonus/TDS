#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Damagable.h"
#include "Weapon.h"

// Components
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "CircleCollider.h"

class Enemy : public GameObject, public Damagable {
public:
	Enemy(GameObject* _player, Weapon _weapon, float _speed = 5, float _attackRange = 1000, float maxHealth = 100);

	// Inherited
	void HandleInput(sf::Event* event);
	void FixedUpdate();
	void Update();
	void Draw(sf::RenderWindow* window);
	void OnCollision(CollisionPoints points, GameObject* other);

	void Damage(float damage, sf::Vector2f impulse = sf::Vector2f());
	void OnDeath();

private:
	Rigidbody* rigidbody;
	GameObject* player;

	Weapon weapon;
	float speed;
	float attackRange;
};

#endif //ENEMY_H