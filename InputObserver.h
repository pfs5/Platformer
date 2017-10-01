#pragma once

#include <SFML\Graphics.hpp>

class InputObserver {
public:
	virtual void keyDown(sf::Keyboard::Key) = 0;
};