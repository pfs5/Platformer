#pragma once
#include "PhysicsEngine.h"
#include <SFML\Graphics.hpp>

namespace Physics {
	struct Collider;
};

class GameObject {
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void input() = 0;
	virtual void update(float _dt) = 0;
	virtual void draw() = 0;

	virtual const bool isStatic() = 0;
	virtual std::vector<Physics::Collider*> const getColliders() = 0;
	virtual void setCollider(const Physics::Collider& _collider) = 0;

	virtual void move(const sf::Vector2f& _distance) = 0;
	virtual void collisionImpulse(const sf::Vector2f& _impulse) = 0;
};

