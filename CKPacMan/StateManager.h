#pragma once
#include "BaseState.h"
#include "CKEnemy.h"
#include <map>

enum class EEnemyState : char
{
	Hunter,
	Hunted,
	Eaten,
	InBox,
};

class StateManager
{
private:
	std::map<EEnemyState, BaseState*> stateMap;

	EEnemyState CurrentStateType;

	class CKEnemy* parentEnemy;
public:
	StateManager(EEnemyState initState, class CKActor* actor);
	void ChangeState(EEnemyState state);
	void UpdateState(float deltaTime);
	EEnemyState GetCurrentStateType();
	inline CKEnemy* GetOwner() { return parentEnemy; }
};

