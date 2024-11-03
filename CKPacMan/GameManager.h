#pragma once
#include "CKSoundManager.h"

enum class EGameType
{
	Ready,
	InGame,
	GameOver,
	GameWin,
};

class GameManager
{
private:
	bool bIsGameWin;
	int point;
	bool bIsPowerTime;

	float powerTimer;
	float powerDuration;
	
	CKSoundManager* m_soundManager;
	sf::SoundBuffer m_start_bgm_buffer;
	sf::SoundBuffer m_siren0_bgm_buffer;
	sf::SoundBuffer m_siren1_bgm_buffer;
	sf::SoundBuffer m_siren2_bgm_buffer;
	sf::SoundBuffer m_siren3_bgm_buffer;
	sf::SoundBuffer m_powerTime_bgm_buffer;
	sf::SoundBuffer m_died_bgm_buffer;
	sf::SoundBuffer m_victory_bgm_buffer;

	EGameType m_gameType;

	float gameTimer;

	int pelletCount;
	int pelletPoint;

	int quadTime;

	int maxPoint;

public:
	GameManager(CKSoundManager* soundManager) : m_soundManager(soundManager)
	{
		point = 0;
		pelletPoint = 10;
		bIsGameWin = false;
		bIsPowerTime = false;
		powerDuration = 8.f;
		pelletCount = 0;
		gameTimer = 4.f;
		if (!m_died_bgm_buffer.loadFromFile("Resource/Sounds/died.mp3"))
		{
			exit(1);
		}
		if (!m_start_bgm_buffer.loadFromFile("Resource/Sounds/start.wav"))
		{
			exit(1);
		}
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
		if (!m_victory_bgm_buffer.loadFromFile("Resource/Sounds/victory.mp3"))
		{
			exit(1);
		}

		m_gameType = EGameType::Ready;
		m_soundManager->PlayBGM(m_start_bgm_buffer, false);
	}
	inline bool IsGameWin() { return bIsGameWin; }
	inline void SetGameWin()
	{ 
		bIsGameWin = true;
		m_gameType = EGameType::GameWin;
		gameTimer = 4.0f;
		m_soundManager->PlayBGM(m_victory_bgm_buffer, false);
	}
	void GameOver();
	inline bool IsPowerTime() { return bIsPowerTime; }
	inline bool IsInGame() { return m_gameType == EGameType::InGame; }
	void SetPowerTime();
	inline void AddPelletPoint() { point += pelletPoint; UpdatePoint(); }
	void Update(float deltaTime);
	inline void SetPelletCount(int count) { pelletCount = count; UpdateMaxPoint(); }


private:
	void UpdateMaxPoint();
	void UpdatePoint();
	void UpdateBGM();
};

