#include "GameScene.h"
#include "Game.h"

// Objects
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Wall.h"
#include "UI_Text.h"
#include "EnemySpawner.h"

void GameScene::Init(std::string _name) {
	Scene::Init(_name);

	UI_Text* hpText = new UI_Text("", 50, sf::Color(250, 50, 100));
	getManager()->AddGameObject(hpText, Transform(sf::Vector2f(0, 800)));

	Player* player = new Player(hpText->GetComponent<TextRenderer>());
	getManager()->AddGameObject(player);
	
	getManager()->AddGameObject(new EnemySpawner(player, 4));
	//BulletOptions bullet = BulletOptions("weapon_axe.png", 700, 10, 500, 10, sf::Color(230, 150, 150));
	//getManager()->AddGameObject(new Enemy(player, Weapon(bullet, 0.2f, 10, 30), 50, 400, 20), Transform(sf::Vector2f(200, 100)));
	/*getManager()->AddGameObject(new Wall(), Transform(sf::Vector2f(-700, 0), 0, sf::Vector2f(1, 10)));
	getManager()->AddGameObject(new Wall(), Transform(sf::Vector2f(0, 700), 0, sf::Vector2f(10, 1)));
	getManager()->AddGameObject(new Wall(), Transform(sf::Vector2f(0, -700), 0, sf::Vector2f(10, 1)));*/

	getManager()->AddGameObject(new Wall(), Transform(sf::Vector2f(0, -300)));
	getManager()->AddGameObject(new Wall(), Transform(sf::Vector2f(600, 0)));
	getManager()->AddGameObject(new Wall(), Transform(sf::Vector2f(0, 300)));
}

void GameScene::HandleInput(sf::Event* event) {
	Scene::HandleInput(event);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		Game::LoadScene(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		Game::RestartScene(Game::getCurrentSceneIndex());
	}
}

void GameScene::FixedUpdate() {
	Scene::FixedUpdate();
}

void GameScene::Update() {
	Scene::Update();
}

void GameScene::Draw(sf::RenderWindow* window) {
	Scene::Draw(window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
		window->setFramerateLimit(10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
		window->setFramerateLimit(120);
	}
}