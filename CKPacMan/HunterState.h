#pragma once
#include "BaseState.h"

class HunterState : public BaseState
{
protected:
	bool bIsTargetFound;
	float huntingTime;
	float chasingTime;
	float timer;

public:
	HunterState(StateManager* InStateManager) : BaseState(InStateManager)
	{
		bIsTargetFound = false;
		huntingTime = 0.15f;
		chasingTime = 0.3f;
		timer = 0.0f;
	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

