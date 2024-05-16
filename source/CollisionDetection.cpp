#include "CollisionDetection.h"

sf::Vector2f getClosestPointLine(Ray ray, sf::Vector2f point) {
	sf::Vector2f pX = Math::normalize(ray.direction);
	sf::Vector2f pY = Math::normalize(sf::Vector2f(-ray.direction.y, ray.direction.x));

	sf::Vector2f dir = point - ray.origin;

	float closestPointDist = 
		(pY.y * dir.x - pY.x * dir.y) /
		(pY.y * pX.x - pY.x * pX.y)
	;

	closestPointDist = Math::clamp(closestPointDist, 0, Math::magnitude(ray.direction));

	sf::Vector2f result = pX * closestPointDist + ray.origin;

	return result;
}

RaycastHit DetectRayCollision(Ray ray, Collider* collider) {
	if (collider->getType() == Circle) {
		CircleCollider* circle = dynamic_cast<CircleCollider*>(collider);
		if(circle)
			return RayCircle(ray, circle);
	}
	if (collider->getType() == Rectangle) {
		RectangleCollider* rectangle = dynamic_cast<RectangleCollider*>(collider);
		if (rectangle)
			return RayRectangle(ray, rectangle);
	}
}
RaycastHit RayCircle(Ray ray, CircleCollider* circle) {
	sf::Vector2f cCenter = circle->getTransform().position;

	// Closest Point
	sf::Vector2f pX = Math::normalize(ray.direction);
	sf::Vector2f pY = Math::normalize(sf::Vector2f(-ray.direction.y, ray.direction.x));

	sf::Vector2f dir = cCenter - ray.origin;

	float closestPointDist =
		(pY.y * dir.x - pY.x * dir.y) /
		(pY.y * pX.x - pY.x * pX.y)
	;

	closestPointDist = Math::clamp(closestPointDist, 0, Math::magnitude(ray.direction));

	sf::Vector2f closestPoint = pX * closestPointDist + ray.origin;

	/*float dist = 
		(pX.y * dir.x - pX.x * dir.y) /
		(pX.y * pY.x - pX.x * pY.y)
	;*/
	float dist = Math::magnitude(closestPoint - cCenter);

	RaycastHit hit;

	if (pow(circle->radius, 2) - pow(dist, 2) >= 0) {
		float a = sqrt(pow(circle->radius, 2) - pow(dist, 2));

		sf::Vector2f point1 = pX * (closestPointDist - a) + ray.origin;
		sf::Vector2f point2 = pX * (closestPointDist + a) + ray.origin;

		if (closestPointDist - a >= 0 && closestPointDist - a <= Math::magnitude(ray.direction))
			hit.points.push_back(point1);
		if (closestPointDist + a >= 0 && closestPointDist + a <= Math::magnitude(ray.direction))
			hit.points.push_back(point2);

		if (hit.points.size() > 0) {
			hit.normal = Math::normalize(hit.points[0] - cCenter);
			hit.hasHit = true;
		}
	}

	return hit;
}

RaycastHit RayRay(Ray ray1, Ray ray2) {

	sf::Vector2f a1 = ray1.origin;
	sf::Vector2f a2 = ray1.origin + ray1.direction;
	sf::Vector2f a3 = ray1.direction;

	sf::Vector2f b1 = ray2.origin;
	sf::Vector2f b2 = ray2.origin + ray2.direction;
	sf::Vector2f b3 = ray2.direction;

	float x = (b1.y - a1.y - (b3.y * b1.x) / b3.x + (a3.y * a1.x) / a3.x) /
		(a3.y / a3.x - b3.y / b3.x);

	float y = (b1.x - a1.x - (b3.x * b1.y) / b3.y + (a3.x * a1.y) / a3.y) /
		(a3.x / a3.y - b3.x / b3.y);

	if (b3.x == 0) x = b1.x;
	if (b3.y == 0) y = b1.y;
	if (a3.x == 0) x = a1.x;
	if (a3.y == 0) y = a1.x;


	// DANGEROUS MAY CAUSE BUGS RELATED WITH ZERO DIVISION
	sf::Vector2f intersection = sf::Vector2f(x,y);

	RaycastHit hit;

	hit.hasHit = Math::between(intersection, a1, a2) && Math::between(intersection, b1, b2);
	if (hit.hasHit) {
		hit.points.push_back(intersection);
	}

	return hit;
}

RaycastHit RayRectangle(Ray ray, RectangleCollider* rectangle) {
	sf::Vector2f rCenter = rectangle->getTransform().position;
	sf::Vector2f rSize = rectangle->getSize();

	std::vector<RaycastHit> hits;
	hits.push_back(RayRay(ray, Ray(sf::Vector2f(-rSize.x, rSize.y) + rCenter, sf::Vector2f(0, -rSize.y * 2)))); // left   0
	hits.push_back(RayRay(ray, Ray(sf::Vector2f(rSize.x, rSize.y) + rCenter, sf::Vector2f(0, -rSize.y * 2)))); //  right  1
	hits.push_back(RayRay(ray, Ray(sf::Vector2f(-rSize.x, rSize.y) + rCenter, sf::Vector2f(rSize.x * 2, 0)))); //  top    2
	hits.push_back(RayRay(ray, Ray(sf::Vector2f(-rSize.x, -rSize.y) + rCenter, sf::Vector2f(rSize.x * 2, 0)))); // bottom 3

	RaycastHit hit;

	for (int i = 0; i < hits.size(); i++)
	{
		if (hits[i].hasHit) {
			bool b = true;
			for (int j = 0; j < hit.points.size(); j++)
			{
				if (hits[i].points[0] == hit.points[j]) b = false;
			}
			if(b) hit.points.push_back(hits[i].points[0]);

			if (hit.normal == sf::Vector2f() || Math::magnitude(hit.points[0] - ray.origin) > Math::magnitude(hits[i].points[0] - ray.origin)) {
				switch (i) {
				case 0:
					hit.normal = sf::Vector2f(-1, 0);
					break;
				case 1:
					hit.normal = sf::Vector2f(1, 0);
					break;
				case 2:
					hit.normal = sf::Vector2f(0, 1);
					break;
				case 3:
					hit.normal = sf::Vector2f(0, -1);
					break;
				}
			}

			for (int i = 0; i < hit.points.size(); i++) {
				for (int j = i + 1; j < hit.points.size(); j++) {
					if (Math::magnitude(hit.points[i] - ray.origin) > Math::magnitude(hit.points[j] - ray.origin)) {
						std::swap(hit.points[i], hit.points[j]);
					}
				}
			}
		}
	}

	/*float minDist = 0;

	for (int i = 0; i < hit.points.size(); i++)
	{
		float dist = Math::magnitude(hit.points[i] - ray.origin);
		if (dist >= minDist) {
			minDist = dist;
			std::swap(hit.points[i], hit.points[0]);
		}
	}*/

	if (hit.points.size() > 0)
		hit.hasHit = true;

	return hit;
}

CollisionPoints DetectCollision(Collider* a, Collider* b) {
	static Collision_Detection_funcs funcs;

	size_t aid = (int)a->getType();
	size_t bid = (int)b->getType();

	if (aid > bid) {
		std::swap(a, b);
		std::swap(aid, bid);
	}

	CollisionPoints points;

	points = funcs.container[aid][bid](a, b);

	return points;
}

sf::Vector2f getCirclePoint(sf::Vector2f normal, CircleCollider* circle) {
	return normal * circle->radius;
}

sf::Vector2f getRectanglePoint(sf::Vector2f normal, RectangleCollider* rectangle) {
	sf::Vector2f dir = normal * Math::magnitude(rectangle->getSize());
	sf::Vector2f result;

	if (dir.y >= rectangle->getSize().y) {
		result.y = rectangle->getSize().y;
		result.x = result.y * normal.x / normal.y;
	}
	else if (dir.y <= -rectangle->getSize().y) {
		result.y = -rectangle->getSize().y;
		result.x = result.y * normal.x / normal.y;
	}
	else if (dir.x >= rectangle->getSize().x) {
		result.x = rectangle->getSize().x;
		result.y = result.x * normal.y / normal.x;
	}
	else if (dir.x <= -rectangle->getSize().x) {
		result.x = -rectangle->getSize().x;
		result.y = result.x * normal.y / normal.x;
	}

	if (normal == sf::Vector2f()) {
		std::cout << "RECTANGLE POINT ERROR\n";
	}

	return result;
}

sf::Vector2f getClosestPointToRectangle(sf::Vector2f point, RectangleCollider* rectangle) {
	sf::Vector2f closestPoint = point;
	sf::Vector2f rCenter = rectangle->getTransform().position;
	closestPoint = Math::clamp(closestPoint, rCenter - rectangle->getSize(), rCenter + rectangle->getSize());
	return closestPoint;
}

CollisionPoints CircleCircle(Collider* a, Collider* b) {
	if (a->getType() != Circle || b->getType() != Circle) throw;

	CircleCollider* A = (CircleCollider*)a;
	CircleCollider* B = (CircleCollider*)b;

	sf::Vector2f aCenter = A->getTransform().position;
	sf::Vector2f bCenter = B->getTransform().position;

	sf::Vector2f ab = bCenter - aCenter;

	sf::Vector2f normal = Math::normalize(ab);

	float distance = Math::magnitude(ab);

	CollisionPoints points;

	points.A = aCenter + getCirclePoint(normal, A);
	points.B = bCenter - getCirclePoint(normal, B);

	points.hasCollision = distance <= A->radius + B->radius;

	points.Fill();

	return points;
}

CollisionPoints RectangleCircle(Collider* a, Collider* b) {
	if (a->getType() != Rectangle || b->getType() != Circle) throw;

	RectangleCollider* R = (RectangleCollider*)a;
	CircleCollider* C = (CircleCollider*)b;

	sf::Vector2f cCenter = C->getTransform().position;

	sf::Vector2f closestPoint = getClosestPointToRectangle(cCenter, R);

	sf::Vector2f rc = cCenter - closestPoint;
	sf::Vector2f normal = Math::normalize(rc);

	CollisionPoints points;

	points.A = closestPoint;

	points.B = cCenter - getCirclePoint(normal, C);

	points.hasCollision = Math::magnitude(rc) <= C->radius;

	points.Fill();

	return points;
}

CollisionPoints RectangleRectangle(Collider* a, Collider* b) {
	if (a->getType() != Rectangle || b->getType() != Rectangle) throw;

	if (a == b) std::cout << "MEGA ERROR PLOT TWIST TWINS\n";

	RectangleCollider* A = (RectangleCollider*)a;
	RectangleCollider* B = (RectangleCollider*)b;

	sf::Vector2f aCenter = A->getTransform().position;
	sf::Vector2f bCenter = B->getTransform().position;

	float aTop = aCenter.y + A->getSize().y;
	float bTop = bCenter.y + B->getSize().y;
	float aBottom = aCenter.y - A->getSize().y;
	float bBottom = bCenter.y - B->getSize().y;

	float aRight = aCenter.x + A->getSize().x;
	float bRight = bCenter.x + B->getSize().x;
	float aLeft = aCenter.x - A->getSize().x;
	float bLeft = bCenter.x - B->getSize().x;

	sf::Vector2f closestPoint = getClosestPointToRectangle(aCenter, B);

	sf::Vector2f ac = closestPoint - aCenter;
	sf::Vector2f normal = Math::normalize(ac);

	CollisionPoints points;

	points.A = aCenter + getRectanglePoint(normal, A);
	
	points.B = closestPoint;

	points.hasCollision = (aBottom <= bTop && bBottom <= aTop) && (bLeft <= aRight && aLeft <= bRight);

	points.Fill();

	return points;
}