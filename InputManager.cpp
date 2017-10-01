#include "stdafx.h"
#include "InputManager.h"
#include "Util.h"

InputManager* InputManager::m_instance = NULL;

InputManager::InputManager() {
	m_keysPressed = new bool[sf::Keyboard::KeyCount];
}


InputManager::~InputManager() {
}

InputManager & InputManager::operator=(const InputManager &i) {
	return *this;
}

void InputManager::keyPressedEvent(const sf::Keyboard::Key& _key) {
	if (!m_keysPressed[_key]) {
		m_keysPressed[_key] = true;
		for (int i = 0; i < m_observers.size(); ++i) {
			m_observers[i]->keyDown(_key);
		}
	}
}

void InputManager::keyReleasedEvent(const sf::Keyboard::Key & _key) {
	if (m_keysPressed[_key]) {
		m_keysPressed[_key] = false;
	}
}

void InputManager::attachObserver(InputObserver * _o) {
	m_observers.push_back(_o);
}

void InputManager::dettachObserver(InputObserver * _o) {
	auto it = std::find(m_observers.begin(), m_observers.end(), _o);
	if (it != m_observers.end()) {
		m_observers.erase(it);
	}
}

