#include "Wall.h"

Wall::Wall() : GameObject("Wall") {
	AddComponent<SpriteRenderer>(new SpriteRenderer(this, "crate.png"));
	AddComponent<Rigidbody>(new Rigidbody(this, Dynamic, 1, 1.1f));
	AddComponent<RectangleCollider>(new RectangleCollider(this, sf::Vector2f(60.f, 60.f)));
	//AddComponent<CircleCollider>(new CircleCollider(this, 70.f));
}