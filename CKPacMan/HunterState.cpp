#include "HunterState.h"
#include "StateManager.h"
void HunterState::Enter()
{
}

void HunterState::Excute(float deltaTime)
{
	timer += deltaTime;
	if (timer > huntingTime)
	{
		if (target == nullptr)
		{
			// TODO: ������ point�� ��Ƽ� FindPath();

			// TODO: target�� ���� ���� �ִ��� ã��.

		}
		else
		{
			stateManager->GetOwner()->FindPath(EActorType::Player);
		}
	}
}

void HunterState::Exit()
{
}
