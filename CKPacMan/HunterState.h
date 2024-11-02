#pragma once
#include "BaseState.h"

class HunterState : public BaseState
{
protected:
	bool bIsTargetFound;
	float huntingTime;
	float huntingTimer;

public:
	HunterState(StateManager* InStateManager) : BaseState(InStateManager)
	{
		bIsTargetFound = true;
		huntingTime = 0.15f;
		huntingTimer = 0.0f;
	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

