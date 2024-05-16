#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Scene.h"
#include "Input.h"

class MainMenu : public Scene
{
public:
	// Inherited
	void Init(std::string _name);
	void HandleInput(sf::Event* event);
	void FixedUpdate();
	void Update();
	void Draw(sf::RenderWindow* window);

	// Getters
	sf::Color getBackgroundColor();
private:
};

#endif //MAIN_MENU_H