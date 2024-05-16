#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"
#include "Transform.h"

class GameObject;

class GameObjectManager
{
public:
	GameObjectManager(Scene* _scene = new Scene());
	~GameObjectManager();

	void HandleInput(sf::Event* event);
	void FixedUpdateAll();
	void UpdateAll();
	void DrawAll(sf::RenderWindow* window);

	// Setters
	GameObject* AddGameObject(GameObject* object, Transform transform = Transform());
	void RemoveGameObject(GameObject* object);
	void RemoveGameObjectByName(std::string objectName, int objectCopyIndex);
	void RemoveGameObjectAt(int objectIndex);
	void RemoveAll();

	// Getters
	std::vector<GameObject*> GetGameObjectByName(std::string objectName);
	GameObject* GetGameObjectByIndex(int objectIndex);
	Scene* getScene();

private:
	Scene* scene;

	std::vector<GameObject*> objects;
};

#endif //GAME_OBJECT_MANAGER_H