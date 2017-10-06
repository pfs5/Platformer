#pragma once

#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "PhysicsEngine.h"
#include "InputObserver.h"
#include "SpotLight.h"
#include "AnimationController.h"

class MainCharacter : public GameObject, InputObserver{
	// Visuals
	sf::RectangleShape m_shape;
	AnimationController m_animationController;
	SpotLight m_light;

	// Physics
	sf::Vector2f m_position;
	Physics::Collider m_collider;
	sf::Vector2f m_velocity;

	bool m_isStatic;

	// Game
	int m_jumpCounter;
	bool m_jumped;

public:
	MainCharacter();
	~MainCharacter();

	// GameObject methods
	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;

	virtual const bool isStatic() override;
	virtual Physics::Collider* const getCollider() override;
	virtual void setCollider(const Physics::Collider& _collider) override;

	virtual void move(const sf::Vector2f& _distance) override;
	virtual void collisionImpulse(const sf::Vector2f& _impulse) override;

	const sf::Vector2f getCenter();

	// Observer
	virtual void keyDown(sf::Keyboard::Key _key) override;

private:
	void moveCharacter(const sf::Vector2f& _distance);
	void updateCollider();
};

