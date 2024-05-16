#include "Rigidbody.h"
#include "PhysicsManager.h"

Rigidbody::Rigidbody(GameObject* _object, BodyType _bodyType, float _mass, float _drag) : 
	object(_object), bodyType(_bodyType), velocity(), drag(_drag), angularVelocity(), angularDrag(1), mass(_mass) {
	transform = object->getTransform();
}

// Inherited
void Rigidbody::FixedUpdate() {
	if (bodyType != Dynamic) return;
	velocity /= drag;
	angularVelocity /= angularDrag;

	RaycastHit hit = object->getPhysics()->Raycast(Ray(transform->position, velocity * Time::getFixedTime()), "Wall");
	if (hit.hasHit) {
		//std::cout << "True";
		velocity = ((hit.points[0] - transform->position) + Math::normalize(hit.points[0] - hit.collider->getTransform().position) * 0.01f) / Time::getFixedTime();
	}

	transform->position += velocity * Time::getFixedTime();
	transform->rotation += angularVelocity * Time::getFixedTime();
}

void Rigidbody::Update() {
}

void Rigidbody::OnCollision(CollisionPoints points, GameObject* other) {
	Rigidbody* otherRigidbody = other->GetComponent<Rigidbody>();
	if (otherRigidbody == nullptr) return;

	if (bodyType == Dynamic && otherRigidbody->bodyType == Dynamic)
		object->getTransform()->position += points.normal * points.depth / 2.f;
	else if(bodyType == Dynamic && otherRigidbody->bodyType != Dynamic)
		object->getTransform()->position += points.normal * points.depth;
}

// Setters
void Rigidbody::AddForce(sf::Vector2f force) {
	if (bodyType != Dynamic) return;
	velocity += force / mass;
}
void Rigidbody::AddTorque(float torque) {
	if (bodyType != Dynamic) return;
	angularVelocity += torque / mass;
}

// Getters
GameObject* Rigidbody::getObject() {
	return object;
}