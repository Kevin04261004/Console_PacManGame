#include "HuntedState.h"
#include "StateManager.h"

void HuntedState::Enter()
{
	elapsedTime = 0.0f;
	huntedDuration = 5.0f;
}

void HuntedState::Excute(float deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime > huntedDuration)
	{
		stateManager->ChangeState(EEnemyState::Hunter);
		return;
	}

	
}

void HuntedState::Exit()
{

}
