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
	std::map<EEnemyState, BaseState*> m_stateMap;

	EEnemyState m_CurrentStateType;

	class CKEnemy* m_parentEnemy;
	
	GameManager* m_gameManager;
public:
	StateManager(EEnemyState initState, class CKActor* actor, GameManager* gm);
	void ChangeState(EEnemyState state);
	void UpdateState(float deltaTime);
	const EEnemyState& const GetCurrentStateType();
	inline CKEnemy* GetOwner() { return m_parentEnemy; }
	inline GameManager* GetGM() { return m_gameManager; }
};

