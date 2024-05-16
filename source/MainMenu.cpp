#include "MainMenu.h"
#include "Game.h"

// Objects
#include "UI_Text.h"

void MainMenu::Init(std::string _name) {
	Scene::Init(_name);

	getManager()->AddGameObject(new UI_Text("PRESS [SPACE] TO START GAME"));
}

void MainMenu::HandleInput(sf::Event* event) {
	Scene::HandleInput(event);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Game::LoadNextScene();
	}
}

void MainMenu::FixedUpdate() {
	Scene::FixedUpdate();
}

void MainMenu::Update() {
	Scene::Update();
}

void MainMenu::Draw(sf::RenderWindow* window) {
	Scene::Draw(window);
}

// Getters
sf::Color MainMenu::getBackgroundColor() {
	return sf::Color(80, 100, 150);
}