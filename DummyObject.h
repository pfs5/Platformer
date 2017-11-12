#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include <vector>

class DummyObject : public GameObject {
	sf::RectangleShape m_shape;
	Physics::Collider m_collider;
public:
	DummyObject(sf::Vector2f _size = sf::Vector2f(50.f, 50.f), sf::Color _color = sf::Color::Yellow);
	~DummyObject();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;

	virtual const bool isStatic() override;
	virtual std::vector<Physics::Collider*> const getColliders() override;
	virtual void setCollider(const Physics::Collider& _collider) override;

	virtual void move(const sf::Vector2f& _distance) override;
	virtual void collisionImpulse(const sf::Vector2f& _impulse) override;
};

