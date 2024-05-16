#include "Scene.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"

#include "Camera.h"

Scene::Scene() : objectManager(), physicsManager() {

}

Scene::~Scene() {
	delete objectManager;
	delete physicsManager;
}

void Scene::Init(std::string _name) {
	name = _name;
	physicsManager = new PhysicsManager();
	objectManager = new GameObjectManager(this);

	getManager()->AddGameObject(new Camera());
}

void Scene::HandleInput(sf::Event* event) {
	getManager()->HandleInput(event);
}

void Scene::FixedUpdate() {
	getManager()->FixedUpdateAll();
	getPhysics()->Update();
}

void Scene::Update() {
	getManager()->UpdateAll();
}

void Scene::Draw(sf::RenderWindow* window) {
	getManager()->DrawAll(window);
}

void Scene::Restart() {
	getManager()->RemoveAll();
	Init(getName());
}

// Setters

// Getters
std::string Scene::getName() {
	return name;
}

GameObjectManager* Scene::getManager() {
	return objectManager;
}

PhysicsManager* Scene::getPhysics() {
	return physicsManager;
}

sf::Color Scene::getBackgroundColor() {
	return sf::Color(80, 150, 100);
}