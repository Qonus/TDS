#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "GameObject.h"
#include "Enemy.h"

struct EnemyOptions {
	float speed;
	float attackRange;
	float maxHealth;
	Weapon weapon;

	EnemyOptions(Weapon _weapon, float _speed = 5, float _attackRange = 1000, float _maxHealth = 100)
		: weapon(_weapon), attackRange(_attackRange), speed(_speed), maxHealth(_maxHealth) {

	}
};

class EnemySpawner : public GameObject {
public:

	EnemySpawner(GameObject* _player, float _spawnRate = 3);

	void FixedUpdate();
	void Update();

	// Setters
	void SpawnEnemy(EnemyOptions enemy);

private:
	GameObject* player;

	sf::Clock spawnClock;
	float spawnRate;

	std::vector<EnemyOptions> enemies;
};

#endif //ENEMY_SPAWNER_H