#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class BackgroundImage {
	const std::string ROOT_FOLDER = "images/";

	sf::Texture m_texture;
	sf::Sprite m_sprite;
public:
	BackgroundImage();
	~BackgroundImage();

	void load(const std::string& _name);

	sf::Drawable * const getDrawable();

	const sf::Vector2u& getSize();
};

