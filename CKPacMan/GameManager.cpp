#include "GameManager.h"

void GameManager::SetPowerTime()
{
	bIsPowerTime = true;
	m_soundManager->PlayBGM(m_powerTime_bgm_buffer);
	powerTimer = 0.0f;
}

void GameManager::Update(float deltaTime)
{
	if (bIsPowerTime)
	{
		powerTimer += deltaTime;
		if (powerTimer > powerDuration)
		{
			bIsPowerTime = false;
			m_soundManager->PlayBGM(m_siren0_bgm_buffer);
			powerTimer = 0.0f;
		}
	}
}
