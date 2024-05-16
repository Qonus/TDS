#include "UI_Object.h"

UI_Object::UI_Object(std::string name) : GameObject(name) {
}

void UI_Object::HandleInput(sf::Event* event) {
	GameObject::HandleInput(event);
}
void UI_Object::FixedUpdate() {
	GameObject::FixedUpdate();
}
void UI_Object::Update() {
	GameObject::Update();
}
void UI_Object::DrawUI(sf::RenderWindow* window) {
	Renderer* renderer = GetComponent<Renderer>();
	if (renderer != nullptr) {
		renderer->UpdateUITransform(window);
	}
	GameObject::DrawUI(window);
}