#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameObject.h"
#include "Damagable.h"
#include "Weapon.h"

// Components
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "TextRenderer.h"

enum PlayerState {
	Moving,
	Dodging,
};

class Player : public GameObject, public Damagable
{
public:
	Player(TextRenderer* _hpText);
	// Inherited
	void HandleInput(sf::Event* event);
	void FixedUpdate();
	void Update();
	void Draw(sf::RenderWindow* window);
	void OnCollision(CollisionPoints points, GameObject* other);

	void Damage(float damage, sf::Vector2f impulse = sf::Vector2f());
	void OnDeath();

	void HandleMovement(sf::Vector2f dir2Mouse);
	void HandleRotation(sf::Vector2f dir2Mouse);

	// Getters
	Weapon* getEquippedWeapon();
private:
	Rigidbody* rigidbody;
	TextRenderer* hpText;

	std::vector<Weapon> weapons;
	int equippedWeapon;

	PlayerState state;
	float dodgeDuration;

	float acceleration;


	sf::Vector2f dir2Mouse;
	sf::Vector2f direction;
	sf::Vector2f lastDirection;
	sf::Clock dodgeClock;
};

#endif