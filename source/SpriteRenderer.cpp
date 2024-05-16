#include "SpriteRenderer.h"
#include "Game.h"

SpriteRenderer::SpriteRenderer(GameObject* object, std::string textureFilePath) : Renderer(object) {
    setTexture(textureFilePath);
}

void SpriteRenderer::Update() {
    Renderer::Update();
}

void SpriteRenderer::Draw(sf::RenderWindow* window) {
    Renderer::Draw(window);
    window->draw(sprite);
}

void SpriteRenderer::UpdateTransform() {
    sprite.setOrigin(sprite.getLocalBounds().getSize() / 2.f);
    sprite.setRotation(transform->rotation);
    sprite.setPosition(Math::reverseY(transform->position));
    sprite.setScale(transform->scale);
}

void SpriteRenderer::UpdateUITransform(sf::RenderWindow* window) {
    sf::View view = window->getView();
    sprite.setPosition(sprite.getPosition() + view.getCenter());
    sprite.setScale(Math::multiplyVectors(sprite.getScale(), Math::divideVectors(view.getSize(), Game::getResolution())));
    sprite.setOrigin(sprite.getLocalBounds().getSize() / 2.f);
    sprite.setRotation(sprite.getRotation() + view.getRotation());
}

// Setters
void SpriteRenderer::setTexture(std::string textureFilePath) {
    if (!texture.loadFromFile(textureFilePath)) {
        std::cerr << "Error while loading asset\n";
        isLoaded = false;
        return;
    }
    sprite.setTexture(texture);
    isLoaded = true;
}

void SpriteRenderer::setColor(sf::Color color) {
    if (!isLoaded) return;
    sprite.setColor(color);
}