#include "HunterState.h"
#include "StateManager.h"

void HunterState::Enter()
{
}

void HunterState::Excute(float deltaTime)
{
	huntingTimer += deltaTime;

	if (huntingTimer > huntingTime)
	{
		huntingTimer = 0.0f;
		if (!bIsTargetFound)
		{
			// TODO: ������ point�� ��Ƽ� FindPath();
			
			// TODO: target�� ���� ���� �ִ��� ã��.

		}
		else
		{
			stateManager->GetOwner()->FindPath(EActorType::Player);
			stateManager->GetOwner()->SetNextDirection();
			stateManager->GetOwner()->Move();
		}
	}
}

void HunterState::Exit()
{
}
