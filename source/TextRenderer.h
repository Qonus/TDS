#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Renderer.h"

class TextRenderer : public Renderer{
public:
	TextRenderer(GameObject* object, std::string fontFilePath, std::string string = "", int characterSize = 10, sf::Color color = sf::Color::White);

	// Inherited
	void Update();
	void DrawUI(sf::RenderWindow* window);
	void UpdateTransform();
	void UpdateUITransform(sf::RenderWindow* window);

	// Setters
	void setString(std::string text);
	void setCharacterSize(unsigned int size);
	void setFont(std::string fontFilePath);
	void setColor(sf::Color color);

private:
	sf::Font font;
	sf::Text text;
};

#endif //TEXT_RENDERER_H