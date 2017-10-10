#include "stdafx.h"
#include "Level.h"
#include "Util.h"
#include "Display.h"
#include <iostream>
#include <fstream>
#include <cmath>

Level::Level() {
}


Level::~Level() {
	for (int i = 0; i < m_obstacles.size(); ++i) {
		delete m_obstacles[i];
	}
}

void Level::load(const std::string& _name) {
	// Load image
	std::string path = ROOT_FOLDER + _name;
	if (!m_backgroundTexture.loadFromFile(path + "_bg.png")) {
		Util::printMessage("[Level] Error loading texture from " + path + "_bg.png");
		return;
	}
	if (!m_foregroundTexture.loadFromFile(path + "_fg.png")) {
		Util::printMessage("[Level] Error loading texture from " + path + "_fg.png");
		return;
	}

	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(1.f, 1.f);

	m_foregroundSprite.setTexture(m_foregroundTexture);
	m_foregroundSprite.setScale(1.f, 1.f);

	// Load obstacles
	std::string collidersPath = ROOT_FOLDER + _name + ".colliders";
	std::string line;
	std::ifstream file(collidersPath);

	if (!file.is_open()) {
		Util::printMessage("[Level] Error loading obstacles from " + collidersPath);
		return;
	}

	while (std::getline(file, line)) {
		std::vector <std::string> data = Util::split(line, " ");
		sf::Vector2f position(std::stof(data[0]), std::stof(data[1]));
		sf::Vector2f size(std::stof(data[2]), std::stof(data[3]));

		m_obstacles.push_back(new Obstacle(size, position));
	}

	file.close();
}

void Level::drawBackground() {
	Display::draw(m_backgroundSprite);
}

void Level::drawForeground() {
	Display::draw(m_foregroundSprite);
	for (int i = 0; i < m_obstacles.size(); ++i) {
		m_obstacles[i]->draw();
	}
}

const sf::Vector2u & Level::getSize() {
	return m_backgroundTexture.getSize();
}

const std::vector<Obstacle*>& Level::getObstacles() {
	return m_obstacles;
}
