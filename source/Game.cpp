#include "Game.h"

unsigned int Game::Width = 1080;
unsigned int Game::Height = 720;
sf::RenderWindow Game::window;

GameState Game::gameState = Uninitialized;
unsigned int Game::currentSceneIndex = 0;
std::vector<Scene*> Game::sceneInstances;

Game::Game() {
}

void Game::Init() {
	if (gameState != Uninitialized) return;

	// Settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Create window
	window.create(sf::VideoMode(Width, Height), "ETG", sf::Style::Default, settings);
	
	window.setFramerateLimit(120);

	// Initialize Scenes
	sceneInstances.emplace_back(new MainMenu());
	sceneInstances[0]->Init("MainMenu");

	sceneInstances.emplace_back(new GameScene());
	sceneInstances[1]->Init("GameScene");

	/*for (Scene* scene : sceneInstances)
	{
		scene->Init("GameScene");
	}*/

	GameLoop();

	window.close();
	for (Scene* scene : sceneInstances) {
		delete scene;
	}
}

// Game Loop

void Game::GameLoop() {
	float fixedElapsedTime = 0.0f;

	// Main Game Loop
	while (gameState != Exiting)
	{
		// Clear with Background Color
		window.clear(getCurrentScene()->getBackgroundColor());

		// Process Input
		ProcessInput();
		// Fixed Update
		fixedElapsedTime += Time::getDeltaTime();
		while (fixedElapsedTime >= Time::getFixedTime()) {
			Time::FixedUpdate();
			//std::cout << 1/Time::getFixedDeltaTime() << '\n';
			FixedUpdate();

			fixedElapsedTime -= Time::getFixedTime();
		}

		// Update
		Update();

		// Show FPS
		//std::cout << "FPS : " << 1 / Time::getDeltaTime() << std::endl;

		// Draw
		Draw();

		window.display();
	}
}

void Game::ProcessInput() {

	Input::Instance()->Update();

	sf::Event event;
	while (window.pollEvent(event)) {
		Input::Instance()->HandleInput(&event);

		getCurrentScene()->HandleInput(&event);

		// Update Game State if window is being closed
		if (event.type == sf::Event::Closed) {
			setState(Exiting);
		}
		// catch the resize events
		//if (event.type == sf::Event::Resized)
		//{
		//	// update the view to the new size of the window
		//	sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
		//	window.setView(sf::View(visibleArea));
		//}
	}
}

void Game::FixedUpdate() {
	Time::FixedUpdate();
	getCurrentScene()->FixedUpdate();
}

void Game::Update() {
	Time::Update();
	getCurrentScene()->Update();
}

void Game::Draw() {
	getCurrentScene()->Draw(&window);
}


// Setters
void Game::setState(GameState _gameState) {
	gameState = _gameState;
}

void Game::LoadScene(int sceneIndex) {
	currentSceneIndex = sceneIndex;
}

void Game::LoadNextScene() {
	currentSceneIndex += 1;
}

void Game::LoadSceneByName(std::string sceneName) {
	for (int i = 0; i < sceneInstances.size(); i++)
	{
		if (sceneInstances[i]->getName() == sceneName) {
			LoadScene(i);
		}
	}
}

void Game::RestartScene(int sceneIndex) {
	sceneInstances[sceneIndex]->Restart();
}


// Getters
GameState Game::getGameState() {
	return gameState;
}
unsigned int Game::getCurrentSceneIndex() {
	return currentSceneIndex;
}
Scene* Game::getCurrentScene() {
	return sceneInstances[getCurrentSceneIndex()];
}
Scene* Game::getScene(std::string sceneName) {
	for (int i = 0; i < sceneInstances.size(); i++)
	{
		if (sceneInstances[i]->getName() == sceneName) {
			return sceneInstances[i];
		}
	}
	return nullptr;
}
sf::RenderWindow* Game::getWindow() {
	return &window;
}
sf::Vector2f Game::getResolution() {
	return sf::Vector2f(Width, Height);
}