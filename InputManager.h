#pragma once
#include <SFML\Graphics.hpp>
#include "InputObserver.h"

class InputManager {
	bool *m_keysPressed;

	std::vector<InputObserver*> m_observers;

private:
	InputManager();
	~InputManager();

	InputManager(const InputManager&);
	InputManager& operator=(const InputManager&);

	static InputManager *m_instance;
public:
	// Singleton
	static InputManager* getInstance() {
		if (m_instance == nullptr) {
			m_instance = new InputManager();
		}
		return m_instance;
	}

	// Methods
	void keyPressedEvent(const sf::Keyboard::Key& _key);
	void keyReleasedEvent(const sf::Keyboard::Key& _key);

	// Observer
	void attachObserver(InputObserver* _o);
	void dettachObserver(InputObserver* _o);
};

