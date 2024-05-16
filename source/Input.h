#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

enum InputType {
	Keyboard,
	Mouse
};

union KeyCode {
	sf::Keyboard::Key key;
	sf::Mouse::Button button;
	KeyCode() {}
	KeyCode(sf::Keyboard::Key _key) { key = _key; }
	KeyCode(sf::Mouse::Button _button) { button = _button; }
};

struct Key
{
	// Is the key down or up
	// 0 up
	// 1 down
	int curState;
	int prevState;
	// Holds the key being bound
	InputType inputType;
	KeyCode keyCode;
	Key(KeyCode _keyCode, InputType _inputType)
	{
		this->curState = 0;
		this->prevState = 0;
		this->inputType = _inputType;
		this->keyCode = _keyCode;
	}
};

enum Action {
	Up,
	Down,
	Right,
	Left,
	Primary1,
	Dodge,

	Slot1,
	Slot2,
	Slot3,
	Slot4,
};

class Input {
public:
	static Input* Instance();

	float deltaScroll;

	void Update();
	void HandleInput(sf::Event* event);

	// Setters
	void KeyBind(int code, sf::Keyboard::Key key);
	void KeyBind(int code, sf::Mouse::Button button);

	// Getters

	// Is key down
	bool KeyDown(int code);
	// Is key up
	bool KeyUp(int code);
	// On key press
	bool KeyPress(int code);
	// On key release
	bool KeyRelease(int code);
private:
	static Input* pInstance;
	Input();

	// This maps a given key to another key as necessary
	std::map<int, Key> binds;
	// Check if a bind exists
	bool IsBound(int k);
};

#endif //INPUT_H