#include "stdafx.h"
#include "BackgroundImage.h"
#include "Util.h"
#include "Display.h"

BackgroundImage::BackgroundImage() {
}


BackgroundImage::~BackgroundImage() {
}

void BackgroundImage::load(const std::string& _name) {
	std::string path = ROOT_FOLDER + _name + ".png";
	if (!m_texture.loadFromFile(path)) {
		Util::printMessage("[BackgroundImage] Error loading texture from " + path);
		return;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(1.f, 1.f);
}

sf::Drawable* const BackgroundImage::getDrawable() {
	return &m_sprite;
}

const sf::Vector2u & BackgroundImage::getSize() {
	return m_texture.getSize();
}
