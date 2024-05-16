#include "TextRenderer.h"
#include "Game.h"

TextRenderer::TextRenderer(GameObject* object, std::string fontFilePath, std::string string, int characterSize, sf::Color color) : Renderer(object) {
	setFont(fontFilePath);
	setString(string);
	setCharacterSize(characterSize);
	setColor(color);
}

// Inherited
void TextRenderer::Update() {
	Renderer::Update();
}

void TextRenderer::DrawUI(sf::RenderWindow* window) {
	Renderer::Draw(window);
	window->draw(text);
}

void TextRenderer::UpdateTransform() {
	text.setOrigin(text.getLocalBounds().getSize() / 2.f);
	text.setRotation(transform->rotation);
	text.setPosition(Math::reverseY(transform->position));
	text.setScale(transform->scale);
}
void TextRenderer::UpdateUITransform(sf::RenderWindow* window) {
	sf::View view = window->getView();
	text.setPosition(text.getPosition() + view.getCenter());
	text.setScale(Math::multiplyVectors(text.getScale(), Math::divideVectors(view.getSize(), Game::getResolution())));
	text.setOrigin(text.getLocalBounds().getSize() / 2.f);
	text.setRotation(text.getRotation() + view.getRotation());
}

// Setters
void TextRenderer::setString(std::string string) {
	text.setString(string);
}

void TextRenderer::setCharacterSize(unsigned int size) {
	text.setCharacterSize(size);
}

// Setters

void TextRenderer::setFont(std::string fontFilePath) {
	if (!font.loadFromFile(fontFilePath)) {
		std::cerr << "Error while loading font\n";
		isLoaded = false;
		return;
	}
	text.setFont(font);
	isLoaded = true;
}

void TextRenderer::setColor(sf::Color color) {
	if (!isLoaded) return;
	text.setFillColor(color);
}