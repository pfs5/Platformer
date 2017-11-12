#include "stdafx.h"
#include "Obstacle.h"
#include "Display.h"
#include "Util.h"

Obstacle::Obstacle(sf::Vector2f _size, sf::Vector2f _position) : m_isStatic(true){
	m_shape.setSize(_size);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(1.f);
	m_shape.setPosition(_position);

	m_collider.gameObject = this;
	m_collider.width = m_shape.getSize().x;
	m_collider.height = m_shape.getSize().y;
}

Obstacle::~Obstacle() {
}

void Obstacle::input() {
}

void Obstacle::update(float _dt) {
}

void Obstacle::draw() {
	Display::draw(m_shape);
}

const bool Obstacle::isStatic() {
	return m_isStatic;
}

std::vector<Physics::Collider *> const Obstacle::getColliders() {
	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;

	return std::vector<Physics::Collider*>({ &m_collider });
}

void Obstacle::setCollider(const Physics::Collider & _collider) {
	m_collider = _collider;
	m_collider.gameObject = this;
}

void Obstacle::move(const sf::Vector2f & _distance) {
	m_shape.move(_distance);
}

void Obstacle::collisionImpulse(const sf::Vector2f & _impulse) {
}
