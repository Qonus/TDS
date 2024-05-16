#include "Input.h"
#include "Game.h"

Input* Input::pInstance = NULL;

Input* Input::Instance()
{
	if (pInstance == NULL)
		pInstance = new Input;

	return pInstance;
}

Input::Input()
{
	// Initialization
	KeyBind(Action::Up, sf::Keyboard::W);
	KeyBind(Action::Down, sf::Keyboard::S);
	KeyBind(Action::Right, sf::Keyboard::D);
	KeyBind(Action::Left, sf::Keyboard::A);

	KeyBind(Action::Primary1, sf::Mouse::Left);
	KeyBind(Action::Dodge, sf::Mouse::Right);

	KeyBind(Action::Slot1, sf::Keyboard::Num1);
	KeyBind(Action::Slot2, sf::Keyboard::Num2);
	KeyBind(Action::Slot3, sf::Keyboard::Num3);
	KeyBind(Action::Slot4, sf::Keyboard::Num4);
}

// Checks if key is bound
bool Input::IsBound(int k)
{
	if (binds.find(k) != binds.end())
		return true;
	return false;
}

void Input::Update() {
	// Updates the previous state with the current state at the start of the current update
	for (auto k : binds)
	{
		binds.find(k.first)->second.prevState = k.second.curState;
	}
	deltaScroll = 0;
}

void Input::HandleInput(sf::Event* event) {
	// Keyboard Events
	if (event->type == sf::Event::KeyReleased)
		for (auto k : binds) if (k.second.inputType == InputType::Keyboard && k.second.keyCode.key == event->key.code)
			binds.find(k.first)
			->second.curState = 0;
	if (event->type == sf::Event::KeyPressed)
		for (auto k : binds) if (k.second.inputType == InputType::Keyboard && k.second.keyCode.key == event->key.code)
			binds.find(k.first)
			->second.curState = 1;
	// Mouse Events
	if (event->type == sf::Event::MouseButtonReleased)
		for (auto k : binds) if (k.second.inputType == InputType::Mouse && k.second.keyCode.button == event->mouseButton.button)
			binds.find(k.first)
			->second.curState = 0;
	if (event->type == sf::Event::MouseButtonPressed)
		for (auto k : binds) if (k.second.inputType == InputType::Mouse && k.second.keyCode.button == event->mouseButton.button)
			binds.find(k.first)
			->second.curState = 1;

	if (event->type == sf::Event::MouseWheelScrolled) {
		deltaScroll = event->mouseWheelScroll.delta;
	}
}

// Setters
// Binds a reference number to a key
void Input::KeyBind(int code, sf::Keyboard::Key key)
{
	if (IsBound(code)) {
		binds.find(code)->second.keyCode = key;
		binds.find(code)->second.inputType = InputType::Keyboard;
	}
	else {
		binds.insert(std::make_pair(code, Key(key, InputType::Keyboard)));
	}
}

void Input::KeyBind(int code, sf::Mouse::Button button)
{
	if (IsBound(code)) {
		binds.find(code)->second.keyCode = button;
		binds.find(code)->second.inputType = InputType::Mouse;
	}
	else {
		binds.insert(std::make_pair(code, Key(button, InputType::Mouse)));
	}
}

// Getters
// Is key down
bool Input::KeyDown(int code)
{
	if (!IsBound(code))
		return false;
	if (binds.find(code)->second.curState)
		return true;

	return false;
}

// Is key up
bool Input::KeyUp(int code)
{
	if (!IsBound(code))
		return false;

	if (!binds.find(code)->second.curState)
		return true;

	return false;
}
// On key press
bool Input::KeyPress(int code)
{
	if (!IsBound(code))
		return false;

	if (binds.find(code)->second.prevState == 0 && binds.find(code)->second.curState == 1)
		return true;

	return false;
}

// On key release
bool Input::KeyRelease(int code)
{
	if (!IsBound(code))
		return false;

	if (binds.find(code)->second.prevState == 1 && binds.find(code)->second.curState == 0)
		return true;

	return false;
}