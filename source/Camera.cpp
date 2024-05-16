#include "Camera.h"
#include "Game.h"

Camera::Camera() : GameObject("Camera"), view(), zoomSensitivity(0.5f), minZoom(0.7f), maxZoom(5){
	float center = (maxZoom - minZoom) / 2.f + minZoom;
	view.setSize(Game::getResolution() * center);
}

void Camera::FixedUpdate(){
}

void Camera::Update() {
	sf::Vector2f viewScale = Math::divideVectors(view.getSize(), Game::getResolution());
	float zoom = -Input::Instance()->deltaScroll * zoomSensitivity / 2 + 1;
	transform->scale = Math::clamp(viewScale * zoom, sf::Vector2f(1, 1) * minZoom, sf::Vector2f(1, 1) * maxZoom);
	view.setSize(Math::multiplyVectors(transform->scale, Game::getResolution()));
	//view.zoom(-Input::Instance()->deltaScroll / 2 + 1);
	view.setCenter(transform->position);
	view.setRotation(transform->rotation);
}

void Camera::Draw(sf::RenderWindow* window) {
	window->setView(view);
}

Camera* Camera::getMainCamera() {
	std::vector<GameObject*> cams = Game::getCurrentScene()->getManager()->GetGameObjectByName("Camera");
	if (cams.size() > 0)
		return (Camera*)cams[0];
	return nullptr;
}