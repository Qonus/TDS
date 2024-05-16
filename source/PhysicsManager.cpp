#include "PhysicsManager.h"

PhysicsManager::PhysicsManager() {

}

PhysicsManager::~PhysicsManager() {
	int size = bodies.size();
	for (int i = 0; i < size; i++)
	{
		RemoveBody(0);
	}
}

RaycastHit PhysicsManager::Raycast(Ray ray, std::string targetName) {
	RaycastHit result;
	std::vector<sf::Vector2f> points;
	std::vector<RaycastHit> hits;

	for (Body* body : bodies)
	{
		if (body->collider->getObject()->getName() != targetName || targetName == "") continue;
		if (!body->collider) continue;

		RaycastHit hit;
		hit = DetectRayCollision(ray, body->collider);

		if (points.size() > 0) {
			for (int i = 0; i < hit.points.size(); i++)
			{
				if (Math::magnitude(hit.points[i] - ray.origin) < Math::magnitude(points[0] - ray.origin)) {
					result.collider = body->collider;
					result.normal = hit.normal;
				}
			}
		}
		else {
			result.collider = body->collider;
			result.normal = hit.normal;
		}

		points.insert(points.end(), hit.points.begin(), hit.points.end());

		for (int i = 0; i < points.size(); i++) {
			for (int j = i + 1; j < points.size(); j++) {
				if (Math::magnitude(points[i] - ray.origin) > Math::magnitude(points[j] - ray.origin)) {
					std::swap(points[i], points[j]);
				}
			}
		}

		if (hit.hasHit && body) {
			hits.push_back(hit);
		}
	}

	result.points = points;

	result.hasHit = (result.points.size() > 0);

	return result;
}

void PhysicsManager::Update() {
	std::vector<Collision> collisions;

	for (Body* a : bodies)
	{
		for (Body* b : bodies)
		{
			if (a == b) break; // unique pairs
			// both have colliders and one of them dynamic
			if (!a->collider || !b->collider || (a->rigidbody->bodyType != Dynamic && b->rigidbody->bodyType != Dynamic)) continue;
			
			CollisionPoints points = DetectCollision(a->collider, b->collider);

			if (points.hasCollision && a && b) {
				collisions.emplace_back(Collision(a, b, points));
			}
		}
	}

	//std::cout << collisions.size() << '\n';

	// Solve collisions
	for (Collision collision : collisions)
	{
		if (collision.A->collider->getObject()->getName() == "" || collision.B->collider->getObject()->getName() == "") continue;
		collision.A->collider->getObject()->OnCollision(collision.points.reverse(), collision.B->collider->getObject());
		if (collision.A->collider->getObject()->getName() == "" || collision.B->collider->getObject()->getName() == "") continue;
		collision.B->collider->getObject()->OnCollision(collision.points, collision.A->collider->getObject());
	}
}

void PhysicsManager::AddBody(Body* body) {
	bodies.emplace_back(body);
}

void PhysicsManager::RemoveBody(GameObject* gameObject) {
	for (int i = 0; i < bodies.size(); i++)
	{
		if (bodies[i]->collider->getObject() == gameObject) {
			RemoveBody(i);
			return;
		}
	}
}

void PhysicsManager::RemoveBody(int bodyIndex) {
	delete bodies[bodyIndex];
	bodies[bodyIndex] = nullptr;
	bodies.erase(bodies.begin() + bodyIndex);
}