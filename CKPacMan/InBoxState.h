#pragma once
#include "BaseState.h"
class InBoxState : public BaseState
{
private:
	float m_timer;
	float m_stopDuration;

public:
	InBoxState(StateManager* InStateManager) : BaseState(InStateManager)
	{
		m_timer = 0.0f;
		m_stopDuration = 3.f;
	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

