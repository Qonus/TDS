#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <iostream>
#include "CollisionDetection.h"

#include "Collision.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	RaycastHit Raycast(Ray ray, std::string targetName = "");

	void Update();

	// Setters
	void AddBody(Body* body);
	void RemoveBody(GameObject* gameObject);
	void RemoveBody(int bodyIndex);

private:
	std::vector<Body*> bodies;
};

#endif //PHYSICS_MANAGER_H