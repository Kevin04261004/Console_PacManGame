#include "EatenState.h"
#include "StateManager.h"

void EatenState::Enter()
{
	stateManager->GetOwner()->GetSoundManager()->PlaySFXOneShoot(m_eaten_sfx_buffer);
	runTimer = 0.0f;
	stateManager->GetOwner()->FindPath(EActorType::InBox);

}

void EatenState::Excute(float deltaTime)
{
	runTimer += deltaTime;
	if (runTimer > runTime)
	{
		runTimer = 0.0f;
		stateManager->GetOwner()->SetNextDirection();
		stateManager->GetOwner()->Move();

		//if (!stateManager->GetOwner()->HasPath())
		//{
		//	stateManager->ChangeState(EEnemyState::InBox);
		//}
	}
}

void EatenState::Exit()
{

}
