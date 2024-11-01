#include "StateManager.h"
#include "HuntedState.h"
#include "HunterState.h"
#include "EatenState.h"
#include "InBoxState.h"
#include "CKEnemy.h"

StateManager::StateManager(EEnemyState initState, CKActor* parent)
{
	m_stateMap.insert({ EEnemyState::Hunter, new HunterState(this) });
	m_stateMap.insert({ EEnemyState::Hunted, new HuntedState(this) });
	m_stateMap.insert({ EEnemyState::InBox, new InBoxState(this) });
	m_stateMap.insert({ EEnemyState::Eaten, new EatenState(this) });

	parentEnemy = static_cast<CKEnemy*>(parent);

	CurrentStateType = initState;
	m_stateMap[CurrentStateType]->Enter();
}

void StateManager::UpdateState(float deltaTime)
{
	m_stateMap[CurrentStateType]->Excute(deltaTime);
}

EEnemyState StateManager::GetCurrentStateType()
{
	return CurrentStateType;
}

void StateManager::ChangeState(EEnemyState state)
{
	m_stateMap[CurrentStateType]->Exit();
	CurrentStateType = state;
	m_stateMap[CurrentStateType]->Enter();
}
