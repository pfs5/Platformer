#include "stdafx.h"
#include "Display.h"
#include "InputManager.h"
#include <memory>
#include <iostream>

namespace Display {
	std::unique_ptr<sf::RenderWindow> window;

	void init() {
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE);
		window.get()->setFramerateLimit(60);
	}

	void clear(const sf::Color& _color) {
		window->clear(_color);
	}

	void display() {
		window->display();
	}

	void draw(const sf::Drawable& _drawable) {
		window->draw(_drawable);
	}

	void checkWindowEvents() {
		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::KeyPressed) {
				InputManager::getInstance()->keyPressedEvent(e.key.code);
			}
			if (e.type == sf::Event::KeyReleased) {
				InputManager::getInstance()->keyReleasedEvent(e.key.code);
			}
			if (e.type == sf::Event::Closed) {
				window->close();
			}
		}
	}

	bool isOpen() {
		return window->isOpen();
	}

	sf::RenderWindow &getWindow() {
		return *window;
	}
}