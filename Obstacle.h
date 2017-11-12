#pragma once
#include "GameObject.h"
class Obstacle : public GameObject {
	sf::RectangleShape m_shape;
	Physics::Collider m_collider;

	bool m_isStatic;
public:
	Obstacle(sf::Vector2f _size = sf::Vector2f(100.f, 100.f), sf::Vector2f _position = sf::Vector2f(0.f, 0.f));
	~Obstacle();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;

	virtual const bool isStatic() override;
	virtual std::vector<Physics::Collider*> const getColliders() override;
	virtual void setCollider(const Physics::Collider& _collider) override;

	virtual void move(const sf::Vector2f& _distance) override;
	virtual void collisionImpulse(const sf::Vector2f& _impulse) override;
};

