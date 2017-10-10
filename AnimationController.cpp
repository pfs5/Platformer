#include "stdafx.h"
#include "AnimationController.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <string>

AnimationController::AnimationController() : m_currentAnimation (0){
}


AnimationController::~AnimationController() {
	for (int i = 0; i < m_animations.size(); i++) {
		delete m_animations[i];
	}
}

void AnimationController::loadFromFile(const std::string & _path) {
	std::string line;
	std::ifstream file(_path);
	
	if (!file.is_open()) {
		Util::printMessage("[AnimationController] Error loading controller from " + _path);
		return;
	}

	while (std::getline(file, line)) {
		// Starting animation
		if (line[0] == 'S') {
			std::string data = line.substr(2, line.length());
			m_currentAnimation = std::stoi(data);
		}

		// Comment
		if (line[0] == '#') {
			continue;
		}

		// Animation
		if (line[0] == 'A') {
			std::vector <std::string> data = Util::split(line.substr(2, line.length() + 1), " ");
			int *frames = new int[data.size() - 3];
			for (int i = 0; i < data.size() - 3; ++i) {
				frames[i] = std::stoi(data[i + 3]);
			}
			bool looping = (data[1].compare(std::string("loop")) == 0);
			addAnimation(new Animation(data[2], frames, data.size() - 3, true), data[0]);

			delete[] frames;
		}
	}

	file.close();
}

void AnimationController::addAnimation(Animation * _a, const std::string& _animationName) {
	m_animations.push_back(_a);
	m_animationNames.emplace(_animationName, m_animations.size() - 1);
}

void AnimationController::playAnimation(std::string _animationName) {
	if (m_animationNames.find(_animationName) != m_animationNames.end()) {
		m_currentAnimation = m_animationNames.at(_animationName);
		if (!m_animations[m_currentAnimation]->isLooping()) {
			m_animations[m_currentAnimation]->reset();
		}
	}
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

