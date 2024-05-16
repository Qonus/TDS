#ifndef DAMAGABLE_H
#define DAMAGABLE_H

#include "GameObject.h"

enum EntityState {
	Alive,
	Invincible,
	Dead,
};

class Damagable {
public:
	Damagable(float _maxHealth);
	~Damagable();

	virtual void Damage(float damage, sf::Vector2f impulse = sf::Vector2f());
	virtual void OnDeath();

	// Getters
	EntityState getState();
	float getMaxHealth();

protected:
	EntityState entityState;
	float health;
	float maxHealth;
};

#endif //DAMAGABLE_H