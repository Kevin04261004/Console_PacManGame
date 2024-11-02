#pragma once
#include "CKSoundManager.h"

class GameManager
{
private:
	bool bIsGameWin;
	int point;
	bool bIsPowerTime;

	float powerTimer;
	float powerDuration;
	
	CKSoundManager* m_soundManager;
	sf::SoundBuffer m_siren0_bgm_buffer;
	sf::SoundBuffer m_siren1_bgm_buffer;
	sf::SoundBuffer m_siren2_bgm_buffer;
	sf::SoundBuffer m_siren3_bgm_buffer;
	sf::SoundBuffer m_powerTime_bgm_buffer;
public:
	GameManager(CKSoundManager* soundManager) : m_soundManager(soundManager)
	{
		point = 0;
		bIsGameWin = false;
		bIsPowerTime = false;
		powerDuration = 8.f;

		if (!m_siren0_bgm_buffer.loadFromFile("Resource/Sounds/siren0.wav"))
		{
			exit(1);
		}
		if (!m_siren1_bgm_buffer.loadFromFile("Resource/Sounds/siren1.wav"))
		{
			exit(1);
		}
		if (!m_siren2_bgm_buffer.loadFromFile("Resource/Sounds/siren2.wav"))
		{
			exit(1);
		}
		if (!m_siren3_bgm_buffer.loadFromFile("Resource/Sounds/siren3.wav"))
		{
			exit(1);
		}
		if (!m_powerTime_bgm_buffer.loadFromFile("Resource/Sounds/fright.wav"))
		{
			exit(1);
		}
		m_soundManager->PlayBGM(m_siren0_bgm_buffer);
	}
	inline bool IsGameWin() { return bIsGameWin; }
	inline void SetGameWin() { bIsGameWin = true; }
	inline void GameOver() { exit(1); }
	inline bool IsPowerTime() { return bIsPowerTime; }
	void SetPowerTime();
	void Update(float deltaTime);
};

