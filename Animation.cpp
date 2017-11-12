#include "stdafx.h"
#include "Animation.h"
#include "Util.h"
#include "Display.h"
#include "GameSettings.h"

Animation::Animation() {
}

void fillVector(std::vector<int>& _v, const int _array[], int _arraySize) {
	for (int i = 0; i < _arraySize; ++i) {
		_v.push_back(_array[i] * GameSettings::MAIN_CHARACTER_ANIMATION_MULTIPLIER);
	}
}

Animation::Animation(std::string _name, int _frames[], int _frameNumber, bool _loop) : m_currentFrame(0), m_loop(_loop), m_playing(true) {
	if (!m_texture.loadFromFile(ROOT_FOLDER + _name)) {
		Util::printMessage("[Animation] Error loading animation " + _name);
		return;
	}

	m_frameSize = m_texture.getSize();
	m_frameSize.x /= _frameNumber;

	fillVector(m_frames, _frames, _frameNumber);
	fillVector(m_activeFrames, _frames, _frameNumber);

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));

	m_sprite.setOrigin(m_frameSize.x / 2.f, m_frameSize.y / 2.f);
	m_sprite.setScale(0.5f, 0.5f);
}


Animation::~Animation() {
}

void Animation::draw() {
	Display::draw(m_sprite);
}

void Animation::update(float _dt) {
	if (!m_playing) {
		return;
	}

	if (m_activeFrames[m_currentFrame] == 1) {
		m_activeFrames[m_currentFrame] = m_frames[m_currentFrame];
		
		if (m_currentFrame == m_frames.size() - 1 && !m_loop) {
			m_playing = false;
		}

		m_currentFrame = (m_currentFrame + 1) % m_frames.size();

		m_sprite.setTextureRect(sf::IntRect(m_frameSize.x * m_currentFrame, 0, m_frameSize.x, m_frameSize.y));
	} else {
		m_activeFrames[m_currentFrame]--;
	}
}

void Animation::reset() {
	m_currentFrame = 0;
	m_playing = true;
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));
}

bool Animation::isLooping() {
	return m_loop;
}

void Animation::move(const sf::Vector2f& _distance) {
	m_sprite.move(_distance);
}

void Animation::setPosition(const sf::Vector2f& _pos) {
	m_sprite.setPosition(_pos);
}
