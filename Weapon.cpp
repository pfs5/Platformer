#include "stdafx.h"
#include "Weapon.h"
#include "Display.h"

void Weapon::initShape() {
	m_shape.setSize(sf::Vector2f(20.f, 20.f));
	m_shape.setOutlineColor(sf::Color::Green);
	m_shape.setOutlineThickness(1.f);
}

Weapon::Weapon() {
	initShape();
}


Weapon::~Weapon() {
}

void Weapon::setRoot(const sf::Vector2f & _root) {
	m_root = _root;
}

void Weapon::input() {
}

void Weapon::update(float _dt) {
}

void Weapon::draw() {
	m_shape.setPosition(m_root);
	Display::draw(m_shape);
}

const bool Weapon::isStatic() {
	return false;
}

std::vector<Physics::Collider*> const Weapon::getColliders() {
	return {};
}

void Weapon::setCollider(const Physics::Collider & _collider) {
}

void Weapon::move(const sf::Vector2f & _distance) {
	m_root += _distance;
}

void Weapon::collisionImpulse(const sf::Vector2f & _impulse) {
}
