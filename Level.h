#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Obstacle.h"

class Level {
	const std::string ROOT_FOLDER = "levels/";

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	sf::Texture m_foregroundTexture;
	sf::Sprite m_foregroundSprite;

	std::vector<Obstacle*> m_obstacles;
public:
	Level();
	~Level();

	void load(const std::string& _name);

	void drawBackground();
	void drawForeground();

	const sf::Vector2u& getSize();
	const std::vector<Obstacle*>& getObstacles();
};

