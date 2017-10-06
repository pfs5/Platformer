#pragma once
#include "Animation.h"
class AnimationController {
	std::vector<Animation*> m_animations;
	std::map<std::string, int> m_animationNames;
	int m_currentAnimation;
public:
	AnimationController();
	~AnimationController();

	void loadFromFile(const std::string& _path);

	void addAnimation(Animation* _a, const std::string& _animationName);
	void playAnimation(std::string _animationName);

	void draw();
	void update(float _dt);

	void move(const sf::Vector2f& _distance);
	void setPosition(const sf::Vector2f& _pos);
};

