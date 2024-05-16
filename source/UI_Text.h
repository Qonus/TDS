#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "UI_Object.h"
#include "TextRenderer.h"

class UI_Text : public UI_Object {
public:

	UI_Text(std::string string = "", int characterSize = 20, sf::Color color = sf::Color::White, std::string fontFilePath = "Comfortaa-VariableFont_wght.ttf");

private:
};

#endif //UI_TEXT_H
