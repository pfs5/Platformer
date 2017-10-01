#include "stdafx.h"
#include "MainCharacter.h"
#include "Display.h"
#include "GameSettings.h"
#include "Util.h"
#include "InputManager.h"

void initShape(sf::RectangleShape& _shape) {
	sf::Vector2f size(30.f, 30.f);

	_shape.setSize(size);
	_shape.setFillColor(sf::Color::Red);

	sf::Vector2u windowSize = Display::getWindow().getSize();
	sf::Vector2f position((float)windowSize.x / 2.f - size.x / 2.f, 200.f);
	_shape.setPosition(position);
}

MainCharacter::MainCharacter() : m_velocity(sf::Vector2f(0.f, 0.f)), m_isStatic(false), m_jumpCounter(0), m_jumped(false) {
	initShape(m_shape);
	
	m_collider.gameObject = this;
	m_collider.width = m_shape.getSize().x;
	m_collider.height = m_shape.getSize().y;

	InputManager::getInstance()->attachObserver(this);
}


MainCharacter::~MainCharacter() {
}

void MainCharacter::input() {
	// Jump
	if (m_jumpCounter > 0 && m_jumped) {
		m_velocity.y = -GameSettings::MAIN_CHARACTER_JUMP_POWER;
		if (m_jumpCounter > 1) {
			m_shape.move(0.f, -GameSettings::MAIN_CHARACTER_JUMP_BOOST);
		}

		m_jumpCounter--;
		m_jumped = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_shape.setPosition(m_shape.getPosition() + sf::Vector2f(-GameSettings::MAIN_CHARACTER_SPEED, 0.f));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_shape.setPosition(m_shape.getPosition() + sf::Vector2f(GameSettings::MAIN_CHARACTER_SPEED, 0.f));
	}
}

void MainCharacter::update(float _dt) {
	// Update collider
	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;

	// Apply gravity
	m_velocity.y += GameSettings::GRAVITY * _dt;

	// Move 
	m_shape.move(m_velocity * _dt);
	m_light.setPosition(getCenter());
}

void MainCharacter::draw() {
	float lightScale = 0.5f * (float)m_jumpCounter - GameSettings::MAIN_CHARACTER_JUMP_LIGHT_FADE * (0.5f * (float)m_jumpCounter - 1.f);
	m_light.setScale(lightScale);
	m_light.draw();

	Display::draw(m_shape);
}

bool const MainCharacter::isStatic() {
	return m_isStatic;
}

Physics::Collider * const MainCharacter::getCollider() {
	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;

	return &m_collider;
}

void MainCharacter::setCollider(const Physics::Collider & _collider) {
	m_collider = _collider;
	m_collider.gameObject = this;
}

void MainCharacter::move(const sf::Vector2f & _distance) {
	m_shape.move(_distance);

	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;
}

void MainCharacter::collisionImpulse(const sf::Vector2f & _impulse) {
	// Move out of collision
	m_shape.move(_impulse);

	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;

	// Collision response
	m_velocity = sf::Vector2f(0.f, 0.f);

	// Reset jump
	m_jumpCounter = GameSettings::MAIN_CHARACTER_JUMP_COUNT;
}

const sf::Vector2f MainCharacter::getCenter() {
	return m_shape.getPosition() + m_shape.getSize() / 2.f;
}

void MainCharacter::keyDown(sf::Keyboard::Key _key) {
	if (_key == sf::Keyboard::Space) {
		m_jumped = true;
	}
}
