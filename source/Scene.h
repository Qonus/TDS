#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class GameObjectManager;
class PhysicsManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init(std::string _name);
	virtual void HandleInput(sf::Event* event);
	virtual void FixedUpdate();
	virtual void Update();
	virtual void Draw(sf::RenderWindow* window);

	void Restart();

	// Getters
	std::string getName();
	GameObjectManager* getManager();
	PhysicsManager* getPhysics();
	virtual sf::Color getBackgroundColor();

protected:
	std::string name;
	GameObjectManager* objectManager;
	PhysicsManager* physicsManager;
};

#endif //SCENE_H