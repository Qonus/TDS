#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Time.h"
#include "Transform.h"
#include "Component.h"
#include "GameObjectManager.h"
#include "CollisionPoints.h"

class GameObject {
public:

	GameObject(std::string _name, Transform* _transform = new Transform());
	virtual ~GameObject();

	virtual void HandleInput(sf::Event* event);
	virtual void FixedUpdate();
	virtual void Update();
	virtual void Draw(sf::RenderWindow* window);
	virtual void DrawUI(sf::RenderWindow* window);
	virtual void OnCollision(CollisionPoints points, GameObject* other);

	// Setters
	template<typename T>
	void AddComponent() {
		AddComponent<T>(new T(this));
	}

	template<typename T>
	void AddComponent(T* component) {
		if (!HasComponent<T>()) {
			components.push_back(component);
			//std::cout << components.size() << " ADD COMPONENT\n";
			return;
		}
		//std::cout << "NOT ADD COMPONENT\n";
	}

	template<typename T>
	void RemoveComponent() {
		for (int i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component) {
				delete component;
				components.erase(components.begin() + i);
				return;
			}
		}
	}

	// Getters
	template<typename T>
	T* GetComponent() {
		for (Component* component : components)
		{
			T* result = dynamic_cast<T*>(component);
			if (result) return result;
		}
		return nullptr;
	}

	template<typename T>
	bool HasComponent() {
		for (Component* component : components)
		{
			T* result = dynamic_cast<T*>(component);
			if (result) return true;
		}
		return false;
	}

	GameObjectManager* getManager();
	PhysicsManager* getPhysics();

	std::string getName();
	int getCopyIndex();
	Transform* getTransform();
protected:
	std::string name;
	int copyIndex;
	GameObjectManager* objectManager;

	std::vector<Component*> components;

	Transform* transform;

	friend class GameObjectManager;
};

#endif //GAME_OBJECT_H