#include "EnemySpawner.h"
#include "Game.h"

EnemySpawner::EnemySpawner(GameObject* _player, float _spawnRate) : GameObject("EnemySpawner"), player(_player), spawnRate(_spawnRate) {
	BulletOptions bullet = BulletOptions("weapon_axe.png", 700, 10, 500, 10, sf::Color(230, 150, 150));
	bullet.speed = 1000;
	enemies.push_back(EnemyOptions(Weapon(bullet, 2, 600, 90, 5), 20, 300, 20));
	SpawnEnemy(enemies[0]);
}

void EnemySpawner::FixedUpdate() {
	GameObject::FixedUpdate();
}

void EnemySpawner::Update() {
	GameObject::Update();
	if (spawnClock.getElapsedTime().asSeconds() >= spawnRate) {
		SpawnEnemy(enemies[0]);
	}
}

void EnemySpawner::SpawnEnemy(EnemyOptions enemy) {
	Game::getScene("GameScene")->getManager()->AddGameObject(
		new Enemy(player, enemy.weapon, enemy.speed, enemy.attackRange, enemy.maxHealth),
		Transform(Math::RotateVector(sf::Vector2f(1000, 0), RANDF(0, 360)))
	);
	spawnClock.restart();
}