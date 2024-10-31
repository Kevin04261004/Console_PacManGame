#pragma once
#include "BaseState.h"

class HunterState : public BaseState
{
public:
	HunterState(StateManager* InStateManager) : BaseState(InStateManager)
	{

	}
	virtual void Enter() override;
	virtual void Excute() override;
	virtual void Exit() override;
};

