#include "stdafx.h"
#include "DefaultState.h"
#include "PlayState.h"
#include <SFML/Graphics.hpp>

DefaultState::DefaultState(Application& _app) : m_app (_app) {
}


DefaultState::~DefaultState() {
}

void DefaultState::input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_app.addGameState(new PlayState());
	}
}

void DefaultState::update(float _dt) {

}

void DefaultState::draw() {

}