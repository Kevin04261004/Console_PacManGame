#pragma once
#include "BaseState.h"
class HuntedState : public BaseState
{
protected:
	float huntedDuration;
	float elapsedTimer;

	float runTime;
	float runTimer;

public:
	HuntedState(StateManager* InStateManager) : BaseState(InStateManager)
	{
		elapsedTimer = 0.0f;
		huntedDuration = 20.0f;

		runTime = 0.5f;
		runTimer = 0.0f;
	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

