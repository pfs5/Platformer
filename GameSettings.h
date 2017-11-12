#pragma once

namespace GameSettings {
	const bool PRINT_FPS = false;

	const float MAIN_CHARACTER_SPEED = 3.f;
	const int MAIN_CHARACTER_ANIMATION_MULTIPLIER = 5;
	const float MAIN_CHARACTER_JUMP_POWER = 800.f;
	const float MAIN_CHARACTER_JUMP_BOOST = 20.f;
	const int MAIN_CHARACTER_JUMP_COUNT = 2;

	const float MAIN_CHARACTER_DASH_BOOST = 600.f;

	const float MAIN_CHARACTER_JUMP_LIGHT_FADE = 0.6;

	constexpr float GRAVITY = 9.81f * 200.f;

	const float AIR_RESISTANCE_HORIZONTAL = 0.01f;
}