#pragma once
#include "BaseState.h"
class HuntedState : public BaseState
{
protected:
	float huntedDuration;
	float elapsedTime;

public:
	HuntedState(StateManager* InStateManager) : BaseState(InStateManager)
	{

	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

