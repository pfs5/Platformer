#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class Animation {
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	int m_currentFrame;
	sf::Vector2u m_frameSize;
	std::vector<int> m_frames;
	std::vector<int> m_activeFrames;

	const std::string ROOT_FOLDER = "images/";
public:
	Animation();
	Animation(std::string _name, int _frames [], int _frameNumber);
	~Animation();

	void draw();
	void update(float _dt);

	void move(const sf::Vector2f& _distance);
	void setPosition(const sf::Vector2f& _pos);
};

