#pragma once
#include "GameState.h"
#include "Level.h"
#include "MainCharacter.h"
#include "PhysicsEngine.h"

class PlayState : public GameState {
	Physics::PhysicsEngine m_engine;

	Level m_level;
	MainCharacter m_mainCharacter;
	std::vector<GameObject*> m_gameObjects;

	sf::View m_view;
	float m_initViewCenterY;

public:
	PlayState();
	~PlayState();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;

private:
	void initTestEnvironment();
};

