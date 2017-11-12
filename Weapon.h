#pragma once
#include "GameObject.h"
class Weapon : public GameObject {
	// Visuals
	sf::RectangleShape m_shape;

	sf::Vector2f m_root;
private:
	void initShape();
public:
	Weapon();
	~Weapon();

	void setRoot(const sf::Vector2f& _root);

	// Inherited via GameObject
	virtual void input() override;

	virtual void update(float _dt) override;

	virtual void draw() override;

	virtual const bool isStatic() override;

	virtual std::vector<Physics::Collider *> const getColliders() override;

	virtual void setCollider(const Physics::Collider & _collider) override;

	virtual void move(const sf::Vector2f & _distance) override;

	virtual void collisionImpulse(const sf::Vector2f & _impulse) override;

};

