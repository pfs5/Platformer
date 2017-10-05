#include "stdafx.h"
#include "Animation.h"
#include "Util.h"
#include "Display.h"

Animation::Animation() {
}

Animation::Animation(std::string _name, int _frames[], int _frameNumber) : m_currentFrame(0){
	if (!m_texture.loadFromFile(ROOT_FOLDER + _name)) {
		Util::printMessage("[Animation] Error loading animation " + _name);
		return;
	}

	m_frameSize = m_texture.getSize();
	m_frameSize.x /= _frameNumber;

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));
	m_sprite.setScale(0.5f, 0.5f);
}


Animation::~Animation() {
}

void Animation::draw() {
	Display::draw(m_sprite);
}

void Animation::update(float _dt) {
	// TODO
}

void Animation::move(const sf::Vector2f& _distance) {
	m_sprite.move(_distance);
}

void Animation::setPosition(const sf::Vector2f& _pos) {
	m_sprite.setPosition(_pos);
}
