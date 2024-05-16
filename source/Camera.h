#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Input.h"
#include "Math.h"

class Camera : public GameObject {
public:
	float minZoom;
	float maxZoom;

	Camera();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Draw(sf::RenderWindow* window);

	static Camera* getMainCamera();

private:
	sf::View view;
	float zoomSensitivity;
};

#endif //CAMERA_H