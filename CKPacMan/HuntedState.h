#pragma once
#include "BaseState.h"
class HuntedState : public BaseState
{
public:
	HuntedState(StateManager* InStateManager) : BaseState(InStateManager)
	{

	}
	virtual void Enter() override;
	virtual void Excute() override;
	virtual void Exit() override;
};

