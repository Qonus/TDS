#include "Player.h"
#include "PhysicsManager.h"
#include "Camera.h"

Player::Player(TextRenderer* _hpText) : GameObject("Player"), Damagable(100), state(Moving), equippedWeapon(0), hpText(_hpText) {
	hpText->setString("HP : " + std::to_string((int)health));

	BulletOptions bullet = BulletOptions("weapon_sword.png", 1500.f, 10, 1000, 10, sf::Color(150, 150, 230));
	weapons.emplace_back(Weapon(bullet, 0.3f, 20, 0));
	weapons.emplace_back(Weapon(bullet, 1.f, 200, 90, 10));
	weapons.emplace_back(Weapon(bullet, 0.1f, 20, 30, 1));
	weapons.emplace_back(Weapon(bullet, 0.8f, 0, 360, 30));

	AddComponent<SpriteRenderer>(new SpriteRenderer(this, "purple_character.png"));

	rigidbody = new Rigidbody(this, Dynamic, 1, 1.2f);
	AddComponent<Rigidbody>(rigidbody);

	AddComponent<CircleCollider>(new CircleCollider(this, 40.f));

	dodgeDuration = 0.15f;

	acceleration = 10;
}

void Player::HandleInput(sf::Event* event) {
	GameObject::HandleInput(event);
	if (Input::Instance()->KeyPress(Slot1))
		equippedWeapon = 0;
	if (Input::Instance()->KeyPress(Slot2))
		equippedWeapon = 1;
	if (Input::Instance()->KeyPress(Slot3))
		equippedWeapon = 2;
	if (Input::Instance()->KeyPress(Slot4))
		equippedWeapon = 3;
}

void Player::FixedUpdate() {
	GameObject::FixedUpdate();

	HandleRotation(dir2Mouse);
	HandleMovement(dir2Mouse);

	/*if (getPhysics()->Raycast(Ray(transform->position, Math::reverseY(dir2Mouse)), "Wall").hasHit) {
		std::cout << "True\n";
	}
	else std::cout << "False\n";*/

	// Make Camera follow Player
	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*Game::getWindow()) - sf::Vector2f(Game::Width, Game::Height) / 2.f;
	Camera::getMainCamera()->getTransform()->position = (Math::lerp(
		Camera::getMainCamera()->getTransform()->position,
		Math::reverseY(transform->position) + mousePos * 0.5f,
		0.3f / Time::getFixedTime())
	);
}

void Player::Update(){
	GameObject::Update();

	dir2Mouse = Game::getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*Game::getWindow())) - Math::reverseY(transform->position);

	// Update Direction
	direction = sf::Vector2f();
	if (state == Moving) {
		if (Input::Instance()->KeyDown(Action::Up)) {
			direction += sf::Vector2f(0, 1);
		}
		if (Input::Instance()->KeyDown(Action::Down)) {
			direction += sf::Vector2f(0, -1);
		}
		if (Input::Instance()->KeyDown(Action::Right)) {
			direction += sf::Vector2f(1, 0);
		}
		if (Input::Instance()->KeyDown(Action::Left)) {
			direction += sf::Vector2f(-1, 0);
		}
		// Make sure that magnitude is equal to 1
		direction = Math::normalize(direction);
		if (direction != sf::Vector2f())
			lastDirection = direction;
	}

	if (Input::Instance()->KeyDown(Action::Primary1) && state != Dodging && getEquippedWeapon()->canShoot()) {
		// SHOOT
		getEquippedWeapon()->Shoot(this, Math::reverseY(dir2Mouse), Transform(sf::Vector2f(), 90, sf::Vector2f(.5f, .5f)));
	}

	if (Input::Instance()->KeyPress(Action::Dodge) && state != Dodging) {
		// DODGE
		state = Dodging;
		entityState = Invincible;
		rigidbody->AddForce(lastDirection * 3000.f);
		dodgeClock.restart();
	}

	if (state == Dodging && dodgeClock.getElapsedTime().asSeconds() >= dodgeDuration) {
		// STOP DODGE
		state = Moving;
		entityState = Alive;
	}
}

void Player::Draw(sf::RenderWindow* window){
	GameObject::Draw(window);
	sf::RectangleShape line(sf::Vector2f(Math::magnitude(dir2Mouse), 5.f));
	line.setFillColor(sf::Color::Green);
	line.setPosition(Math::reverseY(transform->position));
	line.rotate(transform->rotation);
	window->draw(line);
}

void Player::Damage(float damage, sf::Vector2f impulse) {
	if (state == Dodging) return;
	rigidbody->AddForce(impulse);
	Damagable::Damage(damage, impulse);
	if(entityState != Dead)
		hpText->setString("HP : " + std::to_string((int)health));
	else
		hpText->setString("YOU ARE DEAD NOW\nYOU CAN RESTART\nBY PRESSING - [R]");
}

void Player::OnDeath() {
	Damagable::OnDeath();

	getManager()->RemoveGameObject(this);
}

void Player::HandleRotation(sf::Vector2f dir2Mouse) {
	transform->rotation = Math::DirectionToDegrees(dir2Mouse);
}

void Player::HandleMovement(sf::Vector2f dir2Mouse) {
	// apply acceleration
	rigidbody->AddForce(acceleration * direction * Time::getFixedTime() * 1000.f);
	// apply deceleration
	//rigidbody->AddForce(deceleration * rigidbody->velocity * Time::getFixedTime() * -1.f);
}

void Player::OnCollision(CollisionPoints points, GameObject* other) {
	if (other->getName() == "Bullet") return;
	GameObject::OnCollision(points, other);
}

// Getters
Weapon* Player::getEquippedWeapon() {
	return &weapons[equippedWeapon];
}