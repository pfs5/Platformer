#include "stdafx.h"
#include "DummyObject.h"
#include "Display.h"
#include "Util.h"
#include <SFML\Graphics.hpp>

void initShape(sf::RectangleShape& _shape, const sf::Vector2f _size, const sf::Color _color) {
	_shape.setSize(_size);
	_shape.setFillColor(_color);
	_shape.setPosition(sf::Vector2f(200.f, 200.f));
}

DummyObject::DummyObject(sf::Vector2f _size, sf::Color _color) {
	initShape(m_shape, _size, _color);

	m_collider.gameObject = this;
	m_collider.width = m_shape.getSize().x;
	m_collider.height = m_shape.getSize().y;
}


DummyObject::~DummyObject() {
}

void DummyObject::input() {
	sf::Vector2i mousePos = sf::Mouse::getPosition(Display::getWindow());
	m_shape.setPosition(mousePos.x, mousePos.y);
}

void DummyObject::update(float _dt) {
	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;
}

void DummyObject::draw() {
	Display::draw(m_shape);
}

const bool DummyObject::isStatic() {
	return false;
}

Physics::Collider * const DummyObject::getCollider() {
	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;

	return &m_collider;
}

void DummyObject::setCollider(const Physics::Collider & _collider) {
	m_collider = _collider;
	m_collider.gameObject = this;
}

void DummyObject::move(const sf::Vector2f & _distance) {
	m_shape.move(_distance);

	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;
}

void DummyObject::collisionImpulse(const sf::Vector2f & _impulse) {
	// Move out of collision
	m_shape.move(_impulse);

	m_collider.x = m_shape.getPosition().x;
	m_collider.y = m_shape.getPosition().y;
}
