#include "stdafx.h"
#include "AnimationController.h"
#include "Util.h"
#include <iostream>
#include <fstream>

AnimationController::AnimationController() : m_currentAnimation (0){
}


AnimationController::~AnimationController() {
	for (int i = 0; i < m_animations.size(); i++) {
		delete m_animations[i];
	}
}

std::vector<std::string> split(std::string _s, std::string _delimiter) {
	std::vector<std::string> data;
	size_t pos = 0;
	std::string token;

	while ((pos = _s.find(_delimiter)) != std::string::npos) {
		token = _s.substr(0, pos);
		data.push_back(token);
		_s.erase(0, pos + _delimiter.length());
	}
	data.push_back(_s);
	
	return data;
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
			std::vector <std::string> data = split(line.substr(2, line.length() + 1), " ");
			int *frames = new int[data.size() - 2];
			for (int i = 0; i < data.size() - 2; ++i) {
				frames[i] = std::stoi(data[i + 2]);
			}
			addAnimation(new Animation(data[1], frames, data.size() - 2), data[0]);

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

