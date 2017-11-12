#include "stdafx.h"
#include "MainCharacter.h"
#include "Display.h"
#include "GameSettings.h"
#include "Util.h"
#include "InputManager.h"

void initShape(sf::RectangleShape& _shape) {
	sf::Vector2f size(40.f, 60.f);

	_shape.setSize(size);
	_shape.setFillColor(sf::Color::Transparent);
	_shape.setOutlineColor(sf::Color(0, 255, 0, 100));
	_shape.setOutlineThickness(1.f);

	sf::Vector2u windowSize = Display::getWindow().getSize();
	_shape.setOrigin(size / 2.f);
	sf::Vector2f position((float)windowSize.x / 2.f, 200.f);
	_shape.setPosition(0, 0);
}

MainCharacter::MainCharacter() : m_velocity(sf::Vector2f(0.f, 0.f)), m_isStatic(false), m_jumpCounter(0), m_jumped(false), m_isFacingRight(true), m_flying(false){
	initShape(m_shape);
	
	m_collider.gameObject = this;
	m_collider.width = m_shape.getSize().x;
	m_collider.height = m_shape.getSize().y;

	// TODO refactor animation loading
	// Init animator
	m_animationController.loadFromFile("data/main_character.animator");
	m_animationController.setPosition(m_shape.getPosition());

	m_effectsAnimationController.loadFromFile("data/main_character_effects.animator");
	m_effectsAnimationController.setPosition(m_shape.getPosition());

	m_position = m_shape.getPosition();

	// Init weapon
	m_weapon.setRoot(m_position);

	InputManager::getInstance()->attachObserver(this);
}


MainCharacter::~MainCharacter() {
}

void MainCharacter::input() {
	// Jump
	if (m_jumpCounter > 0 && m_jumped) {
		m_flying = true;
		m_velocity.y = -GameSettings::MAIN_CHARACTER_JUMP_POWER;
		if (m_jumpCounter > 1) {
			moveCharacter(sf::Vector2f(0.f, -GameSettings::MAIN_CHARACTER_JUMP_BOOST));
		}

		m_jumpCounter--;
		m_jumped = false;
	}
	
	if (!m_flying) {
		std::string animation = m_isFacingRight ? "IdleRight" : "IdleLeft";
		m_animationController.playAnimation(animation);
	} else {
		// In air
		if (m_dashed) {
			m_dashed = false;
			m_dashing = true;

			m_velocity.x = GameSettings::MAIN_CHARACTER_DASH_BOOST;
			m_velocity.x *= m_isFacingRight ? 1 : -1;

			std::string side = m_isFacingRight ? "Right" : "Left";
			m_animationController.playAnimation("Dash" + side);

			m_effectsAnimationController.setPosition(m_position);
			//m_effectsAnimationController.playAnimation("DashEffect" + side);
		} else if (!m_dashing){
			std::string animation = (m_velocity.y < 0.f) ? "Jump" : "Fall";
			std::string side = m_isFacingRight ? "Right" : "Left";
			m_animationController.playAnimation(animation + side);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveCharacter(sf::Vector2f(-GameSettings::MAIN_CHARACTER_SPEED, 0.f));
		if (!m_flying) {
			m_animationController.playAnimation("RunLeft");
		}
		m_isFacingRight = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveCharacter(sf::Vector2f(GameSettings::MAIN_CHARACTER_SPEED, 0.f));
		if (!m_flying) {
			m_animationController.playAnimation("RunRight");
		}
		m_isFacingRight = true;
	}

}

void MainCharacter::update(float _dt) {
	// Apply gravity
	m_velocity.y += GameSettings::GRAVITY * _dt;

	// Apply vertical air resistance
	m_velocity.x *= (1.f - GameSettings::AIR_RESISTANCE_HORIZONTAL);

	// Move 
	moveCharacter(m_velocity * _dt);
	m_light.setPosition(m_position);

	// Update animator
	m_animationController.update(_dt);
	m_effectsAnimationController.update(_dt);

	// Update weapon
	m_weapon.update(_dt);

	updateCollider();
}

void MainCharacter::draw() {
	// TODO Refactoring for light
	float lightScale = 0.5f * (float)m_jumpCounter - GameSettings::MAIN_CHARACTER_JUMP_LIGHT_FADE * (0.5f * (float)m_jumpCounter - 1.f);
	//m_light.setScale(lightScale);
	m_light.draw();

	m_animationController.draw();
	m_effectsAnimationController.draw();

	m_weapon.draw();

	//Display::draw(m_shape);		// collider
}

bool const MainCharacter::isStatic() {
	return m_isStatic;
}

 std::vector<Physics::Collider*> const MainCharacter::getColliders() {
	updateCollider();

	return std::vector<Physics::Collider*>({ &m_collider });
}

void MainCharacter::setCollider(const Physics::Collider & _collider) {
	m_collider = _collider;
	m_collider.gameObject = this;
}

void MainCharacter::move(const sf::Vector2f & _distance) {
	moveCharacter(_distance);
	updateCollider();
}

void MainCharacter::collisionImpulse(const sf::Vector2f & _impulse) {
	// Move out of collision
	moveCharacter(_impulse);

	updateCollider();

	// Collision response
	m_velocity = sf::Vector2f(0.f, 0.f);

	// Reset jump
	m_jumpCounter = GameSettings::MAIN_CHARACTER_JUMP_COUNT;
	m_flying = false;
	m_dashing = false;
}

const sf::Vector2f MainCharacter::getCenter() {
	return m_position + m_shape.getSize() / 2.f;
}

void MainCharacter::keyDown(sf::Keyboard::Key _key) {
	if (_key == sf::Keyboard::Space) {
		m_jumped = true;
	}

	if (_key == sf::Keyboard::LControl) {
		if (m_flying) {
			m_dashed = true;
		}
	}
}

void MainCharacter::moveCharacter(const sf::Vector2f & _distance) {
	m_position += _distance;

	m_shape.move(_distance);
	m_animationController.move(_distance);

	m_weapon.move(_distance);

	updateCollider();
}

void MainCharacter::updateCollider() {
	m_collider.x = m_position.x - m_collider.width / 2.f;
	m_collider.y = m_position.y - m_collider.height / 2.f;
}
