#pragma once
#include "BaseState.h"

class HunterState : public BaseState
{
protected:
	class CKActor* target;
	float huntingTime;
	float timer;

public:
	HunterState(StateManager* InStateManager) : BaseState(InStateManager)
	{
		target = nullptr;
		huntingTime = 0.3f;
		timer = 0.0f;
	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

