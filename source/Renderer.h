#ifndef RENDERER_H
#define RENDERER_H

#include "Transform.h"
#include "GameObject.h"
#include "Math.h"

class Renderer : public Component {
public:
	Renderer(GameObject* object);

	// Inherited
	void Update();
	void Draw(sf::RenderWindow* window);

	virtual void UpdateTransform();
	virtual void UpdateUITransform(sf::RenderWindow* window);

protected:
	Transform* transform;

	bool isLoaded;
};

#endif //RENDERER_H