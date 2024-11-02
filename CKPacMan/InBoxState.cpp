#include "InBoxState.h"
#include "StateManager.h"


void InBoxState::Enter()
{
	m_timer = 0.0f;
}

void InBoxState::Excute(float deltaTime)
{
	m_timer += deltaTime;

	if (m_timer > m_stopDuration)
	{
		m_timer = 0.0f;
		stateManager->ChangeState(EEnemyState::Hunter);
	}
}

void InBoxState::Exit()
{
}
