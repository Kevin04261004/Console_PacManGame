#pragma once
#include "BaseState.h"

class HunterState : public BaseState
{
protected:
	class CKActor* target;

public:
	HunterState(StateManager* InStateManager) : BaseState(InStateManager)
	{
		target = nullptr;
	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

