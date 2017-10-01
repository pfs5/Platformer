#pragma once
#include <SFML\Graphics.hpp>

class SpotLight {
	const std::string ROOT_FOLDER = "images/";

	sf::Texture m_texture;
	sf::Sprite m_sprite;
public:
	SpotLight();
	~SpotLight();

	void draw();
	void setPosition(const sf::Vector2f& _position);
	void setScale(float _scale);
};

