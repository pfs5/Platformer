#include "stdafx.h"
#include "MainCharacter.h"
#include "Display.h"
#include "GameSettings.h"
#include "Util.h"
#include "InputManager.h"

void initShape(sf::RectangleShape& _shape) {
	sf::Vector2f size(28.f, 63.f);

	_shape.setSize(size);
	_shape.setFillColor(sf::Color::Transparent);
	_shape.setOutlineColor(sf::Color(0, 255, 0, 100));
	_shape.setOutlineThickness(1.f);

	sf::Vector2u windowSize = Display::getWindow().getSize();
	sf::Vector2f position((float)windowSize.x / 2.f - size.x / 2.f, 200.f);
	_shape.setPosition(position);
}

MainCharacter::MainCharacter() : m_velocity(sf::Vector2f(0.f, 0.f)), m_isStatic(false), m_jumpCounter(0), m_jumped(false) {
	initShape(m_shape);
	
	m_collider.gameObject = this;
	m_collider.width = m_shape.getSize().x;
	m_collider.height = m_shape.getSize().y;

	// TODO refactor animation loading
	// Init animator
	m_animationController.loadFromFile("data/main_character.animator");
	m_animationController.setPosition(m_shape.getPosition());

	m_position = m_shape.getPosition();

	InputManager::getInstance()->attachObserver(this);
}


MainCharacter::~MainCharacter() {
}

void MainCharacter::input() {
	// Jump
	if (m_jumpCounter > 0 && m_jumped) {
		m_velocity.y = -GameSettings::MAIN_CHARACTER_JUMP_POWER;
		if (m_jumpCounter > 1) {
			moveCharacter(sf::Vector2f(0.f, -GameSettings::MAIN_CHARACTER_JUMP_BOOST));
		}

		m_jumpCounter--;
		m_jumped = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveCharacter(sf::Vector2f(-GameSettings::MAIN_CHARACTER_SPEED, 0.f));
		m_animationController.playAnimation("IdleLeft");
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveCharacter(sf::Vector2f(GameSettings::MAIN_CHARACTER_SPEED, 0.f));
		m_animationController.playAnimation("IdleRight");
	}
}

void MainCharacter::update(float _dt) {
	// Apply gravity
	m_velocity.y += GameSettings::GRAVITY * _dt;

	// Move 
	moveCharacter(m_velocity * _dt);
	m_light.setPosition(getCenter());

	// Update animator
	m_animationController.update(_dt);

	updateCollider();
}

void MainCharacter::draw() {
	// TODO Refactoring for light
	//float lightScale = 0.5f * (float)m_jumpCounter - GameSettings::MAIN_CHARACTER_JUMP_LIGHT_FADE * (0.5f * (float)m_jumpCounter - 1.f);
	//m_light.setScale(lightScale);
	//m_light.draw();

	m_animationController.draw();
	Display::draw(m_shape);
}

bool const MainCharacter::isStatic() {
	return m_isStatic;
}

Physics::Collider * const MainCharacter::getCollider() {
	updateCollider();

	return &m_collider;
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
}

const sf::Vector2f MainCharacter::getCenter() {
	return m_position + m_shape.getSize() / 2.f;
}

void MainCharacter::keyDown(sf::Keyboard::Key _key) {
	if (_key == sf::Keyboard::Space) {
		m_jumped = true;
	}
}

void MainCharacter::moveCharacter(const sf::Vector2f & _distance) {
	m_position += _distance;

	m_shape.move(_distance);
	m_animationController.move(_distance);

	updateCollider();
}

void MainCharacter::updateCollider() {
	m_collider.x = m_position.x;
	m_collider.y = m_position.y;
}
