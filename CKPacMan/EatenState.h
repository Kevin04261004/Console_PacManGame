#pragma once
#include "BaseState.h"

class EatenState : public BaseState
{
public:
	EatenState(StateManager* InStateManager) : BaseState(InStateManager)
	{

	}
	virtual void Enter() override;
	virtual void Excute() override;
	virtual void Exit() override;
};

