#include "Renderer.h"

Renderer::Renderer(GameObject* object) : isLoaded(false) {
	transform = object->getTransform();
}

// Inherited
void Renderer::Update() {
	if (!isLoaded) return;
	UpdateTransform();
}
void Renderer::Draw(sf::RenderWindow* window) {
	if (!isLoaded) return;
}

// Setters
void Renderer::UpdateTransform() {

}
void Renderer::UpdateUITransform(sf::RenderWindow* window) {

}