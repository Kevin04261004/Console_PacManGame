#pragma once

class BaseState
{
protected:
	class StateManager* stateManager;

public:
	BaseState(StateManager* InStateManager)
	{
		stateManager = InStateManager;
	}
	virtual void Enter() = 0;
	virtual void Excute() = 0;
	virtual void Exit() = 0;
};

