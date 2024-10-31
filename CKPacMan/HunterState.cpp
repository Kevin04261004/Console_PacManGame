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
			// TODO: 랜덤한 point를 잡아서 FindPath();

			// TODO: target이 범위 내에 있는지 찾기.

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
