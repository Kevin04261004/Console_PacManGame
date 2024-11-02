#pragma once
#include "BaseState.h"
#include "SFML/Audio.hpp"

class EatenState : public BaseState
{
private:
	sf::SoundBuffer m_eaten_sfx_buffer;

	float runTime;
	float runTimer;

public:
	EatenState(StateManager* InStateManager) : BaseState(InStateManager)
	{
		if (!m_eaten_sfx_buffer.loadFromFile("Resource/Sounds/eyes.wav"))
		{
			exit(1);
		}
		runTime = 0.1f;
		runTimer = 0.0f;
	}
	virtual void Enter() override;
	virtual void Excute(float deltaTime) override;
	virtual void Exit() override;
};

