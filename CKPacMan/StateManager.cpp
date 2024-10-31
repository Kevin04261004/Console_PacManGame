#include "StateManager.h"
#include "HuntedState.h"
#include "HunterState.h"
#include "EatenState.h"
#include "InBoxState.h"
#include "CKEnemy.h"

StateManager::StateManager(EEnemyState initState, CKActor* parent)
{
	stateMap.insert({ EEnemyState::Hunter, new HunterState(this) });
	stateMap.insert({ EEnemyState::Hunted, new HuntedState(this) });
	stateMap.insert({ EEnemyState::InBox, new InBoxState(this) });
	stateMap.insert({ EEnemyState::Eaten, new EatenState(this) });

	parentEnemy = static_cast<CKEnemy*>(parent);

	CurrentStateType = initState;
}

void StateManager::UpdateState()
{
	stateMap[CurrentStateType]->Excute();
}

EEnemyState StateManager::GetCurrentStateType()
{
	return CurrentStateType;
}

void StateManager::ChangeState(EEnemyState state)
{
	stateMap[CurrentStateType]->Exit();
	CurrentStateType = state;
	stateMap[CurrentStateType]->Enter();
}
