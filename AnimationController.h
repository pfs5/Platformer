#pragma once
#include "Animation.h"
class AnimationController {
	std::vector<Animation*> m_animations;
	int m_currentAnimation;
public:
	AnimationController();
	~AnimationController();

	void addAnimation(Animation* _a);

	void draw();
	void update(float _dt);

	void move(const sf::Vector2f& _distance);
	void setPosition(const sf::Vector2f& _pos);
};

