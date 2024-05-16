#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Renderer.h"

class SpriteRenderer : public Renderer {
public:
	SpriteRenderer(GameObject* object, std::string textureFilePath);

	// Inherited
	void Update();
	void Draw(sf::RenderWindow* window);
	void UpdateTransform();
	void UpdateUITransform(sf::RenderWindow* window);

	// Setters
	void setTexture(std::string textureFilePath);
	void setColor(sf::Color color);

private:
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif //SPRITE_RENDERER_H