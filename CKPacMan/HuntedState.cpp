#include "HuntedState.h"
#include "StateManager.h"

void HuntedState::Enter()
{
	elapsedTimer = 0.0f;
	runTimer = 0.0f;
}

void HuntedState::Excute(float deltaTime)
{
	elapsedTimer += deltaTime;
	if (elapsedTimer > huntedDuration)
	{
		elapsedTimer = 0.0f;
		stateManager->ChangeState(EEnemyState::Hunter);
		return;
	}

	runTimer += deltaTime;
	if (runTimer > runTime)
	{
		runTimer = 0.0f;
		stateManager->GetOwner()->FindPath(EActorType::Player);
		stateManager->GetOwner()->SetReverseNextDirection();
		stateManager->GetOwner()->Move();
	}

	if (!stateManager->GetGM()->IsPowerTime())
	{
		stateManager->ChangeState(EEnemyState::Hunter);
	}
}

void HuntedState::Exit()
{

}
