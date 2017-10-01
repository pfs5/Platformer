#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

namespace Util {
	// DEBUG OUTPUTS
	const bool DEBUG_MODE = true;

	inline void printMessage(const std::string& _s) {
		if (DEBUG_MODE)
			std::cerr << "> string : " <<_s << std::endl;
	}

	inline void printMessage(const float& _f) {
		if (DEBUG_MODE)
			std::cerr << "> float : " << _f << std::endl;
	}

	inline void printVector(const sf::Vector2f _v) {
		if (DEBUG_MODE) 
			std::cerr << "> vector2f : " << _v.x << " " << _v.y << std::endl;
	}

	inline void printVector(const sf::Vector2i _v) {
		if (DEBUG_MODE)
			std::cerr << "> vector2i : " << _v.x << " " << _v.y << std::endl;
	}

	// VECTOR OPERATIONS
	inline sf::Vector2f multiplyByValue(const sf::Vector2f& _v1, const sf::Vector2f& _v2) {
		return sf::Vector2f(_v1.x * _v2.x, _v1.y * _v2.y);
	}
}