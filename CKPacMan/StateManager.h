#pragma once
#include "BaseState.h"
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
	void ChangeState(EEnemyState state);

	class CKEnemy* parentEnemy;
public:
	StateManager(EEnemyState initState, class CKActor* actor);

	void UpdateState();
	EEnemyState GetCurrentStateType();
};

