#pragma once
#include "GameState.h"
#include "Application.h"

class DefaultState : public GameState {
	Application& m_app;
public:
	DefaultState(Application& _app);
	~DefaultState();

	virtual void input() override;
	virtual void update(float _dt) override;
	virtual void draw() override;
};

