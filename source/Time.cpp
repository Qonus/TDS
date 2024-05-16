#include "Time.h"

sf::Clock Time::dtClock;
sf::Clock Time::fdtClock;
float Time::deltaTime = 0;
float Time::fixedTime = 0.02f;
float Time::fixedDeltaTime = 0;
float Time::timeScale = 1.f;

void Time::FixedUpdate() {
	fixedDeltaTime = fdtClock.restart().asSeconds() * timeScale;
}

void Time::Update() {
	deltaTime = dtClock.restart().asSeconds() * timeScale;
}

// Setters
void Time::setFixedTime(float _fixedTime) {
	if(_fixedTime >= 0)
		fixedTime = _fixedTime;
}
void Time::setTimeScale(float _timeScale) {
	if(_timeScale >= 0)
		timeScale = _timeScale;
}

// Getters
float Time::getDeltaTime() {
	return deltaTime;
}
float Time::getFixedTime() {
	return fixedTime;
}
float Time::getFixedDeltaTime() {
	return fixedDeltaTime;
}
float Time::getTimeScale() {
	return timeScale;
}