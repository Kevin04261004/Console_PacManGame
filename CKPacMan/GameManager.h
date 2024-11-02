#pragma once

class GameManager
{
private:
	bool bIsGameWin;
	int point;
	bool bIsPowerTime;

	float powerTimer;
	float powerDuration;
public:
	GameManager()
	{
		point = 0;
		bIsGameWin = false;
		bIsPowerTime = false;
		powerDuration = 8.f;
	}
	inline bool IsGameWin() { return bIsGameWin; }
	inline void SetGameWin() { bIsGameWin = true; }
	inline bool IsPowerTime() { return bIsPowerTime; }
	void SetPowerTime();
	void Update(float deltaTime);
};

