#include "UI_Text.h"

UI_Text::UI_Text(std::string string, int characterSize, sf::Color color, std::string fontFilePath) : UI_Object("UI_Text") {
	AddComponent<TextRenderer>(new TextRenderer(this, fontFilePath, string, characterSize, color));
}