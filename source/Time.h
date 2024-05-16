#ifndef TIME_H
#define TIME_H

#include <SFML/Graphics.hpp>

class Time
{
public:
	static void FixedUpdate();
	static void Update();

	// Setters
	static void setFixedTime(float _fixedTime);
	static void setTimeScale(float _timeScale);

	// Getters
	static float getDeltaTime();
	static float getFixedTime();
	static float getFixedDeltaTime();
	static float getTimeScale();
private:
	static sf::Clock dtClock;
	static sf::Clock fdtClock;
	static float deltaTime;
	static float fixedTime;
	static float fixedDeltaTime;
	static float timeScale;
};

#endif //TIME_H