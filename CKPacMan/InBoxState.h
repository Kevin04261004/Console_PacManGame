#pragma once
#include "BaseState.h"
class InBoxState : public BaseState
{
public:
	InBoxState(StateManager* InStateManager) : BaseState(InStateManager)
	{

	}
	virtual void Enter() override;
	virtual void Excute() override;
	virtual void Exit() override;
};

