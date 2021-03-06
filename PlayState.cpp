#include "stdafx.h"	
#include "PlayState.h"
#include "Display.h"
#include "DummyObject.h"
#include "Obstacle.h"
#include <iostream>

PlayState::PlayState() {
	// Setup level
	m_level.load("level3");
	
	// Setup view
	m_view.reset(sf::FloatRect(0.f, 0.f, Display::WIDTH, Display::HEIGHT));
	m_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	
	m_initViewCenterY = m_level.getSize().y - Display::getWindow().getSize().y / 2.f;

	// Init physics
	m_engine.addGameObject(m_mainCharacter);

	std::vector<Obstacle*> obstacles = m_level.getObstacles();
	for (int i = 0; i < obstacles.size(); ++i) {
		m_engine.addGameObject(*obstacles[i]);
	}

	initTestEnvironment();
}


PlayState::~PlayState() {
	// Delete game objects
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		delete m_gameObjects[i];
	}
}

void PlayState::input() {
	m_mainCharacter.input();
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->input();
	}
}

void PlayState::update(float _dt) {
	m_mainCharacter.update(_dt);
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->update(_dt);
	}

	sf::Vector2f viewCenter = m_mainCharacter.getCenter();
	if (m_mainCharacter.getCenter().y < m_initViewCenterY) {
		viewCenter.y = m_initViewCenterY - (m_initViewCenterY - m_mainCharacter.getCenter().y) * 0.8f;
	}
	else {
		viewCenter.y = m_initViewCenterY;
	}

	m_view.setCenter(viewCenter);
	Display::getWindow().setView(m_view);

	m_engine.update(_dt);
}

void PlayState::draw() {
	m_level.drawBackground();
	
	for (int i = 0; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->draw();
	}
	m_mainCharacter.draw();

	m_level.drawForeground();
}

void PlayState::initTestEnvironment() {
	// Add obstacles
	GameObject* floor = new Obstacle(sf::Vector2f(4000.f, 50.f), sf::Vector2f(0.f, m_level.getSize().y - 5.f));
	m_gameObjects.push_back(floor);
	m_engine.addGameObject(*floor);

	GameObject* leftWall = new Obstacle(sf::Vector2f(200.f, 1000.f), sf::Vector2f(-200.f, 0));
	m_gameObjects.push_back(leftWall);
	m_engine.addGameObject(*leftWall);

}
