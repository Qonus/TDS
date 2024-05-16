#include "Damagable.h"

#include "Rigidbody.h"

Damagable::Damagable(float _maxHealth) : maxHealth(_maxHealth) , health(_maxHealth), entityState(Alive) {
	
}

Damagable::~Damagable() {

}

void Damagable::Damage(float damage, sf::Vector2f impulse) {
	if (entityState == Invincible) return;

	health -= damage;
	if (health <= 0) {
		entityState = Dead;
		OnDeath();
	}
}

void Damagable::OnDeath() {

}

// Getters
EntityState Damagable::getState() {
	return entityState;
}

float Damagable::getMaxHealth() {
	return maxHealth;
}