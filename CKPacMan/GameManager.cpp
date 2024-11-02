#include "GameManager.h"

void GameManager::SetPowerTime()
{
	bIsPowerTime = true;
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
			powerTimer = 0.0f;
		}
	}
}
