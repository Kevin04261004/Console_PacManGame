#include "GameManager.h"

void GameManager::SetPowerTime()
{
	bIsPowerTime = true;
	m_soundManager->PlayBGM(m_powerTime_bgm_buffer);
	powerTimer = 0.0f;
}

void GameManager::Update(float deltaTime)
{
	if (m_gameType == EGameType::Ready)
	{
		gameTimer -= deltaTime;
		if (gameTimer <= 0.0f)
		{
			m_gameType = EGameType::InGame;
			m_soundManager->PlayBGM(m_siren0_bgm_buffer);
		}
	}
	if (m_gameType == EGameType::GameOver)
	{
		gameTimer -= deltaTime;
		if (gameTimer <= 0.0f)
		{
			exit(1);
		}
	}
	if (m_gameType == EGameType::GameWin)
	{
		gameTimer -= deltaTime;
		if (gameTimer <= 0.0f)
		{
			exit(1);
		}
	}
	if (bIsPowerTime)
	{
		powerTimer += deltaTime;
		if (powerTimer > powerDuration)
		{
			bIsPowerTime = false;
			UpdateBGM();
			powerTimer = 0.0f;
		}
	}
}

void GameManager::GameOver()
{
	gameTimer = 4.f;
	m_soundManager->PlayBGM(m_died_bgm_buffer);
	m_gameType = EGameType::GameOver;
}

void GameManager::UpdatePoint()
{
	int pelletQuad = pelletCount / 4;

	if (point == pelletQuad * pelletPoint * 3)
	{
		quadTime = 3;
		UpdateBGM();
	}
	else if (point == pelletQuad * pelletPoint * 2)
	{
		quadTime = 2;
		UpdateBGM();
	}
	else if (point == pelletQuad * pelletPoint * 1)
	{
		quadTime = 1;
		UpdateBGM();
	}

	if (point == maxPoint)
	{
		SetGameWin();
	}
}

void GameManager::UpdateMaxPoint()
{
	maxPoint = pelletCount * 10;
}

void GameManager::UpdateBGM()
{
	if (!IsPowerTime())
	{
		switch (quadTime)
		{
		case 1:
			m_soundManager->PlayBGM(m_siren1_bgm_buffer);
			break;
		case 2:
			m_soundManager->PlayBGM(m_siren2_bgm_buffer);
			break;
		case 3:
			m_soundManager->PlayBGM(m_siren3_bgm_buffer);
			break;
		default:
			m_soundManager->PlayBGM(m_siren1_bgm_buffer);
			break;
		}
	}
}
