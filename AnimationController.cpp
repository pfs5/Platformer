#include "stdafx.h"
#include "AnimationController.h"


AnimationController::AnimationController() : m_currentAnimation (0){
}


AnimationController::~AnimationController() {
	for (int i = 0; i < m_animations.size(); i++) {
		delete m_animations[i];
	}
}

void AnimationController::addAnimation(Animation * _a) {
	m_animations.push_back(_a);
}

void AnimationController::draw() {
	if (m_animations.size() > 0) {
		m_animations[m_currentAnimation]->draw();
	}
}

void AnimationController::update(float _dt) {
	if (m_animations.size() > 0) {
		m_animations[m_currentAnimation]->update(_dt);
	}
}

void AnimationController::move(const sf::Vector2f& _distance) {
	for (int i = 0; i < m_animations.size(); i++) {
		m_animations[i]->move(_distance);
	}
}

void AnimationController::setPosition(const sf::Vector2f& _pos) {
	for (int i = 0; i < m_animations.size(); i++) {
		m_animations[i]->setPosition(_pos);
	}
}

