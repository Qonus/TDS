#include "GameObject.h"
#include "Rigidbody.h"
#include "Collision.h"

GameObject::GameObject(std::string _name, Transform* _transform) : name(_name), transform(_transform), copyIndex(), objectManager() {
	if (name == "") std::cerr << "NULL NAME WARNING NULL NAME!!!\n";
}

GameObject::~GameObject() {
	delete transform;
	transform = nullptr;
	for (Component* component : components) {
		delete component;
		component = nullptr;
	}
}

void GameObject::HandleInput(sf::Event* event) {
	int i = 0;
	while (i < components.size()) {
		components[i]->HandleInput(event);
		i++;
	}
}

void GameObject::FixedUpdate() {
	int i = 0;
	while (i < components.size()) {
		components[i]->FixedUpdate();
		i++;
	}
}

void GameObject::Update() {
	int i = 0;
	while (i < components.size()) {
		components[i]->Update();
		i++;
	}
}

void GameObject::Draw(sf::RenderWindow* window) {
	// instead of calling draw for every component we can check if Game object Has renderer componenwt, call Draw if true
	int i = 0;
	while (i < components.size()) {
		components[i]->Draw(window);
		i++;
	}
}

void GameObject::DrawUI(sf::RenderWindow* window) {
	int i = 0;
	while (i < components.size()) {
		components[i]->DrawUI(window);
		i++;
	}
}

void GameObject::OnCollision(CollisionPoints points, GameObject* other) {
	GetComponent<Rigidbody>()->OnCollision(points, other);
}

// Setters

// Getters

GameObjectManager* GameObject::getManager() {
	return objectManager;
}

PhysicsManager* GameObject::getPhysics() {
	return getManager()->getScene()->getPhysics();
}

std::string GameObject::getName() { return name; }

int GameObject::getCopyIndex() {
	return copyIndex;
}

Transform* GameObject::getTransform() { return transform; }