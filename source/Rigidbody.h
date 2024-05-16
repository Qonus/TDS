#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"
#include "Time.h"
#include "GameObject.h"

enum BodyType {
	Dynamic,
	Kinematic,
};

class Rigidbody : public Component{
public:

	// Variables
	BodyType bodyType;

	sf::Vector2f velocity;
	float drag;
	// Degrees per second
	float angularVelocity;
	float angularDrag;

	float mass;


	Rigidbody(GameObject* _object, BodyType _bodyType = Dynamic, float _mass = 1, float _drag = 1);

	// Inherited
	void FixedUpdate();
	void Update();

	void OnCollision(CollisionPoints points, GameObject* other);

	// Setters
	void AddForce(sf::Vector2f force);
	void AddTorque(float torque);

	// Getters
	GameObject* getObject();

private:
	GameObject* object;
	Transform* transform;
};

#endif //RIGIDBODY_H