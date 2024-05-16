#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"

class GameScene : public Scene
{
public:
	// Inherited
	void Init(std::string _name);
	void HandleInput(sf::Event* event);
	void FixedUpdate();
	void Update();
	void Draw(sf::RenderWindow* window);
private:
};

#endif //GAME_SCENE_H