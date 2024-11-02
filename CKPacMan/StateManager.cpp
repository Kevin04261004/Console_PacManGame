#include "StateManager.h"
#include "HuntedState.h"
#include "HunterState.h"
#include "EatenState.h"
#include "InBoxState.h"
#include "CKEnemy.h"

StateManager::StateManager(EEnemyState initState, CKActor* parent, GameManager* gm)
{
	m_stateMap.insert({ EEnemyState::Hunter, new HunterState(this) });
	m_stateMap.insert({ EEnemyState::Hunted, new HuntedState(this) });
	m_stateMap.insert({ EEnemyState::InBox, new InBoxState(this) });
	m_stateMap.insert({ EEnemyState::Eaten, new EatenState(this) });

	m_parentEnemy = static_cast<CKEnemy*>(parent);

	m_CurrentStateType = initState;
	m_stateMap[m_CurrentStateType]->Enter();

	m_gameManager = gm;
}

void StateManager::UpdateState(float deltaTime)
{
	m_stateMap[m_CurrentStateType]->Excute(deltaTime);
}

const EEnemyState& const StateManager::GetCurrentStateType()
{
	return m_CurrentStateType;
}

void StateManager::ChangeState(EEnemyState state)
{
	m_stateMap[m_CurrentStateType]->Exit();
	m_CurrentStateType = state;
	m_stateMap[m_CurrentStateType]->Enter();
}
