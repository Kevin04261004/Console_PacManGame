#include "HunterState.h"
#include "StateManager.h"

void HunterState::Enter()
{
	bIsTargetFound = false;
	timer = 0.0f;
	stateManager->GetOwner()->FindRandomPointAndPath();
}

void HunterState::Excute(float deltaTime)
{
	timer += deltaTime;
	
	bIsTargetFound = stateManager->GetOwner()->IsPlayerInRange(100);

	if (!bIsTargetFound && timer > chasingTime)
	{
		timer = 0.0f;
		if (!stateManager->GetOwner()->HasPath())
		{
			stateManager->GetOwner()->FindRandomPointAndPath();
		}
		stateManager->GetOwner()->SetNextDirection();
		stateManager->GetOwner()->Move();
	}
	
	if (bIsTargetFound && timer > huntingTime)
	{
		timer = 0.0f;
		stateManager->GetOwner()->FindPath(EActorType::Player);
		stateManager->GetOwner()->SetNextDirection();
		stateManager->GetOwner()->Move();
	}

	if (stateManager->GetGM()->IsPowerTime())
	{
		stateManager->ChangeState(EEnemyState::Hunted);
	}
}

void HunterState::Exit()
{
}
