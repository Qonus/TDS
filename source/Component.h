#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Component
{
public:
	Component();
	~Component();

	virtual void HandleInput(sf::Event* event);
	virtual void FixedUpdate();
	virtual void Update();
	virtual void Draw(sf::RenderWindow* window);
	virtual void DrawUI(sf::RenderWindow* window);

protected:
};

#endif //COMPONENT_H