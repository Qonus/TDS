#ifndef UI_OBJECT_H
#define UI_OBJECT_H

#include "GameObject.h"
#include "Renderer.h"

class UI_Object : public GameObject {
public:

	UI_Object(std::string name);

	void HandleInput(sf::Event* event);
	void FixedUpdate();
	void Update();
	void DrawUI(sf::RenderWindow* window);

protected:
};

#endif //UI_OBJECT_H