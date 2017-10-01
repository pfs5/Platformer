#include "stdafx.h"
#include "SpotLight.h"
#include "Util.h"
#include "Display.h"

SpotLight::SpotLight() {
	std::string path = ROOT_FOLDER + "light_source" + ".png";
	if (!m_texture.loadFromFile(path)) {
		Util::printMessage("[SpotLight] Error loading texture from " + path);
		return;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2.f, m_texture.getSize().y / 2.f);
}


SpotLight::~SpotLight() {

}

void SpotLight::draw() {
	Display::draw(m_sprite);
}

void SpotLight::setPosition(const sf::Vector2f & _position) {
	m_sprite.setPosition(_position);
}

void SpotLight::setScale(float _scale) {
	m_sprite.setScale(_scale, _scale);
}
