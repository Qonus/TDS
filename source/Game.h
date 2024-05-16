#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Time.h"
#include "Input.h"
#include "Scene.h"

// Scenes
#include "GameScene.h"
#include "MainMenu.h"

enum GameState {
    Uninitialized,
    Playing,
    Exiting,
};

class Game
{
public:
    static unsigned int Width;
    static unsigned int Height;

    Game();

    static void Init();

    // Game loop
    static void GameLoop();

    static void ProcessInput();
    static void FixedUpdate();
    static void Update();
    static void Draw();

    // Setters
    static void setState(GameState _gameState);
    static void LoadScene(int sceneIndex);
    static void LoadNextScene();
    static void LoadSceneByName(std::string sceneName);
    static void RestartScene(int sceneIndex);

    // Getters
    static GameState getGameState();
    static unsigned int getCurrentSceneIndex();
    static Scene* getCurrentScene();
    static Scene* getScene(std::string sceneName);
    static sf::RenderWindow* getWindow();
    static sf::Vector2f getResolution();

private:
    static GameState gameState;
    static unsigned int currentSceneIndex;
    static std::vector<Scene*> sceneInstances;
    static sf::RenderWindow window;
};

#endif